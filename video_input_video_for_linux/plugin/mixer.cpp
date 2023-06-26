#include "framework.h"

//#include "aura/update.h"


namespace audio
{


   mixer::mixer()
   {

      m_bEof = false;
      m_bNonStopOnEof = false;
      m_iDecoder = -1;
      m_bExtra = false;

   }


   mixer::~mixer()
   {

   }


   bool mixer::audio_initialize()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!::audio::plugin::audio_initialize())
      {

         return false;

      }

      m_bStop = false;

      m_bEof = false;

      return true;

   }


   bool mixer::audio_finalize()
   {

      return true;

   }


   void mixer::audio_move_next()
   {


   }


   bool mixer::audio_eof()
   {

      if (m_bNonStopOnEof)
      {

         return false;

      }

      return m_bEof && audio_file().get_size() == 0;

   }


   u32 mixer::audio_get_samples_per_second() const
   {

      return 44100;

   }


   u32 mixer::audio_get_channel_count() const
   {

      return 2;

   }


   u32 mixer::audio_get_bits_per_sample() const
   {

      return 16;

   }


   memsize mixer::audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize)
   {

      bool bAllEOF = true;

      bool bFirst = true;

      ::u8 * pdata = (::u8 *) lpvoidBuffer;

      auto uBufferSize = uiBufferSize;

      for(int i = 0; i < m_plugina.get_size(); i++)
      {

         plugin * pplugin = m_plugina[i];

         ::time ::time;
         ::time.Now();
         bool bLog = false;

         if (!pplugin->audio_is_initialized())
         {

            bLog = true;
            init_child(pplugin);

         }

         if(pplugin->audio_eof())
         {

            pplugin->audio_restart();

         }

         if (bLog)
         {

            auto elapsed = ::time.elapsed();

            infomration("elapsedd " + as_string(elapsed.m_i));

         }

         if(pplugin != nullptr && !pplugin->audio_eof())
         {

            memsize uPos = 0;

            if (pplugin->m_iAudioRead <= 0)
            {

               u64 uSampleByteCount = audio_get_channel_count() * audio_get_bits_per_sample() / 8;

               u64 uStartOffset = pplugin->m_iStartOffset;

               if (!m_pwaveout || m_pwaveout->m_pwavebuffer->PCMOutGetInBufferSize() <= 0)
               {

                  uStartOffset = 0;

               }
               else
               {

                  uStartOffset = uStartOffset % m_pwaveout->m_pwavebuffer->PCMOutGetInBufferSize();

               }

               uPos = (memsize) ((uStartOffset / uSampleByteCount) * uSampleByteCount);

            }

            bAllEOF = false;

            ::u8 * pdst = &pdata[uPos];

            memsize uToRead = uBufferSize - uPos;

            if(bFirst)
            {

               if(uPos > 0)
               {

                  ::zero(pdata, uPos);

               }

               memsize uRead = pplugin->audio_read(pdst, uToRead);

               memsize uEnd = uRead + uPos;

               memsize uRemain = uBufferSize - uEnd;

               if(uRemain > 0)
               {

                  ::zero(&pdst[uEnd], uRemain);

               }

            }
            else
            {

               m_memory.set_size(uToRead);

               ::u8 * psrc = m_memory.get_data();

               memsize uRead = pplugin->audio_read(psrc, m_memory.get_size());

               int iSampleType = audio_get_bits_per_sample() / 8;

               if(iSampleType == 1)
               {

                  for(memsize u = 0; u < uRead; u++)
                  {

                     *pdst = ((*psrc ^ 0x80) + (*pdst ^ 0x80)) ^ 0x80;

                     pdst++;

                     psrc++;

                  }

               }
               else
               {

                  short * pshSrc = (short *) psrc;

                  short * pshDst = (short *) pdst;

                  for(memsize u = 0; u < uRead; u += 2)
                  {

                     *pshDst = *pshSrc + *pshDst;

                     pshDst++;

                     pshSrc++;

                  }

               }

            }

            bFirst = false;

         }

         if (pplugin && pplugin->audio_eof())
         {

            information("mixer plugin:EOF");

            if (pplugin->m_bLoop)
            {

               information("mixer plugin:seek_begin (Loop=1) (RESTART)");

            }
            else if (pplugin->m_ppluginNext != nullptr)
            {

               information("mixer plugin:set (NextPlugin) NEXTA");

               m_plugina.set_at(i, pplugin->m_ppluginNext);

            }
            else
            {

               information("mixer plugin:REMOVE");

               m_plugina.erase_at(i);

               i--;

            }

         }

      }

      if(bFirst)
      {

         ::zero(pdata, uBufferSize);

      }

      if(!m_bNonStopOnEof)
      {

         m_bEof = bAllEOF;

      }

      return uBufferSize;

   }


   void mixer::audio_stop()
   {

      m_bStop = true;

   }


   void mixer::audio_seek_begin()
   {

      m_bStop = false;

      m_bEof   = false;

   }


   void mixer::audio_seek_end()
   {

      ::audio::plugin::audio_seek_end();

   }


   i64 mixer::audio_get_sample_count()
   {

      return m_nSampleCount;

   }


   bool mixer::audio_set_non_stop_on_eof(bool bSet)
   {

      m_bNonStopOnEof = bSet;

      return m_bNonStopOnEof;

   }


   void mixer::add_plugin(plugin* pplugin)
   {

      if (is_null(pplugin))
      {

         throw ::exception(error_bad_argument);

      }

      if (pplugin == this)
      {

         throw ::exception(error_bad_argument);

      }

      synchronous_lock synchronouslock(this->synchronization());

      m_plugina.add(pplugin);

   }


   void mixer::replace_with_track(plugin* pplugin)
   {

      if (is_null(pplugin))
      {

         throw ::exception(error_bad_argument);

      }

      if (pplugin == this)
      {

         throw ::exception(error_bad_argument);

      }

      pplugin->audio_finalize();

      synchronous_lock synchronouslock(this->synchronization());

      m_plugina.erase_all();

      m_plugina.add(pplugin);

   }


} // namespace audio



