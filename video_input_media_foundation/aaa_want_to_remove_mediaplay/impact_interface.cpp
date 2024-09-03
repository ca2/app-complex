#include "framework.h"

#include "aura/update.h"
//#include "audio/_.h"
#include "acme/constant/timer.h"
#include "acme/constant/id.h"


void global_on_media_playback_start()
{
}

namespace mediaplay
{


   impact_interface::impact_interface() :
      m_spgraphics(e_create),
      m_scalarTime(this,scalar_time),
      m_scalarVolume(this, scalar_audio_volume)
   {

      //common_construct();

   }


   impact_interface::~impact_interface()
   {

   }




   //impact_interface::impact_interface():
   //   m_spgraphics(e_create),
   //   m_scalarTime(this, scalar_time),
   //   m_scalarVolume(this, scalar_audio_volume)
   //{

   //   common_construct();

   //}


   //void impact_interface::common_construct()
   //{

   //   m_bIpiPostNewSong = true;

   //   m_bAlbumArt                   = true;

   //   m_etimerFade                  = e_timer_none;

   //   m_precordnotifyview           = ::place(new ::mediaplay::record_notify_impact());

   //   m_spgraphics->CreateCompatibleDC(nullptr);

   //   m_dBlend                      = 0.0;

   //   m_dAudioBlend                 = 1.0;

   //   m_pdocument                   = nullptr;

   //   m_bFadeOut                    = false;

   //   m_bWaitingToPlay              = false;

   //   m_bDestroy                    = false;

   //   m_bAutoSaveSongPosition       = false;

   //   m_bSavingPlaylist             = false;

   //}


   void impact_interface::initialize(::particle * pparticle)
   {

      auto estatus = ::user::impact::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      m_bIpiPostNewSong = true;

      m_bAlbumArt = true;

      m_etimerFade = e_timer_none;

      m_precordnotifyview = ::place(new ::mediaplay::record_notify_impact());

      m_spgraphics->CreateCompatibleDC(nullptr);

      m_dBlend = 0.0;

      m_dAudioBlend = 1.0;

      m_pdocument = nullptr;

      m_bFadeOut = false;

      m_bWaitingToPlay = false;

      m_bDestroy = false;

      m_bAutoSaveSongPosition = false;

      m_bSavingPlaylist = false;

      return ::success;

   }


   void impact_interface::destroy()
   {

      //return true;

   }


