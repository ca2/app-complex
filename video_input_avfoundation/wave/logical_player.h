#pragma once


namespace wave
{


   class CLASS_DECL_APP_CORE_AUDIO logical_player :
      virtual public player,
      virtual public ::audio::plugin
   {
   public:



      ::pointer<::audio::plugin>                 m_ppluginPlay;
      ::pointer<::audio::plugin>                 m_ppluginRead;
      class ::time                                 m_timeDeviceStart;
      class ::time                                 m_timeStart;
      u64                                         m_uFrameByteCount;


      logical_player();
      virtual ~logical_player();

      void prepare_wave_player(e_purpose epurpose) override;

      //void install_message_routing(::channel* pchannel) override;

      bool DecoderOpen(player_command* pcommand) override;

      bool DecoderIsActive() override;
      bool audio_initialize() override;
      void audio_initialize(::pointer<::file::file>pfile) override;
      void audio_close() override;
      void DecoderRun() override;
      virtual out * wave_out() override;

      virtual memsize audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize) override;

      //virtual void multimedia_read_frame() override;

      virtual bool player_command_procedure(player_command* pcommand) override;

      void FadeOutAndStop() override;
      void SetState(enum_state estate) override;
      enum_state GetState() override;
      bool ExecuteIsPaused() override;
      bool GetStopEnable() override;
      bool GetPlayEnable() override;
      bool IsPlaying() override;
      enum_device_state GetDeviceState() override;
      enum_decoder_state GetDecoderState() override;
      void SetDeviceState(enum_device_state estate) override;
      void SetDecoderState(enum_decoder_state estate) override;

      void post_event(enum_player_event event, player_command* pcommand = nullptr) override;
      void OnEvent(enum_player_event event, player_command* pcommand = nullptr) override;
      bool DeviceIsOpened() override;
      bool DecoderIsOpened() override;


      static string GetDeviceStateString(enum_device_state edevicestate);
      static string GetDecoderStateString(enum_decoder_state edecoderstate);
      static string GetStateString(enum_state estate);


      void post_command(player_command* pcommand) override;



      void _Stop() override;
      void ExecuteStop() override;


      virtual void add_listener(listener* plistener) override;
      virtual void erase_listener(listener* plistener) override;
      virtual void erase_all_listeners() override;

      virtual u32                audio_get_samples_per_second() const override;
      virtual u32                audio_get_channel_count() const override;
      virtual u32                audio_get_bits_per_sample() const override;



      class ::time player_get_time_for_synch() override;
      //class ::time player_get_time_for_synch() override;

      virtual ::audio::plugin* plugin() override;

      virtual class ::time player_get_prebuffer_millis_length() override;

      virtual u64 player_get_frame_byte_count() override;

   };


} // namespace multimedia



