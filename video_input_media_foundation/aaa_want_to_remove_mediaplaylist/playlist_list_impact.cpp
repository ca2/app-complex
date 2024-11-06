#include "framework.h"

#include "aura/update.h"
#include "acme/constant/id.h"


namespace mediaplaylist
{


   playlist_list_impact::playlist_list_impact()
   {

      m_iLastClickItem           = -1;
      m_cSameItemClick           = 0;
      m_emode                    = mode_normal;
      m_eview                    = impact_report;
      m_bHoverSelect             = false;

   }


   playlist_list_impact::~playlist_list_impact()
   {

   }


   void playlist_list_impact::install_message_routing(::channel * pchannel)
   {

      simple_form_list_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_left_button_double_click,pchannel,this,&playlist_list_impact::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_context_menu,pchannel,this,&playlist_list_impact::on_message_context_menu);
      MESSAGE_LINK(e_message_create,pchannel,this,&playlist_list_impact::on_message_create);

      add_command_handler("edit_delete",&playlist_list_impact::_001OnEditRemove);
      add_command_prober("edit_delete",&playlist_list_impact::_001OnUpdateEditRemove);
      add_command_handler("execute_play",&playlist_list_impact::_001OnPlaylistExecutePlay);
      add_command_prober("execute_play",&playlist_list_impact::_001OnUpdatePlaylistExecutePlay);

   }


   void playlist_list_impact::assert_ok() const
   {

      simple_form_list_impact::assert_ok();

   }


   void playlist_list_impact::dump(dump_context & dumpcontext) const
   {

      simple_form_list_impact::dump(dumpcontext);

   }


   ::mediaplaylist::document * playlist_list_impact::get_document() const
   {

      if (::user::impact::get_document() == nullptr)
      {

         return nullptr;

      }

      ASSERT(base_class <::mediaplaylist::document >::bases(::user::impact::get_document()));

      return dynamic_cast < ::mediaplaylist::document * > (::user::impact::get_document());

   }


   void playlist_list_impact::SetMode(e_mode emode)
   {

      m_emode = emode;

      _001UpdateColumns();

   }


   void playlist_list_impact::on_insert_columns()
   {

      {

         auto pinteraction = __allocate ::user::control_descriptor();

         pinteraction->m_bTransparent              = true;
         pinteraction->m_type                  = ::type < ::user::button >();
         pinteraction->m_atom                        = "play_button";
         pinteraction->add_function(::user::e_control_function_action);
         pinteraction->set_control_type(::user::e_control_type_button);

         auto pcolumn = new_list_column();

         pcolumn->m_uiText = "";
         pcolumn->m_iWidth                     = 18;
         pcolumn->m_iSubItem                   = 1;
         pcolumn->m_iControl                   = _001AddControl(pinteraction);
         pcolumn->m_bCustomDraw                = true;
         

      }

      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth            = 300;
         pcolumn->m_uiText            = "Name";
         pcolumn->m_iSubItem          = 2;
         

      }

      e_mode emode = m_emode;

      if(emode == mode_verbose)
      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth            = 300;
         pcolumn->m_uiText            = "<string atom='mediaplaylist:playlist_list_impact:file_name'>Playlist</string>";
         pcolumn->m_iSubItem          = 3;
         pcolumn->m_iSmallImageWidth  = 16;
         pcolumn->m_colorSmallMask       = rgb(255,0,255);
         
      }

   }


   void playlist_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_initial)
      {

         call_subject(id_playlists_changed);

      }
      else if(ptopic->m_atom == id_playlists_changed)
      {

         __construct(m_plisting);

         papp->mediaplaylist()->GetPath(*m_plisting);

         _001OnUpdateItemCount();

      }

   }


   bool playlist_list_impact::WndFrameworkDownUpGetUpEnable()
   {

      return get_parent_frame()->get_parent() != nullptr;//     || GetMode() == mode_minimum;

   }


   bool playlist_list_impact::WndFrameworkDownUpGetDownEnable()
   {

      return get_parent_frame()->get_parent() == nullptr;//         || GetMode() == mode_normal;

   }


   bool playlist_list_impact::TransparentFrameWndDownUpGetUpEnable()
   {

      return get_parent_frame()->get_parent() != nullptr; // &&        GetMode() == mode_normal;

   }


   bool playlist_list_impact::TransparentFrameWndDownUpGetDownEnable()
   {

      return get_parent_frame()->get_parent() == nullptr; //  &&         GetMode() == mode_minimum;

   }


   playlist_list_impact::e_mode playlist_list_impact::GetMode()
   {

      return m_emode;

   }


   void playlist_list_impact::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::collection::index iItem;

      if(_001HitTest_(pmouse->m_point,iItem))
      {

         playlist_play(iItem);

      }

   }


   void playlist_list_impact::_001GetItemImage(::user::mesh_item * pitem)
   {
      if(pitem->m_item.m_iSubItem == 0 || pitem->m_item.m_iSubItem == 1)
      {
         pitem->m_iImage = 0;
         pitem->m_bOk = true;
      }
      else
      {
         pitem->m_iImage = -1;
         pitem->m_bOk = false;
      }
   }


   void playlist_list_impact::on_message_context_menu(::message::message * pmessage)
   {
      
      ::pointer<::message::context_menu>pcontextmenu(pmessage);
      
      ::int_point pointContextMenu = pcontextmenu->GetPoint();

      auto item = hit_test(pointContextMenu);

      if(item)
      {

         //     SimpleMenu menu(BaseMenuCentral::GetMenuCentral(this));
         /*      if (menu.LoadMenu(IDR_POPUP_PLAYLIST_ITEM))
         {
         SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
         ASSERT(pPopup != nullptr);
         frame_window * pframe = get_parent_frame();
         pPopup->TrackPopupMenu(
         point.x(), point.y(),
         (::windowing::window *) pframe);
         }*/
      }
      else
      {
         //     ::user::menu menu;
         /*      if (menu.LoadMenu(IDR_POPUP_PLAYLIST))
         {
         ::user::menu* pPopup = menu.GetSubMenu(0);
         ASSERT(pPopup != nullptr);
         frame_window * pframe = get_parent_frame();
         pPopup->TrackPopupMenu(
         point.x(), point.y(),
         (::windowing::window *) pframe);
         }*/
      }
   }


   void playlist_list_impact::_001OnEditRemove(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      _001RemoveSelection();
   }

   void playlist_list_impact::_001OnUpdateEditRemove(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);

      ::user::range range;

      get_selection(range);

      pcommand->enable(range.get_item_count() > 0);
      pcommand->m_bRet = true;
   }


   /*PaneImpact * playlist_list_impact::GetParentPane()
   {
   //::pointer<::user::interaction>puserinteraction = get_parent();
   if(base_class <PaneImpact >::bases(puserinteraction))
   {
   return dynamic_cast < PaneImpact * > (puserinteraction);
   }*/
   /* return nullptr;
   }*/

   void playlist_list_impact::_001OnPlaylistExecutePlay(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      ::user::range range;

      get_selection(range);

      if(range.get_item_count() > 0)
      {
         ::collection::index iItem = range.ItemAt(0).get_lower_bound();

         playlist_play(iItem);

      }

   }


   void playlist_list_impact::_001OnUpdatePlaylistExecutePlay(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);
      ::user::range range;
      get_selection(range);
      pcommand->enable(range.get_item_count() > 0);
      pcommand->m_bRet = true;
   }


   void playlist_list_impact::_001OnInitializeControl(::pointer<::user::interaction>pinteraction)
   {

      simple_form_list_impact::_001OnInitializeControl(pinteraction);

      if(pinteraction->descriptor().m_atom == "play_button")
      {
         ::pointer<::user::button>pbutton = pinteraction;
         pbutton->set_button_style(::user::button::style_list);
         ::user::button::list * plist = pbutton->m_plist;
         plist->m_pimagelistNormal = m_pimagelistNormal;
         plist->m_iImageNormal = 0;
         plist->m_pimagelistItemHover = m_pimagelistItemHover;
         plist->m_iImageItemHover = 0;
         plist->m_pimagelistSubItemHover = m_pimagelistSubItemHover;
         plist->m_iImageSubItemHover = 0;
      }

   }

   void playlist_list_impact::_001OnButtonAction(::pointer<::user::interaction>pinteraction)
   {

      if(pinteraction->descriptor().m_atom == "play_button")
      {

         playlist_play(pinteraction->GetEditItem());

      }

   }

   ::collection::count playlist_list_impact::_001GetItemCount()
   {

      ::collection::count iAddUp = 0;

      try
      {

         if (papp->mediaplaylist()->spotify() != nullptr)
         {

            synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex2);

            iAddUp = papp->mediaplaylist()->spotify()->m_pla.get_count();

         }

      }
      catch (...)
      {

      }

      return m_plisting->get_count() + iAddUp;

   }


   void playlist_list_impact::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      pmessage->previous();

      if (get_parent_frame() != nullptr)
      {

         get_parent_frame()->m_impactptraCommandHandlers.add_unique(papp->m_pmediaplayview);

      }

      if (get_document()->m_pviewTopic == nullptr)
      {

         get_document()->m_pviewTopic = this;

      }

      set_impact_title("Playlist");

      get_parent_frame()->set_frame_title("Playlist");

      m_pimagelistSubItemHover   = __allocate image_list();
      m_pimagelistNormal         = __allocate image_list();
      m_pimagelistItemHover      = __allocate image_list();

      m_pimagelistSubItemHover->create(16,16,0,10,10);
      m_pimagelistSubItemHover->add_file("matter://mediaplaylist/execute_play_16.png");


      ::draw2d::graphics_pointer spgraphics(e_create);
      spgraphics->CreateCompatibleDC(nullptr);

      psystem->imaging().change_hue(
         m_pimagelistNormal,
         m_pimagelistSubItemHover,
         rgb(220,220,215),
         0.50);

      psystem->imaging().color_blend(
      m_pimagelistItemHover,
      m_pimagelistSubItemHover,
      rgb(220,220,215),
      127);

      m_pimagelistGroupHover = __allocate image_list();

      m_pimagelistGroupHover->create(96,96,0,10,10);
      m_pimagelistGroupHover->add_file("matter://mediaplaylist/playlist_96.png");
      m_pimagelistGroup = m_pimagelistGroupHover;


      _001UpdateColumns();


      ::mediaplay::document * pplayerdoc = dynamic_cast < ::mediaplay::document * > (papp->mediaplay()->get_document_template()->get_document());

      if(pplayerdoc != nullptr)
      {

         if(pplayerdoc->get_media_impact() != nullptr)
         {

            pplayerdoc->get_media_impact()->attach_playlist(get_document());

         }

      }

      papp->mediaplaylist()->m_pplaylistlistview = this;

