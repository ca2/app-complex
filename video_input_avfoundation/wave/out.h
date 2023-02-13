#pragma once


namespace wave
{


   class CLASS_DECL_APP_CORE_AUDIO out :
      virtual public base
   {
   public:


      enum  enum_state
      {

         e_state_initial,
         e_state_opened,
         e_state_playing,
         e_state_stopping,
         state_stopped,
         e_state_paused,
         state_closing,

      };


      class CLASS_DECL_APP_CORE_AUDIO output_thread :
         virtual public ::thread
      {
      public:


         out * m_pwaveout;

         manual_reset_event   m_evFilled;
         list < ::index >     m_listFilled;


         output_thread();
         virtual ~output_thread();


         virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
         {

            return ::thread::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

         }

         virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
         {

            return ::thread::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

         }



         virtual void init_thread() override;
         virtual void run() override;


         void on_filled(::index i);


         //DECLARE_MESSAGE_HANDLER(on_filled);


//            virtual bool register_at_required_threads() override;


      };


      class CLASS_DECL_APP_CORE_AUDIO synth_thread :
         virtual public ::thread
      {
      public:


         out * m_pwaveout;


         manual_reset_event      m_evFree;
         list < ::index >        m_listFree;
         
         synth_thread();
         virtual ~synth_thread();


         virtual void init_thread() override;
         virtual void run() override;


         void on_free(::index i);


//            virtual bool register_at_required_threads() override;


      };


   public:

   //protected:

     // friend class pre_buffer;
      ::pointer<pre_buffer>                   m_pprebuffer;


   public:

      e_purpose                                  m_epurpose;
      player *                                   m_pplayer;
      double                                     m_dVolume;

      index                                      m_iLastBufferId;
      bool                                       m_bDirectOutput;
      ::thread *                                 m_pthreadCallback;
      enum_state                                    m_estate;
      int                                        m_iBufferedCount;
      //iaudio::stream_effect *                  m_peffect;
      i64                                        m_iLostBytes;
      class ::time                                m_timeStart;
      bool                                       m_bEOS;
      ::pointer<output_thread>                m_poutputthread;
      ::pointer<synth_thread>                 m_psynthtask;


      out();
      virtual ~out();


      void install_message_routing(::channel * pchannel) override;

      bool defer_pump_message() override;


      virtual bool raw_pump_message() override;

      virtual bool out_set_plugin(::audio::plugin * pplugin);
      virtual ::audio::plugin * out_plugin();


      virtual ::count out_get_buffered_buffer_count();
      virtual class ::time out_get_time();
      virtual class ::time out_get_time_for_synch();
      //virtual class ::time out_get_time();
      //virtual class ::time out_get_time_for_synch();
      //virtual class ::time out_get_time();
      //virtual class ::time out_get_time_for_synch();
      virtual enum_state out_get_state();
      virtual void out_launch_buffers();


      ::pointer<buffer>out_get_buffer();

      virtual void     out_open_ex(::thread * pthreadCallback, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, e_purpose epurpose);
      virtual void     out_close();
      virtual void     out_start(const class ::time & position);
      //virtual void out_set_stream_effect(::iaudio::stream_effect * peffect);
      virtual void out_set_stream_out_effect(::iaudio::wave_stream_effect * peffect);
      virtual void     out_pause();
      virtual void     out_restart();
      virtual void     out_stop();
      virtual void     out_errno();
      virtual memsize out_get_buffer_size();
      virtual ::count out_get_buffer_sample_count();
      virtual void * out_get_buffer_data(index iBuffer);
      virtual void * out_get_os_data();
      virtual void out_post_close();
      virtual void out_prebuffer_eof();


      virtual void out_on_playback_end();

      virtual void init_thread() override;
      virtual void term_thread() override;

      DECLARE_MESSAGE_HANDLER(on_open);
      DECLARE_MESSAGE_HANDLER(on_close);
      DECLARE_MESSAGE_HANDLER(on_start);
      DECLARE_MESSAGE_HANDLER(on_stop);
      DECLARE_MESSAGE_HANDLER(on_filled);
      DECLARE_MESSAGE_HANDLER(on_free);

      virtual void defer_open();
      virtual void defer_start();

      virtual void out_filled(index iBuffer);
      virtual void out_free(index iBuffer);
      virtual void out_on_pre_buffer(index iId);
//         virtual bool register_at_required_threads() override;


      inline class ::time get_prebuffer_millis_length() { return m_pprebuffer->get_millis_length(); }

   };


} // namespace multimedia




