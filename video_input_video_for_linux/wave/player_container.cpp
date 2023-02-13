#include "framework.h"



namespace wave
{


   player_container::player_container()
   {

   }


   player_container::~player_container()
   {

   }

   
   bool player_container::create_logical_wave_player(::wave::enum_purpose epurpose)
   {

      if (m_pwaveplayer)
      {

         return true;

      }

      auto plogicalplayer = __create_new<logical_player>();

      m_pwaveplayer = plogicalplayer;

      paudio->defer_initialize_audio_playback(epurpose);

      paudio->sound_track()->mix(plogicalplayer);

      m_pwaveplayer->add_listener(this);

      return true;

   }

   
   player* player_container::get_wave_player()
   {

      return m_pwaveplayer;

   }




} // namespace wave


