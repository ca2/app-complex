#include "framework.h"

//#include "aura/update.h"


namespace audio
{


   track::track()
   {

      m_chCountDown = 128;
      m_bEof = false;
      m_bNonStopOnEof = false;
      m_iDecoder = -1;
      m_bExtra = false;

   }


   track::~track()
   {

   }


   bool track::audio_initialize()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!::audio::plugin::audio_initialize())
      {

         return false;

      }

      m_iReadPointer = 0;

      return true;

   }


   bool track::audio_finalize()
   {

      return true;

   }


   void track::audio_seek_begin()
   {

      ::audio::plugin::audio_seek_begin();

      m_iDecoder = 0;

      m_iReadPointer = 0;

   }


   void track::audio_move_next()
   {

   }


   bool track::audio_eof()
   {

      if (m_bNonStopOnEof)
      {

         return false;

      }

      return m_bEof && audio_file().get_size() == 0;

   }


   u32 track::audio_get_samples_per_second() const
   {

      return 44100;

   }


   u32 track::audio_get_channel_count() const
   {

      return 2;

   }


   u32 track::audio_get_bits_per_sample() const
   {

      return 16;

   }


   memsize track::audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize)
   {

      if (m_plugina.is_empty())
      {

         return 0;

      }

      m_pplugin = m_plugina[maximum(0, m_iDecoder) %m_plugina.get_count()];

      if(!m_pplugin->audio_is_initialized())
      {

         init_child(m_pplugin);

      }

      if (m_pplugin->audio_eof())
      {

         if (m_pplugin->m_iRestartPosition >= 0)
         {

            m_pplugin->audio_seek_begin();

         }


      }

      auto uRead = m_pplugin->audio_read(lpvoidBuffer, uiBufferSize);

      if(m_pplugin->audio_eof())
      {

         m_iDecoder++;

         if(m_iDecoder >= m_plugina.get_count())
         {

            if(m_bLoop)
            {

               m_iDecoder = 0;

               m_pplugin = m_plugina[m_iDecoder %m_plugina.get_count()];

            }
            else
            {

               m_bEof = true;

            }

         }
         else
         {

            m_pplugin = m_plugina[m_iDecoder %m_plugina.get_count()];

         }

      }

      return uRead;

   }


   void track::audio_stop()
   {

      m_bStop = true;

   }


   void track::audio_seek_end()
   {

      synchronous_lock synchronouslock(this->synchronization());

      ::audio::plugin::audio_seek_end();

      m_iReadPointer    = 0;

   }


   i64 track::audio_get_sample_count()
   {

      return m_nSampleCount;

   }


   bool track::audio_set_non_stop_on_eof(bool bSet)
   {

      m_bNonStopOnEof = bSet;

      return m_bNonStopOnEof;

   }


   void track::add_plugin(plugin* pplugin)
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

      pplugin->audio_finalize();

      m_plugina.add(pplugin);

   }


   void track::replace_with_track(plugin* pplugin)
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



