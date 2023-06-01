#include "framework.h"

#include "base/update.h" 


#ifdef LINUX
#include <locale.h>


double str_to_double(const ::string & str)
{

   string strAlternate(str);

   strAlternate.replace(".", localeconv()->decimal_point);

   return atof(strAlternate);

}
#else

double str_to_double(const ::string & str)
{

   return atof(str);

}

#endif

namespace mediaplay
{


   impact::impact()
   {

   }


   impact::~impact()
   {

   }

   
   void impact::initialize(::particle * pparticle)
   {

      auto estatus = ::mediaplay::impact_interface::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      m_bPlaylistStartupLoaded = false;

      m_bFranceExit = false;

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);
      m_impactlineaStatus.m_linea.add(__new(xfplayer_impact_line(&m_impactlineaStatus)));
      papp->m_pmediaplayview = this;

      return estatus;

   }


   void impact::install_message_routing(::channel * pchannel)
   {
      ::user::impact::install_message_routing(pchannel);
      ::mediaplay::impact_interface::install_message_routing(pchannel);

      //MESSAGE_LINK(e_message_size        , pchannel, this, &impact::on_message_size);
      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &impact::on_message_context_menu);
      //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &impact::on_message_set_cursor);

      add_command_prober("execute_previous", &impact::_001OnUpdateExecutePrevious);
      add_command_handler("execute_previous", &impact::_001OnExecutePrevious);
      add_command_prober("execute_next", &impact::_001OnUpdateExecuteNext);
      add_command_handler("execute_next", &impact::_001OnExecuteNext);
      add_command_prober("execute_play", &impact::_001OnUpdateExecutePlay);
      add_command_handler("execute_play", &impact::_001OnExecutePlay);
      add_command_prober("execute_stop", &impact::_001OnUpdateExecuteStop);
      add_command_handler("execute_stop", &impact::_001OnExecuteStop);
      add_command_prober("playlist_next", &impact::_001OnUpdatePlaylistNext);
      add_command_handler("playlist_next", &impact::_001OnPlaylistNext);
      add_command_prober("playlist_previous", &impact::_001OnUpdatePlaylistPrevious);
      add_command_handler("playlist_previous", &impact::_001OnPlaylistPrevious);
      add_command_prober("execute_roulette", &impact::_001OnUpdateExecuteRoulette);
      add_command_handler("execute_roulette", &impact::_001OnExecuteRoulette);
   }

