#include "framework.h"



namespace audio
{


   plugin::plugin()
   {


      defer_create_synchronization();

      m_bInitialized = false;

      m_pmutexAudio = __new(class mutex());

      m_bReleasePlaybackMemory = true;

      m_bEof = false;

      m_bDecodeEof = false;

      m_iStartOffset = 0;

      m_iNoBlockSilence = 0;

      m_pfileAudio = create_memory_file();

      m_pfileFrame = create_memory_file();

      m_bSynch = true;

      m_iRestartPosition = 0;

      m_ppluginNext = nullptr;

      m_bPersistent = false;

      m_bKick = true;

      m_bStop = false;

      m_bRealTime = false;

      m_iDecodeLength = -1;

      m_bInitialized = false;

      m_iReadBlockSize = -1;

      m_iAudioRead = 0;

      m_iFrameRead = 0;

      m_bLoop = false;

      m_bWait = true;

   }


   plugin::~plugin()
   {

   }


   void plugin::init_child(plugin * pplugin)
   {

      if (::is_null(pplugin))
      {

         return;

      }

      if (pplugin == this)
      {

         return;

      }

      pplugin->__refer(pplugin->m_pwaveout, m_pwaveout);

      pplugin->__refer(pplugin->m_ppluginParent, this);

      ::pointer<sampler>psampler = pplugin;

      if(psampler.is_set())
      {

         psampler->m_fSamplePerSecond = (float) audio_get_samples_per_second();

      }

      ::pointer<resampler>presampler = pplugin;

      if(presampler.is_set())
      {

         presampler->m_dwTargetSamplesPerSecond = audio_get_samples_per_second();
         presampler->m_iTargetBitsPerSample = audio_get_bits_per_sample();
         presampler->m_iTargetChannelCount = audio_get_channel_count();

      }

      pplugin->audio_initialize();

      if (pplugin->m_iRestartPosition == 0)
      {

         pplugin->audio_seek_begin();

      }

   }


   bool plugin::audio_finalize()
   {

      if (!audio_is_initialized())
      {

         return true;

      }

      audio_stop();

      synchronous_lock synchronouslock(this->synchronization());

      try
      {

         synchronous_lock slAudio(synchronization());

         if(m_bReleasePlaybackMemory)
         {

            audio_file().set_size(0);

         }

      }
      catch (...)
      {

      }

      frame_file().set_size(0);

      if (m_pprebuffer != nullptr)
      {

         m_pprebuffer->defer_unset_plugin(this);

      }

      return true;

   }


   void plugin::audio_stop()
   {

   }


   void plugin::audio_close()
   {

   }


   bool plugin::audio_is_loop()
   {

      return m_bLoop;

   }


   i64 plugin::audio_get_millis_length()
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


   i64 plugin::audio_get_position_read()
   {

      auto blockAlign = audio_get_bits_per_sample() * audio_get_channel_count() / 8;

      return m_iRead / blockAlign;

   }


   i64 plugin::audio_get_millis_read()
   {

      u32 uiRate = audio_get_samples_per_second();

      if (uiRate != 0)
      {

         return audio_get_position_read() * 1000 / uiRate;

      }
      else
      {

         return 0;

      }

   }


   bool plugin::audio_set_real_time(bool bRealTime)
   {

      return m_bRealTime = bRealTime;

   }


   bool plugin::audio_set_seekable(bool bSet)
   {

      UNREFERENCED_PARAMETER(bSet);

      return true;

   }


   bool plugin::audio_is_seekable()
   {

      return true;

   }


   bool plugin::audio_is_real_time()
   {

      return m_bRealTime;

   }


   i32 plugin::audio_set_read_block_size(i32 iSize)
   {

      m_iReadBlockSize = iSize;

      return m_iReadBlockSize;

   }


   void plugin::audio_seek_end()
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_bStop = false;

      m_bEof = false;

      {

         synchronous_lock slAudio(synchronization());

         if(m_bReleasePlaybackMemory)
         {

            audio_file().set_size(0);

         }

      }

