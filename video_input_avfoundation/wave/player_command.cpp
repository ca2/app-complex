#include "framework.h"



namespace wave
{


   player_command::player_command()
   {

      m_pbResult = nullptr;

      m_bSeekable = true;

   }


   player_command::player_command(const player_command & command) :
      ::object(command)
   {

      operator =(command);

   }


   player_command & player_command::operator =(const player_command & command)
   {

      SetCommand(command.GetCommand());
      set_open_file(command.get_open_file());
      SetOpenDecoder(command.m_ppluginOpen);
      m_bResult = command.m_bResult;
      m_pbResult = command.m_pbResult;
      m_evptra = command.m_evptra;
      m_bSeekable = command.m_bSeekable;
      m_time = command.m_time;
      m_bFadeIn = command.m_bFadeIn;

      return *this;

   }


   enum_command player_command::GetCommand() const
   {

      return m_ecommand;

   }


   void player_command::SetCommand(enum_command ecommand)
   {

      m_ecommand = ecommand;

   }


   ::file::file * player_command::get_open_file() const
   {

      return m_pfile;

   }


   void player_command::set_open_file(::file::file * pfile)
   {

      m_pfile = pfile;

   }


   void player_command::SetOpenDecoder(::audio::plugin * pplugin)
   {

      m_ppluginOpen = pplugin;

   }


   void player_command::OpenDecoder(::audio::plugin * pplugin)
   {

      SetCommand(command_open_plugin);

      SetOpenDecoder(pplugin);

   }


   void player_command::OpenRtpFile(::file::file * pfile)
   {

      SetCommand(command_open_file_rtp);

      set_open_file(pfile);

   }


   void player_command::OpenMp3File(::file::file * pfile)
   {

      SetCommand(command_open_file_mp3);

      set_open_file(pfile);

   }


   void player_command::OpenAiffFile(::file::file * pfile)
   {

      SetCommand(command_open_file_aiff);

      set_open_file(pfile);

   }


   void player_command::OpenCdaFile(::file::file * pfile)
   {

      SetCommand(command_open_file_cda);

      set_open_file(pfile);

   }


   void player_command::OpenVqfFile(::file::file * pfile)
   {

      SetCommand(command_open_file_vqf);

      set_open_file(pfile);

   }


   void player_command::OpenWmFile(::file::file * pfile)
   {

      SetCommand(command_open_file_wm);

      set_open_file(pfile);

   }


   void player_command::OpenWavFile(::file::file * pfile)
   {

      SetCommand(command_open_file_wav);

      set_open_file(pfile);

   }


   void player_command::OpenFile(::file::file * pfile, bool bSeekable)
   {

      SetCommand(command_open_file);

      set_open_file(pfile);

      m_bSeekable = bSeekable;

   }


   void player_command::Play(::time time, bool bFadeIn)
   {

      SetCommand(command_execute_play);

      m_time = time;

      m_bFadeIn = bFadeIn;

   }


   void player_command::AttachEvent(event *pevent)
   {

      m_evptra.add(pevent);

   }


   void player_command::SetEvents()
   {
      for (i32 i = 0; i < m_evptra.get_size(); i++)
      {
         m_evptra[i]->SetEvent();
      }
   }

   void player_command::Stop()
   {
      SetCommand(command_execute_stop);
   }

   void player_command::CloseDevice()
   {
      SetCommand(command_close_device);
   }


   void player_command::OpenDevice()
   {

      SetCommand(command_open_device);

   }


} // namespace wave


