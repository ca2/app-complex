#include "framework.h"

#include "apex/message.h"


namespace wave
{


   logical_player::logical_player()
   {

      m_timeDeviceStart =-1;
      m_timeStart = 0;

      //m_bMessageThread = true;

      m_estate = e_state_initial;
      m_epurpose = purpose_default;

      //m_bSynch = false;

   }


   logical_player::~logical_player()
   {

   }


   void logical_player::prepare_wave_player(e_purpose epurpose)
   {

      synchronous_lock synchronouslock(this->synchronization());

      //if (thread_active())
      //{

      //   return ::success_none;

      //}

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

      //if (!begin_synch())
      //{

      //   return ::error_failed;

      //}

      return ::success;

   }



   //void logical_player::install_message_routing(::channel* pchannel)
   //{

   //   ::thread::install_message_routing(pchannel);

   //   MESSAGE_LINK(e_message_player_command, pchannel, this, &logical_player::on_player_command);
   //   MESSAGE_LINK(e_message_player_event, pchannel, this, &logical_player::on_event);

   //}


   bool logical_player::DecoderOpen(player_command* pcommand)
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

         if (!pplugin->audio_matches(this))
         {

            auto presampler = __create_new<::audio::resampler>();

            presampler->m_pplugin = pplugin;

            paudio->sound_track()->m_paudiomixer->init_child(presampler);

            //presampler->audio_initialize();

            //presampler->audio_seek_begin();

            pplugin = presampler;

         }

