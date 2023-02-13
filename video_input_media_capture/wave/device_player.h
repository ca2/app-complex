#pragma once


namespace wave
{


   class CLASS_DECL_APP_CORE_AUDIO device_player :
      virtual public ::thread,
      virtual public player
   {
   public:


      ::pointer<out>                       m_pwaveout;


      device_player();
      virtual ~device_player();


      void prepare_wave_player(e_purpose epurpose) override;

      void install_message_routing(::channel* pchannel) override;

      virtual void init_thread() override;
      virtual void term_thread() override;

      bool DecoderOpen(player_command* pcommand)override;

      bool DecoderIsActive()override;
      void audio_initialize(::pointer<::file::file>pfile)override;
      void audio_close()override;
      void DecoderRun()override;




      virtual bool player_command_procedure(player_command* pcommand)override;

      void FadeOutAndStop()override;
      void SetState(enum_state estate)override;
      enum_state GetState()override;
      bool ExecuteIsPaused()override;
      bool GetStopEnable()override;
      bool GetPlayEnable()override;
      virtual out * wave_out() override;
      bool IsPlaying()override;
      enum_device_state GetDeviceState()override;
      enum_decoder_state GetDecoderState()override;
      void SetDeviceState(enum_device_state estate)override;
      void SetDecoderState(enum_decoder_state estate)override;

      void post_event(enum_player_event event, player_command* pcommand = nullptr)override;
      void OnEvent(enum_player_event event, player_command* pcommand = nullptr)override;
      bool DeviceIsOpened()override;
      bool DecoderIsOpened()override;


      static string GetDeviceStateString(enum_device_state edevicestate);
      static string GetDecoderStateString(enum_decoder_state edecoderstate);
      static string GetStateString(enum_state estate);


      void post_command(player_command* pcommand)override;


      DECLARE_MESSAGE_HANDLER(on_open_response);
      DECLARE_MESSAGE_HANDLER(on_player_command);
      DECLARE_MESSAGE_HANDLER(on_event);

      void _Stop()override;
      void ExecuteStop()override;


      virtual void add_listener(listener* plistener)override;
      virtual void erase_listener(listener* plistener)override;
      virtual void erase_all_listeners()override;

      class ::time player_get_time_for_synch() override;
      //class ::time player_get_time_for_synch() override;

      virtual ::audio::plugin* plugin()override;
      virtual void player_set_volume(double dVolume) override;
      virtual double player_get_volume() override;

      virtual class ::time player_get_prebuffer_millis_length()override;

      virtual u64 player_get_frame_byte_count() override;

   };


} // namespace multimedia



