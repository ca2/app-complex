#include "framework.h"

//#include "aura/message.h"


namespace wave
{


   player::player()
   {

      m_bMessageThread = true;

      m_estate = e_state_initial;
      m_epurpose = purpose_default;

   }


   player::~player()
   {

   }


   void player::prepare_wave_player(e_purpose epurpose)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (thread_active())
      {

         return ::success_none;

      }

      //if (!allocate_player())
      //{

         // return false;

      //}

      //if (m_pwaveplayerForListener->thread_active())
      //{

         // return true;

      //}

      m_epurpose = epurpose;

      synchronouslock.unlock();

      if (!begin_synch())
      {

         return ::error_failed;

      }

      return ::success;

   }

   

   void player::install_message_routing(::channel * pchannel)
   {

      ::thread::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_player_command, pchannel, this, &player::on_player_command);
      MESSAGE_LINK(e_message_player_event, pchannel, this, &player::on_event);

   }


   bool player::DecoderOpen(player_command  * pcommand)
   {

      if (DecoderIsActive())
      {

         audio_close();

      }

      string strDecoder;

      ::pointer<::audio::plugin>pplugin;

      if (pcommand->GetCommand() == command_open_plugin)
      {

         pplugin = pcommand->m_ppluginOpen;

      }
      else if (pcommand->GetCommand() == command_open_file)
      {

         if (pcommand->m_bSeekable)
         {

            pplugin = paudio->audiowave()->m_pdecoderset->GetNewDecoder(pcommand->get_open_file(), pcommand->m_bSeekable);

         }
         else
         {

            pplugin = paudio->audiowave()->m_pdecoderset->GetNewDecoder(pcommand->get_open_file(), pcommand->m_bSeekable, 1024);

         }

      }
      else
      {

         switch (pcommand->GetCommand())
         {
         case command_open_file_aiff:
            //m_pplugin = memory_new _vmsaiffdec::plugin();
            return false;
            break;
         case command_open_file_cda:
         {
            strDecoder = libfilename("audio_cd");
         }
         break;
         case command_open_file_mp3:
         case command_open_file_rtp:
         {
            strDecoder = libfilename("audio_libmpg123");
         }
         break;
         case command_open_file_vqf:
            //m_pplugin = memory_new _vmstwinvqdec::plugin();
            return false;
            break;
         case command_open_file_wm:
         {
            strDecoder = libfilename("audio_window_media");
         }
         break;
         case command_open_file_wav:
         {
            strDecoder = libfilename("audio_wave");
         }
         break;
         default:
            return false;
            break;
         }

         auto pdecoderplugin = paudio->audiowave()->m_pdecoderset->LoadPlugin(strDecoder);

         if(!pdecoderplugin)
         {

            return false;

         }

         ::pointer<::audio::decoder>pdecoder = pdecoderplugin->NewDecoder();

         if (pdecoder.is_null())
         {

            return false;

         }

         if (pcommand->GetCommand() == command_open_file_rtp)
         {

            if (pdecoder->audio_set_seekable(false))
            {

               return false;

            }

            if (!pdecoder->audio_set_real_time())
            {

               return false;

            }

            if (pdecoder->audio_set_read_block_size(1024) != 1024)
            {

               return false;

            }

         }

         if (!pdecoder->multimedia_open(pcommand->get_open_file()))
         {

            return false;

         }

         pplugin = pdecoder;

      }

      if (pplugin.is_set())
      {

         m_pwaveout->out_set_plugin(pplugin);

      }

      OnEvent(EventOpenDecoder, pcommand);

      return pplugin.is_set();

   }


   void player::audio_initialize(::pointer<::file::file>ayloadFile)
   {

      __UNREFERENCED_PARAMETER(payloadFile);

   }


   bool player::DecoderIsActive()
   {

      if(::is_null(m_pwaveout))
      {

         return false;

      }

      return m_pwaveout->out_plugin() != nullptr;

   }


   void player::audio_close()
   {

      try
      {

         m_pwaveout->out_set_plugin(nullptr);

      }
      catch (...)
      {


      }

   }


   void player::DecoderRun()
   {

   }


   void player::init_thread()
   {

      if (!::thread::init_thread())
      {

         return false;

      }

      auto estatus = __construct(m_pwaveout);

      if (!estatus)
      {

         return estatus;

      }

      set_thread_priority(::e_priority_highest);

      m_pwaveout->m_pplayer = this;

      if (!m_pwaveout->thread_active())
      {

         if (!m_pwaveout->begin_synch(::e_priority_highest))
         {

            return false;

         }

      }

      return true;

   }


   void player::term_thread()
   {

      try
      {

         for (auto & plistener : m_listenera)
         {

            try
            {

               plistener->OnWavePlayerEvent(this, EventDestroy);

            }
            catch (...)
            {


            }

         }

      }
      catch (...)
      {


      }

      erase_all_listeners();

      thread::term_thread();

   }



   void player::post_command(player_command * pcommand)
   {

      post_object(e_message_player_command, 0, pcommand);

   }


   void player::on_player_command(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      ::pointer<player_command>pcommand(pusermessage->m_lparam);

      player_command_procedure(pcommand);

      if (pcommand->m_pbResult != nullptr)
      {

         *pcommand->m_pbResult = pcommand->m_bResult;

      }

      pmessage->m_bRet = true;

   }


   bool player::player_command_procedure(player_command * pcommand)
   {

      pcommand->m_bResult = true;

      enum_command ecommand = pcommand->GetCommand();

      switch (ecommand)
      {
      case command_open_plugin:
      case command_open_file_cda:
      case command_open_file_mp3:
      case command_open_file_rtp:
      case command_open_file_aiff:
      case command_open_file_vqf:
      case command_open_file_wm:
      case command_open_file_wav:
      case command_open_file:
      {

         if (IsPlaying())
         {
            return true;
         }

         if (DecoderIsActive())
         {

            audio_close();

         }

         if (!DecoderOpen(pcommand))
         {

            pcommand->m_bResult = false;

            OnEvent(EventOpenDecoderFailed);

            break;

         }

         if (!DecoderIsActive())
         {

            pcommand->m_bResult = false;

            OnEvent(EventOpenDecoderFailed);

            break;

         }

         OnEvent(EventOpenDecoder, pcommand);

      }
      break;
      case command_execute_play:
      {

         TRACE("audio_player command_execute_play");

         if (IsPlaying())
         {

            TRACE("Error : Wrong State : audio_player audio already playing");

            pcommand->m_bResult = false;

            break;

         }

         if (m_pwaveout->out_plugin() == nullptr)
         {

            TRACE("audio_player plugin isn't set : NOT going to play");

            pcommand->m_bResult = false;

            break;

         }

         m_pwaveout->post_object(e_message_player_start, 0, pcommand);

      }
      break;
      case command_execute_stop:
      {

         FadeOutAndStop();

      }
      break;
      case command_execute_pause:
      {

         m_pwaveout->out_pause();

      }
      break;
      case command_execute_restart:
      {

         m_pwaveout->out_restart();

      }
      break;
      case command_close_device:
      {

         if(m_pwaveout != nullptr)
         {

            m_pwaveout->out_close();

         }

         OnEvent(EventCloseDevice);

      }
      break;
      default:
         ASSERT(false);
         break;
      }

      pcommand->SetEvents();

      return pcommand->m_bResult;

   }



   void player::ExecuteStop()
   {

      m_pwaveout->out_stop();

   }


   bool player::DeviceIsOpened()
   {

      return GetDeviceState() == e_device_state_opened;

   }


   bool player::DecoderIsOpened()
   {

      return GetDecoderState() == e_decoder_state_opened;

   }


   bool player::IsPlaying()
   {

      return m_pwaveout != nullptr && (GetDeviceState() == e_device_state_playing
                                       || GetDeviceState() == e_device_state_stopping
                                       || m_estate == e_state_fading_out_to_stop);

   }


   bool player::GetPlayEnable()
   {

      return GetDecoderState() == e_decoder_state_opened
               && !IsPlaying();

   }


   bool player::GetStopEnable()
   {

      return IsPlaying();

   }


   void player::post_event(e_event eevent, player_command * pcommand)
   {

      ::pointer<player_command>spcommand(pcommand);

      post_message(e_message_player_event, (WPARAM)eevent, spcommand);

   }


   void player::on_event(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      ::pointer<player_command>pcommand(pusermessage->m_lparam);

      OnEvent((e_event) pusermessage->m_wparam.m_number, pcommand);

   }


   void player::OnEvent(e_event eevent, player_command * pcommand)
   {

      switch (eevent)
      {
      case e_player_event_open_device:
         TRACE("player OnEvent e_player_event_open_device");
         SetDeviceState(e_device_state_opened);
         break;
      case EventOpenDeviceFailed:
         TRACE("player OnEvent EventOpenDeviceFailed");
         SetDeviceState(e_device_state_initial);
         break;
      case EventOpenDecoder:
         TRACE("player OnEvent EventOpenDecoder");
         SetDecoderState(e_decoder_state_opened);
         break;
      case EventStartDeviceFailed:
      {

         TRACE("player OnEvent EventStartDeviceFailed");

         SetDeviceState(e_device_state_opened);
         SetState(e_state_initial);

      }
      break;
      case EventPlay:
      {

         TRACE("player OnEvent EventPlay");

         SetDeviceState(e_device_state_playing);
         SetState(e_state_playing);

      }
      break;
      case EventStop:
      {

         TRACE("player OnEvent EventStop");

         SetDeviceState(e_device_state_stopping);
         SetState(e_state_initial);
      }
      break;
      case EventFadeOutAndStop:
      {

         TRACE("player OnEvent EventFadeOutAndStop");

         SetState(e_state_fading_out_to_stop);

      }
      break;
      case EventExecutePause:
      {

         TRACE("player OnEvent EventDeviceOpen");

         SetDeviceState(e_device_state_paused);
         SetState(e_state_paused);

      }
      break;
      case EventExecuteRestart:
      {

         TRACE("player OnEvent EventExecuteRestart");

         SetDeviceState(e_device_state_playing);


         SetState(e_state_playing);

      }
      break;
      case EventEOF:
      {

         TRACE("player OnEvent EventEOF");

      }
      break;
      case EventPlaybackEnd:
      {

         TRACE("player EventPlaybackEnd");

         m_pwaveout->out_close();

         SetDeviceState(e_device_state_initial);

         if (m_pwaveout->out_plugin() != nullptr)
         {

            m_pwaveout->out_plugin()->audio_stop();

            SetDecoderState(e_decoder_state_opened);

            m_pwaveout->out_plugin()->audio_seek_begin();

         }

         SetState(e_state_initial);

         m_estate = e_state_initial;

      }
      break;
      case EventStopped:
      {

         TRACE("player EventStopped");

         m_pwaveout->out_close();

         if (m_pwaveout->out_plugin() != nullptr)
         {

            m_pwaveout->out_plugin()->audio_stop();

            SetDecoderState(e_decoder_state_opened);

            m_pwaveout->out_plugin()->audio_seek_begin();

         }

         SetState(e_state_initial);

         SetDeviceState(e_device_state_initial);

      }
      break;
      case EventCloseDevice:
      {
         TRACE("player OnEvent EventCloseDevice");
         SetDeviceState(e_device_state_initial);
      }
      break;
      case EventCloseDecoder:
      {
         TRACE("player OnEvent EventCloseDecoder");
         SetDecoderState(e_decoder_state_initial);
      }
      break;
      case EventOpenDecoderFailed:
      {
         TRACE("player OnEvent EventOpenDecoderFailed");
         SetDecoderState(e_decoder_state_initial);
      }
      break;
      case EventDestroy:
      {
         TRACE("player OnEvent EventDestroy");
         SetDeviceState(e_device_state_initial);
      }
      break;
      }

      for (auto plistener : m_listenera)
      {

         plistener->OnWavePlayerEvent(this, eevent, pcommand);

      }

   }


   void player::SetDeviceState(enum_device_state estate)
   {

      m_edevicestate = estate;

   }


   void player::SetDecoderState(enum_decoder_state estate)
   {
      m_epluginstate = estate;
   }

   void player::SetState(enum_state estate)
   {
      m_estate = estate;
   }


   player::enum_state player::GetState()
   {

      return m_estate;

   }


   player::enum_device_state player::GetDeviceState()
   {

      if (m_edevicestate == e_device_state_playing
            || m_edevicestate == e_device_state_stopping)
      {

         if (m_pwaveout->out_get_state() != out::e_state_playing
               && m_pwaveout->out_get_state() != out::e_state_stopping)
         {

            m_edevicestate = e_device_state_opened;

         }

      }

      return m_edevicestate;

   }


   player::enum_decoder_state player::GetDecoderState()
   {

      return m_epluginstate;

   }


   out * player::get_out()
   {

      return m_pwaveout;

   }


   bool player::ExecuteIsPaused()
   {

      return m_estate == e_state_paused;

   }


   void player::_Stop()
   {

      if (IsPlaying())
      {

         m_pwaveout->post_message(e_message_player_stop);

      }

   }


   void player::FadeOutAndStop()
   {

      if (m_estate != e_state_playing)
      {

         return;

      }

      OnEvent(EventFadeOutAndStop);

      effect_diminuendo * pdiminuendo = memory_new effect_diminuendo;

      pdiminuendo->m_bEnd = true;
      pdiminuendo->m_bSustain = true;
      pdiminuendo->m_bTriggerEnd = true;
      pdiminuendo->SetLengthMillis(5000, m_pwaveout->out_get_buffer()->m_waveformatOut.nSamplesPerSec);
      pdiminuendo->Initialize();

      m_pwaveout->out_set_stream_out_effect(pdiminuendo);

   }


   player::listener::listener()
   {

   }


   player::listener::~listener()
   {

      //try
      //{

      //   synchronous_lock synchronouslock(this->synchronization());

      //   if (m_pwaveplayerForListener.is_set())
      //   {

      //      m_pwaveplayerForListener->erase_listener(this);

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   void player::listener::OnWavePlayerEvent(player * pplayer, player::e_event event, player_command * pcommand)
   {

   }


   ::wave::player* player::listener::get_wave_player()
   {

      return nullptr;

   }


   //player * player::listener::get_player()
   //{

   //   return m_pwaveplayerForListener;

   //}


   void player::add_listener(listener * plistener)
   {

      try
      {

         synchronous_lock synchronouslock(this->synchronization());

         plistener->assert_ok();

         //try
         //{


         //   if (plistener->m_pwaveplayerForListener != this)
         //   {

         //      if (plistener->m_pwaveplayerForListener.is_set())
         //      {

         //         plistener->m_pwaveplayerForListener->erase_listener(plistener);

         //      }

         //      plistener->m_pwaveplayerForListener = this;

         //   }

         //}
         //catch (...)
         //{


         //}

         try
         {

            m_listenera.add_unique(plistener);

         }
         catch (...)
         {

         }

      }
      catch (...)
      {

      }

   }


   void player::erase_listener(listener * plistener)
   {

      try
      {

         synchronous_lock synchronouslock(this->synchronization());

         //try
         //{

         //   if (plistener->m_pwaveplayerForListener == this)
         //   {

         //      plistener->m_pwaveplayerForListener.release();

         //   }

         //}
         //catch (...)
         //{


         //}

         try
         {

            m_listenera.erase(plistener);

         }
         catch (...)
         {

         }

      }
      catch (...)
      {

      }

   }


   void player::erase_all_listeners()
   {

      try
      {

         synchronous_lock synchronouslock(this->synchronization());

         while (m_listenera.get_count() > 0)
         {

            erase_listener(m_listenera[0]);

         }

      }
      catch (...)
      {

      }

   }


   string player::GetDeviceStateString(enum_device_state edevicestate)
   {

      switch(edevicestate)
      {
      case e_device_state_initial:
         return "e_device_state_initial";
      case e_device_state_opened:
         return "e_device_state_opened";
      case e_device_state_playing:
         return "e_device_state_playing";
      case e_device_state_stopping:
         return "e_device_state_stopping";
      case e_device_state_paused:
         return "e_device_state_paused";
      default:
         return "unknown device state";
      }

   }


   string player::GetDecoderStateString(enum_decoder_state edecoderstate)
   {

      switch(edecoderstate)
      {
      case e_decoder_state_initial:
         return "e_decoder_state_initial";
      case e_decoder_state_opened:
         return "e_decoder_state_opened";
      default:
         return "unknown decoder state";
      }

   }


   string player::GetStateString(enum_state estate)
   {

      switch(estate)
      {
      case e_state_initial:
         return "e_state_initial";
      case e_state_playing:
         return "e_state_playing";
      case e_state_paused:
         return "e_state_paused";
      case e_state_fading_out_to_stop:
         return "e_state_fading_out_to_stop";
      default:
         return "unknown state";
      }

   }


   ::audio::plugin * player::plugin()
   {

      if (m_pwaveout.is_null())
      {

         return nullptr;

      }

      return m_pwaveout->out_plugin();

   }


} // namespace wave



