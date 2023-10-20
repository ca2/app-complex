#include "framework.h"

#include "apex/message.h"


namespace wave
{


   device_player::device_player()
   {

      m_bMessageThread = true;

      m_estate = e_state_initial;
      m_epurpose = purpose_default;

   }


   device_player::~device_player()
   {

   }


   void device_player::prepare_wave_player(e_purpose epurpose)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (task_active())
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



   void device_player::install_message_routing(::channel* pchannel)
   {

      ::thread::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_player_command, pchannel, this, &device_player::on_player_command);
      MESSAGE_LINK(e_message_player_event, pchannel, this, &device_player::on_event);

   }


   bool device_player::DecoderOpen(player_command* pcommand)
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
            strDecoder = library_file_name("audio_cd");
         }
         break;
         case command_open_file_mp3:
         case command_open_file_rtp:
         {
            strDecoder = library_file_name("audio_libmpg123");
         }
         break;
         case command_open_file_vqf:
            //m_pplugin = memory_new _vmstwinvqdec::plugin();
            return false;
            break;
         case command_open_file_wm:
         {
            strDecoder = library_file_name("audio_window_media");
         }
         break;
         case command_open_file_wav:
         {
            strDecoder = library_file_name("audio_wave");
         }
         break;
         default:
            return false;
            break;
         }

         auto pdecoderplugin = paudio->audiowave()->m_pdecoderset->LoadPlugin(strDecoder);

         if (!pdecoderplugin)
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

         pplugin->__refer(pplugin->m_pwaveout, m_pwaveout);

         pplugin->audio_initialize();

         pplugin->audio_seek_begin();

      }

      OnEvent(e_player_event_open_decoder, pcommand);

      return pplugin.is_set();

   }


   void device_player::audio_initialize(::pointer<::file::file>ayloadFile)
   {

      UNREFERENCED_PARAMETER(payloadFile);

   }


   bool device_player::DecoderIsActive()
   {

      if (::is_null(m_pwaveout))
      {

         return false;

      }

      return m_pwaveout->out_plugin() != nullptr;

   }


   void device_player::audio_close()
   {

      try
      {

         m_pwaveout->out_set_plugin(nullptr);

      }
      catch (...)
      {


      }

   }


   void device_player::DecoderRun()
   {

   }


   void device_player::init_thread()
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

      if (!m_pwaveout->task_active())
      {

         if (!m_pwaveout->begin_synch(::e_priority_highest))
         {

            return false;

         }

      }

      return true;

   }


   void device_player::term_thread()
   {

      try
      {

         for (auto& plistener : m_listenera)
         {

            try
            {

               plistener->OnWavePlayerEvent(this, e_player_event_destroy);

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



   void device_player::post_command(player_command* pcommand)
   {

      post_object(e_message_player_command, 0, pcommand);

   }


   void device_player::on_player_command(::message::message* pmessage)
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


   bool device_player::player_command_procedure(player_command* pcommand)
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

            OnEvent(e_player_event_open_decoder_failed);

            break;

         }

         if (!DecoderIsActive())
         {

            pcommand->m_bResult = false;

            OnEvent(e_player_event_open_decoder_failed);

            break;

         }

         OnEvent(e_player_event_open_decoder, pcommand);

      }
      break;
      case command_execute_play:
      {

         informationf("audio_player command_execute_play");

         if (IsPlaying())
         {

            informationf("Error : Wrong State : audio_player audio already playing");

            pcommand->m_bResult = false;

            break;

         }

         if (m_pwaveout->out_plugin() == nullptr)
         {

            informationf("audio_player plugin isn't set : NOT going to play");

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

         if (m_pwaveout != nullptr)
         {

            m_pwaveout->out_close();

         }

         OnEvent(e_player_event_close_device);

      }
      break;
      default:
         ASSERT(false);
         break;
      }

      pcommand->SetEvents();

      return pcommand->m_bResult;

   }



   void device_player::ExecuteStop()
   {

      m_pwaveout->out_stop();

   }


   bool device_player::DeviceIsOpened()
   {

      return GetDeviceState() == e_device_state_opened;

   }


   bool device_player::DecoderIsOpened()
   {

      return GetDecoderState() == e_decoder_state_opened;

   }


   bool device_player::IsPlaying()
   {

      return m_pwaveout != nullptr && (GetDeviceState() == e_device_state_playing
         || GetDeviceState() == e_device_state_stopping
         || m_estate == e_state_fading_out_to_stop);

   }


   bool device_player::GetPlayEnable()
   {

      return GetDecoderState() == e_decoder_state_opened
         && !IsPlaying();

   }


   bool device_player::GetStopEnable()
   {

      return IsPlaying();

   }


   void device_player::post_event(enum_player_event eevent, player_command* pcommand)
   {

      ::pointer<player_command>spcommand(pcommand);

      post_message(e_message_player_event, (WPARAM)eevent, spcommand);

   }


   void device_player::on_event(::message::message* pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      ::pointer<player_command>pcommand(pusermessage->m_lparam);

      OnEvent((enum_player_event)pusermessage->m_wparam.m_number, pcommand);

   }


   void device_player::OnEvent(enum_player_event eevent, player_command* pcommand)
   {

      switch (eevent)
      {
      case e_player_event_open_device:
         informationf("device_player OnEvent e_player_event_open_device");
         SetDeviceState(e_device_state_opened);
         break;
      case e_player_event_open_device_failed:
         informationf("device_player OnEvent e_player_event_open_device_failed");
         SetDeviceState(e_device_state_initial);
         break;
      case e_player_event_open_decoder:
         informationf("device_player OnEvent e_player_event_open_decoder");
         SetDecoderState(e_decoder_state_opened);
         break;
      case e_player_event_start_device_failed:
      {

         informationf("device_player OnEvent e_player_event_start_device_failed");

         SetDeviceState(e_device_state_opened);
         SetState(e_state_initial);

      }
      break;
      case e_player_event_play:
      {

         informationf("device_player OnEvent e_player_event_play");

         SetDeviceState(e_device_state_playing);
         SetState(e_state_playing);

      }
      break;
      case e_player_event_stop:
      {

         informationf("device_player OnEvent e_player_event_stop");

         SetDeviceState(e_device_state_stopping);
         SetState(e_state_initial);
      }
      break;
      case e_player_event_fade_out_and_stop:
      {

         informationf("device_player OnEvent e_player_event_fade_out_and_stop");

         SetState(e_state_fading_out_to_stop);

      }
      break;
      case e_player_event_execute_pause:
      {

         informationf("device_player OnEvent EventDeviceOpen");

         SetDeviceState(e_device_state_paused);
         SetState(e_state_paused);

      }
      break;
      case e_player_event_execute_restart:
      {

         informationf("device_player OnEvent e_player_event_execute_restart");

         SetDeviceState(e_device_state_playing);


         SetState(e_state_playing);

      }
      break;
      case e_player_event_eof:
      {

         informationf("device_player OnEvent e_player_event_eof");

      }
      break;
      case e_player_event_playback_end:
      {

         informationf("device_player e_player_event_playback_end");

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
      case e_player_event_stopped:
      {

         informationf("device_player e_player_event_stopped");

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
      case e_player_event_close_device:
      {
         informationf("device_player OnEvent e_player_event_close_device");
         SetDeviceState(e_device_state_initial);
      }
      break;
      case e_player_event_close_decoder:
      {
         informationf("device_player OnEvent e_player_event_close_decoder");
         SetDecoderState(e_decoder_state_initial);
      }
      break;
      case e_player_event_open_decoder_failed:
      {
         informationf("device_player OnEvent e_player_event_open_decoder_failed");
         SetDecoderState(e_decoder_state_initial);
      }
      break;
      case e_player_event_destroy:
      {
         informationf("device_player OnEvent e_player_event_destroy");
         SetDeviceState(e_device_state_initial);
      }
      break;
      }

      for (auto plistener : m_listenera)
      {

         plistener->OnWavePlayerEvent(this, eevent, pcommand);

      }

   }


   void device_player::SetDeviceState(enum_device_state estate)
   {

      m_edevicestate = estate;

   }


   void device_player::SetDecoderState(enum_decoder_state estate)
   {
      m_epluginstate = estate;
   }

   void device_player::SetState(enum_state estate)
   {
      m_estate = estate;
   }


   device_player::enum_state device_player::GetState()
   {

      return m_estate;

   }


   device_player::enum_device_state device_player::GetDeviceState()
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


   device_player::enum_decoder_state device_player::GetDecoderState()
   {

      return m_epluginstate;

   }


   out* device_player::wave_out()
   {

      return m_pwaveout;

   }


   bool device_player::ExecuteIsPaused()
   {

      return m_estate == e_state_paused;

   }


   void device_player::_Stop()
   {

      if (IsPlaying())
      {

         m_pwaveout->post_message(e_message_player_stop);

      }

   }


   void device_player::FadeOutAndStop()
   {

      if (m_estate != e_state_playing)
      {

         return;

      }

      OnEvent(e_player_event_fade_out_and_stop);

      effect_diminuendo* pdiminuendo = memory_new effect_diminuendo;

      pdiminuendo->m_bEnd = true;
      pdiminuendo->m_bSustain = true;
      pdiminuendo->m_bTriggerEnd = true;
      pdiminuendo->SetLengthMillis(5000, m_pwaveout->out_get_buffer()->m_waveformatOut.m_waveformat.nSamplesPerSec);
      pdiminuendo->Initialize();

      m_pwaveout->out_set_stream_out_effect(pdiminuendo);

   }


   //device_player::listener::listener()
   //{

   //}


   //device_player::listener::~listener()
   //{

   //   //try
   //   //{

   //   //   synchronous_lock synchronouslock(this->synchronization());

   //   //   if (m_pwaveplayerForListener.is_set())
   //   //   {

   //   //      m_pwaveplayerForListener->erase_listener(this);

   //   //   }

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //}


   //void device_player::listener::OnWavePlayerEvent(player* pplayer, player::enum_player_event event, player_command* pcommand)
   //{

   //}


   //::wave::player* device_player::listener::get_wave_player()
   //{

   //   return nullptr;

   //}


   //device_player * device_player::listener::get_player()
   //{

   //   return m_pwaveplayerForListener;

   //}


   void device_player::add_listener(listener* plistener)
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


   void device_player::erase_listener(listener* plistener)
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


   void device_player::erase_all_listeners()
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


string device_player::GetDeviceStateString(enum_device_state edevicestate)
{

   switch (edevicestate)
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


string device_player::GetDecoderStateString(enum_decoder_state edecoderstate)
{

   switch (edecoderstate)
   {
   case e_decoder_state_initial:
      return "e_decoder_state_initial";
   case e_decoder_state_opened:
      return "e_decoder_state_opened";
   default:
      return "unknown decoder state";
   }

}


string device_player::GetStateString(enum_state estate)
{

   switch (estate)
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


::time device_player::player_get_time_for_synch()
{

   return m_pwaveout->out_get_time_for_synch();

}


//::time device_player::player_get_time_for_synch()
//{
//
//   return m_pwaveout->out_get_time_for_synch();
//
//}


::audio::plugin* device_player::plugin()
{

   if (m_pwaveout.is_null())
   {

      return nullptr;

   }

   return m_pwaveout->out_plugin();

}


void device_player::player_set_volume(double dVolume)
{

   m_pwaveout->m_dVolume = dVolume;

}


double device_player::player_get_volume()
{
   if(!m_pwaveout)
      {

      return 1.0;
}

      return m_pwaveout->m_dVolume;
   }


   ::time device_player::player_get_prebuffer_millis_length()
   {

      return m_pwaveout->get_prebuffer_millis_length();

   }


   u64 device_player::player_get_frame_byte_count()
   {

      return m_pwaveout->m_pwavebuffer->PCMOutGetInBufferSize();

   }

} // namespace wave