#ifdef _DEBUG
   void impact::assert_ok() const
   {
      ::user::impact::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //_DEBUG



   bool impact::pre_create_window(::user::system * pusersystem)
   {

      return ::user::impact::pre_create_window(pusersystem);
   }


   ::pointer<::user::interaction>impact::KaraokeGetWnd()
   {

      return this;

   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

         if (ptopic->m_atom == id_delete_contents)
         {

            on_delete_contents();

         }
         else if (ptopic->m_atom == id_pre_close_document)
         {

            destroy();


            if (m_pwaverecorder != nullptr && m_pwaverecorder->IsRecording())
            {
               _StopRecording();
               m_pwaverecorder->m_eventStopped.wait(::duration((2000 + 197) * 20));
            }


            //if(_ExecuteIsEntertaining())
            {

               // _ExecuteStopAndQuit();

            }
            //else
            {

               try
               {

                  ::wave::player * pwaveplayer = get_wave_player();

                  if (pwaveplayer != nullptr)
                  {

                     pwaveplayer->set_finish();

                  }

               }
               catch (...)
               {
               }
            }

         }



         if(ptopic->m_atom == id_execute_stop)
         {

            _ExecuteStop();

         }
         else if(ptopic->m_atom == id_close_device)
         {
            CloseDevice();
         }
         else if(ptopic->m_atom == id_do_play)
         {
            _ExecutePlay(true, ptopic->payload(id_time), false);
         }
         else if(ptopic->m_atom == id_play_if_not_playing)
         {
            
            if(!_ExecuteIsPlaying())
            {

               _ExecutePlay(true, ptopic->payload(id_time), false);

            }

         }
         else if(ptopic->m_atom == id_get_topic_wave_player && pupdate->m_pobjectTopic == nullptr)
         {

            if(get_wave_player() == nullptr)
            {

               ::audio::compose_wave_player(m_pwaveplayer, this);

               get_wave_player()->prepare_wave_player(::audio::purpose_playback);

            }

            pupdate->m_pobjectTopic = get_wave_player();

         }
         else if(ptopic->m_atom == id_full_screen)
         {
            
            if(ptopic->payload(id_full_screen))
            {
               ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
            }
            else
            {
               ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);
            }

         }
         else if (ptopic->m_atom == id_after_open_document)
         {



         }


   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {
//      ::pointer<::message::size>psize(pmessage);

      //pmessage->previous();


      client_rectangle(m_rectangleKaraokeImpact);


      ::rectangle_f64 rectangleClient;
      client_rectangle(rectangleClient);
      ::rectangle_f64 rectangle = rectangleClient;

      rectangle.top = rectangle.bottom - 24;
      m_impactlineaStatus.m_pinteraction = this;
      m_impactlineaStatus.Prepare();
      m_impactlineaStatus.line_at(0)->SetPlacement(rectangle);


      m_rectangleKaraokeImpact.bottom -= 16;


   }

   /*void impact::_001OnPaint(::message::message * pmessage)
   {
      CPaintDC spgraphics(this); // device context for painting
      _001OnDraw(&spgraphics);
   }
   */


   void impact::on_message_create(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;




      ::mediaplay::impact_interface::m_pdocument = dynamic_cast < ::mediaplay::document * > (get_document());
      ::mediaplay::impact_interface::m_pdocument->m_pmediaplayview = this;


      //SetTimer(e_timer_lyric, 40, nullptr); // maximum. 25 fps
      //SetTimer(10, 784, nullptr);
      //SetTimer(::timer::hover, 100, nullptr);

      if (top_level_frame() != nullptr)
      {

         top_level_frame()->m_impactptraCommandHandlers.add_unique(this);

      }

      if (get_parent_frame() != nullptr)
      {

         get_parent_frame()->m_impactptraCommandHandlers.add_unique(this);

      }


   }
   void impact::on_message_context_menu(::message::message * pmessage)
   {
      ::pointer<::message::context_menu>pcontextmenu(pmessage);
      ::point_i32 point = pcontextmenu->GetPoint();
//      ::karaoke::lyric_impact_lines & lyriclines = GetLyricLines();
      ::point_i32 pointCursor;
      pointCursor = point;
      screen_to_client(&pointCursor);
      /* linux   if(m_lyrictemplatelines.hit_test(pointCursor, iLine, iToken, iChar)
            == ::user::e_line_hit_link)
         {
            string str;
            lyriclines.get_link(str, iLine, iToken, iChar);
            m_wstrCurrentLink = str;
            SimpleMenu menu(BaseMenuCentral::GetMenuCentral(this));
            if (menu.LoadMenu(m_uiPopupLink))
            {
               SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
               ASSERT(pPopup != nullptr);
               frame_window * pframe = get_parent_frame();
               pPopup->TrackPopupMenu(
                  point.x(), point.y(),
                  (::user::interaction_impl *) pframe);
            }
         }
         else
         {
            ::user::menu menu;
            if (menu.LoadMenu(m_uiPopup))
            {
               ::user::menu* pPopup = menu.GetSubMenu(0);
               ASSERT(pPopup != nullptr);
               frame_window * pframe = get_parent_frame();
               pPopup->TrackPopupMenu(
                  point.x(), point.y(),
                  (::user::interaction_impl *) pframe);
            }
         }*/

   }


   void impact::_001OnTabClick(i32 iTab)
   {

      if(iTab == 1)
      {

         output_error_message("Playlist");

      }

   }


   document * impact::get_document()
   {

      return dynamic_cast < document * > (::user::impact::get_document());

   }


   void impact::OnWavePlayerEvent(::wave::player * pplayer, ::wave::player::e_event eevent, ::wave::player_command * pcommand)
   {

      switch(eevent)
      {
      case ::wave::player::EventDestroy:
      {

         return;
      }

      case ::wave::player::EventOpenDecoder:
      {
         //get_wave_player()->m_pdecoder->m_pathOrigin = get_document()->m_filepath;

         if(pcommand->GetCommand() == ::wave::command_open_plugin)
         {

            ::file::path pathOrigin = get_wave_player()->plugin()->multimedia_get_origin_path();

            FORMATTED_TRACE("wave_player::EventOpenDecoder pathOrigin = %s", pathOrigin.c_str());

         }
         else
         {

            if (get_wave_player() != nullptr && get_wave_player()->plugin() != nullptr)
            {

               get_wave_player()->plugin()->multimedia_set_origin_path(pcommand->get_open_file()->get_file_path());

            }

         }

      }
      break;
      case ::wave::player::EventOpenDecoderFailed:
      {
         m_dBlend = 1.0;
         //playlist_on_playback_end();
      }
      break;
      case ::wave::player::EventPlay:

         OnMediaPlaybackStart(pcommand);

         break;

      case ::wave::player::EventPlaybackEnd:


         on_media_playback_end();

         break;
      case ::wave::e_player_event_open_device:
      {

         papp->mediaplaylist()->load_startup();

         string str;

         {

            synchronous_lock synchronouslock(papp->mediaplaylist()->mutex());

            str = papp->mediaplaylist()->m_pstartup->set("wave_player.audio_volume").as_string().c_str();

         }

         if (str.is_empty())
         {

            if (pplayer->m_pwaveout->m_dVolume < 0.0)
            {

               pplayer->m_pwaveout->m_dVolume = 0.0;

            }
            else if(pplayer->m_pwaveout->m_dVolume > 1.0)
            {

               pplayer->m_pwaveout->m_dVolume = 1.0;

            }

            str = as_string(pplayer->m_pwaveout->m_dVolume);

            {

               synchronous_lock synchronouslock(papp->mediaplaylist()->mutex());

               papp->mediaplaylist()->m_pstartup->set("wave_player.audio_volume") = str;

            }

         }
         else
         {

            double dVolume = str_to_double(str);

            pplayer->m_pwaveout->m_dVolume = dVolume;

         }

      }
      break;
      case ::wave::player::EventExecutePause:
         break;
      case ::wave::player::EventStop:
         break;
      case ::wave::player::EventFadeOutAndStop:
         break;
      case ::wave::player::EventStopped:
         break;
      default:
         break;
      }

      if (eevent == ::wave::player::EventFadeOutAndStop
            || eevent == ::wave::player::EventStop
            || eevent == ::wave::player::EventStopped
            || eevent == ::wave::player::EventPlaybackEnd
            || eevent == ::wave::player::EventCloseDevice
            || eevent == ::wave::player::EventDestroy)
      {

         auto pdocument = papp->mediaplaylist()->m_pplaylistdoc;

         if (::is_set(pdocument))
         {

            pdocument->set_playback_playlist(nullptr);

         }

      }

   }


   void impact::_001OnUpdateImpactEncoding(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);
      u32 dwCodePage = IdToCodePage(pcommand->m_atom);
      if(GetKaraokeCodePage(nullptr) == dwCodePage)
      {
         pcommand->_001SetCheck(::e_check_checked);
         pcommand->enable(0);
      }
      else
      {
         pcommand->_001SetCheck(::e_check_unchecked);
         pcommand->enable(1);
      }
      pcommand->m_bRet = true;
   }
   void impact::_001OnShowEncoding(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);
      u32 dwCodePage = IdToCodePage(pcommand->m_atom);
      SetKaraokeCodePage(dwCodePage);
   }


   // void impact::on_message_set_cursor(::message::message * pmessage)
   // {

   //    auto pmouse = pmessage->m_union.m_pmouse;

   //    pmouse->m_ecursor = cursor_arrow;

   //    pmessage->previous();

   // }


   data * impact::get_data()
   {
      return ::mediaplay::impact_interface::get_data();
   }


   void impact::_001OnExecuteFirst(::message::message * pmessage)
   {

      if (!_ExecuteIsPlaying())
      {

         StartFadeOut(::mediaplay::ExecuteStop, ::mediaplay::ExecuteFirst);

      }
      else
      {
         _Execute(::mediaplay::ExecuteFirst);

      }

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void impact::_001OnUpdateExecuteFirst(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pcommand->m_bRet = true;

   }


   void impact::_001OnExecuteLast(::message::message * pmessage)
   {

      if (!_ExecuteIsPlaying())
      {

         StartFadeOut(::mediaplay::ExecuteStop, ::mediaplay::ExecuteLast);

      }
      else
      {
         _Execute(::mediaplay::ExecuteLast);

      }

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void impact::_001OnUpdateExecuteLast(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pcommand->m_bRet = true;

   }



   void impact::_001OnExecutePrevious(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (!_ExecuteIsPlaying())
      {

         StartFadeOut(::mediaplay::ExecuteStop, ::mediaplay::ExecutePrevious);

      }
      else
      {
         _Execute(::mediaplay::ExecutePrevious);

      }

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void impact::_001OnUpdateExecutePrevious(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pcommand->m_bRet = true;

   }


   void impact::_001OnExecuteNext(::message::message * pmessage)
   {

      if (!_ExecuteIsPlaying())
      {

         StartFadeOut(::mediaplay::ExecuteStop, ::mediaplay::ExecuteNext);

      }
      else
      {
         _Execute(::mediaplay::ExecuteNext);

      }

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void impact::_001OnUpdateExecuteNext(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pcommand->m_bRet = true;

   }


   void impact::_001OnExecuteRoulette(::message::message * pmessage)
   {

      if (!_ExecuteIsPlaying())
      {

         StartFadeOut(::mediaplay::ExecuteStop, ::mediaplay::ExecuteRoulette);

      }
      else
      {
         _Execute(::mediaplay::ExecuteRoulette);

      }

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }

   void impact::_001OnUpdateExecuteRoulette(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pcommand->m_bRet = true;

   }


   void impact::_001OnExecutePlay(::message::message * pmessage)
   {

      if (!_ExecuteIsPlaying())
      {

         papp->mediaplaylist()->m_pplaylistdoc->restart(::e_source_user, true);

      }

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void impact::_001OnUpdateExecutePlay(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(_ExecuteGetPlayEnable());

      pcommand->m_bRet = true;

   }

   void impact::_001OnExecuteStop(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (_ExecuteIsPlaying())
      {

         if (::is_set(papp->mediaplaylist()))
         {

            if (papp->mediaplaylist()->GetCurrentPlaylist(true) != nullptr)
            {

               papp->mediaplaylist()->m_pstartup->m_bWasPlaying = false;

               papp->mediaplaylist()->save_startup();

               papp->mediaplaylist()->GetCurrentPlaylist(true)->DoPlaylistSave();

            }

         }

         StartFadeOut(::mediaplay::ExecuteStop, ::mediaplay::ExecuteNone);

      }

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }


   }


   void impact::_001OnUpdateExecuteStop(::message::message * pmessage)
   {
      /*bool bEnable = false;
      ::pointer<::user::document>pdocument = get_document();
      switch(pdocument->get_data()->GetMode())
      {
      case mediaplay::data::ModeMidi:
      {
      bEnable = get_midi_player() &&
      (get_midi_sequence()->GetState() == ::music::midi::sequence::StatusPaused ||
      get_midi_sequence()->GetState() == ::music::midi::sequence::StatusPlaying ||
      ExecuteIsWaitingToPlay());
      break;
      }
      case mediaplay::data::ModeWave:
      {
      //         bEnable = m_pwaveplayer != nullptr
      //          && m_pwaveplayer->IsPlaying();
      break;
      }
      }*/
      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(_ExecuteGetStopEnable());

      pcommand->m_bRet = true;

   }


   void impact::_001OnPlaylistPrevious(::message::message * pmessage)
   {

      papp->mediaplaylist()->m_pplaylistlistview->playlist_previous();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void impact::_001OnUpdatePlaylistPrevious(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pcommand->m_bRet = true;

   }


   void impact::_001OnPlaylistNext(::message::message * pmessage)
   {

      papp->mediaplaylist()->m_pplaylistlistview->playlist_next();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void impact::_001OnUpdatePlaylistNext(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pcommand->m_bRet = true;

   }


} // namespace mediaplay
