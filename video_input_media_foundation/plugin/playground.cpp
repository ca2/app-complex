#include "framework.h"

//#include "aura/update.h"


namespace audio
{


   playground::playground()
   {

      m_chCountDown = 128;

      m_bEof = false;

      m_bNonStopOnEof = false;

      m_bExtra = false;

   }


   playground::~playground()
   {

   }


   bool playground::audio_initialize()
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_bStop = false;

      m_iReadPointer = 0;

      m_bEof = false;

      for (auto& pplugin : m_plugina)
      {

         init_child(pplugin);

      }

      return true;

   }


   bool playground::audio_finalize()
   {

      return true;

   }


   void playground::audio_move_next()
   {

   }


   bool playground::audio_eof()
   {

      if(m_bNonStopOnEof)
      {

         return false;

      }

      return m_bStop;

   }


   u32 playground::audio_get_samples_per_second() const
   {

      return 44100;

   }


   u32 playground::audio_get_channel_count() const
   {

      return 2;

   }


   u32 playground::audio_get_bits_per_sample() const
   {

      return 16;

   }


   memsize playground::audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize)
   {

      if(m_bEof)
      {

         return 0 ;

      }

      if (m_plugina.is_empty())
      {

         return 0;

      }

      auto pplugin = m_plugina.first();

      if (pplugin->audio_is_initialized())
      {

         init_child(pplugin);

      }

      char sz[512];

      auto uRead = pplugin->audio_read(sz,sizeof(sz));

      {

         m_pfileFrame->write(sz, uRead);

      }

      if(m_plugina.get_count() > 1)
      {

         int i = 1;

         while(i < m_plugina.get_count() && (m_plugina[i]->m_bKick || m_plugina[i - 1]->audio_eof()))
         {

            i++;

         }

         if(i > 1)
         {


            while(i > 1)
            {

               m_plugina.erase_at(0);

               i--;

            }

            init_child(m_plugina[0]);

         }

      }
      else
      {
         if(pplugin->audio_eof())
         {

            if(pplugin->audio_is_loop())
            {

               init_child(pplugin);

            }
            else
            {

               m_bEof = true;

               audio_on_event(event_eof);

            }

         }

      }

      return uRead;

   }


   void playground::audio_stop()
   {

      m_bStop = true;

   }


   void playground::audio_seek_begin()
   {

      plugin::audio_seek_begin();

      m_iReadPointer    = 0;

   }


   void playground::audio_seek_end()
   {

      synchronous_lock synchronouslock(this->synchronization());

      ::audio::plugin::audio_seek_end();

      m_bStop           = false;
      m_bEof            = false;
      m_iReadPointer    = 0;

   }


   i64 playground::audio_get_sample_count()
   {

      return m_nSampleCount;

   }


   bool playground::audio_set_non_stop_on_eof(bool bSet)
   {

      m_bNonStopOnEof = bSet;

      return m_bNonStopOnEof;

   }


} // namespace audio



