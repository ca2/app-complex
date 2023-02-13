#include "framework.h"



namespace audio
{


   sampler::sampler()
   {

      m_dwSample = 0;
      m_bEof = false;
      m_iChannelCount = 2;
      m_iBitsPerSample = 16;
      m_bStop = false;
      m_bMute = false;

   }


   sampler::~sampler()
   {

   }


   void sampler::initialize_sampler(plugin * pplugin)
   {

      auto estatus = ::audio::plugin::initialize(pplugin);

      if (!estatus)
      {

         return estatus;

      }

      m_pplugin = pplugin;

      return estatus;

   }


   void sampler::reset(float fSamplesPerSecond)
   {
      m_dwSample = 0;
      m_iIndex = 0;
      m_fSamplePerSecond =fSamplesPerSecond;
      m_bEof = false;
   }



   void sampler::audio_seek_begin()
   {
      plugin::audio_seek_begin();
      reset(m_fSamplePerSecond);

   }

   bool sampler::audio_eof()
   {

      return m_bEof;

   }


   memsize sampler::audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize)
   {

      m_fSamplePerSecond = (float) audio_get_samples_per_second();

      short * psh = (short *)lpvoidBuffer;

      int iChannelCount = audio_get_channel_count();

      auto iCount = uiBufferSize;

      int iStep = sizeof(short) * iChannelCount;

      short sh;

      memsize iRead = 0;

      for(; iRead < iCount; iRead+=iStep)
      {

         int iSample = 0;

         if(sample(&sh))
         {

            m_dwSample++;

         }
         else
         {

            m_bDecodeEof = true;

            break;

         }

         iSample += sh;

         sh = minimum(SHRT_MAX,maximum(SHRT_MIN,iSample));

         for (index i = 0; i < iChannelCount; i++)
         {
            
            *psh++ = sh;

         }

      }

      return iRead;

   }


   //memsize sampler::multimedia_read_frame()
   //{

   //   if(m_bEof)
   //      return 0;

   //   float fSamplePerSecond = (float) audio_get_samples_per_second();


   //   m_fSamplePerSecond = (float)audio_get_samples_per_second();

   //   m_fSamplePerSecond = (float)audio_get_samples_per_second();

   //   short sh;

   //   while(audio_memory_file().get_length() < 480 * 4 * 2)
   //   {

   //      int iSample = 0;

   //      if(sample(&sh))
   //      {
   //         m_dwSample++;
   //      }
   //      else
   //      {
   //         m_bEof = true;
   //         break;
   //      }

   //      iSample += sh;

   //      sh = minimum(SHRT_MAX,maximum(SHRT_MIN,iSample));

   //      {

   //         synchronous_lock slMemoryFile(&audio_memory_file());

   //         audio_memory_file().write(&sh, sizeof(sh));
   //
   //         audio_memory_file().write(&sh, sizeof(sh));

   //      }


   //   }
   //   //sleep(1_ms);

   //}

   i64   sampler::audio_get_sample_count()
   {
      return 0;
   }

   u32 sampler::audio_get_samples_per_second() const
   {

      return (u32)m_fSamplePerSecond;

   }


   u32 sampler::audio_get_channel_count() const
   {

      return m_iChannelCount;

   }


   u32 sampler::audio_get_bits_per_sample() const
   {

      return m_iBitsPerSample;

   }


} // namespace audio



