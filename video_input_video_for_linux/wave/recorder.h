#pragma once



namespace wave
{


   class in;


   class CLASS_DECL_APP_CORE_AUDIO recorder :
      virtual public ::thread,
      virtual public in_listener
   {
   public:


      ::pointer<in>                            m_pwavein;
      file_pointer                              m_spfile;
      ::pointer<::audio::encoder>              m_pencoder;
      ::audio::encoder_plugin_set               m_pluginset;
      manual_reset_event                        m_eventStopped;
      i32                                       m_iOutBufferSampleCount;


      recorder();
      virtual ~recorder();


      void ExecuteStop();
      void ExecutePlay();

      bool IsRecording();

      virtual void in_data_proc(in * pwavein, u32 dwSampleTime, int iBuffer) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void init_thread() override;
      virtual void term_thread() override;

      bool recorder_command_procedure(::wave::recorder_command * pcommand);
      void post_command(::wave::recorder_command * pcommand);
      DECLARE_MESSAGE_HANDLER(on_recorder_command);


   };


} // namespace wave




