#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO sound_track_player_container :
      virtual public ::wave::player::listener
   {
   public:


      ::pointer<::audio::sound_track_player>             m_psoundtrackplayer;



      sound_track_player_container();
      virtual ~sound_track_player_container();


      sound_track_player* sound_track();

      
      virtual void defer_initialize_audio_playback(::wave::enum_purpose epurpose = ::wave::purpose_playground);



      virtual ::wave::player* get_wave_player() override;



   };


} // namespace audio


