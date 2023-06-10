#include "framework.h"



namespace audio
{


   decoder::decoder()
   {

      m_bReleasePlaybackMemory = false;

      m_bSynch = false;

      m_bPersistent = false;

      m_bKick = true;

      m_bStop = false;

      m_bRealTime = false;

      m_iDecodeLength = -1;

      m_dwAsynchDecodeLength = (uptr)-1;

      m_bInitialized = false;

      m_iReadBlockSize = -1;

      m_bLoop = false;

      m_bWait = true;

   }


   decoder::~decoder()
   {

   }


   bool decoder::audio_initialize()
   {

      return ::audio::plugin::audio_initialize();

   }


   void decoder::multimedia_open(::file::file * pfile)
   {

      m_bStop = false;

      m_bInitialized = false;

      m_iAudioRead = 0;

      m_iFrameRead = 0;

      m_iDecodeLength = -1;

      m_dwAsynchDecodeLength = (uptr)-1;

      synchronous_lock lock(synchronization());

      m_iaLostPosition.erase_all();

      m_iaLostCount.erase_all();

      m_iRead = 0;

      m_iReadExpanded = 0;

      lock.unlock();

      m_pathOrigin = pfile->get_file_path();

      if (paudio->m_bLocalFileSystemSynch)
      {

         if (acmefile()->exists(m_pathOrigin))
         {

            m_bSynch = true;

         }

      }

      if (!impl_multimedia_open(pfile))
      {

         m_pathOrigin.empty();

         return false;

      }

      return ::success;

   }


   bool decoder::audio_finalize()
   {

      bool bOk1 = multimedia_close();

      bool bOk2 = ::audio::plugin::audio_finalize();

      return bOk1 & bOk2;

   }


   bool decoder::multimedia_close()
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_pathOrigin.empty();

      try
      {

         synchronous_lock slAudio(m_pmutexAudio);

         audio_file().set_size(0);

      }
      catch (...)
      {

      }

      frame_file().set_size(0);

      audio_stop();

      impl_multimedia_close();

