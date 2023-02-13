#pragma once


namespace wave
{


   class CLASS_DECL_APP_CORE_AUDIO recorder_container :
      virtual public ::object
   {
   public:


      ::wave::recorder *      m_pwaverecorder;


      recorder_container();
      virtual ~recorder_container();


      ::pointer<::wave::recorder> get_recorder();


      virtual bool initialize_recorder();


   };


} // namespace wave






