#include "framework.h"



namespace wave
{


   pre_buffer::pre_buffer()
   {

      m_pwaveout           = nullptr;
      m_time           = 0;
      m_iBytes             = 0;

      defer_create_synchronization();

   }


   pre_buffer::~pre_buffer()
   {

   }


   bool pre_buffer::open(::count iChannelCount, ::count iBufferCount, ::count iSampleCount)
   {

      m_iChannelCount = iChannelCount;

      m_iBufferCount = iBufferCount;

      m_iSampleCount = iSampleCount;

      //m_buffera.set_size(m_iBufferCount);

      //for (auto & buffer : m_buffera)
      //{

      //   buffer.m_memory.set_size(get_buffer_size());

      //}

      return true;

   }


   void pre_buffer::defer_unset_plugin(::audio::plugin * pinterface)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pplugin != pinterface)
      {

         return;

      }

      ASSERT(pinterface->m_pprebuffer == this);

      set_plugin(nullptr);

   }


   void pre_buffer::set_plugin(::audio::plugin * pinterface)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pplugin.is_set())
      {

         try
         {

            m_pplugin->audio_stop();

         }
         catch (...)
         {

         }

         if (!m_pplugin->m_bPersistent)
         {

            if (m_pplugin.is_set())
            {

               ::pointer<::audio::plugin>pplugin = m_pplugin;

               m_pplugin.release();

               pplugin->audio_finalize();

            }

         }

      }

      if(pinterface != nullptr)
      {

         if (pinterface->m_pprebuffer == this)
         {

            ASSERT(m_pplugin == pinterface);

            return;

         }

         if (pinterface->m_pprebuffer != nullptr)
         {

            pinterface->m_pprebuffer->defer_unset_plugin(pinterface);

         }

         pinterface->__construct(pinterface->m_pprebuffer, this);

      }

      m_pplugin = pinterface;

      if (pinterface != nullptr)
      {

         m_bPluginEverSet = true;

      }

   }


   void * pre_buffer::get_buffer_data(index iId)
   {

      return m_buffera[iId].m_memory.get_data();

   }


   ::memsize pre_buffer::get_frame_size()
   {

      return sizeof(short) * m_iChannelCount;

   }


   ::memsize pre_buffer::get_buffer_size()
   {

      return m_iSampleCount * get_frame_size();

   }


   bool pre_buffer::is_eof()
   {

      if (m_pplugin == nullptr)
      {

         return true;

      }

      if (m_pplugin->audio_eof())
      {

         return true;

      }

      if (m_pstreameffectOut.is_set() && m_pstreameffectOut->IsEndOfEffect())
      {

         return true;

      }

      return false;

   }


   bool pre_buffer::read_buffer(void * pbuffer, memsize s, index iId)
   {

      synchronous_lock synchronouslock(this->synchronization());

      ::count cLeft = s;

      while (cLeft > 0)
      {

         auto readNow = m_pplugin->audio_read(pbuffer, cLeft);

         if (readNow <= 0)
         {

            break;

         }

         cLeft -= readNow;

      }

      if (cLeft > 0)
      {

         memset(&((::u8*)pbuffer)[s - cLeft], 0, cLeft);

      }

      return true;

   }


   bool pre_buffer::fill_buffer(index iId)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (iId < 0 || iId >= m_iBufferCount)
      {

         throw invalid_index_exception("pre_buffer::fill_buffer");

      }

      buffer & buffer = m_buffera[iId];

      if (buffer.m_bFilled)
      {

         //throw ::exception("invalid state");

         information("pre_buffer::fill_buffer Buffer ALREADY Filled : invalid state");

         return false;

      }

      synchronouslock.unlock();

      memsize iBytesRecorded = 0;

      if(m_pplugin != nullptr)
      {

         if (m_pplugin->m_bSynch)
         {

            iBytesRecorded = fill_synch(&buffer);

         }
         else
         {

            iBytesRecorded = fill_asynch(&buffer);

         }

         if (iBytesRecorded == 0 && m_pplugin->m_bEof)
         {

            return false;

         }

      }

      i64 iRemain = get_buffer_size() - iBytesRecorded;

      if(iRemain > 0)
      {

         ::u8 * pdata = (::u8 *) buffer.m_memory.get_data();

         int iFormat = 1; // short

         if (m_pplugin != nullptr && m_pplugin->audio_get_bits_per_sample() == 8)
         {

            memory_set(&pdata[iBytesRecorded], 0x80, (size_t)iRemain);

         }
         else if (iFormat == 1)
         {

            ::zero(&pdata[iBytesRecorded], (size_t) iRemain);

         }
         else
         {

            ::zero(&pdata[iBytesRecorded], (size_t) iRemain);

         }

         m_iLostBytes += memsize(iRemain);

         m_pwaveout->m_iLostBytes += (u32) (iRemain);

         iBytesRecorded += iRemain;

      }

      if(!pre_output(&buffer))
      {

         return false;

      }

      synchronouslock.lock();

      if ((m_pplugin == nullptr && m_bPluginEverSet) || (::comparison::lt(iBytesRecorded, get_buffer_size()) && m_pplugin->audio_eof()))
      {

         return false;

      }

      buffer.m_bFilled = true;

      m_evWritten.SetEvent();

      return true;

   }


   ::count pre_buffer::fill_asynch(buffer * pbuffer)
   {

      if (pbuffer == nullptr)
      {

         return 0;

      }

      auto ppos = pbuffer->m_memory.get_data();

      if (ppos == nullptr)
      {

         return 0;

      }

      //auto pend = ppos + pbuffer->m_memory.get_size();

      synchronous_lock synchronouslock(this->synchronization());

      memsize iFrameSize = get_frame_size();

      memsize iRemain = pbuffer->m_memory.get_size();

      auto iRead = m_pplugin->audio_read(ppos, (iRemain / iFrameSize) * iFrameSize);

      if (iRead < 8820)
      {
         infomration("1");

      }
      ppos += iRead;

      iRemain -= iRead;

      m_iBytes += iRead;

      m_time = (double) (m_iBytes / iFrameSize);

      bool bStarving = ::comparison::ge(iRemain, iFrameSize) && iRemain > 0;

      if (bStarving)
      {

         if (is_eof())
         {

            try
            {

               m_pplugin->m_bStop = true;

            }
            catch (...)
            {

            }

            return 0;

         }

         m_iLostBytes = iRemain;

         m_pwaveout->m_iLostBytes = iRemain;

         // Otherwise write silence

         synchronous_lock synchronouslock(this->synchronization());

         ::u8 * lpb = ppos;

         int iFormat = 1; // short

         if (m_pplugin->audio_get_bits_per_sample() == 8)
         {

            memory_set(lpb, 0x80, (size_t)iRemain);

         }
         else if (iFormat == 1)
         {

            memory_set(lpb, 0, (size_t)iRemain);

         }
         else
         {

            memory_set(lpb, 0, (size_t)iRemain);

         }

      }

      return iRead;

   }


   ::count pre_buffer::fill_synch(buffer * pbuffer)
   {

      memsize iBytesRecorded = 0;

      iBytesRecorded += m_pplugin->audio_read(&((char*)pbuffer->m_memory.get_data())[iBytesRecorded], pbuffer->m_memory.get_size() - iBytesRecorded);

//         if(iBytesRecorded < pbuffer->m_memory.get_size())
//         {
//
//            infomration("end of data or starving or ?");
//
//         }

      memsize iFrameSize = get_frame_size();

      m_iBytes += iBytesRecorded;

      m_time = m_timeStart + m_iBytes / iFrameSize;

      if (m_pplugin->audio_eof())
      {

         try
         {

            m_pplugin->m_bEof = true;

         }
         catch (...)
         {

         }

         try
         {

            m_pplugin->m_bStop = true;

         }
         catch (...)
         {

         }

      }

      return iBytesRecorded;

   }


   bool pre_buffer::pre_output(buffer * pbuffer)
   {

      if(m_pstreameffectOut.is_set())
      {

         m_pstreameffectOut->CallProcess16bits((short *) pbuffer->m_memory.get_data(), m_iSampleCount);

         if(m_pstreameffectOut->IsEndOfEffect())
         {

            //if(!eameffectOut->m_bEnd)
            //{

               return false;

            //}

            //if(m_pstreameffectOut->m_bDeleteOnEnd)
            //{

            //   m_pstreameffectOut.release();

            //}

         }

      }

      if (m_pwaveout->m_dVolume >= 0.0 && m_pwaveout->m_dVolume < 1.0)
      {

         i16 * pshStream = (i16 *) pbuffer->m_memory.get_data();

         auto iCount = pbuffer->m_memory.get_size() / sizeof(short);

         {

            i16 * psh = pshStream;

            for (int i = 0; ::comparison::lt(i, iCount); i++)
            {

               *psh = (i16)(*psh * m_pwaveout->m_dVolume);

               if (*psh != 0)
               {

                  *psh = *psh + 1 - 1;

               }

               psh++;

            }

         }

      }

      return true;

   }


   ::count pre_buffer::get_buffer_count()
   {

      return m_iBufferCount;

   }


   //void pre_buffer::start(const ::time & position)
   //{

   //   {

   //      synchronous_lock synchronouslock(this->synchronization());

   //      m_bPluginEverSet  = m_pplugin != nullptr;

   //      m_bPlayPreBuffer  = true;

   //      m_positionStart   = floor(position);

   //      m_time        = floor(position);

   //      m_iBytes          = 0;

   //      m_iLostBytes      = 0;

   //      m_evRead.ResetEvent();

   //      m_evWritten.ResetEvent();

   //   }

   //   memsize iRead;

   //   if (m_pplugin != nullptr && m_positionStart* get_frame_size() > m_pplugin->m_dwDecodePosition)
   //   {

   //      memory mem;

   //      mem.set_size(1024 * 128);

   //      memsize iRemain = (i32) (m_positionStart * get_frame_size() - m_pplugin->m_dwDecodePosition);

   //      while (iRemain > 0 && m_bPlayPreBuffer && ::task_get_run() && !m_pplugin->audio_eof())
   //      {

   //         iRead = m_pplugin->audio_read(mem.get_data(), minimum(iRemain, mem.get_size()));

   //         iRemain -= iRead;

   //      }

   //   }

   //   int iId = 0;

   //   for (auto & buffer : m_buffera)
   //   {

   //      buffer.m_bFilled = false;

   //      fill_buffer(iId);

   //      iId++;

   //   }

   //   m_pthreadFillBuffer = fork([&]()
   //   {

   //      ::parallelization::set_priority(::e_priority_above_normal);

   //      int iId = 0;

   //      synchronous_lock synchronouslock(this->synchronization());

   //      while (m_bPlayPreBuffer && ::task_get_run())
   //      {

   //         if (m_buffera[iId].m_bFilled)
   //         {

   //            m_evRead.ResetEvent();

   //            synchronouslock.unlock();

   //            m_evRead.wait(one_second());

   //            synchronouslock.lock();

   //            continue;

   //         }

   //         synchronouslock.unlock();

   //         if(!fill_buffer(iId))
   //         {

   //            break;

   //         }

   //         synchronouslock.lock();

   //         iId++;

   //         if (iId >= m_iBufferCount)
   //         {

   //            iId = 0;

   //         }

   //      }

   //      m_bPlayPreBuffer = false;

   //   });

   //}


   //void pre_buffer::stop()
   //{

   //   m_bPlayPreBuffer = false;

   //   ///children_post_quit();

   //   m_evRead.ResetEvent();

   //   m_evWritten.ResetEvent();

   //   //children_post_quit_and_wait(seconds(5));

   //}


   ::time pre_buffer::get_millis_length()
   {

      if (m_pplugin == nullptr)
      {

         return -0.0;

      }

      return (double) m_pplugin->audio_get_millis_length();

   }


   void pre_buffer::set_finish_composites(::object * pcontextobjectFinish)
   {

      bool bPending = false;

      auto estatus = ::object::set_finish_composites(pcontextobjectFinish);

      if (estatus == error_pending)
      {

         bPending = true;

      }

      m_evRead.SetEvent();

      m_evWritten.SetEvent();

      if (bPending)
      {

         return error_pending;

      }

      return ::success;

   }


} // namespace wave



