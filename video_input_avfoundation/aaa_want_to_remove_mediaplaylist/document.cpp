#include "framework.h"

#include "base/update.h"


namespace mediaplaylist
{


   const LPARAM document::LHINT_FRAMEDOWN    = 1001;
   const LPARAM document::LHINT_FRAMEUP      = 1002;


   info::info()
   {

      m_pdocument                = nullptr;
      m_iCurrentSong             = -1;
      m_uHint                    = id_play_if_not_playing;
      m_bMakeVisible             = true;
      m_bFadeIn                  = false;
      m_time                     = 0;
      m_bPendingRestart          = false;
      m_bRandom                  = false;

   }


   info::~info()
   {

   }



   document::document()
   {

      m_bPendingRestart = false;

   }


   bool document::on_new_playlist()
   {

      m_path = papp->mediaplaylist()->get_new_playlist_path();

      m_filepathPreviousRegular = m_path;

      m_pathFile = m_path;

      delete_contents();

      pcontext->m_papexcontext->file()->put_contents(m_pathFile,"");

      on_open_document(m_pathFile);

      informationf("file path is %s", m_path.c_str());

      update_all_impacts(id_playlists_changed);

      return true;

   }


   bool document::on_new_document()
   {

      delete_contents();

      ::file::path path;

      papp->mediaplaylist()->GetDefaultPath(path, true);

      m_pathFile = path;

      m_filepathPreviousRegular = path;

      auto pplaylist = __allocate< multimedia_playlist::veriwell::playlist >();

      set_impact_playlist(pplaylist);

      pplaylist->initialize_multimedia_playlist_veriwell_playlist(papp->mediaplaylist()->m_psessionVeriwell);

      impact_playlist()->m_path = path;

      //{

      //   file_pointer file = pcontext->m_papexcontext->file()->get_file(path,::file::e_open_binary | ::file::e_open_read_write | ::file::e_open_no_truncate | ::file::e_open_create | ::file::e_open_defer_create_directory);

      //}

      if(!on_open_document(path))
      {

         return false;

      }

      return true;

   }


   document::~document()
   {

   }


   void document::on_final_release()
   {
      // When the last object for an automation object is released
      // on_final_release is called.  The base class will automatically
      // deletes the object.  add additional cleanup required for your
      // object before calling the base class.

      ::user::document::on_final_release();

   }


#ifdef _DEBUG


   void document::assert_ok() const
   {

      ::user::document::assert_ok();

   }


   void document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }


