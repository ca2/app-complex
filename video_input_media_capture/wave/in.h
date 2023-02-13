#pragma once


//#define WAVM_PROC_DATA 1000


namespace wave
{



   class CLASS_DECL_APP_CORE_AUDIO in :
      virtual public base
   {
   public:


         
      enum  enum_state
      {
         e_state_initial,
         e_state_opened,
         state_recording,
         e_state_stopping,
         state_stopped,
      };


      enum e_device
      {

         device_default = ((u32) -1),

      };


      audio::encoder *          m_pencoder;

      bool                             m_bResetting;
      i32                          m_iBuffer;
      enum_state                          m_estate;




      in_listener_set             m_listenerset;

      //event                            m_evInitialized;
      event                            m_eventExitInstance;
      event                            m_eventStopped;


      in();
      virtual ~in();


      virtual bool in_initialize_encoder();

      virtual void in_add_buffer(i32 iBuffer);
      virtual void in_erase_listener(in_listener * plistener);
      virtual void in_add_listener(in_listener * plistener);
      virtual synchronization * in_get_mutex();
      virtual bool in_is_opened();
      virtual bool in_is_recording();
      virtual void * in_get_os_data();
      virtual u32 in_get_analysis_millis();
      virtual bool in_is_resetting();

      virtual u32 in_get_state();
      virtual ::pointer<format>in_get_format();


      virtual ::pointer<buffer>in_get_buffer();

      virtual void     in_open(i32 iBufferCount, i32 iBufferSampleCount);
      virtual void     in_close();
      virtual void     in_stop();
      virtual void     in_start();
      virtual void     in_reset();

      virtual void init_thread() override;
      virtual void term_thread() override;
      virtual void pre_translate_message(::message::message * pmessage) override;


   };


} // namespace wave