      frame_file().set_size(0);

   }


   bool plugin::audio_set_non_stop_on_eof(bool bSet)
   {

      UNREFERENCED_PARAMETER(bSet);

      return false;

   }


   void plugin::audio_move_next()
   {

   }


   bool plugin::audio_decode_eof()
   {

      return m_bDecodeEof;

   }


   bool plugin::audio_eof()
   {

      bool bEof;

      if (m_iDecodeLength == -1)
      {

         bEof = false;

      }
      else
      {

         bEof = ::comparison::ge(m_iAudioRead, m_iDecodeLength);

      }

      if (bEof)
      {

         return true;

      }
      else
      {

         return false;

      }

   }

   
   memsize plugin::audio_read(void * lpvoidBuffer, memsize uiBufferSize)
   {

      ::u8* p = (::u8 *) lpvoidBuffer;

      memsize iTotalRead = 0;

      while (uiBufferSize > 0)
      {

         memsize iRead = audio_read_raw(p, uiBufferSize);

         if (iRead <= 0)
         {

            if (audio_decode_eof())
            {

               m_bEof = true;

               audio_on_event(event_eof);

            }

            break;

         }

         uiBufferSize -= iRead;

         p += iRead;

         iTotalRead += iRead;

      }

      m_iAudioRead += iTotalRead;

      return iTotalRead;

   }


   memsize plugin::audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize)
   {

      // Implementators
      // Append extra frame data to m_pfileFrame, or;
      // Set its memory buffer to the frame data.
      // (m_pfileFrame is reset before and after each multimedia_read_frame call).

      return 0;

   }


   //memsize plugin::call_multimedia_read_frame()
   //{

   //   if(m_bEof)
   //   {

   //      return 0;

   //   }

   //   synchronous_lock synchronouslock(this->synchronization());

   //   frame_file().set_size(0);

   //   multimedia_read_frame();

   //   auto size = frame_file().get_size();

   //   if(size > 0)
   //   {

   //      m_iFrameRead += size;

   //      {

   //         synchronous_lock slAudio(audio_mutex());

   //         audio_file().get_memory()->append(frame_file().get_data(), size);

   //      }

   //      frame_file().set_size(0);

   //   }

   //   return size;

   //}


   //memsize plugin::audio_read2(LPVOID lpvoidBuffer,memsize iBufferSize)
   //{

   //   if (m_bStop)
   //   {

   //      return 0;

   //   }

   //   if (audio_eof())
   //   {

   //      return 0;

   //   }

   //   if (iBufferSize <= 0)
   //   {

   //      return 0;

   //   }

   //   memsize sizeRead = 0;

   //   if (m_bSynch)
   //   {

   //      sizeRead = audio_read_blocking(lpvoidBuffer, iBufferSize);

   //   }
   //   else
   //   {

   //      sizeRead = audio_read_no_block(lpvoidBuffer, iBufferSize);

   //   }

   //   if (audio_decode_eof() && sizeRead < iBufferSize)
   //   {

   //      m_bEof = true;

   //      audio_on_event(event_eof);

   //   }

   //   return sizeRead;

   //}


   //memsize plugin::audio_read2(LPVOID lpvoidBuffer, memsize iBufferSize)
   //{
   //   
   //   return 0;

   //   //memsize iRemain = iBufferSize;

   //   //memsize iTotalRead = 0;

   //   //memsize iSize;

   //   //LPBYTE lpb = (LPBYTE)lpvoidBuffer;

   //   //while (iRemain > 0)
   //   //{

   //   //   while (iRemain > 0)
   //   //   {

   //   //      iSize = minimum(iRemain, audio_file().get_size() - audio_file().get_position());

   //   //      if (iSize <= 0)
   //   //      {

   //   //         break;

   //   //      }

   //   //      {

   //   //         synchronous_lock slAudio(audio_mutex());

   //   //         if (m_bReleasePlaybackMemory)
   //   //         {

   //   //            iSize = audio_file().erase_begin(lpb, iSize);

   //   //         }
   //   //         else
   //   //         {

   //   //            iSize = audio_file().read(lpb, iSize);

   //   //         }

   //   //      }

   //   //      if (iSize <= 0)
   //   //      {

   //   //         break;

   //   //      }

   //   //      iRemain -= iSize;

   //   //      iTotalRead += iSize;

   //   //      lpb += iSize;

   //   //   }

   //   //   if (iRemain <= 0)
   //   //   {

   //   //      break;

   //   //   }

   //   //   if (m_bStop)
   //   //   {

   //   //      break;

   //   //   }

   //   //   if (audio_decode_eof())
   //   //   {

   //   //      break;

   //   //   }

   //   //   if (call_multimedia_read_frame() == 0)
   //   //   {

   //   //      break;

   //   //   }

   //   //}

   //   //if (iTotalRead > 0)
   //   //{

   //   //   //m_iAudioRead += iTotalRead;

   //   //}
   //   //else if (m_bDecodeEof)
   //   //{

   //   //   m_bEof = true;

   //   //}

   //   //return iTotalRead;

   //}