   void impact_interface::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &impact_interface::on_message_create);

      MESSAGE_LINK(WM_APP + 111, pchannel, this, &impact_interface::_001OnMessageX);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &impact_interface::on_message_destroy);

   }

   ::wave::player * impact_interface::get_wave_player()
   {

      return m_pwaveplayer;

   }


   ::mediaplay::data * impact_interface::get_data()
   {

      if(m_pdocument == nullptr)
      {

         return nullptr;

      }

      return m_pdocument->get_media_data();

   }


   void impact_interface::_ExecutePlay(bool bMakeVisible, ::duration time, bool bFadeIn)
   {

      __UNREFERENCED_PARAMETER(bMakeVisible);

      if(!OnExecuteBeforePlay())
      {

         return;

      }

      if(false && m_bAutoRecord)
      {

         try
         {

            _StartRecording();

         }
         catch(...)
         {

         }

      }

      data * pdata = get_data();

      switch(pdata->get_mode())
      {
      case data::mode_midi:
      {
      }
      break;
      case data::mode_wave:
      {

         ::wave::player_command_pointer command(e_create);

         command->Play(time, bFadeIn);

         get_wave_player()->post_command(command);

      }
      break;
      default:
         break;
      }

   }


   void impact_interface::on_delete_contents()
   {

      data * pdata = get_data();

      if(pdata == nullptr)
      {

         return;

      }

      switch(pdata->get_mode())
      {
      case data::mode_midi:
      {

         if (_ExecuteIsPlaying())
         {

            _ExecuteStop();

         }
         else
         {

            CloseDevice();

         }

      }
      break;
      case data::mode_wave:
      {

         if (_ExecuteIsPlaying())
         {

            _ExecuteStop();

         }
         else
         {

            CloseDevice();

         }

      }
      break;
      default:
         break;
      }

   }


   void impact_interface::CloseDevice()
   {

      data * pdata = get_data();

      if (pdata != nullptr)
      {

         switch (pdata->get_mode())
         {
         case data::mode_wave:
         {

            if (!is_null(get_wave_player()))
            {

               ::wave::player_command_pointer command(e_create);

               command->CloseDevice();

               get_wave_player()->post_command(command);

            }

         }
         break;
         default:
            break;
         }

      }

   }


   void impact_interface::_ExecuteStop()
   {

      data * pdata = get_data();

      if (pdata == nullptr)
      {

         return;

      }

      switch(pdata->get_mode())
      {
      case data::mode_wave:
      {

         ::wave::player_command_pointer command(e_create);

         command->Stop();

         get_wave_player()->post_command(command);

      }
      break;
      default:
         break;
      }

   }


   void impact_interface::_ExecuteStopAndQuit()
   {

   }


   void impact_interface::_ExecutePause()
   {

   }


   bool impact_interface::_ExecuteIsPaused()
   {

      return false;

   }


   bool impact_interface::_ExecuteGetPauseEnable()
   {

      data * pdata = get_data();

      if(pdata == nullptr)
      {

         return false;

      }

      switch(pdata->get_mode())
      {
      case data::mode_wave:
      {
         return false;
      }
      default:
         return false;

      }
   }


   bool impact_interface::_ExecuteGetPlayEnable()
   {

      data * pdata = get_data();

      if (pdata == nullptr)
      {

         return false;

      }

      switch(pdata->get_mode())
      {
      case data::mode_none:
      {

         return false;

      }
      case data::mode_wave:

         if (get_wave_player()->GetPlayEnable())
         {

            return true;

         }

         return false;

      default:

         return false;

      }

   }


   bool impact_interface::_ExecuteGetStopEnable()
   {

      data * pdata = get_data();

      if (pdata == nullptr)
      {

         return false;

      }

      switch(pdata->get_mode())
      {
      case data::mode_wave:

         if (get_wave_player() != nullptr && get_wave_player()->IsPlaying())
         {

            return true;

         }

         return false;

      default:

         return false;

      }

   }



   void impact_interface::_ExecuteListenMinusOne(bool bMinusOne)
   {
      bool bPreviousMinusOne = false;
      if(!DBListenMinusOne(false, m_pdocument->get_file_path(), bPreviousMinusOne)
            || is_different(bPreviousMinusOne, bMinusOne))
      {
         DBListenMinusOne(true, m_pdocument->get_file_path(), bMinusOne);
      }

   }

   void impact_interface::_ExecuteToggleListenMinusOne()
   {

      data * pdata = get_data();

      ASSERT(_ExecuteGetListenMinusOneEnable());

      if(_ExecuteGetListenMinusOneEnable())
      {

         switch(pdata->get_mode())
         {
         case data::mode_wave:
         {
            //            get_wave_player()->Devocalize(!get_wave_player()->IsDevocalized());
         }
         break;
         default:
            break;
         }
      }
   }


   bool impact_interface::_ExecuteGetListenMinusOneEnable()
   {

      bool bEnable = (get_wave_player() != nullptr && (get_wave_player()->IsPlaying() || get_wave_player()->DecoderIsOpened()));
      return bEnable;

   }


   bool impact_interface::GetListenMinusOneCheck()
   {

      data * pdata = get_data();

      if(_ExecuteGetListenMinusOneEnable())
      {

         switch(pdata->get_mode())
         {
         case data::mode_midi:
         {

            bool b;

            if (!DBListenMinusOne(false, pdata->get_file_path(), b))
            {

               return false;

            }
            else
            {

               return b;

            }

         }
         default:
         {

            return false;

         }

         }
      }
      else
      {

         return false;

      }

   }


   bool impact_interface::_ExecuteIsWaitingToPlay()
   {

      return m_bWaitingToPlay;

   }

   void impact_interface::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      if (::is_null(m_pplaylistdoc))
      {

         m_pplaylistdoc = papp->mediaplaylist()->m_pplaylistdoc;

      }

   }


   void impact_interface::on_message_destroy(::message::message * pmessage)
   {

      m_precordnotifyview.release();

      child_post_quit("save_song_position");

   }


   void impact_interface::start_saving_song_position()
   {

      defer_fork("save_song_position", [&]() { _thread_save_song_position(); });

   }


   void impact_interface::_thread_save_song_position()
   {

      try
      {

         while (::task_get_run())
         {

            m_durationLastOnSongPositionAlive= ::duration::now();

            try
            {

               if (!save_song_position())
               {

                  break;

               }

            }
            catch (...)
            {

            }

            task_sleep(5000_ms);

         }

      }
      catch (...)
      {

      }

   }


   ::duration impact_interface::get_millis_for_synch()
   {

      ::duration time = 0;

      data * pdata = get_data();

      switch(pdata->get_mode())
      {
      case data::mode_wave:

         time = get_wave_player()->get_out()->out_get_time_for_synch();

         break;

      default:

         break;

      }

      return time;

   }


   ::duration impact_interface::get_position_for_synch()
   {

      ::duration pos = 0;

      data * pdata = get_data();

      switch(pdata->get_mode())
      {
      case data::mode_wave:

         if(get_wave_player() != nullptr
               && get_wave_player()->get_out() != nullptr)
         {

            pos = get_wave_player()->get_out()->out_get_time_for_synch();

         }

         break;

      default:

         break;

      }

      return pos;

   }


   void impact_interface::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      //::duration tickNow= ::duration::now();


      switch(ptimer->m_uEvent)
      {
      case e_timer_lyric:
      {

         synchronous_lock synchronouslock(m_impactlineaStatus.mutex());

         if(m_impactlineaStatus.get_line_count() > 0 && m_impactlineaStatus.line_at(0) != nullptr)
         {

            rectangle_i32_array recta;

            m_impactlineaStatus.line_at(0)->OnTimerAnimate(nullptr, recta);

         }

      }

      break;

      case e_timer_audio_visual_fade_out:
      case e_timer_visual_fade_out:
      {

         ::duration tickPeriod;

         if (get_data() == nullptr || get_data()->get_mode() == data::mode_wave)
         {

            tickPeriod = 3_s; // Fade out completely ::durations.

         }
         else
         {

            tickPeriod = 8_s;

         }

         m_dBlend = 1.0 - m_durationFadeStart.period_rate(tickPeriod);

         if(m_dBlend <= 0.0)
         {

            m_dBlend = 0.0;

            KillTimer(ptimer->m_uEvent);

            m_etimerFade = e_timer_none;

         }

         set_need_redraw();

         post_redraw();

      }
      break;
      case e_timer_audio_visual_fade_in:
      case e_timer_visual_fade_in:
      {

         ::duration tickPeriod = 5_s; // Fade out completely time.

         double dBlend = m_durationFadeStart.period_rate(tickPeriod);

         if(dBlend >= 1.0)
         {

            m_dBlend = 1.0;

            KillTimer(ptimer->m_uEvent);

            m_etimerFade = e_timer_none;

            papp->mediaplaylist()->m_bRestartFadeIn = false;

         }
         else
         {

            m_dBlend = dBlend;

         }

         set_need_redraw();

         post_redraw();

      }
      break;
      }

      if(_ExecuteIsWaitingToPlay())
      {

         if(m_durationPlayWait.elapsed() > 0)
         {

            StartMusicRendering();

         }

      }

      if(m_rectangleaUpdate.get_size() > 0)
      {

         if(m_durationLastUpdate.elapsed() > 100)
         {

            rectangle_i32_array recta;

            UpdateScreen(recta, 0);

         }
      }
      ptimer->m_bRet = false;
   }




   void impact_interface::StartMusicRendering()
   {
   }


   bool impact_interface::UpdateScreen(rectangle_i32_array & recta, u32 uiRedraw)
   {

      __UNREFERENCED_PARAMETER(uiRedraw);

      m_rectangleaUpdate.add(recta);

      ::duration tickNow= ::duration::now();

      if(m_rectangleaUpdate.get_size() <= 0)
      {

         m_durationLastUpdate = tickNow;

         return true;

      }

      u32 dwElapseOptimization = 83;

      if(tickNow - m_durationLastUpdate < dwElapseOptimization)
      {

//      informationf("Great Optimization!\n");

         return true;

      }

      m_durationLastUpdate = tickNow;

      set_need_redraw();

      m_rectangleaUpdate.erase_all();

      return true;

   }


   bool impact_interface::backimpact_GetDestroy()
   {

      return m_bDestroy;

   }


   void impact_interface::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_f64 rectangleX;

      this->rectangle(rectangleX);

      if (m_precordnotifyview != nullptr)
      {

         m_precordnotifyview->set_window_position(zorder_none,
                                           maximum(0, rectangleX.width() - 20),
                                           maximum(0, rectangleX.height() - 100), 20, 100, SWP_NOZORDER);

      }

   }


   void impact_interface::backimpact_Feedback(::image * pimage)
   {
      __UNREFERENCED_PARAMETER(pimage);
   }

   void impact_interface::_001OnTopDraw(::image * pimage)
   {
      __UNREFERENCED_PARAMETER(pimage);
   }

   void impact_interface::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }

   void impact_interface::karaoke_bouncing_ball()
   {

   }

   void impact_interface::KaraokeGradualFilling()
   {

   }




   i32 impact_interface::InitGL()
   {

      return true;

   }

   ::draw2d::graphics * impact_interface::GetGdi()
   {
      return m_gdi;
   }


   u32 impact_interface::GetKaraokeCodePage(const ::string & lpsz)
   {

      __UNREFERENCED_PARAMETER(lpsz);
      //return KaraokeGetCodePage(lpsz);
      return 0;

   }

   u32 impact_interface::IdToCodePage(const ::string & psz)
   {
      __UNREFERENCED_PARAMETER(psz);
      ASSERT(false);
      //u32_array dwa;
      return 0xffffffff;
   }

   void impact_interface::SetKaraokeCodePage(u32 dw)
   {
      __UNREFERENCED_PARAMETER(dw);
      /*     CVmsDataServerInterface & db = ((CVmpLightApp *) System)->GetVmsDataServerInterface();

         COleVariant ::payload;
         payload.vt = VT_I4;
         payload.lVal = dw;

      //   db.set_data(
        //    _vmsp::CConfiguration::CfgKaraokeEncoding,
          //  GetLanguage(),
            //0,
            //::payload);
         db.set_data(
            _vmsp::CConfiguration::CfgKaraokeEncoding,
            0,
            0,
            ::payload);*/

   }


   void impact_interface::CopyLinkLocation()
   {
      /* trans   if (!KaraokeGetWnd()->OpenClipboard())
         {
            message_box( "Cannot open the Clipboard" );
            return;
         }

         // erase the current Clipboard contents
         if(!EmptyClipboard())
         {
            message_box( "Cannot is_empty the Clipboard" );
            CloseClipboard();
            return;
         }
         string str;
         UnicodeToACP(str, m_wstrCurrentLink);

         HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE,
                  (str.length() + 1) * sizeof(char));
              if (hglbCopy == nullptr)
              {
                  CloseClipboard();
                  return;
              }

              // lock the handle and copy the text to the buffer.

              char * lptstrCopy = (char *) GlobalLock(hglbCopy);
              ::memory_copy(lptstrCopy, (const ::string &) str,
                  str.length() * sizeof(char));
              lptstrCopy[str.length()] = (char) 0;    // nullptr character
              GlobalUnlock(hglbCopy);
         // ...
         // get the currently selected data
         // ...
         // For the appropriate data formats...
         if ( ::SetClipboardData( CF_TEXT, hglbCopy ) == nullptr )
         {
            message_box( "Unable to set Clipboard data" );
            CloseClipboard();
            return;
         }
         // ...
         CloseClipboard();   */
   }



   bool impact_interface::_ExecuteIsEntertaining()
   {

      return _ExecuteIsPlaying() || _ExecuteIsWaitingToPlay();

   }


   bool impact_interface::_ExecuteIsPlaying()
   {

      return (get_wave_player() != nullptr && get_wave_player()->IsPlaying());

   }


   bool impact_interface::DBListenMinusOne(bool bSave, const ::string & lpcszPathName, bool &bMinusOne)
   {

      throw ::not_implemented();

   }


   bool impact_interface::OnExecuteBeforePlay()
   {

      m_bFadeOut = false;

      if (::is_set(papp->mediaplaylist()))
      {

         if (papp->mediaplaylist()->m_pplaylistdoc != nullptr)
         {

            papp->mediaplaylist()->m_pstartup->m_bWasPlaying = true;

            ::file::path path = papp->mediaplaylist()->m_pplaylistdoc->m_pplaylistImpact->m_path;

            path = pcontext->m_papexcontext->defer_make_file_system_url(path);

            papp->mediaplaylist()->m_pstartup->m_strPlaylist = path;

            papp->mediaplaylist()->m_pstartup->m_strPlaylistPlaying = path;

            papp->mediaplaylist()->save_startup();

            papp->mediaplaylist()->m_pplaylistdoc->DoPlaylistSave();

         }

      }

      return true;

   }



   void impact_interface::on_media_playback_end()
   {

      try
      {

         if (get_wave_player() != nullptr && get_wave_player()->plugin() != nullptr)
         {

            synchronous_lock synchronouslock(papp->mutex());

            papp->m_mapMediaCallTitle.erase_key(get_wave_player()->plugin()->multimedia_get_origin_path());

            papp->m_mapMediaCallAlbumArt.erase_key(get_wave_player()->plugin()->multimedia_get_origin_path());

         }

      }
      catch (...)
      {


      }

      try
      {

         synchronous_lock synchronouslock(this->synchronization());

         m_imageaAlbum.erase_all();

      }
      catch (...)
      {


      }

      papp->mediaplaylist()->m_bRestartFadeIn = false;


      try
      {

         if (m_bAutoRecord)
         {

            _StopRecording();

         }

      }
      catch (...)
      {


      }


      try
      {

         ::pointer<::multimedia::inteprocess_channel>pipi = papp->m_pinterprocesscommunication;

         if(pipi.is_set())
         {

            // if (get_data()->get_mode() == ::mediaplay::data::mode_wave)
            {

               if (m_strLastTitle.has_char())
               {

                  pipi->on_media_playback_end(m_pathLastOrigin, m_strLastTitle, m_straLastPerformer, m_strAlbum);

               }

            }

         }

      }
      catch(...)
      {


      }

      try
      {

         CloseDevice();

      }
      catch (...)
      {

      }

      bool bFadeOut = m_bFadeOut;

      fork([=]()
      {

         //if (m_pplPlaying != nullptr && m_pplPlaying->m_bDiscard && m_pplPlaying->get_count() > 0)
         //{

         //   m_pplPlaying->erase_song(0);

         //   m_pplPlaying->save();

         //   if (::is_null(m_pplPlaying) || m_pplPlaying->get_count() <= 0)
         //   {

         //      m_pplPlaying = nullptr;

         //      m_pplaylistdoc->m_bPendingRestart = false;

         //      m_pplaylistdoc->restart(::e_source_initialize, true);

         //      return;

         //   }

         //}

         if(m_pplaylistdoc != nullptr && m_pplaylistdoc->defer_open_discard_erase_first())
         {

            return;

         }
         else if (m_pplaylistdoc != nullptr && m_pplaylistdoc->m_bPendingRestart)
         {

            m_pplPlaying = nullptr;

            m_pplaylistdoc->m_bPendingRestart = false;

            m_pplaylistdoc->restart(::e_source_initialize, true);

         }
         else if(bFadeOut)
         {

            m_pplPlaying = nullptr;

            OnFadeOutEnd();

         }
         else
         {

            m_pplPlaying = nullptr;

            playlist_on_playback_end();

         }

      });

   }


   bool impact_interface::get_short_title(string & strTitle, string_array & straArtist, string & strPlaylist)
   {

      if (get_data() != nullptr)
      {

         if (get_data()->get_mode() == ::mediaplay::data::mode_wave)
         {

            if (get_wave_player() == nullptr)
            {

               return false;

            }

            ::pointer<::audio_decode::decoder>pdecoder = get_wave_player()->plugin();

            if (pdecoder.is_null())
            {

               return false;

            }

            {

               ::payload v;

               if (pdecoder->multimedia_get_attribute(id_title, v))
               {

                  strTitle = v;

               }
               else
               {

                  strTitle = ::file::path(pdecoder->multimedia_get_origin_path()).title();

               }

            }

            {

               ::payload v;

               pdecoder->multimedia_get_attribute(id_artist, v);

               straArtist = v;

            }

            if (papp->mediaplaylist()->m_pplaylistdoc->play_playlist() != nullptr
                  && papp->mediaplaylist()->m_pplaylistdoc->play_playlist()->m_bDiscard)
            {

               strPlaylist.empty();

            }
            else if (strTitle.has_char())
            {

               strPlaylist = papp->mediaplaylist()->m_pplaylistdoc->play_playlist()->m_strName;

            }

            return strTitle.has_char();

         }

      }

      return false;

   }


   void impact_interface::defer_update_full_short_title()
   {

      string strTitle;

      string_array straArtist;

      string strPlaylist;

      get_short_title(strTitle, straArtist, strPlaylist);

      m_strFullShortTitle = strTitle + "/" + straArtist.implode(";") + "/" + strPlaylist;

   }


   void impact_interface::ipi_post_new_song()
   {

      if (get_data() != nullptr && get_data()->get_mode() == ::mediaplay::data::mode_wave)
      {

         ::fork(get_app(), [=]()
         {

            try
            {

               ::pointer<::multimedia::inteprocess_channel>pipi = papp->m_pinterprocesscommunication;

               if (pipi.is_set())
               {


                  ::pointer<::multimedia::inteprocess_channel>pipi = papp->m_pinterprocesscommunication;

                  string strTitle;

                  string_array straPerformer;

                  int iTry = 0;

retry:

                  if (get_wave_player() == nullptr)
                     return;

                  ::pointer<::audio_decode::decoder>pdecoder = get_wave_player()->plugin();

                  if (pdecoder.is_null())
                     return;

                  bool bMediaCall = false;

                  ::file::path strPathOrigin = (string)pdecoder->multimedia_get_origin_path();

                  {

                     synchronous_lock synchronouslock(papp->mutex());

                     strTitle = papp->m_mapMediaCallTitle[strPathOrigin];

                  }

                  if (strTitle.has_char())
                  {

                     bMediaCall = true;

                  }
                  else
                  {

                     ::payload v;



                     pdecoder->multimedia_get_attribute(id_title, v);

                     strTitle = v;

                     if (strTitle.is_empty())
                     {

                        strTitle = pdecoder->m_pathOrigin.title();

                     }

                  }


                  ::payload vPerformer;

                  {



                     pdecoder->multimedia_get_attribute(id_artist, vPerformer);

                     straPerformer = vPerformer;

                  }

                  if (vPerformer.is_new() && !bMediaCall)
                  {

                     if (iTry > 8)
                     {

                        m_bIpiPostNewSong = true;

                        return;

                     }

                     iTry++;

                     sleep(1_s);

                     goto retry;

                  }

                  ::image_pointer pimage;

                  ::payload vDib;

retry2:

                  {

                     pdecoder->multimedia_get_attribute(id_album_art, vDib);

                     pimage = vDib.image();

                  }



                  if (vDib.is_new() && !bMediaCall)
                  {

                     if (iTry > 8)
                     {

                        m_bIpiPostNewSong = true;

                        return;

                     }

                     iTry++;

                     sleep(1_s);

                     goto retry2;

                  }



                  ::payload vAlbum;

                  string strAlbum;

retry3:

                  {



                     pdecoder->multimedia_get_attribute(id_album, vAlbum);

                     strAlbum = vAlbum;

                  }

                  if (vAlbum.is_new() && !bMediaCall)
                  {

                     if (iTry > 8)
                     {

                        m_bIpiPostNewSong = true;

                        return;

                     }

                     iTry++;

                     sleep(1_s);

                     goto retry3;

                  }

                  ::payload vUrl;

                  string strUrl;

retry4:

                  {



                     pdecoder->multimedia_get_attribute(id_url, vUrl);

                     strUrl = vUrl;

                  }

                  if (vUrl.is_new() && !bMediaCall)
                  {

                     if (iTry > 8)
                     {

                        m_bIpiPostNewSong = true;

                        return;

                     }

                     iTry++;

                     sleep(1_s);

                     goto retry4;

                  }


                  synchronous_lock synchronouslock(this->synchronization());

                  if (m_bIpiPostNewSong || strTitle != m_strLastTitle || straPerformer != m_straLastPerformer || strAlbum != m_strAlbum)
                  {

                     m_bIpiPostNewSong = false;

                     m_strLastTitle = strTitle;

                     m_straLastPerformer = straPerformer;

                     m_strAlbum = strAlbum;

                     synchronouslock.unlock();

                     auto pfile = create_memory_file();

                     pcontext->m_papexcontext->save_image(pfile, pimage);

                     pipi->on_media_playback_start(strPathOrigin, m_strLastTitle, m_straLastPerformer, m_strAlbum, *pfile->get_primitive_memory(), strUrl);

                  }

               }


            }
            catch (...)
            {


            }

         });

      }

   }


   void impact_interface::OnMediaPlaybackStart(::wave::player_command * pcommand)
   {

      global_on_media_playback_start();

      OnMediaPlaybackStart();

      if(pcommand != nullptr
            && pcommand->m_ecommand == ::wave::command_execute_play
            && pcommand->m_bFadeIn)
      {

         StartVisualFadeIn(true);

      }
      else
      {

         StartVisualFadeIn(false);

      }

   }


   void impact_interface::OnMediaPlaybackStart()
   {

      ::pointer<::multimedia_playlist::track>ptrack;

      try
      {

         if (get_document() == nullptr)
         {

            return;

         }

         string strPath = get_document()->m_path;

         auto pmediaplaylist = papp->mediaplaylist();

         if (::is_set(pmediaplaylist) && ::is_set(pmediaplaylist->m_pplaylistdoc))
         {

            auto pplPlaying = pmediaplaylist->m_pplaylistdoc->play_playlist();

            if (pplPlaying != nullptr)
            {

               if (pplPlaying->m_tracka.is_index_ok(pplPlaying->m_iCurrentSong))
               {

                  papp->mediaplaylist()->m_pplaylistdoc->set_playback_playlist(pplPlaying);

                  ptrack = pplPlaying->m_tracka[pplPlaying->m_iCurrentSong];

                  if (ptrack.is_set())
                  {

                     string strTrackPath = ptrack->get_path();

                     if (strPath.case_insensitive_order(strTrackPath) != 0)
                     {

                        ptrack.release();

                     }

                  }

               }

            }

         }

         if (ptrack.is_set())
         {

            papp->mediaplaylist()->m_pplaylistlistview->m_rangeHighlight.m_itemrangea.erase_all();
            papp->mediaplaylist()->m_pplaylistlistview->m_rangeSelection.m_itemrangea.erase_all();

            user::item_range range;
            range.m_iLowerBound = papp->mediaplaylist()->m_pplaylistlistview->playlist_index();
            range.m_iUpperBound = range.m_iLowerBound;
            papp->mediaplaylist()->m_pplaylistlistview->m_rangeHighlight.add_item(range);
            papp->mediaplaylist()->m_pplaylistlistview->m_rangeSelection.add_item(range);

         }

      }
      catch (...)
      {
      }



      {

         synchronous_lock synchronouslock(this->synchronization());

         m_bIpiPostNewSong = true;

      }

      ipi_post_new_song();

      string strTitle;

      try
      {

         ::pointer<::mediaplay::document>pmediadoc = get_document();

         if (pmediadoc.is_set() &&
               ::is_set(pmediadoc->get_media_data()) &&
               pmediadoc->get_media_data()->m_emode == data::mode_wave)
         {

            ::pointer<::multimedia::decoder>pdecoder = pmediadoc->get_media_impact()->get_wave_player()->get_out()->out_plugin();

            if (pdecoder.is_set())
            {
               ::payload payload;

               pdecoder->multimedia_get_attribute(id_title, payload);

               strTitle = payload;



            }

         }

      }
      catch(...)
      {

      }

      if (strTitle.has_char())
      {

         try
         {

            if (ptrack.is_set())
            {

               ptrack->m_strName = strTitle;

            }

         }
         catch (...)
         {

         }

      }

      try
      {

         ::mediaplay::mediaplay * pmediaplay = papp->mediaplay();

         if (pmediaplay != nullptr)
         {

            ::user::impact_system * ptemplate = pmediaplay->get_document_template();

            if (ptemplate != nullptr)
            {

               ::user::document * pdocument = ptemplate->get_document();

               ::mediaplay::document * pmediadoc = dynamic_cast <::mediaplay::document*>(pdocument);

               pmediadoc->update_all_impacts(id_title);

            }

         }

      }
      catch (...)
      {

      }

      if (m_bAutoSaveSongPosition)
      {

         start_saving_song_position();

      }

   }


   void impact_interface::_001OnMessageX(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      if(pusermessage->m_wparam == 1)
      {

         rectangle_i32_array * precta = (rectangle_i32_array *) pusermessage->m_lparam.m_lparam;

         UpdateScreen(*precta, RDW_INVALIDATE );

         delete precta;

      }

      pusermessage->m_lresult = 0;

   }


   bool impact_interface::StartFadeIn(::mediaplaylist::info * pinfo)
   {

      auto pupdate = new_update();

      if(is_playing())
      {

         if(pinfo->m_uHint == id_play_and_fail_if_playing)
         {

            return false;

         }

         {

            synchronous_lock synchronouslock(this->synchronization());

            m_propertysetaBatch.erase_all();

            m_propertysetaBatch.add(__allocate< property_set >());

            auto & prop = m_propertysetaBatch.last();

            prop["command"] = "StartFadeIn";
            prop["::duration"] = pinfo->m_time;
            prop["song"] = pinfo->m_iCurrentSong;
            prop["hint"] = id_do_play;
            if (m_pplaylistdoc->m_bPendingRestart)
            {
               m_pplaylistdoc->m_bPendingRestart = false;
               prop["pending_restart"] = true;
            }
            prop["doc"] = this;
            prop["make_visible"] = true;
            prop["context"] = (i64) pinfo->m_context.m_esource;

         }

         if(!StartFadeOut(::mediaplay::ExecuteStop,::mediaplay::ExecuteProcessBatch))
         {

            return false;

         }

      }
      else
      {

         pinfo->m_bFadeIn = true;

         if(!papp->mediaplaylist()->m_pplaylistdoc->play(pinfo))
         {

            return false;

         }

      }

      return true;

   }


   void impact_interface::StartVisualFadeOut()
   {

      KillTimer(e_timer_audio_visual_fade_out);

      KillTimer(e_timer_visual_fade_out);

      KillTimer(e_timer_audio_visual_fade_in);

      KillTimer(e_timer_visual_fade_in);

      m_durationFadeStart.Now();

      SetTimer(e_timer_visual_fade_out, 50,nullptr);

      m_etimerFade = e_timer_visual_fade_out;

   }


   void impact_interface::StartVisualFadeIn(bool bAudio)
   {

      KillTimer(e_timer_audio_visual_fade_out);
      KillTimer(e_timer_visual_fade_out);
      KillTimer(e_timer_audio_visual_fade_in);
      KillTimer(e_timer_visual_fade_in);

      m_durationFadeStart.Now();

      if(bAudio)
      {
         SetTimer(e_timer_audio_visual_fade_in,100,nullptr);
         m_etimerFade = e_timer_audio_visual_fade_in;
      }
      else
      {
         SetTimer(e_timer_visual_fade_in,100,nullptr);
         m_etimerFade = e_timer_visual_fade_in;
      }

   }


   bool impact_interface::StartFadeOut(EExecute eexecuteNow, EExecute eexecuteAfterFadeOut)
   {

      m_bFadeOut = true;

      _Execute(eexecuteNow);

      m_eexecuteAfterFadeOut = eexecuteAfterFadeOut;

      m_durationFadeStart.Now();

      KillTimer(e_timer_audio_visual_fade_out);
      KillTimer(e_timer_visual_fade_out);
      KillTimer(e_timer_audio_visual_fade_in);
      KillTimer(e_timer_visual_fade_in);

      SetTimer(e_timer_audio_visual_fade_out, 100, nullptr);
      m_etimerFade = e_timer_audio_visual_fade_out;

      return true;

   }


   void impact_interface::OnFadeOutEnd()
   {

      if (m_pplaylistdoc != nullptr)
      {

         ::collection::index iStartSong = m_pplaylistdoc->play_playlist()->m_iCurrentSong;

         m_bFadeOut = false;

         if (!_Execute(m_eexecuteAfterFadeOut))
         {

            while (!PlaylistPlay(1))
            {

               if (m_pplaylistdoc->play_playlist()->m_iCurrentSong == iStartSong)
               {

                  break;

               }

            }

         }

      }
      else
      {

         playlist_on_playback_end();

      }

   }


   bool impact_interface::_Execute(EExecute eexecute)
   {
      switch(eexecute)
      {
      case ExecuteNext:
         return PlaylistPlay(1);
      case ExecutePrevious:
         return PlaylistPlay(-1);
      case ExecuteRoulette:
         return PlaylistPlayRandomItem();
      case ExecuteFirst:
         PlaylistPlayByIndex(0);
         break;
      case ExecuteLast:
         PlaylistPlayByIndex(-1);
         break;
      case ExecuteStop:
         _ExecuteStop();
         break;
      case ExecuteApplicationExit:
      {
         ::pointer<::simple_frame_window>pframe = top_level_frame();

         if (pframe.is_set())
         {
            pframe->::simple_frame_window::on_message_close(nullptr);
         }
         else
         {
            papp->set_finish();
         }
      }
      default:
         break;
      }
      return true;
   }

   void impact_interface::_StartRecording()
   {

      try
      {

         if(m_pwaverecorder->IsRecording())
            return;

         string strRec;

         data * pdata = get_data();

         if(pdata == nullptr)
            return;

         if (pdata->m_etype == data::type_rtp)
         {

            return;

         }

         ::file::path strPath = pdata->get_file_path();


         ::file::path strTitle = strPath.name();

         ::file::path strFolder = pcontext->m_papexcontext->dir()->appdata() /unitext("Gravacões de Karaokê");
         pcontext->m_papexcontext->dir()->create(strFolder);


         ::file::path strBase;

         strBase = strFolder / strTitle;

         i32 i = 1;
         while(true)
         {
            strRec.formatf("%s.%d.wav", strBase.c_str(), i);
            if(!pcontext->m_papexcontext->file()->exists(strRec))
               break;
            i++;
         }

         if(m_spfileRecord.is_null())
            m_spfileRecord.create(this);

         if(m_spfileRecord->open(strRec, ::file::e_open_create | ::file::e_open_write | ::file::e_open_binary))
         {

            {

               ::wave::recorder_command_pointer reccommand(e_create);

               reccommand->OpenWavFile(m_spfileRecord);

               m_pwaverecorder->post_command(reccommand);

            }

            {

               ::wave::recorder_command_pointer reccommand(e_create);

               reccommand->Record();

               m_pwaverecorder->post_command(reccommand);

            }

         }

      }
      catch(...)
      {
      }

   }

   void impact_interface::_StopRecording()
   {

      if (m_pwaverecorder == nullptr)
         return;

      if(!m_pwaverecorder->IsRecording())
         return;

      {

         ::wave::recorder_command_pointer reccommand(e_create);

         reccommand->Stop();

         m_pwaverecorder->post_command(reccommand);

      }

      m_spfileRecord.release();

   }


   void impact_interface::_ToggleAutoRecord()
   {
      _AutoRecord(!m_bAutoRecord);
   }

   void impact_interface::_AutoRecord(bool bRecord)
   {
      if(m_bAutoRecord && !bRecord)
      {
         m_bAutoRecord = false;
         if(_ExecuteIsPlaying())
         {
            _StopRecording();
         }
      }
      else if(!m_bAutoRecord && bRecord)
      {
         m_bAutoRecord = true;
         if(_ExecuteIsPlaying())
         {
            _StartRecording();
         }
      }
      // xyz
      // datastream()->set("General.AutoRecord", m_bAutoRecord);
   }

   void impact_interface::on_set_scalar(e_scalar i,double d,int iFlags)
   {
      __UNREFERENCED_PARAMETER(i);
      __UNREFERENCED_PARAMETER(d);
   }

   void impact_interface::get_scalar_minimum(e_scalar i, double & d)
   {
      __UNREFERENCED_PARAMETER(i);
      d = 0.0;
   }

   void impact_interface::get_scalar(e_scalar i, double & d)
   {
      __UNREFERENCED_PARAMETER(i);
      d = 0.0;
   }

   void impact_interface::get_scalar_maximum(e_scalar i, double & d)
   {
      __UNREFERENCED_PARAMETER(i);
      d = 0.0;
   }


   void impact_interface::on_set_scalar(e_scalar i,i64 iValue,int iFlags)
   {

      __UNREFERENCED_PARAMETER(i);
      __UNREFERENCED_PARAMETER(iValue);

   }

   void impact_interface::get_scalar_minimum(e_scalar i, i64 & iValue)
   {

      __UNREFERENCED_PARAMETER(i);
      __UNREFERENCED_PARAMETER(iValue);

   }

   void impact_interface::get_scalar(e_scalar i, i64 & iValue)
   {

      __UNREFERENCED_PARAMETER(i);
      __UNREFERENCED_PARAMETER(iValue);

   }

   void impact_interface::get_scalar_maximum(e_scalar i, i64 & iValue)
   {

      __UNREFERENCED_PARAMETER(i);
      __UNREFERENCED_PARAMETER(iValue);

   }

   bool impact_interface::is_ok_for_rendering()
   {
      if(m_pdocument == nullptr)
         return false;
      try
      {
         if(m_pdocument->m_bWriting)
            return false;
      }
      catch(...)
      {
         return false;
      }
      if(m_pdocument->get_typed_data < ::mediaplay::data > () == nullptr)
         return false;
      bool bIsWriting = true;
      try
      {
         bIsWriting = m_pdocument->get_media_data()->is_writing();
      }
      catch(...)
      {
         bIsWriting = true;
      }
      return !bIsWriting;
   }


   i32 impact_interface::KaraokeGetLyricsDelay()
   {

      return m_iDelay;

   }


   bool impact_interface::save_song_position()
   {

      try
      {

         if (!_ExecuteIsPlaying() || !m_bAutoSaveSongPosition)
         {

            return false;

         }

         if (papp->mediaplaylist() == nullptr)
         {

            return false;

         }

         if (papp->mediaplaylist()->m_pplaylistdoc == nullptr)
         {

            return false;

         }

         if(m_bSavingPlaylist)
         {

            return true;

         }

         if(m_durationLastPlaylistSaving.elapsed() < 4000)
         {

            return true;

         }

         m_durationLastPlaylistSaving= ::duration::now();

         KEEP(m_bSavingPlaylist);

         {

            data * pdata = get_data();

            if (pdata != nullptr)
            {

               if (m_etimerFade != e_timer_visual_fade_out && m_etimerFade != e_timer_audio_visual_fade_out)
               {

                  if (get_data()->m_emode == ::mediaplay::data::mode_wave && get_wave_player() != nullptr && get_wave_player()->get_out()->get_prebuffer_millis_length() > 5000)
                  {

                     i64 iPosition = (i64) ( get_wave_player()->get_out()->out_get_time_for_synch());

                     i64 iLength = (i64) ( get_wave_player()->get_out()->get_prebuffer_millis_length());

                     if (m_dBlend > 0.001 && iPosition - iLength >= -5000)
                     {

                        StartVisualFadeOut();

                     }

                  }

               }

               ::duration time = get_millis_for_synch();

               ::duration pos = get_position_for_synch();

               ::mediaplaylist::document * pdocument = papp->mediaplaylist()->m_pplaylistdoc;

               if (pdocument != nullptr && !pdocument->m_bPendingRestart && (pdocument->play_playlist() == nullptr || !pdocument->play_playlist()->m_bDiscard))
               {

                  {

                     auto & pstartup = papp->mediaplaylist()->m_pstartup;

                     synchronous_lock synchronouslock(papp->mediaplaylist());
                     
                     ::file::path path = pdocument->m_pathFile;

                     path = pcontext->m_papexcontext->defer_make_file_system_url(path);

                     pstartup->set(path + ".current_song_millis") = time;

                     pstartup->set(path + ".current_song_position") = pos;

                     if (::is_null(pdocument->playback_playlist()))
                     {

                        return false;

                     }

                     pdocument->playback_playlist()->set_int("current_song_millis", (i64) time);

                     pdocument->playback_playlist()->save();

                  }

                  papp->mediaplaylist()->save_startup();

                  pdocument->do_save(nullptr, true);

               }

            }

         }

      }
      catch(...)
      {

      }

      return true;

   }


   bool impact_interface::is_playing()
   {

      return _ExecuteIsPlaying();

   }


   bool impact_interface::PlaylistOnBeforePlay(mediaplaylist::info * pinfo)
   {

      return true;

   }


   mediaplaylist::e_play impact_interface::PlaylistPlay(mediaplaylist::info * pinfo)
   {

      ::mediaplay::document * pmediadoc = dynamic_cast <::mediaplay::document *>(get_document());

      if(pmediadoc != nullptr)
      {

         auto pupdate = new_update();

         if(pinfo->m_uHint == id_do_play)
         {

            if(is_playing())
            {

               pmediadoc->save_modified();

               {

                  synchronous_lock synchronouslock(this->synchronization());

                  m_propertysetaBatch.erase_all();

                  m_propertysetaBatch.add(__allocate< property_set >());

                  property_set & prop = m_propertysetaBatch.last();

                  prop["command"] = pinfo->m_bFadeIn ? "StartFadeIn" : "PlaylistPlay";
                  prop["doc"] = pinfo->m_pdocument;
                  prop["song"] = pinfo->m_iCurrentSong;
                  prop["path"] = pinfo->m_strFilePath;
                  prop["hint"] = pinfo->m_uHint;
                  prop["pending_restart"] = m_pplaylistdoc->m_bPendingRestart;
                  pinfo->m_bPendingRestart = m_pplaylistdoc->m_bPendingRestart;
                  m_pplaylistdoc->m_bPendingRestart = false;
                  prop["make_visible"] = pinfo->m_bMakeVisible;
                  prop["::duration"] = pinfo->m_time;
                  prop["context"] = (i64)pinfo->m_context.m_esource;

               }

               StartFadeOut(::mediaplay::ExecuteStop, ::mediaplay::ExecuteProcessBatch);

               return mediaplaylist::play_success;

            }

            try
            {

               ::payload payloadFile;

               payloadFile["url"] = pinfo->m_strFilePath;

               payloadFile["::duration"] = pinfo->m_time;

               if(!on_open_document(payloadFile))
               {

                  //on_media_playback_end();

                  return mediaplaylist::play_error_continue;

                  /*string str;
                  str = "*file open error";
                  wait_message_dialog dialog(e_create);
                  dialog.m_dwDelay = 5000;
                  ::property_set propset;
                  propset["message"] = str;
                  dialog.show("system\\wait_dialog.html", propset);
                  if(dialog.m_strResponse == "continue"
                  || dialog.m_strResponse == "timeout")
                  {
                     return PlaylistPlayErrorContinue;
                  }
                  else
                  {
                     return PlaylistPlayErrorCancel;
                  }*/
               }
            }
            catch(::file::exception *)
            {
               return mediaplaylist::play_error_continue;
               /*string str;
               pe->get_error_message(str);
                  str = "An error occurred while opening file: " + str;
                  wait_message_dialog dialog(e_create);
                  dialog.m_dwDelay = 5000;
                  ::property_set propset;
                  propset["message"] = str;
                  dialog.show("system\\wait_dialog.html", propset);
                  if(dialog.m_strResponse == "continue"
                  || dialog.m_strResponse == "timeout")
                  {
                     return PlaylistPlayErrorContinue;
                  }
                  else
                  {
                     return PlaylistPlayErrorCancel;
                  }*/
            }

            if(string_begins(pinfo->m_strFilePath,"spotify_track:"))
            {

               _ExecutePlay(true, 0, pinfo->m_bFadeIn);

            }
            else
            {

               _ExecutePlay(true, pinfo->m_time, pinfo->m_bFadeIn);

            }

         }
         else if(pinfo->m_uHint == id_play_if_not_playing)
         {

            if(!_ExecuteIsEntertaining())
            {

               ::payload payloadFile;

               payloadFile["url"] = pinfo->m_strFilePath;

               payloadFile["::duration"] = pinfo->m_time;

               if(!on_open_document(payloadFile))
               {

                  return mediaplaylist::play_error_cancel;

               }

               //if(string_begins(pinfo->m_strFilePath,"spotify_track:"))
               //{

               //   _ExecutePlay(true, 0, pinfo->m_bFadeIn);

               //}
               //else
               {

                  _ExecutePlay(true, pinfo->m_time, pinfo->m_bFadeIn);

               }

            }
            else
            {

               return mediaplaylist::play_success;

            }

         }

      }

      return mediaplaylist::play_success;

   }


   void impact_interface::PlaylistOnBeforeOpen()
   {
      ::mediaplaylist::player::PlaylistOnBeforeOpen();
   }

   bool impact_interface::PlaylistHasBatch()
   {

      synchronous_lock synchronouslock(this->synchronization());

      return m_propertysetaBatch.has_elements();

   }

   bool impact_interface::PlaylistStepBatch()
   {

      bool bPlay = false;

      mediaplaylist::info info;

      {

         synchronous_lock synchronouslock(this->synchronization());

         if (!PlaylistHasBatch())
            return false;

         property_set prop;

         {

            synchronous_lock synchronouslock(this->synchronization());

            prop = *m_propertysetaBatch[0];

            m_propertysetaBatch.erase_at(0);

         }

         if (prop["command"] == "runnable")
         {

            ::particle * pparticle = prop["runnable"].cast < ::object >();

            if (pparticle)
            {

               pparticle->run();

            }

         }
         else if (prop["command"] == "PlaylistPlay"
                  || prop["command"] == "StartFadeIn")
         {

            bPlay = true;

            info.m_pdocument = prop["doc"].cast < mediaplaylist::document >();
            info.m_strFilePath = prop["path"];
            info.m_iCurrentSong = prop["song"];
            info.m_uHint = prop["hint"];
            if ((bool)prop["pending_restart"] && m_pplaylistdoc != nullptr)
            {
               m_pplaylistdoc->m_bPendingRestart = true;
            }
            info.m_bMakeVisible = prop["make_visible"];
            info.m_time = prop["::duration"].get_double();
            info.m_context += (::e_source) (prop["context"].i64());
            info.m_bFadeIn = prop["command"] == "StartFadeIn";

         }
         else if (prop["command"] == "DeferRestartOnWasPlaying")
         {

            ::fork(get_app(), [=]()
            {

               papp->mediaplaylist()->GetCurrentPlaylist(false)->defer_restart_on_was_playing();

            });

         }

      }

      if (bPlay)
      {

         auto result = PlaylistPlay(&info);

         if(result == mediaplaylist::play_success)
         {

            return true;

         }
         else if (result == mediaplaylist::play_error_continue)
         {

            return false;

         }

      }

      return true;

   }


   bool impact_interface::PlaylistDeferBatch()
   {

      if(!PlaylistHasBatch())
      {

         return false;

      }


      while(true)
      {

         if(PlaylistStepBatch())
            break;

         if (!PlaylistHasBatch())
         {

            return false;

         }


      }

      return true;

   }


   void impact_interface::playlist_on_playback_end()
   {

      if(!PlaylistDeferBatch())
      {

         ::mediaplaylist::player::playlist_on_playback_end();

      }

   }


   bool impact_interface::on_open_document(const ::payload & payloadFile)
   {

      ::mediaplay::document * pmediadoc = dynamic_cast <::mediaplay::document*>(get_document());

      return pmediadoc->on_open_document(payloadFile);

   }


   void impact_interface::attach_playlist(::mediaplaylist::document * pplaylistdoc)
   {
      pplaylistdoc->set_player(this);
      m_pplaylistdoc = pplaylistdoc;
   }



   double impact_interface::get_alpha(::user::interaction * puiTarget)
   {

      if (m_etimerFade != e_timer_none)
      {

         return m_dBlend;

      }
      else
      {

         return 1.0;
      }

   }


   void impact_interface::on_alpha_target_initial_frame_position()
   {

      m_dBlend = 1.0;

   }



} // namespace mediaplay




