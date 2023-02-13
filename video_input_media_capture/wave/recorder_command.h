#pragma once


namespace wave
{


   class out;
   class pre_buffer;


   class CLASS_DECL_APP_CORE_AUDIO recorder_command :
      virtual public ::object
   {
   public:


         
      ::wave::enum_command                      m_ecommand;
      ::pointer<::file::file>                  m_pfileOpen;
      array < event *, event * >                m_evptra;
      bool                                      m_bResult;
      bool *                                    m_pbResult;


      //      void CloseDevice();
      //    void OpenDevice();

      recorder_command();
      recorder_command(const recorder_command & command);

      void SetEvents();
      void AttachEvent(event * pevent);
      recorder_command & operator =(const recorder_command & command);
      void OpenWavFile(::pointer<::file::file>pfile);
      void Record();
      void Stop();
      void SetOpenFile(::pointer<::file::file>pfile);
      ::pointer<::file::file>GetOpenFile() const;
      void SetCommand(::wave::enum_command ecommand);
      ::wave::enum_command GetCommand() const;


   };


   typedef ::pointer<recorder_command>recorder_command_pointer;


} //  namespace wave