         //m_pwaveout->out_set_plugin(pplugin);
         m_ppluginPlay = pplugin;

      }

      OnEvent(e_player_event_open_decoder, pcommand);

      return m_ppluginPlay.is_set();

   }
   bool logical_player::audio_initialize()
   {
      return ::audio::plugin::audio_initialize();

   }

   void logical_player::audio_initialize(::pointer<::file::file>ayloadFile)
   {

      __UNREFERENCED_PARAMETER(payloadFile);

   }


   bool logical_player::DecoderIsActive()
   {

      return m_ppluginPlay.is_set();
      //if (::is_null(m_pwaveout))
      //{

      //   return false;

      //}

      //return m_pwaveout->out_plugin() != nullptr;

   }


   void logical_player::audio_close()
   {

      m_ppluginPlay.release();
      try
      {

         //m_pwaveout->out_set_plugin(nullptr);

      }
      catch (...)
      {


      }

   }


   void logical_player::DecoderRun()
   {

   }


   out * logical_player::wave_out()
   {

      return m_pwaveout;

   }


   u64 logical_player::player_get_frame_byte_count()
   {

      return m_uFrameByteCount;

   }


   void logical_player::post_command(player_command* pcommand)
   {

      player_command_procedure(pcommand);

   }


   bool logical_player::player_command_procedure(player_command* pcommand)
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

         TRACE("audio_player command_execute_play");

         if (IsPlaying())
         {

            TRACE("Error : Wrong State : audio_player audio already playing");

            pcommand->m_bResult = false;

            break;

         }

         if (m_ppluginPlay == nullptr)
         {

            TRACE("audio_player plugin isn't set : NOT going to play");

            pcommand->m_bResult = false;

            break;

         }

         m_ppluginRead = m_ppluginPlay;

         post_event(player::e_player_event_play, pcommand);

      }
      break;
      case command_execute_stop:
      {

         FadeOutAndStop();

      }
      break;
      case command_execute_pause:
      {

         m_ppluginRead.release();

      }
      break;
      case command_execute_restart:
      {

         m_ppluginRead->audio_seek_begin();

      }
      break;
      case command_close_device:
      {

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


   void logical_player::ExecuteStop()
   {

      m_ppluginRead.release();

   }


   bool logical_player::DeviceIsOpened()
   {

      return GetDeviceState() == e_device_state_opened;

   }


   bool logical_player::DecoderIsOpened()
   {

      return GetDecoderState() == e_decoder_state_opened;

   }


   bool logical_player::IsPlaying()
   {

      return (GetDeviceState() == e_device_state_playing
         || GetDeviceState() == e_device_state_stopping
         || m_estate == e_state_fading_out_to_stop);

   }


   bool logical_player::GetPlayEnable()
   {

      return GetDecoderState() == e_decoder_state_opened
         && !IsPlaying();

   }


   bool logical_player::GetStopEnable()
   {

      return IsPlaying();

   }


   void logical_player::post_event(enum_player_event eevent, player_command* pcommand)
   {

      OnEvent(eevent, pcommand);

   }


   //void logical_player::on_event(::message::message* pmessage)
   //{

   //   ::pointer<::user::message>pusermessage(pmessage);

   //   ::pointer<player_command>pcommand(pusermessage->m_lparam);

   //   OnEvent((e_event)pusermessage->m_wparam.m_number, pcommand);

   //}


   void logical_player::OnEvent(enum_player_event eevent, player_command* pcommand)
   {

      switch (eevent)
      {
      case e_player_event_open_device:
         TRACE("logical_player OnEvent e_player_event_open_device");
         SetDeviceState(e_device_state_opened);
         break;
      case e_player_event_open_device_failed:
         TRACE("logical_player OnEvent e_player_event_open_device_failed");
         SetDeviceState(e_device_state_initial);
         break;
      case e_player_event_open_decoder:
         TRACE("logical_player OnEvent e_player_event_open_decoder");
         SetDecoderState(e_decoder_state_opened);
         break;
      case e_player_event_start_device_failed:
      {

         TRACE("logical_player OnEvent e_player_event_start_device_failed");

         SetDeviceState(e_device_state_opened);
         SetState(e_state_initial);

      }
      break;
      case e_player_event_play:
      {

         TRACE("logical_player OnEvent e_player_event_play");

         SetDeviceState(e_device_state_playing);
         SetState(e_state_playing);

      }
      break;
      case e_player_event_stop:
      {

         TRACE("logical_player OnEvent e_player_event_stop");

         SetDeviceState(e_device_state_stopping);
         SetState(e_state_initial);
      }
      break;
      case e_player_event_fade_out_and_stop:
      {

         TRACE("logical_player OnEvent e_player_event_fade_out_and_stop");

         SetState(e_state_fading_out_to_stop);

      }
      break;
      case e_player_event_execute_pause:
      {

         TRACE("logical_player OnEvent EventDeviceOpen");

         SetDeviceState(e_device_state_paused);
         SetState(e_state_paused);

      }
      break;
      case e_player_event_execute_restart:
      {

         TRACE("logical_player OnEvent e_player_event_execute_restart");

         SetDeviceState(e_device_state_playing);


         SetState(e_state_playing);

      }
      break;
      case e_player_event_eof:
      {

         TRACE("logical_player OnEvent e_player_event_eof");

      }
      break;
      case e_player_event_playback_end:
      {

         TRACE("logical_player e_player_event_playback_end");

         m_ppluginRead.release();

         m_pstreameffectOut.release();

         SetDeviceState(e_device_state_initial);

         if (m_ppluginPlay)
         {

            SetDecoderState(e_decoder_state_opened);

            m_ppluginPlay->audio_seek_begin();

         }

         SetState(e_state_initial);

         m_estate = e_state_initial;

      }
      break;
      case e_player_event_stopped:
      {

         TRACE("logical_player e_player_event_stopped");

         //m_pwaveout->out_close();
         m_ppluginRead.release();

         //if (m_pwaveout->out_plugin() != nullptr)
         if(m_ppluginRead)
         {

            //m_pwaveout->out_plugin()->audio_stop();

            SetDecoderState(e_decoder_state_opened);

            //m_pwaveout->out_plugin()->audio_seek_begin();
            m_ppluginPlay->audio_seek_begin();

         }

         SetState(e_state_initial);

         SetDeviceState(e_device_state_initial);

      }
      break;
      case e_player_event_close_device:
      {
         TRACE("logical_player OnEvent e_player_event_close_device");
         SetDeviceState(e_device_state_initial);
      }
      break;
      case e_player_event_close_decoder:
      {
         TRACE("logical_player OnEvent e_player_event_close_decoder");
         SetDecoderState(e_decoder_state_initial);
      }
      break;
      case e_player_event_open_decoder_failed:
      {
         TRACE("logical_player OnEvent e_player_event_open_decoder_failed");
         SetDecoderState(e_decoder_state_initial);
      }
      break;
      case e_player_event_destroy:
      {
         TRACE("logical_player OnEvent e_player_event_destroy");
         SetDeviceState(e_device_state_initial);
      }
      break;
      }

      for (auto plistener : m_listenera)
      {

         plistener->
            OnWavePlayerEvent(this, eevent, pcommand);

      }

   }


   void logical_player::SetDeviceState(enum_device_state estate)
   {

      m_edevicestate = estate;

   }


   void logical_player::SetDecoderState(enum_decoder_state estate)
   {
      m_epluginstate = estate;
   }

   void logical_player::SetState(enum_state estate)
   {
      m_estate = estate;
   }


   logical_player::enum_state logical_player::GetState()
   {

      return m_estate;

   }



   //memsize logical_player::audio_read2(LPVOID lpvoidBuffer, memsize uiBufferSize)
   //{

   //   ::zero(lpvoidBuffer, uiBufferSize);

   //   auto uRead = ::audio::plugin::audio_read2(lpvoidBuffer, uiBufferSize);

   //   if (m_timeDeviceStart < 0 && m_iAudioRead > 0)
   //   {

   //      m_timeDeviceStart = (double)paudio->sound_track()->m_paudiomixer->audio_get_position_read();

   //      //if (m_ppluginRead)
   //      {

   //         m_iDecodeLength = m_ppluginRead->m_iDecodeLength;

   //      }

   //   }



   //   if (m_pstreameffectOut.is_set())
   //   {

   //      m_pstreameffectOut->CallProcess16bits((short*)lpvoidBuffer, uRead /
   //         (audio_get_bits_per_sample() * audio_get_channel_count() / 8));

   //      if (m_pstreameffectOut->IsEndOfEffect())
   //      {

   //         post_event(player::e_player_event_playback_end);
   //         //{

   //         return 0;

   //         //}

   //         //if(m_pstreameffectOut->m_bDeleteOnEnd)
   //         //{

   //         //   m_pstreameffectOut.release();

   //         //}

   //      }

   //   }

   //   return uRead;

   //}


   memsize logical_player::audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize)
   {

      if (!m_ppluginRead)
      {

         return 0;

      }


      memsize uRead = 0;

      byte* poutput = (byte*)lpvoidBuffer;

      auto uBufferSize = uiBufferSize;

      ::audio::plugin* pplugin = m_ppluginRead;

      if (!pplugin->audio_is_initialized())
      {

         init_child(pplugin);

      }

      if (pplugin != nullptr && !pplugin->audio_eof())
      {

         memsize uPos = 0;

         byte* pdst = &poutput[uPos];

         memsize uToRead = uBufferSize;

         uRead = pplugin->audio_read(pdst, uToRead);

         m_iRead += uRead;

         m_iAudioRead += uRead;

         if (pplugin->audio_eof())
         {

            TRACE("mixer plugin:EOF");

            audio_on_event(::audio::event_eof);

            post_event(player::e_player_event_playback_end);

         }

      }

      if (m_timeDeviceStart < 0 && m_iAudioRead > 0)
      {

         auto iParentAudioRead = m_ppluginParent->m_iAudioRead;

         m_timeDeviceStart = (double) (iParentAudioRead / m_pwaveout->m_pprebuffer->get_frame_size()) / ((double) m_pwaveout->m_pwaveformat->m_waveformat.nSamplesPerSec);

         //auto position = paudio->sound_track()->m_pwaveplayer->player_get_time_for_synch();

         //m_timeDeviceStart += m_iAudioRead - uRead;

         //if (m_ppluginRead)
         {

            m_iDecodeLength = m_ppluginRead->m_iDecodeLength;

         }

      }



      if (m_pstreameffectOut.is_set())
      {

         m_pstreameffectOut->CallProcess16bits((short*)lpvoidBuffer, uRead /
            (audio_get_bits_per_sample() * audio_get_channel_count() / 8));

         if (m_pstreameffectOut->IsEndOfEffect())
         {

            post_event(player::e_player_event_playback_end);
            //{

            return 0;

            //}

            //if(m_pstreameffectOut->m_bDeleteOnEnd)
            //{

            //   m_pstreameffectOut.release();

            //}

         }

      }

      return uiBufferSize;

   }



   logical_player::enum_device_state logical_player::GetDeviceState()
   {

      if (m_edevicestate == e_device_state_playing
         || m_edevicestate == e_device_state_stopping)
      {

         //if (m_pwaveout->out_get_state() != out::e_state_playing
         //   && m_pwaveout->out_get_state() != out::e_state_stopping)
         //{

         //   m_edevicestate = e_device_state_opened;

         //}

      }

      return m_edevicestate;

   }


   logical_player::enum_decoder_state logical_player::GetDecoderState()
   {

      return m_epluginstate;

   }


   //out* logical_player::get_out()
   //{

   //   return m_pwaveout;

   //}


   ::time logical_player::player_get_prebuffer_millis_length()
   {

      return paudio->sound_track()->m_pwaveplayer->player_get_prebuffer_millis_length();

   }


   bool logical_player::ExecuteIsPaused()
   {

      return m_estate == e_state_paused;

   }


   void logical_player::_Stop()
   {

      if (IsPlaying())
      {

         m_ppluginRead.release();

      }

      //   m_pwaveout->post_message(e_message_player_stop);

      //}

   }


   void logical_player::FadeOutAndStop()
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
      pdiminuendo->SetLengthMillis(5000, audio_get_samples_per_second());
      pdiminuendo->Initialize();

      m_pstreameffectOut = pdiminuendo;

   }


   //logical_player::listener::listener()
   //{

   //}


   //logical_player::listener::~listener()
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


   //void logical_player::listener::OnWavePlayerEvent(player* pplayer, player::enum_player_event event, player_command* pcommand)
   //{

   //}


   //::wave::player* logical_player::listener::get_wave_player()
   //{

   //   return nullptr;

   //}


   //logical_player * logical_player::listener::get_player()
   //{

   //   return m_pwaveplayerForListener;

   //}


   void logical_player::add_listener(listener* plistener)
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


   void logical_player::erase_listener(listener* plistener)
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


   void logical_player::erase_all_listeners()
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


   string logical_player::GetDeviceStateString(enum_device_state edevicestate)
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


   string logical_player::GetDecoderStateString(enum_decoder_state edecoderstate)
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


   string logical_player::GetStateString(enum_state estate)
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


   ::audio::plugin* logical_player::plugin()
   {

      return m_ppluginPlay;

      //if (m_pwaveout.is_null())
      //{

      //   return nullptr;

      //}

      //return m_pwaveout->out_plugin();

   }


   u32 logical_player::audio_get_samples_per_second() const
   {

      return paudio->sound_track()->m_paudiomixer->audio_get_samples_per_second();

   }


   u32                logical_player::audio_get_channel_count() const
   {
      return paudio->sound_track()->m_paudiomixer->audio_get_channel_count();
   }
   u32           logical_player::audio_get_bits_per_sample() const
   {
      return paudio->sound_track()->m_paudiomixer->audio_get_bits_per_sample();
   }
   //::time logical_player::player_get_time_for_synch()
   //{

   //   if (audio_get_samples_per_second() <= 0)
   //   {

   //      return 0;

   //   }

   //   auto position = player_get_time_for_synch();

   //   if (position < 0)
   //      return -1;

   //   return position * 1000.0 / audio_get_samples_per_second();


   //}


   ::time logical_player::player_get_time_for_synch()
   {

      if (m_timeDeviceStart < 0)
      {

         return 0;

      }

      auto & audio = Audio;

      if (::is_null(audio))
      {

         return 0;

      }

      auto psoundtrack = audio.sound_track();

      if (::is_null(psoundtrack))
      {

         return 0;

      }

      auto pwaveplayer = psoundtrack->m_pwaveplayer;

      if (::is_null(pwaveplayer))
      {

         return 0;

      }

      ::time positionDevice = pwaveplayer->player_get_time_for_synch();

      return positionDevice - m_timeDeviceStart + m_timeStart;

   }

} // namespace wave