      return true;

   }


   bool decoder::impl_multimedia_close()
   {

      return false;

   }


   void decoder::impl_multimedia_open(::file::file * pfile)
   {

      return ::success;

   }


   void decoder::audio_stop()
   {

      m_pthreadDecode->finish();

   }


   void decoder::audio_close()
   {

      synchronous_lock synchronouslock(this->synchronization());

      {

         synchronous_lock slAudio(audio_mutex());

         audio_file().set_size(0);

      }

      frame_file().set_size(0);

   }


   bool decoder::audio_is_loop()
   {

      return m_bLoop;

   }


   i64 decoder::audio_get_millis_length()
   {

      u32 uiRate = audio_get_samples_per_second();

      if (uiRate != 0)
      {

         return audio_get_sample_count() * 1000 / uiRate;

      }
      else
      {

         return 0;

      }

   }


   bool decoder::audio_set_real_time(bool bRealTime)
   {

      return m_bRealTime = bRealTime;

   }


   bool decoder::audio_set_seekable(bool bSet)
   {

      UNREFERENCED_PARAMETER(bSet);

      return true;

   }


   bool decoder::audio_is_seekable()
   {

      return true;

   }


   bool decoder::audio_is_real_time()
   {

      return m_bRealTime;

   }


   i32 decoder::audio_set_read_block_size(i32 iSize)
   {

      m_iReadBlockSize = iSize;

      return m_iReadBlockSize;

   }


   void decoder::audio_seek_end()
   {

   }


   bool decoder::audio_set_non_stop_on_eof(bool bSet)
   {

      UNREFERENCED_PARAMETER(bSet);

      return false;

   }


   void decoder::audio_move_next()
   {

   }


   bool decoder::audio_eof()
   {

      if (m_bStop)
      {

         return true;

      }

      if(m_bEof)
      {

         return true;

      }

      return false;

   }


   bool decoder::audio_decode_eof()
   {

      return ::audio::plugin::audio_decode_eof();

   }

   
   memsize decoder::read_frame(void * lpvoidBuffer, memsize uiBufferSize)
   {

      return 0;

   }


   memsize decoder::audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize)
   {

      synchronous_lock synchronouslock(audio_mutex());

      if (m_bReleasePlaybackMemory)
      {

         return audio_file().erase_begin(lpvoidBuffer, uiBufferSize);

      }
      else
      {

         return audio_file().read(lpvoidBuffer, uiBufferSize);

      }

   }


   bool decoder::begin_decode_thread()
   {

      if(!m_bReleasePlaybackMemory && (m_pthreadDecode || audio_file().get_size() > 0 || audio_decode_eof()))
      {

         return false;

      }

      if(!m_pthreadDecode)
      {

         __construct(m_pthreadDecode, fork([this]()
         {

            run_decode_thread();

         }));

      }

      return true;

   }


   void decoder::audio_decode_seek_begin()
   {

      ::audio::plugin::audio_seek_begin();

   }


   void decoder::audio_seek_begin()
   {

      if (m_bSynch || (!m_bReleasePlaybackMemory && (m_pthreadDecode || audio_file().get_size() > 0 || audio_decode_eof())))
      {

         audio_decode_seek_begin();

      }
      else
      {

         begin_decode_thread();

         if (paudio->m_timePreBuffer > 0_s)
         {

            //sleep(paudio->m_timePreBuffer);

         }

      }

   }


   i32 decoder::run_decode_thread()
   {

      ::parallelization::set_priority(::e_priority_highest);

      m_bRunning = true;

      memsize iDecodeLength = 0;

      bool bSleep;

      m_dwAsynchDecodeLength = numeric_info < memsize > ::get_allset_value();

      audio_decode_seek_begin();

      m_memory.set_size(1_mb);

      try
      {

         while(m_pthreadDecode && m_pthreadDecode->task_get_run())
         {

            bSleep = true;

            try
            {

               u64 uReadFrame = read_frame(m_memory.get_data(), m_memory.get_size());

               if (uReadFrame > 0)
               {

                  ASSERT((uReadFrame & 0x8000000000000000) == 0);

                  iDecodeLength += (memsize)(uReadFrame);

                  bSleep = false;

                  synchronous_lock synchronouslock(audio_mutex());

                  audio_file().get_memory()->append(m_memory.get_data(), uReadFrame);

               }
               else if (audio_decode_eof())
               {

                  break;

               }

            }
            catch(...)
            {

               break;

            }

            if(bSleep)
            {

               sleep(23_ms);

            }

         }

      }
      catch(...)
      {

      }

      m_dwAsynchDecodeLength = iDecodeLength;

      m_bRunning = false;

      return 0;

   }


   //::time decoder::audio_get_lost_time(::time dwExpandedMillis)
   //{

   //   synchronous_lock lock(synchronization());

   //   ::time position;

   //   position = (double) ((i64)dwExpandedMillis * audio_get_samples_per_second() * audio_get_channel_count() * audio_get_bits_per_sample()) / ((i64)8 * 1000);

   //   i64 den = (i64)audio_get_samples_per_second() * audio_get_channel_count()  * audio_get_bits_per_sample();

   //   if(den <= 0)
   //   {

   //      return 0;

   //   }

   //   i64 num = (i64)audio_get_lost_time(position) * 8 * 1000;

   //   return (double) (num / den);

   //}


   ::time decoder::audio_get_lost_time(::time positionExpanded)
   {

      synchronous_lock lock(synchronization());

      ::time position = positionExpanded;

      ::time iTotalLostCount = 0;

      for(i32 i = 0; i < m_iaLostPosition.get_size(); i++)
      {

         i64 iLostPosition = m_iaLostPosition[i];

         i64 iLostCount    = m_iaLostCount[i];

         if(position >(iLostPosition + iLostCount))
         {

            iTotalLostCount += iLostCount;

         }
         else if(position >= iLostPosition)
         {

            iTotalLostCount += minimum(position - iLostPosition,iLostCount);

            break;

         }
         else
         {

            break;

         }

      }

      return iTotalLostCount;

   }


   void decoder::audio_on_event(e_event eevent)
   {

      ::audio::plugin::audio_on_event(eevent);

   }


   bool decoder::audio_set_expected_parameters(u32 uiSamplesPerSec,u32 uiChannelCount,u32 uiBitCount,u32 uiEncodedAvgBitRate)
   {

      UNREFERENCED_PARAMETER(uiSamplesPerSec);
      UNREFERENCED_PARAMETER(uiChannelCount);
      UNREFERENCED_PARAMETER(uiBitCount);
      UNREFERENCED_PARAMETER(uiEncodedAvgBitRate);

      return false;

   }


   u32 decoder::audio_get_average_bit_rate()
   {

      return audio_get_raw_bit_rate(); // pre calculates a default optimistic worst case

   }


   u32 decoder::audio_get_raw_bit_rate()
   {

      return audio_get_samples_per_second() * audio_get_bits_per_sample();

   }


   u32 decoder::audio_get_raw_size(u32 uiEncodeSize)
   {

      return (u32)((u64)uiEncodeSize * (u64)audio_get_raw_bit_rate() / (u64)audio_get_average_bit_rate());

   }


   string decoder::multimedia_get_origin_path()
   {

      return ::multimedia::decoder::multimedia_get_origin_path();

   }


   void decoder::multimedia_set_origin_path(const ::string & strOriginPath)
   {

      ::multimedia::decoder::multimedia_set_origin_path(strOriginPath);

   }


} // namespace auddev