#endif //_DEBUG


   bool document::on_save_document(::payload payloadFile)
   {

      synchronous_lock synchronouslock(m_pmutexData);

      if (play_playlist() != nullptr)
      {

         play_playlist()->save();

      }

      if (impact_playlist() != nullptr)
      {

         if(play_playlist() == nullptr || impact_playlist()->m_path != play_playlist()->m_path)
         {

            impact_playlist()->save();

         }

      }

      return true;

   }


   stream & document::write(stream & outputstream) const
   {

      //string str;

      //if(m_filepath == play_playlist()->m_path)
      //{
      //
      //   str = play_playlist()->m_xmldoc.get_xml();

      //}
      //else
      //{

      //   str = impact_playlist()->m_xmldoc.get_xml();

      //}

      //outputstream.seek_to_begin();

      //outputstream.write(str);
      
      return outputstream;

   }


   stream & document::read(stream & inputstream) 
   {

      if (impact_playlist() == nullptr)
      {

         auto pplaylist = __allocate< ::multimedia_playlist::veriwell::playlist >();

         set_impact_playlist(pplaylist);

         pplaylist->initialize_multimedia_playlist_veriwell_playlist(papp->mediaplaylist()->m_psessionVeriwell);

      }

      synchronous_lock synchronouslock(m_pmutexData);

      impact_playlist()->load(m_pathFile);

      return inputstream;

   }


   bool document::has_next_song()
   {

      synchronous_lock synchronouslock(m_pmutexData);

      if(get_current_playlist_song_count() <= 0)
      {

         return false;

      }

      if(play_playlist()->is_loop())
      {

         return true;

      }

      if(get_current_queue_song_count() <= 0)
      {

         return false;

      }

      return true;

   }


   string_array document::get_songs(bool bEditingPlaylist)
   {

      synchronous_lock synchronouslock(m_pmutexData);

      if(bEditingPlaylist)
      {

         return m_straImpact;

      }
      else
      {

         return m_straPlay;

      }

   }


   void document::defer_update_songs(const string_array * pstraNew, const string_array * pstraDel)
   {

      {

         string_array stra;

         update_songs(stra, true);

         synchronous_lock synchronouslock(m_pmutexData);

         m_straImpact = stra;

      }

      {

         string_array stra;

         update_songs(stra, false);

         synchronous_lock synchronouslock(m_pmutexData);

         m_straPlay = stra;

      }

      update_all_impacts(id_songs_changed);

      if (pstraNew != nullptr)
      {

         if(pstraNew->get_count() > 0)
         {

            synchronous_lock synchronouslock(m_pmutexData);

            for (index i = 0; i < m_straOnAddPlay.get_count(); i++)
            {

               for (index j = 0; j < pstraNew->get_count(); j++)
               {

                  if (m_straOnAddPlay[i].case_insensitive_order(pstraNew->element_at(j)) == 0)
                  {

                     string strOnAddPlay = m_straOnAddPlay[i];

                     m_straOnAddPlay.erase_all();
                     m_straOnAddQueue.erase_all();

                     synchronouslock.unlock();

                     papp->on_song_added(strOnAddPlay);

                     info info;
                     info.m_iCurrentSong = m_straImpact.find_first_ci(strOnAddPlay);
                     info.m_pdocument = this;
                     info.m_bMakeVisible = false;
                     info.m_uHint = id_do_play;


                     play(&info);

                     goto processed_new;

                  }

               }

            }

            for (index i = 0; i < m_straOnAddQueue.get_count(); i++)
            {

               for (index j = 0; j < pstraNew->get_count(); j++)
               {

                  if (m_straOnAddQueue[i].case_insensitive_order(pstraNew->element_at(j)) == 0)
                  {

                     string strOnAddQueue = m_straOnAddQueue[i];

                     synchronouslock.unlock();

                     papp->on_song_added(strOnAddQueue);

                     info info;
                     info.m_iCurrentSong = m_straImpact.find_first_ci(strOnAddQueue);
                     info.m_pdocument = this;
                     info.m_bMakeVisible = false;
                     info.m_uHint = id_play_if_not_playing;

                     play(&info);

                     goto processed_new;
                  }

               }

            }

         }

      }

processed_new:
      ;


   }


   bool document::update_songs(string_array & stra, bool bEditingPlaylist)
   {

      stra.erase_all();

      ::pointer<::multimedia_playlist::playlist>ppl;

      if (bEditingPlaylist)
      {

         ppl = impact_playlist();

      }
      else
      {

         ppl = play_playlist();

      }

      if(ppl.is_set())
      {

         stra = ppl->get_stra();

      }

      return true;

   }


   bool document::get_song_current_queue(string_array & stra, bool bEditingPlaylist)
   {

      synchronous_lock synchronouslock(m_pmutexData);

      string_array straTotal = get_songs(bEditingPlaylist);

      for(i32 i = 0; i < m_iaQueue.get_count(); i++)
      {

         stra.add(straTotal[m_iaQueue[i]]);

      }

      return true;

   }


   index document::get_current_song(bool bEditingPlaylist)
   {

      synchronous_lock synchronouslock(m_pmutexData);

      if(bEditingPlaylist)
      {

         return impact_playlist()->m_iCurrentSong;

      }
      else
      {

         return play_playlist()->m_iCurrentSong;

      }

   }


   bool document::play(info * pinfo)
   {

      if (pinfo->m_uHint == id_play_if_not_playing && get_player() != nullptr && get_player()->is_playing())
      {

         return false;

      }

      {

         set_play_playlist(impact_playlist());

         papp->mediaplaylist()->m_plistview->m_bHighHighLight = true;

         on_update_playlist();

      }

      if (pinfo->m_iCurrentSong < 0)
      {

         pinfo->m_iCurrentSong = play_playlist()->get_int("current_song", -1);

         if (pinfo->m_time < 0)
         {

            pinfo->m_time = (::duration) play_playlist()->get_int("current_song_millis", 0);

            if (pinfo->m_time < 5000)
            {

               pinfo->m_time = 0;

            }
            else
            {

               pinfo->m_bFadeIn = true;

            }

         }

      }

      string str;

      index iSong = pinfo->m_iCurrentSong;

      if (pinfo->m_context.is_user_source()
            || pinfo->m_uHint == id_do_play
            || (pinfo->m_uHint == id_play_if_not_playing && (get_player() == nullptr || !get_player()->is_playing())))
      {

         populate_queue(pinfo->m_iCurrentSong);

      }


      if (get_player() == nullptr)
      {

         return false;

      }

      e_play eplay;

      int iLoopNotOpened = 0;

      int iLoop;

      while(true)
      {

         {

            iLoop = 0;

            if(!pick_song(iSong, str, pinfo->m_bRandom, iLoop))
            {

               return false;

            }

            if (iLoop)
            {

               iLoopNotOpened++;

               if (iLoopNotOpened >= 0)
               {

                  fork([this]()
                  {

                     output_error_message("Non playable songs found.");

                  });

                  break;

               }

            }

            synchronous_lock synchronouslock(m_pmutexData);

            if(play_playlist()->m_setFile[str].is_empty())
            {

               play_playlist()->m_setFile[str] = str;

            }

            pinfo->m_strFilePath = play_playlist()->m_setFile[str];

            pinfo->m_pdocument = this;

         }

         eplay = get_player()->PlaylistPlay(pinfo);

         if(eplay == play_success)
         {

            if (!pinfo->m_bPendingRestart && !play_playlist()->m_bDiscard)
            {

               play_playlist()->m_iCurrentSong = iSong;

               play_playlist()->set_int("current_song", iSong);

               {

                  auto & pstartup = papp->mediaplaylist()->m_pstartup;

                  synchronous_lock synchronouslock(papp->mediaplaylist()->mutex());

                  ::file::path path = m_pathFile;

                  path = pcontext->m_papexcontext->defer_make_file_system_url(m_pathFile);

                  pstartup->m_strPlaylistPlaying = path;

                  pstartup->set(path + ".current_song") = iSong;

                  pstartup->set(path + ".current_song_position") = 0;

                  pstartup->set(path + ".current_song_millis") = 0;

               }

               papp->mediaplaylist()->save_startup();

               auto ptopic = new_action(id_current_song);

               update_all_impacts(ptopic);

               papp->mediaplaylist()->m_pplaylistlistview->update_playlist_hilite(m_pathFile);

               papp->mediaplaylist()->m_plistview->defer_update_track_hilite();

            }

            if(IsDefaultPlaylist())
            {

               DoDefaultPlaylistSave();

            }

            return true;

         }
         else
         {

            if (play_playlist()->m_bDiscard)
            {

               play_playlist()->erase_song(iSong);

               play_playlist()->save();

            }
            else if (eplay != play_error_continue)
            {

               return false;

            }

         }

      }

      return false;

   }


   void document::defer_restart_on_was_playing()
   {

      ::pointer<::mediaplaylist::media_playlist>spmediaplaylist = papp->mediaplaylist();

      ::pointer<::mediaplay::mediaplay>spmediaplay = papp->mediaplay();

      spmediaplaylist->load_startup();

      bool bOk;

      if(spmediaplaylist->m_pstartup->m_bWasPlaying)
      {

         bOk = restart(::e_source_user, true);

      }
      else
      {

         bOk = false;

      }

      if(bOk)
      {

         spmediaplaylist->m_bRestartFadeIn = true;

      }
      else
      {

         spmediaplaylist->m_bRestartFadeIn = false;

         if(spmediaplay.is_set())
         {

            if(spmediaplay->get_impact() != nullptr)
            {

               spmediaplay->get_impact()->m_dBlend = 1.0;

               if (!spmediaplay->get_impact()->top_level_frame()->is_window_visible())
               {

                  ::pointer<::user::frame_window>pframe = spmediaplay->get_impact()->top_level_frame();

                  if (pframe.is_set())
                  {

                     pframe->InitialFramePosition();

                  }

               }

            }

         }

      }

      ::user::document * pdocument = spmediaplay->m_pimpactsystem->get_document();

      auto ptopic = new_action(id_restart_track);

      if(pdocument != nullptr)
      {

         pdocument->update_all_impacts(ptopic);

      }

   }


   bool document::restart(const ::action_context & context, bool bFadeIn)
   {

      info info;

      papp->mediaplaylist()->load_startup();

      ::file::path path = papp->mediaplaylist()->m_pstartup->m_strPlaylistPlaying;

      if (path.is_empty())
      {

         return false;

      }

      if (!on_open_document(path))
      {

         return false;

      }

      //{

      //   auto & startup = papp->mediaplaylist()->m_startup;

      //   synchronous_lock synchronouslock(pstartup->mutex());

      //   info.m_time = pstartup->m_set[path + ".current_song_millis"];

      //   info.m_iCurrentSong = pstartup->m_set[path + ".current_song"];

      //}

      //info.m_time = pstartup->m_set[path + ".current_song_millis"];

      info.m_time = -1; // restart at playlist last saved played song last saved position

      info.m_iCurrentSong = -1; // restart at playlist last saved played song

      info.m_uHint               = id_play_if_not_playing;

      info.m_bMakeVisible        = true;

      info.m_context       += ::e_source_user;

      if(bFadeIn && info.m_time > 0)
      {

         ::pointer<::mediaplay::document>pmediadoc = papp->mediaplay()->get_document_template()->get_document();

         if(pmediadoc != nullptr)
         {

            ::mediaplay::impact_interface * pimpact = pmediadoc->get_typed_impact < ::mediaplay::impact_interface >();

            return pimpact->StartFadeIn(&info);

         }
         else
         {

            return play(&info);

         }

      }
      else
      {

         return play(&info);

      }

   }


   void document::OnPlay()
   {

      info info;

      info.m_iCurrentSong     = get_current_song(true);
      info.m_uHint            = id_do_play;
      info.m_bMakeVisible     = true;

      play(&info);

   }


   bool document::AddSong(LPINT lpiaSongs, ::count iSongCount, bool bDoPlay, bool bMakeVisible)
   {

      bool bFirst = bDoPlay;

      for(index i = 0; i < iSongCount; i++)
      {

         AddSong(lpiaSongs[i], bFirst, bMakeVisible, false);
         //        if(pSongsSet->FindCode(lpiaSongs[i]))
         //      {
         //        pSongsSet->GetData(3);
         //      string str(pSongsSet->m_bstrPath);
         //    AddSong(str, bFirst, bMakeVisible, false);
         //  bFirst = false;
         //}
      }

      update_all_impacts(id_songs_added);

      OnAddSong();

      return true;

   }


   string document::AddSong(::payload payloadFile, EAddSong eaddsong, bool bMakeVisible, bool bUpdateAllImpacts, bool bAddDuplicate)
   {

      UNREFERENCED_PARAMETER(bUpdateAllImpacts);

      string strPathName;

      if(payloadFile.get_type() == ::e_type_property_set && payloadFile.propset()["url"].get_string().has_char())
      {

         strPathName = payloadFile.propset()["url"];

      }
      else if(payloadFile.cast < ::file::file > () != nullptr)
      {

         strPathName = pdatetime->international().get_gmt_date_time() + "." + get_document_template()->payload("default_extension");

      }
      else
      {

         strPathName = payloadFile;

      }

      string strId;

      //index iSongIndex = -1;

      {

         if (impact_playlist() == nullptr)
         {

            auto pplaylist = __allocate< multimedia_playlist::veriwell::playlist >();

            set_impact_playlist(pplaylist);

            pplaylist->initialize_multimedia_playlist_veriwell_playlist(papp->mediaplaylist()->m_psessionVeriwell);

            synchronous_lock synchronouslock(m_pmutexData);

            impact_playlist()->load(m_pathFile);

         }

         synchronous_lock synchronouslock(m_pmutexData);

         strId = impact_playlist()->add_song(payloadFile, bAddDuplicate);

         if(strId.is_empty())
         {

            informationf("The song was not added (1) ::mediaplaylist::document::AddSong .\n\n");

            return "";



         }

         switch (eaddsong)
         {
         case AddSongOnly:
            break;
         case AddSongAndPlay:
            m_straOnAddPlay.add(strId);
            break;
         case AddSongAndPlayIfNotPlaying:
            m_straOnAddQueue.add(strId);
            break;
         default:
            ASSERT(false);
            return "";
         }


         if (impact_playlist()->m_psession == papp->mediaplaylist()->m_psessionVeriwell)
         {
            impact_playlist()->save();

         }

      }

      update_all_impacts(id_songs_added);

      OnAddSong();




      return strId;

   }


   bool document::AddSong(::index nSong, bool bDoPlay, bool bMakeVisible, bool bUpdateAllImpacts)
   {

      UNREFERENCED_PARAMETER(nSong);
      UNREFERENCED_PARAMETER(bDoPlay);
      UNREFERENCED_PARAMETER(bMakeVisible);
      UNREFERENCED_PARAMETER(bUpdateAllImpacts);

      return false;


      //   CVMSApp * pApp = (CVMSApp *) System;
      //   ASSERT(pApp != nullptr);
      //  db_server* pDataCentral = db();
      //ASSERT(pDataCentral != nullptr);
      //   CDBSongSet * pSongsSet = pDataCentral->GetSongsSet();
      //ASSERT(pSongsSet != nullptr);

      //    if(!pSongsSet->FindCode(nSong))
      //      return false;

      //pSongsSet->GetData(3);
      //   string str(pSongsSet->m_bstrPath);
      //   return AddSong(str, bDoPlay, bMakeVisible, bUpdateAllImpacts);


   }

   bool document::AddSong(string_array  & stra, bool bDoPlay, bool bMakeVisible)
   {

      //DBCentralInterface * pDataCentral = db();
      //ASSERT(pDataCentral != nullptr);

      bool bFirst = bDoPlay;

      for(i32 i = 0; i < stra.get_size(); i++)
      {
         AddSong(stra.element_at(i), bFirst ? (bDoPlay ? AddSongAndPlay : AddSongOnly) : AddSongOnly, bMakeVisible, false);
         //        if(pSongsSet->FindCode(lpiaSongs[i]))
         //      {
         //        pSongsSet->GetData(3);
         //      string str(pSongsSet->m_bstrPath);
         //    AddSong(str, bFirst, bMakeVisible, false);
         //  bFirst = false;
         //}
      }

      update_all_impacts(id_songs_added);

      OnAddSong();

      return true;

   }


   void document::delete_contents()
   {

      synchronous_lock synchronouslock(m_pmutexData);

      m_iaQueue.erase_all();

      m_iCurrentPlaylistSongCount = -1;

      m_straQueue.erase_all();

   }


   ::multimedia_playlist::playlist * document::impact_playlist()
   {

      return m_pplaylistImpact;

   }


   ::multimedia_playlist::playlist * document::play_playlist()
   {

      return m_pplaylistPlay;

   }


   ::multimedia_playlist::playlist * document::playback_playlist()
   {

      return m_pplaylistPlayback;

   }


   void document::set_impact_playlist(::multimedia_playlist::playlist * pplaylist)
   {

      {

         synchronous_lock synchronouslock(m_pmutexData);

         if (pplaylist == m_pplaylistImpact)
         {

            return;

         }

         m_pplaylistImpact = pplaylist;

      }

      {

         auto ptopic = new_action(id_playlist_list_selection_changed);

         ptopic->user_interaction() = m_pplaylistImpact;

         update_all_impacts(ptopic);

      }

      update_all_impacts(id_impact_playlist_changed);

   }


   void document::set_play_playlist(::multimedia_playlist::playlist * pplaylist)
   {

      if (pplaylist == m_pplaylistPlay)
      {

         return;

      }

      m_pplaylistPlay = pplaylist;

      {

         auto ptopic = new_action(id_playlist_list_selection_changed);

         ptopic->user_interaction() = m_pplaylistPlay;

         update_all_impacts(ptopic);

      }

      update_all_impacts(id_play_playlist_changed);

   }


   void document::set_playback_playlist(::multimedia_playlist::playlist * pplaylist)
   {

      if (pplaylist == m_pplaylistPlayback)
      {

         return;

      }

      m_pplaylistPlayback = pplaylist;

      {

         auto ptopic = new_action(id_playlist_list_selection_changed);

         ptopic->user_interaction() = m_pplaylistPlayback;

         update_all_impacts(ptopic);

      }

      update_all_impacts(id_playback_playlist_changed);

   }


   //void document::on_change_impact_playlist()
   //{

   //   on_change_playlist();

   //   auto plistview = papp->mediaplaylist()->m_plistview;

   //   if (::is_set(plistview))
   //   {

   //      plistview->on_subject(id_current_song_changed, nullptr);

   //   }

   //}


   //void document::on_change_play_playlist()
   //{

   //   on_change_playlist();

   //}


   //void document::on_change_playlist()
   //{

   //   auto plistview = papp->mediaplaylist()->m_plistview;

   //   if (m_pplPlay2 == m_pplImpact2)
   //   {

   //      if (::is_set(plistview))
   //      {

   //         plistview->m_bHighHighLight = true;

   //      }

   //   }
   //   else
   //   {

   //      if (::is_set(plistview))
   //      {

   //         plistview->m_bHighHighLight = false;

   //      }

   //   }

   //}


   bool document::on_open_document(const ::payload & payloadFile)
   {

      bool bDiscard = false;

      bool bSearch = false;

      if (payloadFile.get_type() == ::e_type_property_set)
      {

         if ((bool)payloadFile["discard"])
         {

            bDiscard = true;

         }

      }

      string strName;

      set_impact_playlist(nullptr);

      delete_contents();

      {

         synchronous_lock synchronouslock(m_pmutexData);

         m_pathFile = payloadFile.get_file_path();

         strName = m_pathFile;

      }


      {

         if (m_pathFile.case_insensitive_find("api.spotify.com/v1/search") >= 0)
         {

            bSearch = true;

         }
         else if(!bDiscard)
         {

            m_filepathPreviousRegular = m_pathFile;

         }

         set_impact_playlist(papp->mediaplaylist()->open_playlist(m_pathFile));

         if (impact_playlist() == nullptr)
         {

            return false;

         }

         impact_playlist()->m_bDiscard = bDiscard;

         {

//            auto & startup = papp->mediaplaylist()->m_startup;

            //          synchronous_lock synchronouslock(pstartup->mutex());

            impact_playlist()->m_iCurrentSong = impact_playlist()->get_int("current_song", 0);

            update_all_impacts(id_current_song_changed);

         }

         impact_playlist()->ensure_playlist();

      }


      if (this == papp->mediaplaylist()->m_pplaylistdoc)
      {

         if (papp->mediaplaylist()->m_plistview != nullptr)
         {

            papp->mediaplaylist()->m_plistview->defer_update_track_hilite();

         }

      }

      OnChangeSongs();

      m_path = m_pathFile;

      return true;

   }


   bool document::defer_open_discard_erase_first()
   {

      ::multimedia_playlist::playlist * ppl;

      bool bDiscardWasPlaying = false;

      if (impact_playlist() != nullptr && play_playlist()->m_bDiscard)
      {

         ppl = play_playlist();

         bDiscardWasPlaying = true;

      }
      else if(impact_playlist() != nullptr && impact_playlist()->m_bDiscard)
      {

         ppl = impact_playlist();

      }
      else
      {

         ::file::path path;

         if(!papp->mediaplaylist()->GetDiscardPath(path))
         {

            return false;

         }

         if(!pcontext->m_papexcontext->file()->exists(path))
         {

            return false;

         }

         ppl = papp->mediaplaylist()->open_playlist(path);

         if (ppl == nullptr)
         {

            return false;

         }

         ppl->m_bDiscard = true;

         ppl->ensure_playlist();

      }

      if (bDiscardWasPlaying)
      {

         ppl->erase_song(0);

      }

      if (ppl->get_count() <= 0)
      {

         return false;

      }

      delete_contents();

      {

         synchronous_lock synchronouslock(m_pmutexData);

         m_pathFile = ppl->m_path;

      }

      set_impact_playlist(ppl);

      impact_playlist()->m_iCurrentSong = -1;

      if (this == papp->mediaplaylist()->m_pplaylistdoc)
      {

         if (papp->mediaplaylist()->m_plistview != nullptr)
         {

            papp->mediaplaylist()->m_plistview->defer_update_track_hilite();

         }

      }

      OnChangeSongs();

      save_modified();

      defer_update_songs();

      on_update_playlist();

      if (papp->mediaplay() != nullptr)
      {

         if (papp->mediaplay()->m_pmediaplaylistplayer != nullptr)
         {

            papp->mediaplay()->m_pmediaplaylistplayer->PlaylistPlayByIndex(0);

         }

      }

      return true;

   }




   void document::on_close_document()
   {

      if(IsDefaultPath())
      {

         papp->mediaplaylist()->OnCloseDefaultPlaylist();

      }

      ::user::document::on_close_document();

   }


   bool document::save_modified()
   {

      return do_save(m_pathFile, true);



   }


   void document::update_title()
   {

      ::pointer<mediaplaylist::media_playlist>pplaylistcentral = papp->mediaplaylist();

      ::file::path wstrDefault;

      pplaylistcentral->GetDefaultPath(wstrDefault);

      if(IsDefaultPath())
      {

         string str;
         //      str.load_string(IDS_DEFAULT_PLAYLIST_TITLE);
         set_title(str);

      }

   }


   ::count document::get_song_count(bool bEditingPlaylist)
   {

      return get_songs(bEditingPlaylist).get_size();

   }


   bool document::get_song_at(::file::path & str, ::index iSong, bool bEditingPlaylist)
   {

      if(iSong < 0)
         return false;

      synchronous_lock synchronouslock(m_pmutexData);

      string_array * pstra = nullptr;

      if(bEditingPlaylist)
      {

         pstra = &m_straImpact;

      }
      else
      {

         pstra = &m_straPlay;

      }

      if(pstra->get_size() <= 0)
         return false;

      if(iSong >= pstra->get_size())
         return false;

      str = pstra->element_at(iSong);

      return true;

   }

   void document::populate_queue(::index iSong)
   {

      if (play_playlist() != nullptr && play_playlist()->m_bDiscard)
      {

         return;

      }

      string_array stra;

      //int iTry = 0;

      //int iMod = 10;

//retry:

      stra = get_songs(false);

      if (iSong < 0)
      {

         iSong = 0;

      }

      if (iSong >= stra.get_size())
      {

         iSong = 0;

      }

      if(iSong >= stra.get_size())
         return;

      synchronous_lock synchronouslock(m_pmutexData);

      m_iaQueue.erase_all();

      bool bShuffle = false;

      if(play_playlist()->is_shuffle() && bShuffle)
         iSong = 0;

      ::papaya::array::populate(m_iaQueue, iSong, stra.get_upper_bound(), (index) 1, true, true, true);

      if(bShuffle)
      {

         if(m_iaQueue.contains(iSong))
         {
            // maintains iSong the first song in queue;
            m_iaQueue.erase(iSong);
            ::papaya::array::randomize(m_iaQueue);
            m_iaQueue.insert_at(0, iSong);
         }
         else
         {
            ::papaya::array::randomize(m_iaQueue);
         }

      }

   }


   bool document::pick_song(index & iSong, string & str, bool bRandom, int & iLoop)
   {

      synchronous_lock synchronouslock(m_pmutexData);

retry0:

      if (play_playlist() != nullptr && play_playlist()->m_bDiscard)
      {

         string_array stra;

         stra = get_songs(false);

         iSong = 0;

         if (iSong >= stra.get_size())
         {

            return false;

         }

         str = stra[iSong];


      }
      else
      {

         string_array stra;

         //int iTry = 0;

         stra = get_songs(false);

         if (iSong < 0)
         {

            papp->mediaplaylist()->m_bProcessingQueue = false;

            iSong = 0;

         }

         if (iSong >= stra.get_size())
         {

            papp->mediaplaylist()->m_bProcessingQueue = false;

            iSong = 0;

         }

         if (iSong >= stra.get_size())
         {

            papp->mediaplaylist()->m_bProcessingQueue = false;

            return false;

         }

         if (m_iaQueue.get_count() <= 0)
         {

            bool bLoop = true;

            if (play_playlist()->is_loop() && bLoop)
            {

               return false;

            }

            iLoop++;

            populate_queue(0);

         }

         if (m_iaQueue.get_size() <= 0)
         {

            papp->mediaplaylist()->m_bProcessingQueue = false;

            return false;

         }

         int iIndex;

         if (bRandom)
         {

            iIndex = (int) random(0, m_iaQueue.get_upper_bound());

         }
         else
         {

            iIndex = 0;

         }


         iSong = m_iaQueue[iIndex];

         m_iaQueue.erase_at(iIndex);

         str = stra[iSong];


      }

      if (str.is_empty())
      {

         papp->mediaplaylist()->m_bProcessingQueue = false;

         play_playlist()->erase_song(iSong);

         defer_update_songs();

         on_update_playlist();

         goto retry0;


      }

      return true;

   }


   bool document::RemoveSong(index iSong, ::pointer<::user::impact>pimpact, bool bUpdate)
   {

      if(iSong < 0)
      {

         return false;

      }

      if(iSong >= get_song_count(true))
      {

         return false;

      }

      if (bUpdate)
      {

         if (play_playlist() != nullptr && play_playlist()->m_path == impact_playlist()->m_path)
         {

            if (iSong == play_playlist()->m_iCurrentSong)
            {

               ::pointer<::mediaplay::impact>pimpact = papp->mediaplay()->get_impact();

               if (pimpact->_ExecuteIsPlaying())
               {

                  info info;

                  info.m_iCurrentSong = iSong;
                  info.m_uHint = id_do_play;
                  info.m_bMakeVisible = true;

                  play(&info);

               }

            }

         }

      }

      impact_playlist()->erase_song(iSong, bUpdate);

      if (bUpdate)
      {

         OnRemoveSong(pimpact);

      }

      return true;

   }


   void document::OnAddSong()
   {

      OnChangeSongs();

   }


   void document::OnChangeSongs(::pointer<::user::impact>pimpact)
   {

      UNREFERENCED_PARAMETER(pimpact);

      on_update_playlist();

      if(IsDefaultPlaylist())
      {

         DoDefaultPlaylistSave();

      }

      update_all_impacts(id_songs_changed);

   }


   void document::DoDefaultPlaylistSave()
   {

      if(IsDefaultPlaylist())
      {

         DoPlaylistSave();

      }

   }


   void document::DoPlaylistSave()
   {

      on_save_document(nullptr);

   }


   bool document::IsDefaultPlaylist()
   {

      return IsDefaultPath();

   }

   void document::OnRemoveSong(::pointer<::user::impact>pimpact)
   {

      OnChangeSongs(pimpact);

   }


   bool document::IsDefaultPath(const ::file::path & path)
   {

      ::pointer<::mediaplaylist::media_playlist>mediaplaylist = papp->mediaplaylist();

      if(mediaplaylist.is_null())
      {

         return false;

      }

      ::file::path strDefault;

      mediaplaylist->GetDefaultPath(strDefault);

      return strDefault ==  pcsz;

   }


   bool document::IsDefaultPath()
   {

      return IsDefaultPath(get_file_path());

   }


   ::pointer<::user::impact>document::GetFirstAttachableImpact()
   {

      auto ptopic = new_action(id_get_attachable_impact);

      update_all_impacts(ptopic);

      auto pimpacta = pupdate->cast < pointer_array < ::user::impact > >(id_attachable);

      if(!pimpacta || pimpacta->is_empty())
      {

         return nullptr;

      }

      return pimpacta->first_pointer();

   }


   void document::Popimpacts()
   {

      auto ptopic = new_action(id_pop);

      update_all_impacts(ptopic);

   }


   void document::set_current_playlist(const ::string & pszPath)
   {

      set("current_playlist", pszPath);

   }


   string document::get_current_playlist_path()
   {

      string str;

      get("current_playlist", str);

      return str;

   }


   string document::get_default_playlist_path()
   {

      return "playlist/default";

   }


   ::count document::get_current_playlist_song_count()
   {

      return m_iCurrentPlaylistSongCount;

   }


   ::count document::get_current_queue_song_count()
   {

      synchronous_lock synchronouslock(m_pmutexData);

      return m_straQueue.get_count();

   }




   bool document::do_save(const ::string & pszPathName, bool bReplace)
   // Save the document_interface data to a file
   // lpszPathName = path name where to save document_interface file
   // if lpszPathName is nullptr then the ::account::user will be prompted (SaveAs)
   // note: lpszPathName can be different than 'm_strPathName'
   // if 'bReplace' is true will change file name if successful (SaveAs)
   // if 'bReplace' is false will not change path name (SaveCopyAs)
   {

      on_save_document(nullptr);

      //::memory_file_pointer memfileXml(e_create);
      //::memory_file_pointer memfileEdit(e_create);

      //stream osXml(memfileXml);
      //stream osEdit(memfileEdit);

      //string strXml = play_playlist()->m_xmldoc.get_root()->get_xml();

      //osXml.write(strXml, strXml.length());

      //osEdit.m_b64bit = true;

      //::file::array::write(osEdit, *play_playlist()->m_pxmledit);

      //::count iXmlSize = memfileXml->get_size();
      //::count iEditSize = memfileEdit->get_size();

      //::memory_file * pfile;

      //bool bEdit;

      //if(string_begins_ci(pszPathName, "uifs://") && iEditSize < iXmlSize)
      //{
      //   pfile = memfileEdit;
      //   bEdit = true;
      //}
      //else
      //{
      //   pfile = memfileXml;
      //   bEdit = false;
      //}

      //::payload newName = play_playlist()->m_path;
      //::payload newName = pszPathName;
      //if (newName.is_empty() || is_new_document())
      //{
      //   ::pointer<::user::impact_system>ptemplate = get_document_template();
      //   ASSERT(ptemplate != nullptr);

      //   newName = m_filepath;
      //   if (bReplace && (newName.is_empty() || is_new_document()))
      //   {
      //      newName = m_strTitle;
      //      // check for dubious filename
      //      strsize iBad = newName.get_string().FindOneOf(":/\\");
      //      if (iBad != -1)
      //         newName = newName.get_string().left(iBad);

      //      // append the default suffix if there is one
      //      string strExt;
      //      if (ptemplate->GetDocString(strExt, ::user::impact_system::filterExt) &&
      //        !strExt.is_empty())
      //      {
      //         ASSERT(strExt[0] == '.');
      //         strsize iStart = 0;
      //         newName += strExt.Tokenize(";", iStart);
      //      }
      //   }

      //   if (!psystem->do_prompt_file_name(newName, 0 /*bReplace ? WINDOWS_DEFINITION_IDS_SAVEFILE : WINDOWS_DEFINITION_IDS_SAVEFILECOPY*/, 0 /*OFN_HIDEREADONLY | OFN_PATHMUSTEXIST */, false, ptemplate, this))
      //      return false;       // don't even attempt to save

      //}

//      wait_cursor wait(this);
//
//      if(bEdit)
//      {
//         string strName = newName.get_string();
//         newName["url"] = strName;
//         newName["xmledit"] = __allocate< ::memory_file >(*memfileEdit);
////         newName["xmledit"].cast < ::memory_file >()->release();
//         newName["xml"] = __allocate< ::memory_file >(*memfileXml);
//  //       newName["xml"].cast < ::memory_file >()->release();
//      }
//
//      if(!on_save_document(newName))
//      {
//         //if(pszPathName == nullptr)
//         //{
//         //   // be sure to delete the file
//         //   try
//         //   {
//         //      pcontext->m_papexcontext->file()->del(newName);
//         //   }
//         //   catch(const ::exception & e)
//         //   {
//         //      information(trace_category_appmsg, 0, "Warning: failed to delete file after failed SaveAs.\n");
//         //      ::exception_pointer esp(pe);
//         //   }
//
//         //}
//         //return false;
//      }
//
//      play_playlist()->m_pxmledit->erase_all();
//      play_playlist()->m_pxmledit->m_iEdit = 0;
//
//      // reset the title and change the document_interface name
//      if (bReplace)
//         set_path_name(newName);

      return true;        // success
   }


   void document::add_listener(listener * plistener)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_listenera.add(plistener);

   }


   void document::erase_listener(listener * plistener)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_listenera.erase(plistener);

   }


   void document::set_player(::mediaplaylist::player * spplayer)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_pplayer = spplayer;

   }


   ::mediaplaylist::player * document::get_player()
   {

      return m_pplayer;

   }


   void document::on_update_playlist()
   {

      defer_update_songs();

   }



   void document::defer_update_spl()
   {


   }

   void document::defer_check_restart()
   {

      defer_restart_on_was_playing();


   }

} // namespace mediaplaylist