//      papp->mediaplaylist()->m_pspotify = __allocate ::multimedia_playlist::session(this);

      //#else

      //if(papp->mediaplaylist()->m_bPendingCheckForRestartOnWasPlaying)
      //{

      //   papp->mediaplaylist()->m_bPendingCheckForRestartOnWasPlaying = false;

      //   get_document()->defer_restart_on_was_playing();

      //}

//#endif

      //m_pfont->create_point_font("Calibri", 13, 800);
      //m_pfontHover->create_point_font("Calibri", 13, 800);


   }

   //::collection::count playlist_list_impact::_001GetGroupCount()
   //{
   //   if(get_document() == nullptr)
   //      return 0;
   //   if(get_document()->m_pnodePlaylist == nullptr)
   //      return 0;
   //   if(get_document()->is_recursive())
   //   {
   //      return get_document()->m_pnodePlaylist->get_children_count("playlist",-1) + 1;
   //   }
   //   else
   //   {
   //      return 1;
   //   }
   //}

   //::collection::count playlist_list_impact::_001GetGroupItemCount(::collection::index iGroup)
   //{
   //   if(get_document() == nullptr)
   //      return 0;
   //   if(get_document()->m_pnodePlaylist == nullptr)
   //      return 0;
   //   if(get_document()->is_recursive())
   //   {
   //      if(iGroup == m_nGroupCount - 1)
   //      {
   //         return get_document()->m_pnodePlaylist->get_children_count("song");
   //      }
   //      else
   //      {
   //         ::pointer<::xml::node>pnode = get_document()->m_pnodePlaylist->get_child_at("playlist",iGroup,-1);
   //         if(pnode == nullptr)
   //            return 0;
   //         return pnode->get_children_count("song");
   //      }
   //   }
   //   else
   //   {
   //      return get_document()->m_pnodePlaylist->get_children_count("song");
   //   }
   //}

   void playlist_list_impact::_001GetItemColor(::user::mesh_item * pitem)
   {

      simple_form_list_impact::_001GetItemColor(pitem);

      if(pitem->m_bOk)
         return;

      if(pitem->m_item.m_iItem < 0)
      {
         pitem->m_bOk = false;
         return;
      }

      ::pointer<::user::draw_list_item>pdrawitem = pitem;

      if (pdrawitem->m_bListItemSelected)
      {

         pitem->m_colorItemBackground = argb(49, 0, 0, 0);

      }
      else
      {

         pitem->m_colorItemBackground = argb(0, 0, 0, 0);

      }


      if(pitem->m_item.m_iItem >= m_plisting->get_size()
         && ::is_set(papp->mediaplaylist()->spotify()))
      {

         synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex2);

         if(pitem->m_item.m_iItem < m_plisting->get_size() + papp->mediaplaylist()->spotify()->m_pla.get_count())
         {
            pitem->m_colorText = argb(255, 80, 184, 123);

            pitem->m_bOk = true;
            return;

         }



         pitem->m_bOk = false;


         return;

      }

      pitem->m_colorText = argb(255,0,0,0);

      pitem->m_bOk = true;

   }

   void playlist_list_impact::_001GetItemText(::user::mesh_item * pitem)
   {

      simple_form_list_impact::_001GetItemText(pitem);

      if (pitem->m_bOk)
      {

         return;

      }

      if(pitem->m_item.m_iItem < 0)
      {

         pitem->m_bOk = false;

         return;

      }

      if(pitem->m_item.m_iItem >= m_plisting->get_size())
      {

         synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex2);

         if(pitem->m_item.m_iItem < m_plisting->get_size() + papp->mediaplaylist()->spotify()->m_pla.get_count())
         {

            auto iItem = pitem->m_item.m_iItem - m_plisting->get_size();

            auto pl = papp->mediaplaylist()->spotify()->m_pla[iItem];

            string strName = pl->get_name();

            if(strName.is_empty())
            {

               strName = "Loading...";

            }

            if(pitem->m_item.m_iSubItem == 0)
            {

               pitem->m_strText =  "spotify://" + strName;

            }
            else if(pitem->m_item.m_iSubItem == 1)
            {

               pitem->m_strText ="spotify://" + strName;

            }
            else if(pitem->m_item.m_iSubItem == 2)
            {

               pitem->m_strText = strName;

            }
            else if(pitem->m_item.m_iSubItem == 3)
            {

               pitem->m_strText = "spotify://" + strName;

            }
            else if (pitem->m_item.m_iSubItem == 5)
            {

               pitem->m_strText = pl->m_strUrl;

            }

            pitem->m_bOk = true;

            return;

         }


         pitem->m_bOk = false;

         return;

      }

      ASSERT_VALID(this);
      //::pointer<::mediaplaylist::document>pdocument = get_document();
      //::file::path wstrSongPath;
      if(pitem->m_item.m_iSubItem == 0)
      {

         pitem->m_strText = (*m_plisting)[pitem->m_item.m_iItem];

      }
      else if(pitem->m_item.m_iSubItem == 1)
      {

         pitem->m_strText = (*m_plisting)[pitem->m_item.m_iItem];

      }
      else if(pitem->m_item.m_iSubItem == 2)
      {

         pitem->m_strText = (*m_plisting)[pitem->m_item.m_iItem].title();

      }
      else if(pitem->m_item.m_iSubItem == 3)
      {

         pitem->m_strText = (*m_plisting)[pitem->m_item.m_iItem];

      }

      pitem->m_bOk = true;

   }


   bool playlist_list_impact::on_click(::item * pitem)
   {

      index_array iaSelection;

      m_rangeSelection.get_items(iaSelection);

      if (item.m_iItem == m_iLastClickItem
            && iaSelection.get_count() == 1
            && iaSelection[0] == item.m_iItem)
      {

         m_cSameItemClick++;

      }
      else
      {

         m_cSameItemClick = 1;

      }

      m_iLastClickItem = item.m_iItem;

      if (!m_rangeHighlight.has_item(item.m_iItem))
      {

         if (m_cSameItemClick == 2)
         {


            fork([this, item]()
            {

               // play it ... (now)

               playlist_play(item.m_iItem);

            });

            return true;

         }

      }

      playlist_select(item.m_iItem);

      papp->m_pmediaplaylist->m_pstartup->m_pathDefault = papp->m_pmediaplaylist->m_pplaylistdoc->m_pathFile;

      return true;

   }


   //void playlist_list_impact::on_selection_change()
   //{

   //   ::user::range range;

   //   get_selection(range);

   //   if(range.get_item_count() > 0)
   //   {

   //      index iItem = range.ItemAt(0).get_lower_bound();

   //      playlist_select(iItem);

   //      string strPlaylist = papp->m_pmediaplaylist->m_pplaylistdoc->m_pathFile;

   //      if(strPlaylist.has_character())
   //      {

   //         papp->mediaplaylist()->datastream()->set("default_playlist",strPlaylist);

   //      }

   //   }

   //}


   ::collection::index playlist_list_impact::playlist_index()
   {

      ::file::path path;

      if (papp->m_pmediaplaylist != nullptr)
      {

         if (papp->m_pmediaplaylist->m_pplaylistdoc != nullptr)
         {

            if (papp->m_pmediaplaylist->m_pplaylistdoc->play_playlist() != nullptr)
            {

               path = papp->m_pmediaplaylist->m_pplaylistdoc->play_playlist()->m_path;

            }
            else
            {

               path = papp->m_pmediaplaylist->m_pplaylistdoc->m_pathFile;

            }

         }
         else
         {

            papp->m_pmediaplaylist->GetDefaultPath(path);

         }

      }

      if (path.is_empty())
      {

         return -1;

      }

      return playlist_index(path);

   }


   ::collection::index playlist_list_impact::playlist_index(const ::file::path & pathName)
   {

      auto pFind = m_plisting->predicate_find_first([=](auto & i)
      {

         return i == pathName;

      });

      if (::is_set(pFind))
      {

         return iFind;

      }

      if (papp->mediaplaylist() != nullptr  && papp->mediaplaylist()->spotify() != nullptr)
      {

         iFind = papp->mediaplaylist()->spotify()->m_pla.predicate_find_first([=](auto & i)
         {

            return i->m_path == pathName;

         });

         if (::is_set(pFind))
         {

            return m_plisting->get_size() + iFind;

         }

      }

      return -1;

   }


   void playlist_list_impact::update_playlist_hilite(const ::file::path & pathPlaylist)
   {

      ::collection::index iPlaylist = playlist_index(pathPlaylist);

      _001Highlight(iPlaylist, true);

   }


   bool playlist_list_impact::playlist_previous()
   {

      ::collection::index iItem = playlist_index();

      if (iItem < 0)
      {

         return false;

      }

      ::collection::index iNewItem = iItem - 1;

      if (iNewItem < 0)
      {

         iNewItem = _001GetItemCount()-1;

      }

      if (iItem == iNewItem)
      {

         return false;

      }

      while (!playlist_play(iNewItem))
      {

         iNewItem++;

         if (iNewItem < 0)
         {

            iNewItem = _001GetItemCount()-1;

         }

         if (iItem == iNewItem)
         {

            return false;

         }

      }

      return true;

   }


   bool playlist_list_impact::playlist_next()
   {

      ::collection::index iItem = playlist_index();

      if (iItem < 0)
      {

         return false;

      }

      ::collection::index iNewItem = iItem + 1;

      if (iNewItem >= _001GetItemCount())
      {

         iNewItem = 0;

      }

      if (iItem == iNewItem)
      {

         return false;

      }

      while(!playlist_play(iNewItem))
      {

         iNewItem++;

         if (iNewItem >= _001GetItemCount())
         {

            iNewItem = 0;

         }

         if (iItem == iNewItem)
         {

            return false;

         }

      }

      return true;

   }


   bool playlist_list_impact::playlist_roulette()
   {

      int iTry = 3;

restart:

      if(_001GetItemCount() <= 1)
      {

         return playlist_next();

      }

      ::collection::index iItem = playlist_index();

      ::collection::index iNewItem = -1;

      while(true)
      {

         iNewItem = random(0, _001GetItemCount() - 1);

         if(iNewItem != iItem)
         {

            break;

         }

      }

      if(!playlist_play(iNewItem))
      {

         if(iTry >= 0)
         {

            goto restart;

         }

         return false;

      }

      return true;

   }


   bool playlist_list_impact::playlist_play(::collection::index iItem)
   {

      if(!playlist_select(iItem))
      {

         return false;

      }

      if (get_document()->play_playlist() != nullptr
            && get_document()->play_playlist() != get_document()->impact_playlist())
      {

         get_document()->play_playlist()->save();

      }

      info info;

      string strPath = get_document()->impact_playlist()->m_path;

      //papp->mediaplaylist()->datastream()->get(strPath + ".current_song_millis", info.m_time);

      //papp->mediaplaylist()->datastream()->get(strPath + ".current_song", info.m_iCurrentSong);

      info.m_time = -1;

      info.m_iCurrentSong = -1;

      info.m_uHint               = id_do_play;
      info.m_bMakeVisible        = true;
      info.m_context       += ::e_source_user;

      get_document()->play(&info);

      return true;

   }

   bool playlist_list_impact::playlist_select(::collection::index iItem)
   {

      if (iItem < 0)
      {

         return false;

      }

      if(iItem >= m_plisting->get_count())
      {

         iItem -= m_plisting->get_count();

         synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex2);

         if(iItem < papp->mediaplaylist()->spotify()->m_pla.get_count())
         {

            string strPlaylist;

            for(::collection::index i = 0; i < 8; i++)
            {

               strPlaylist = papp->mediaplaylist()->spotify()->m_pla[iItem]->get_name();

               synchronouslock.unlock();

               if(strPlaylist.has_character())
               {

                  synchronouslock.lock();

                  break;

               }

               sleep(840_ms);

               synchronouslock.lock();

            }

            string strName = "spotify_playlist:" + strPlaylist;

            synchronouslock.unlock();

            if (!papp->mediaplaylist()->OpenPlaylist(strName, true))
            {

               return false;

            }

            return true;

         }


         return false;

      }

      if (!papp->mediaplaylist()->OpenPlaylist((*m_plisting)[iItem], true))
      {

         return false;

      }

      return true;

   }


   bool playlist_list_impact::playlist_erase(::collection::index iItem)
   {

      //::pointer<::mediaplaylist::document>pdocument = get_document();
      //return pdocument->RemoveSong(iItem);
      return true;

   }


   int playlist_list_impact::_001CalcItemHeight(int iBaseHeight)
   {

      return simple_form_list_impact::_001CalcItemHeight(iBaseHeight);

   }


   void playlist_list_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      simple_form_list_impact::_001OnDraw(pgraphics);

   }


} // namespace mediaplaylist