//memsize plugin::audio_fill(LPVOID lpvoidBuffer, memsize iBufferSize)
//{
//
//   audio_read2(lpvoidBuffer, uiBuffer_)
//
//}

   //memsize plugin::audio_read_blocking(LPVOID lpvoidBuffer, memsize iBufferSize)
   //{

   //   memsize iRemain = iBufferSize;

   //   memsize iTotalRead = 0;

   //   memsize iSize;

   //   LPBYTE lpb = (LPBYTE)lpvoidBuffer;

   //   while (iRemain > 0)
   //   {

   //      while (iRemain > 0)
   //      {

   //         iSize = minimum(iRemain, audio_file().get_size() - audio_file().get_position());

   //         if (iSize <= 0)
   //         {

   //            break;

   //         }

   //         {

   //            synchronous_lock slAudio(audio_mutex());

   //            if(m_bReleasePlaybackMemory)
   //            {

   //               iSize = audio_file().erase_begin(lpb, iSize);

   //            }
   //            else
   //            {

   //               iSize = audio_file().read(lpb, iSize);

   //            }

   //         }

   //         if (iSize <= 0)
   //         {

   //            break;

   //         }

   //         iRemain -= iSize;

   //         iTotalRead += iSize;

   //         lpb += iSize;

   //      }

   //      if (iRemain <= 0)
   //      {

   //         break;

   //      }

   //      if (m_bStop)
   //      {

   //         break;

   //      }

   //      if (audio_decode_eof())
   //      {

   //         break;

   //      }

   //      if (call_multimedia_read_frame() == 0)
   //      {

   //         break;

   //      }

   //   }

   //   if (iTotalRead > 0)
   //   {

   //      //m_iAudioRead += iTotalRead;

   //   }
   //   else if (m_bDecodeEof)
   //   {

   //      m_bEof = true;

   //   }

   //   return iTotalRead;

   //}


   //memsize plugin::audio_read_no_block(LPVOID lpvoidBuffer, memsize iBufferSize)
   //{

   //   memsize iRead = 0;

   //   {

   //      synchronous_lock slAudio(audio_mutex());

   //      auto moreDataSize = audio_file().get_size() - audio_file().get_position();

   //      auto startThreshold = default_frame_size() * 64;

   //      if(audio_decode_eof() || moreDataSize >= startThreshold)
   //      {

   //         iRead = minimum(iBufferSize, moreDataSize);

   //         if(m_bReleasePlaybackMemory)
   //         {

   //            iRead = audio_file().erase_begin(lpvoidBuffer, iRead);

   //         }
   //         else
   //         {

   //            iRead = audio_file().read(lpvoidBuffer, iRead);

   //         }

   //      }

   //   }

   //   if (iRead > 0)
   //   {

   //      //m_iAudioRead += iRead;

   //   }

   //   if (!audio_decode_eof() && iRead < iBufferSize)
   //   {

   //      auto iSilence = iBufferSize - iRead;

   //      if (audio_get_bits_per_sample() == 8)
   //      {

   //         memset(lpvoidBuffer, 127, iSilence);

   //      }
   //      else
   //      {

   //         memset(lpvoidBuffer, 0, iSilence);

   //      }

   //      m_iNoBlockSilence += iSilence;

   //      iRead = iBufferSize;

   //   }

   //   return iRead;

   //}


   memsize plugin::default_frame_size()
   {

      return m_pwaveout->m_pwavebuffer->PCMOutGetInBufferSize();

   }


   memory_base & plugin::default_frame()
   {

      auto memsizeFrameDefault = default_frame_size();

      m_pfileFrame->set_size(memsizeFrameDefault);

      return *m_pfileFrame->get_memory();

   }


   bool plugin::audio_initialize()
   {

      m_bStop = false;

      m_bInitialized = false;

      m_iAudioRead = 0;

      m_iFrameRead = 0;

      m_iDecodeLength = -1;

      synchronous_lock lock(synchronization());

      m_iaLostPosition.erase_all();
      m_iaLostCount.erase_all();
      m_iRead = 0;
      m_iReadExpanded = 0;
      lock.unlock();

      m_bEof = false;

      m_bInitialized = true;

      return true;

   }


   void plugin::audio_seek_begin()
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_bWait = true;
      m_bStop = false;
      m_bKick = true;
      m_iAudioRead = 0;
      m_iFrameRead = 0;
      m_iNoBlockSilence = 0;
      m_bEof = false;

      if (m_bReleasePlaybackMemory)
      {

         m_bDecodeEof = false;

      }

      {

         synchronous_lock slAudio(audio_mutex());

         if(m_bReleasePlaybackMemory)
         {

            audio_file().set_size(0);

         }
         else
         {

            audio_file().seek_begin();

         }

      }

      frame_file().set_size(0);

   }


   void plugin::audio_restart()
   {

      if(m_iRestartPosition == 0)
      {

         audio_seek_begin();

      }

   }


   //::time plugin::audio_get_lost_time(::time dwExpandedMillis)
   //{

   //   synchronous_lock lock(synchronization());

   //   ::time position;

   //   position = (double) ((i64)dwExpandedMillis * audio_get_samples_per_second() * audio_get_channel_count()  * audio_get_bits_per_sample()) / ((i64)8 * 1000);

   //   i64 den = (i64)audio_get_samples_per_second() * audio_get_channel_count()  * audio_get_bits_per_sample();

   //   if (den <= 0)
   //   {

   //      return 0;

   //   }

   //   i64 num = (i64)audio_get_lost_time(position) * 8 * 1000;

   //   return (double) (num / den);

   //}


   ::time plugin::audio_get_lost_time(::time positionExpanded)
   {

      synchronous_lock lock(synchronization());

      ::time position = positionExpanded;

      ::time iTotalLostCount = 0;

      for (i32 i = 0; i < m_iaLostPosition.get_size(); i++)
      {
         i64 iLostPosition = m_iaLostPosition[i];
         i64 iLostCount = m_iaLostCount[i];
         if (position > (iLostPosition + iLostCount))
         {
            iTotalLostCount += iLostCount;
         }
         else if (position >= iLostPosition)
         {
            iTotalLostCount += minimum(position - iLostPosition, iLostCount);
            break;
         }
         else
         {
            break;
         }
      }

      return iTotalLostCount;

   }


   void plugin::audio_on_event(::audio::e_event eevent)
   {

      string strEvent;

      strEvent.format("audio_plugin_event:%d", (::i32) eevent);

      run_property(strEvent);

      if (eevent == event_eof)
      {

         if (m_ppluginaFree)
         {

            synchronous_lock synchronouslock(m_ppluginaFree->synchronization());

            m_ppluginaFree->add(this);

         }

      }

   }


   bool plugin::audio_set_expected_parameters(u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitCount, u32 uiEncodedAvgBitRate)
   {

      UNREFERENCED_PARAMETER(uiSamplesPerSec);
      UNREFERENCED_PARAMETER(uiChannelCount);
      UNREFERENCED_PARAMETER(uiBitCount);
      UNREFERENCED_PARAMETER(uiEncodedAvgBitRate);

      return false;

   }

   u32 plugin::audio_get_average_bit_rate()
   {
      return audio_get_raw_bit_rate(); // pre calculates a default optimistic worst case
   }

   u32 plugin::audio_get_raw_bit_rate()
   {
      return audio_get_samples_per_second() * audio_get_bits_per_sample();
   }

   u32 plugin::audio_get_raw_size(u32 uiEncodeSize)
   {
      return (u32)((u64)uiEncodeSize * (u64)audio_get_raw_bit_rate() / (u64)audio_get_average_bit_rate());
   }


