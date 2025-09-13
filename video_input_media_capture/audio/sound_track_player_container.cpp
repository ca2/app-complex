#include "framework.h"



namespace audio
{


   sound_track_player_container::sound_track_player_container()
   {

      defer_create_synchronization();

   }


   sound_track_player_container::~sound_track_player_container()
   {

   }

   ::wave::player* sound_track_player_container::get_wave_player()
   {

      if (!m_psoundtrackplayer)
      {

         return nullptr;

      }

      return m_psoundtrackplayer->m_pwaveplayer;

   }

   void sound_track_player_container::defer_initialize_audio_playback(::wave::enum_purpose epurpose)
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (::is_set(m_psoundtrackplayer))
      {

         return ::success_none;

      }

      auto estatus = øconstruct_new(m_psoundtrackplayer);

      if (!estatus)
      {

         return estatus;

      }

      synchronouslock.unlock();

      estatus = m_psoundtrackplayer->defer_start(epurpose);

      if (!estatus)
      {

         return estatus;

      }

      m_psoundtrackplayer->m_pwaveplayer->add_listener(this);

      return estatus;

   }


   sound_track_player* sound_track_player_container::sound_track()
   {

      return m_psoundtrackplayer;

   }



} // namespace audio




