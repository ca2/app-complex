#include "framework.h"

#include "apex/message.h"


namespace wave
{


   recorder::recorder()
   {

      //m_pwavein = create_object <  in  > ();

      m_pencoder = nullptr;

   }


   recorder::~recorder()
   {

   }


   void recorder::init_thread()
   {

      if(m_pwavein == nullptr)
         return false;

      m_pwavein->begin(::e_priority_above_normal);

      //m_pwavein->m_pplayer = this;

      return true;
   }


   void recorder::term_thread()
   {

      thread::term_thread();

   }


   void recorder::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_recorder_command, pchannel, this, &recorder::on_recorder_command);

   }

   /* // 
   ON_THREAD_MESSAGE(audMessageCommand, OnaudCommandMessage)
   // 
   */

   // recorder message handlers

   void recorder::post_command(recorder_command * pcommand)
   {

      post_object(e_message_recorder_command, 0, pcommand);

   }


   void recorder::on_recorder_command(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      ::pointer<recorder_command>pcommand(pusermessage->m_lparam);

      recorder_command_procedure(pcommand);

      if(pcommand->m_pbResult != nullptr)
      {

         *pcommand->m_pbResult = pcommand->m_bResult;

      }

   }

   bool recorder::recorder_command_procedure(recorder_command * pcommand)
   {

      pcommand->m_bResult = true;

      switch(pcommand->GetCommand())
      {
      case command_open_file_wav:
      {

         m_iOutBufferSampleCount = 48 * 1024;

         m_spfile = pcommand->GetOpenFile();

         if(m_pencoder == nullptr)
         {

            try
            {
               m_pencoder  = m_pluginset.GetNewEncoder("*.wav");
               if(m_pencoder == nullptr)
                  return false;
            }
            catch(...)
            {
               pcommand->m_bResult = false;
               return false;
            }

         }

         m_pwavein->m_pencoder = m_pencoder;

         m_pencoder->EncoderSetFile(m_spfile);

      }
      break;

      case ::wave::command_execute_record:
      {
         /*if(m_pencoder == nullptr)
         {
         pcommand->m_bResult = false;
         return false;
         }*/
         m_pwavein->in_open(8, m_iOutBufferSampleCount);
         m_pwavein->in_start();
      }
      break;
      case ::wave::command_close_device:
      case ::wave::command_execute_stop:
      {

         m_eventStopped.ResetEvent();
         m_pwavein->in_stop();
         m_pwavein->m_eventStopped.wait(::time((5000) * 20));
         m_pwavein->in_close();
         m_pencoder->EncoderFinalize();
         m_eventStopped.SetEvent();

         ::release(m_spfile.m_p);

      }
      break;
      default:
         ASSERT(false);
         break;
      }
      pcommand->SetEvents();
      return pcommand->m_bResult;
   }


   recorder_command::recorder_command()
   {
      m_pbResult = nullptr;
   }

   recorder_command::recorder_command(const recorder_command & command)
   {
      operator =(command);
   }

   recorder_command & recorder_command::operator =(const recorder_command & command)
   {
      SetCommand(command.GetCommand());
      SetOpenFile(command.GetOpenFile());
      m_bResult = command.m_bResult;
      m_pbResult = command.m_pbResult;
      m_evptra = command.m_evptra;
      return *this;

   }

   enum_command recorder_command::GetCommand() const
   {
      return m_ecommand;
   }

   void recorder_command::SetCommand(enum_command ecommand)
   {
      m_ecommand = ecommand;
   }

   ::pointer<::file::file>recorder_command::GetOpenFile() const
   {
      return m_pfileOpen;
   }

   void recorder_command::SetOpenFile(::pointer<::file::file>file)
   {
      m_pfileOpen = pfile;
   }

   void recorder_command::OpenWavFile(::pointer<::file::file>pfile)
   {
      SetCommand(command_open_file_wav);
      SetOpenFile(pfile);
   }


   void recorder_command::SetEvents()
   {
      for(i32 i = 0;  i < m_evptra.get_size(); i++)
      {
         m_evptra[i]->SetEvent();
      }
   }
   void recorder_command::Stop()
   {
      SetCommand(::wave::command_execute_stop);

   }

   void recorder_command::Record()
   {
      SetCommand(::wave::command_execute_record);

   }


   void recorder::in_data_proc(in * pwavein, u32 dwSampleTime, int iBuffer)
   {

      __UNREFERENCED_PARAMETER(pwavein);
      __UNREFERENCED_PARAMETER(dwSampleTime);
      __UNREFERENCED_PARAMETER(iBuffer);

   }

   bool recorder::IsRecording()
   {

      if(m_pwavein == nullptr)
         return false;

      return m_pwavein->in_is_recording();

   }


} // namespace wave



