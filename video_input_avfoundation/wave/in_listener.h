#pragma once


namespace wave
{


   class in;


   class CLASS_DECL_APP_CORE_AUDIO in_listener
   {
   public:


      comparable_array < in *, in * > m_waveinptra;


      in_listener();
      virtual ~in_listener();

      virtual void in_data_proc(in * pwavein, u32 dwSampleTime, int iBuffer);

      void HookWaveIn(in * pwavein);
      void UnhookWaveIn(in * pwavein);


   };


} // namespace wave



