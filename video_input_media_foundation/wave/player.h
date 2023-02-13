#pragma once


namespace wave
{


   class CLASS_DECL_APP_CORE_AUDIO player :
      virtual public ::object
   {
   public:


      friend class out;


      enum enum_device_state
      {
         
         e_device_state_initial,
         e_device_state_opened,
         e_device_state_playing,
         e_device_state_stopping,
         e_device_state_paused,

      };


      enum enum_decoder_state
      {

         e_decoder_state_initial,
         e_decoder_state_opened,

      };


      enum enum_state
      {

         e_state_initial,
         e_state_playing,
         e_state_paused,
         e_state_fading_out_to_stop,

      };


      enum enum_player_event
      {

         e_player_event_open_decoder,
         e_player_event_open_device,
         e_player_event_play,
         e_player_event_stop,
         e_player_event_execute_pause,
         e_player_event_execute_restart,
         e_player_event_eof,
         e_player_event_playback_end,
         e_player_event_stopped,
         e_player_event_close_decoder,
         e_player_event_fade_out_and_stop,
         e_player_event_close_device,
         e_player_event_open_decoder_failed,
         e_player_event_open_device_failed,
         e_player_event_start_device_failed,
         e_player_event_destroy

      };



      class CLASS_DECL_APP_CORE_AUDIO listener :
         virtual public ::object
      {
      public:


         listener();
         virtual ~listener();

         virtual void OnWavePlayerEvent(::wave::player* pplayer,::wave::player::enum_player_event event, ::wave::player_command* pcommand = nullptr);

         virtual ::wave::player* get_wave_player();


      };


      pointer_array < listener >                    m_listenera;

      enum_device_state                                 m_edevicestate;
      enum_decoder_state                                m_epluginstate;
      enum_state                                      m_estate;
      i32                                          m_iBufferId;
      e_purpose                                    m_epurpose;
      ::pointer<::iaudio::wave_stream_effect>     m_pstreameffectOut;


      player();
      virtual ~player();


      virtual void prepare_wave_player(e_purpose epurpose);

      virtual bool DecoderOpen(player_command* pcommand);

      virtual bool DecoderIsActive();
      virtual void audio_initialize(::pointer<::file::file>pfile);
      virtual void audio_close();
      virtual void DecoderRun();




      virtual bool player_command_procedure(player_command* pcommand);

      virtual void FadeOutAndStop() = 0;
      virtual void SetState(enum_state estate);
      virtual enum_state GetState();
      virtual bool ExecuteIsPaused();
      virtual bool GetStopEnable();
      virtual bool GetPlayEnable();
      //virtual out* get_out();
      virtual bool IsPlaying();
      virtual enum_device_state GetDeviceState();
      virtual enum_decoder_state GetDecoderState();
      virtual void SetDeviceState(enum_device_state estate);
      virtual void SetDecoderState(enum_decoder_state estate);

      virtual void post_event(enum_player_event event, player_command* pcommand = nullptr);
      virtual void OnEvent(enum_player_event event, player_command* pcommand = nullptr);
      virtual bool DeviceIsOpened();
      virtual bool DecoderIsOpened();


      static string GetDeviceStateString(enum_device_state edevicestate);
      static string GetDecoderStateString(enum_decoder_state edecoderstate);
      static string GetStateString(enum_state estate);


      virtual void post_command(player_command* pcommand);



      virtual void _Stop();
      virtual void ExecuteStop();


      virtual void add_listener(listener* plistener);
      virtual void erase_listener(listener* plistener);
      virtual void erase_all_listeners();


      virtual class ::time player_get_time_for_synch();
      //virtual class ::time player_get_time_for_synch();

      virtual ::audio::plugin* plugin();

      virtual void player_set_volume(double dVolume);
      virtual double player_get_volume();

      virtual class ::time player_get_prebuffer_millis_length();
      virtual u64 player_get_frame_byte_count();


      virtual out * wave_out();


   };


} // namespace multimedia



