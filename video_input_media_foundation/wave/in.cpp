#include "framework.h"



namespace wave
{


   in::in()
   {

      m_pencoder = nullptr;
      m_estate = e_state_initial;
      m_bResetting = false;
      __construct(m_pwavebuffer, __new(buffer));

      if(m_pwavebuffer == nullptr)
         throw ::exception(error_no_memory);

      __construct(m_pwaveformat, __new(format));

   }

   in::~in()
   {

   }


   void in::init_thread()
   {

      information("in::init_instance %X\n", get_itask());

      //SetMainWnd(nullptr);

      //ASSERT(GetMainWnd() == nullptr);

      set_thread_priority(::e_priority_highest);

//         m_evInitialized.SetEvent();

      return true;

   }


   void in::term_thread()
   {

      m_eventExitInstance.SetEvent();

      thread::term_thread();

   }


   void in::pre_translate_message(::message::message * pmessage)
   {
      return thread::pre_translate_message(pmessage);
   }

   void     in::in_open(i32 iBufferCount, i32 iBufferSampleCount)
   {
      return error_failed;
   }

   ::pointer<buffer>in::in_get_buffer()
   {
      return m_pwavebuffer;
   }

   void     in::in_close()
   {

      return error_failed;

   }


   void     in::in_start()
   {

      return error_failed;

   }


   void     in::in_stop()
   {

      return error_failed;

   }


   ::pointer<format>in::in_get_format()
   {

      return m_pwaveformat;

   }


   u32 in::in_get_state()
   {

      return m_estate;

   }


   void     in::in_reset()
   {

      return error_failed;

   }


   bool in::in_is_resetting()
   {

      return m_bResetting;

   }


   u32 in::in_get_analysis_millis()
   {

      return (u32) ((double) m_pwavebuffer->m_uiAnalysisSize * m_pwavebuffer->m_iSkippedSamplesCount * 1000.0 / m_pwaveformat->m_waveformat.nSamplesPerSec);

   }


   bool in::in_is_recording()
   {

      return m_estate == state_recording;

   }


   bool in::in_is_opened()
   {

      return m_estate == e_state_opened;

   }


   synchronization * in::in_get_mutex()
   {

      return mutex();

   }


   void in::in_add_listener(in_listener *plistener)
   {

      m_listenerset.add_unique(plistener);

      plistener->HookWaveIn(this);

   }


   void in::in_erase_listener(in_listener *plistener)
   {

      m_listenerset.erase(plistener);

   }


   void     in::in_add_buffer(i32 iBuffer)
   {

      return error_failed;

   }



   bool in::in_initialize_encoder()
   {

      if(m_pencoder == nullptr)
         return false;

      m_pencoder->EncoderSetSamplesPerSec(m_pwaveformat->m_waveformat.nSamplesPerSec);

      m_pencoder->EncoderSetBitsPerSample(m_pwaveformat->m_waveformat.wBitsPerSample);

      m_pencoder->EncoderSetChannelCount(m_pwaveformat->m_waveformat.nChannels);

      m_pencoder->EncoderInitialize();

      return true;

   }


   void * in::in_get_os_data()
   {

      return nullptr;

   }


} // namespace wave