//   ::memory_file & plugin::audio_memory_file()
//   {
//
//      return m_memfileDecoder;
//
//   }

   u32           plugin::audio_get_samples_per_second() const
   {

      return 44100;

   }


   u32           plugin::audio_get_channel_count() const
   {

      return 2;

   }


   u32           plugin::audio_get_bits_per_sample() const
   {

      return 16;

   }

   i64 plugin::audio_get_sample_count()
   {

      return -1;

   }


   //::memory_file & plugin::audio_memory_file()
   //{

   //   return m_memfileDecoder;

   //}

   string plugin::multimedia_get_origin_path()
   {

      return __type_name(this) + ":" + ::hex::upper_from((uptr)this);

   }

   void plugin::multimedia_set_origin_path(const ::string & strOriginPath)
   {

      //throw ::exception(error_not_supported);

   }


   bool plugin::audio_matches(const ::audio::plugin * ppluginOther) const
   {

      if (::is_null(ppluginOther))
      {

         return false;

      }

      if (ppluginOther == this)
      {

         return false;

      }

      return
      audio_get_samples_per_second() == ppluginOther->audio_get_samples_per_second()
      && audio_get_channel_count() == ppluginOther->audio_get_channel_count()
      && audio_get_bits_per_sample() == ppluginOther->audio_get_bits_per_sample();
   }


   LPWAVEOUT plugin::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   {

      return nullptr;

   }


} // namespace audio



