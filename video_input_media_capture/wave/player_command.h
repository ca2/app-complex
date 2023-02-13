#pragma once


namespace wave
{

      
   class out;
   class pre_buffer;


   class CLASS_DECL_APP_CORE_AUDIO player_command :
      virtual public object
   {
   public:


      ::wave::enum_command                            m_ecommand;
      ::file_pointer                                  m_pfile;
      array < event *, event * >                      m_evptra;
      bool                                            m_bResult;
      bool *                                          m_pbResult;
      bool                                            m_bSeekable;
      class ::time                                     m_time;
      //class ::time                                 m_position;
      ::pointer<::audio::plugin>              m_ppluginOpen;
      bool                                            m_bFadeIn;


      player_command();
      player_command(const player_command & command);


      void set_open_file(::file::file * pfile);
      void SetOpenDecoder(::audio::plugin * pplugin);
      ::file::file * get_open_file() const;
      void SetCommand(::wave::enum_command ecommand);
      ::wave::enum_command GetCommand() const;


      void SetEvents();
      void AttachEvent(event * pevent);


      void OpenDecoder(::audio::plugin * pplugin);
      void OpenRtpFile(::file::file * pfile);
      void OpenMp3File(::file::file * pfile);
      void OpenAiffFile(::file::file * pfile);
      void OpenCdaFile(::file::file * pfile);
      void OpenWmFile(::file::file * pfile);
      void OpenWavFile(::file::file * pfile);
      void OpenFile(::file::file * pfile, bool bSeekable = true);
      void OpenVqfFile(::file::file * pfile);

      void Play(class ::time time, bool bFadeIn);
      void Stop();
      void OpenDevice();
      void CloseDevice();

      player_command & operator =(const player_command & command);

   };


   typedef ::pointer<player_command>player_command_pointer;


} // namespace wave



