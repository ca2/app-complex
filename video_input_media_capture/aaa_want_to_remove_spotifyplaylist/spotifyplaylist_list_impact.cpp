#include "framework.h"



namespace mediaplaylist
{


   list_impact::list_impact(::particle * pparticle) :
      ::object(pparticle),
      ::user::interaction(pparticle),
      simple_form_list_impact(pparticle)
   {
      ::draw2d::graphics_pointer spgraphics(e_create);
      spgraphics->CreateCompatibleDC(nullptr);

      m_iGroupMinHeight = 96;
      /*   m_pimagelistSubItemHover->add(
            (HICON) ::LoadImage(
               psystem->m_hInstance,
               MAKEINTRESOURCE(IDI_EXECUTE_PLAY),
               IMAGE_ICON,
               16,
               16,
               LR_SHARED));*/

      /*  psystem->imaging().Createcolor_blend_ImageList(
            &m_pimagelistNormal,
            &m_pimagelistHover,
            rgb(255, 255, 240),
            64);*/

      SetCacheInterface(&m_listcache);

      m_emode = mode_normal;
      //::type typeinfo = ::type < list_impact >();
      //m_dataid = typeinfo->name();
      //m_bGroup = true;
      //m_bLateralGroup = true;


   }

   list_impact::~list_impact()
   {
   }

   void list_impact::install_message_routing(::channel * pchannel)
   {
      simple_form_list_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &list_impact::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &list_impact::on_message_context_menu);
      MESSAGE_LINK(e_message_size, pchannel, this, &list_impact::on_message_size);
      MESSAGE_LINK(e_message_create, pchannel, this, &list_impact::on_message_create);

      add_command_handler("edit_delete", &list_impact::_001OnEditRemove);
      add_command_prober("edit_delete", &list_impact::_001OnUpdateEditRemove);
      add_command_handler("execute_play", &list_impact::_001OnPlaylistExecutePlay);
      add_command_prober("execute_play", &list_impact::_001OnUpdatePlaylistExecutePlay);
   }



   void list_impact::assert_ok() const
   {
      simple_form_list_impact::assert_ok();
   }

   void list_impact::dump(dump_context & dumpcontext) const
   {
      simple_form_list_impact::dump(dumpcontext);
   }

   ::pointer<::mediaplaylist::document>list_impact::get_document() const// non-debug version is inline
   {
      if(::user::impact::get_document() == nullptr)
         return nullptr;
      ASSERT(base_class <::mediaplaylist::document >::bases(::user::impact::get_document()));
      return  (::user::impact::get_document());
   }

   /////////////////////////////////////////////////////////////////////////////
   // list_impact message handlers

   bool list_impact::pre_create_window(::user::system * pusersystem)
   {
      //   pusersystem->m_createstruct.style |= LVS_REPORT;
      //   pusersystem->m_createstruct.style |= LVS_OWNERDRAWFIXED;
      //   pusersystem->m_createstruct.style |= LVS_OWNERDATA;

      return simple_form_list_impact::pre_create_window(pusersystem);
   }



   void list_impact::SetMode(e_mode emode)
   {
      m_emode = emode;
      //   CListCtrl & list = GetListCtrl();
      //   while(list.DeleteColumn(0));
      _001UpdateColumns();
      set_need_redraw();

   }


   void list_impact::on_insert_columns()
   {

      class ::user::control_descriptor control;

      control.m_bTransparent              = true;
      control.m_type                  = ::type < ::user::button >();
      control.id()                        = "play_button";
      control.add_function(::user::e_control_function_action);
      control.set_type(::user::e_control_type_button);

      auto pcolumn = new_list_column();

      pcolumn->m_iWidth                     = 18;
      pcolumn->m_iSubItem                   = 1;
      pcolumn->m_iControl                   = _001AddControl(control);
      pcolumn->m_bCustomDraw                = true;
      _001AddColumn(column);

      pcolumn->m_iControl = -1;


      e_mode emode = m_emode;

      if(emode == mode_minimum)
      {
         pcolumn->m_iWidth            = 300;
         pcolumn->m_uiText            = "<string atom='mediaplaylist:list_impact:file_name'>file name</string>";
         pcolumn->m_iSubItem          = 2;
         pcolumn->m_iSmallImageWidth  = 16;
         pcolumn->m_colorSmallMask       = rgb(255, 0, 255);
         _001AddColumn(column);
      }
      else if(emode == mode_normal)
      {
         pcolumn->m_iWidth            = 170;
         pcolumn->m_uiText            = "<string atom='mediaplaylist:list_impact:file_name'>file name</string>";
         pcolumn->m_iSubItem          = 2;
         pcolumn->m_iSmallImageWidth  = 16;
         pcolumn->m_colorSmallMask       = rgb(255, 0, 255);
         _001AddColumn(column);

         pcolumn->m_iWidth            = 400;
         pcolumn->m_uiText            = "<string atom='mediaplaylist:list_impact:file_path'>file path</string>";
         pcolumn->m_iSubItem          = 3;
         _001AddColumn(column);

      }



   }

   void list_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {
      __UNREFERENCED_PARAMETER(pimpact);
      if(eupdate == 0)
      {
         _001UpdateColumns();
      }
      else if(eupdate == 5000)
      {
         _001OnUpdateItemCount();
      }
      ::pointer<::mediaplaylist::document>pdocument = get_document();
      if(eupdate == ::mediaplaylist::document::LHINT_FRAMEDOWN)
      {
         if(GetMode() == mode_normal)
            SetMode(mode_minimum);
         else
            SetMode(mode_normal);
      }
      else if(eupdate == ::mediaplaylist::document::LHINT_FRAMEUP)
      {
         if(GetMode() == mode_minimum)
            SetMode(mode_normal);
         else
            SetMode(mode_minimum);
      }

      ASSERT_VALID(this);
      ::update * ppluh = (::update *) pHint;
      ::update * pupdate = (::update *) pHint;
      bool bAllUpdates = pHint == nullptr
                         ||
                         (ppluh != nullptr
                          && ppluh->GetHint() == ::update::HintFull);
      if(bAllUpdates ||
            ppluh != nullptr)
      {
         if(bAllUpdates ||
               ppluh->GetHint() == ::update::HintFull)
         {
            _001OnUpdateItemCount();
            set_need_redraw();
         }

         if(bAllUpdates ||
               ppluh->GetHint() == ::update::HintCurrentSong)
         {
            if(pdocument->m_impact.m_path == pdocument->m_play.m_path)
            {
               on_change_impact();
            }

         }
      }
      if(ppluh != nullptr)
      {
         if(ppluh->GetHint() ==
               update_get_attachable_impact)
         {
            ppluh->AddAttachableImpact(this);
         }
      }
      if(pupdate != nullptr)
      {
         switch(pupdate->GetHint())
         {
         case update_pop:
         {
            ::pointer<::simple_frame_window>pframewnd =  (::user::list::get_parent_frame());
            OnActivateFrame(WA_INACTIVE, pframewnd);
            pframewnd->ActivateFrame(e_display_normal);
            OnActivateImpact(true, this, this);
            set_need_redraw();
         }
         break;
         case ::update::HintInitial:
         {
            _001UpdateColumns();
            _001OnUpdateItemCount();
            handle(::topic * ptopic, ::handler_context * pcontext);
         }
         break;
         }
      }
      m_listcache._001Invalidate();
      _001OnUpdateItemCount();


   }


   void list_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      simple_form_list_impact::handle(::topic * ptopic, ::handler_context * pcontext);

      //_001UpdateColumns();

      set_need_redraw();

      informationf("list_impact::OnInitialUpdate() oswindow = %d\n", get_handle());

      /*   CTransparentFrameWndV4 * pframe = dynamic_cast < CTransparentFrameWndV4 * > (get_parent_frame());
         if(pframe != nullptr)
         {
            pframe->GetWndFramework()->SetDownUpInterface(this);
            pframe->SetDownUpInterface(this);
         }*/
   }


   bool list_impact::WndFrameworkDownUpGetUpEnable()
   {
      return get_parent_frame()->get_parent() != nullptr
             || GetMode() == mode_minimum;
   }
   bool list_impact::WndFrameworkDownUpGetDownEnable()
   {
      return get_parent_frame()->get_parent() == nullptr
             || GetMode() == mode_normal;
   }

   bool list_impact::TransparentFrameWndDownUpGetUpEnable()
   {
      return get_parent_frame()->get_parent() != nullptr &&
             GetMode() == mode_normal;
   }
   bool list_impact::TransparentFrameWndDownUpGetDownEnable()
   {
      return get_parent_frame()->get_parent() == nullptr &&
             GetMode() == mode_minimum;
   }

   list_impact::e_mode list_impact::GetMode()
   {
      return m_emode;
   }


   void list_impact::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::int_point point(pmouse->m_point);

      screen_to_client()(point);

      ::collection::index iItem;

      if(_001HitTest_(pt, iItem))
      {

         info info;

         info.m_iCurrentSong = iItem;
         info.m_ehint = id_do_play;
         info.m_bMakeVisible = true;

         get_document()->play(&info);

      }

   }




   void list_impact::_001GetItemImage(::user::mesh_item * pitem)
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

   void list_impact::on_message_context_menu(::message::message * pmessage)
   {
      ::pointer<::message::context_menu>pcontextmenu(pmessage);
      ::int_point point = pcontextmenu->GetPoint();
      ::collection::index iItem;
      ::int_point ptClient = point;
      screen_to_client(&ptClient);
      if(_001HitTest_(ptClient, iItem))
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

   void list_impact::on_message_size(::message::message * pmessage)
   {
      pmessage->previous();

      update_drawing_objects();
   }

   void list_impact::update_drawing_objects()
   {
//      cube1sp(::aura::application) papp = dynamic_cast < cube1sp(::aura::application) > (this);
      //    ASSERT(papp != nullptr);
      //   ::aura::savings & savings = session()->savings();
      /*   m_enhmetafile = papp->LoadEnhMetaFile(IDR_MUSICALPLAYER);*/
      /*      if(m_enhmetafile != nullptr)
            {
                 GetEnhMetaFileHeader(
                     m_enhmetafile,
                     sizeof(m_emh),
                     &m_emh);
            }*/

   }

   void list_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      simple_form_list_impact::_001OnDraw(pgraphics);
   }

   void list_impact::_001OnEditRemove(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      _001RemoveSelection();
      get_document()->on_save_document(nullptr);
   }

   void list_impact::_001OnUpdateEditRemove(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);

      ::user::range range;

      get_selection(range);

      pcommand->enable(range.get_item_count() > 0);
      pcommand->m_bRet = true;
   }

   bool list_impact::_001OnRemoveItem(::collection::index iItem)
   {
      ::pointer<::mediaplaylist::document>pdocument = get_document();
      return pdocument->RemoveSong(iItem);
   }

   /*PaneImpact * list_impact::GetParentPane()
   {
      //::pointer<::user::interaction>puserinteraction = get_parent();
      if(base_class <PaneImpact >::bases(puserinteraction))
      {
         return dynamic_cast < PaneImpact * > (puserinteraction);
      }*/
   /* return nullptr;
   }*/

   void list_impact::_001DrawBackground(::draw2d::graphics *graphics, ::int_rectangle * lprect)
   {
      ::double_rectangle rectangleThis;
      this->rectangle(rectangleThis);

//      ::user::list::_001DrawBackground(pgraphics, lprect);

      /*   if(m_enhmetafile != nullptr)
         {
            ::double_rectangle rectangleUpdate;
            pgraphics->get_clip_box(rectangleUpdate);
            CBaseRect rectangleMeta;

            rectangleMeta.left() = 0;
            rectangleMeta.top() = 0;
            rectangleMeta.right() = m_emh.rclBounds.right() - m_emh.rclBounds.left();
            rectangleMeta.bottom() = m_emh.rclBounds.bottom() - m_emh.rclBounds.top();
            rectangleMeta.FitOnCenterOf(rectangleThis);

            m_gimageuffer.GetBuffer()->PlayMetaFile(m_enhmetafile, rectangleMeta);

            class imaging & imaging = psystem->imaging();
            imaging.bitmap_blend(
               pgraphics,
               rectangleUpdate.left(),
               rectangleUpdate.top(),
               rectangleUpdate.width(),
               rectangleUpdate.height(),
               m_gimageuffer.GetBuffer(),
               rectangleUpdate.left(),
               rectangleUpdate.top(),
               96);
         }*/

   }

   void list_impact::_001OnPlaylistExecutePlay(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      ::user::range range;
      get_selection(range);
      if(range.get_item_count() > 0)
      {
         ::collection::index iItem = range.ItemAt(0).get_lower_bound();

         info info;

         info.m_iCurrentSong  = iItem;
         info.m_ehint         = id_do_play;
         info.m_bMakeVisible  = true;

         get_document()->play(&info);

      }


   }

   void list_impact::_001OnUpdatePlaylistExecutePlay(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);
      ::user::range range;
      get_selection(range);
      pcommand->enable(range.get_item_count() > 0);
      pcommand->m_bRet = true;
   }


   void list_impact::_001OnInitializeForm(::pointer<::user::interaction>pinteraction)
   {
      simple_form_list_impact::_001OnInitializeForm(pinteraction);
      if(pinteraction->descriptor().id() == "play_button")
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

   void list_impact::_001OnButtonAction(::pointer<::user::interaction>pinteraction)
   {
      if(pinteraction->descriptor().id() == "play_button")
      {

         info info;

         info.m_iCurrentSong     = pinteraction->GetEditItem();
         info.m_ehint            = id_do_play;
         info.m_bMakeVisible     = true;
         info.m_context    += ::e_source_user;

         get_document()->play(&info);

      }
   }

   ::collection::count list_impact::_001GetItemCount()
   {
      if(get_document() != nullptr)
         return get_document()->get_song_count(true);
      else
         return -1;
   }


   void list_impact::on_message_create(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);

      pmessage->previous();


      m_pimagelistSubItemHover   = ___new image_list(this);
      m_pimagelistNormal         = ___new image_list(this);
      m_pimagelistItemHover      = ___new image_list(this);

      m_pimagelistSubItemHover->create(16, 16, 0,  10, 10);
      m_pimagelistSubItemHover->add_matter("mediaplaylist/execute_play_16.png");


      ::draw2d::graphics_pointer spgraphics(e_create);
      spgraphics->CreateCompatibleDC(nullptr);

      psystem->imaging().CreateHueImageList(
      spgraphics,
      m_pimagelistNormal,
      m_pimagelistSubItemHover,
      rgb(220, 220, 215),
      0.50);

      psystem->imaging().Createcolor_blend_ImageList(
      m_pimagelistItemHover,
      m_pimagelistSubItemHover,
      rgb(220, 220, 215),
      127);

      m_pimagelistGroupHover   = ___new image_list(this);

      m_pimagelistGroupHover->create(96, 96, 0,  10, 10);
      m_pimagelistGroupHover->add_matter("mediaplaylist/playlist_96.png");
      m_pimagelistGroup = m_pimagelistGroupHover;
   }

   //::collection::count list_impact::_001GetGroupCount()
   //{
   //   if(get_document() == nullptr)
   //      return 0;
   //   if(get_document()->m_pnodePlaylist == nullptr)
   //      return 0;
   //   if(get_document()->is_recursive())
   //   {
   //      return get_document()->m_pnodePlaylist->get_children_count("playlist", -1) + 1;
   //   }
   //   else
   //   {
   //      return 1;
   //   }
   //}

   //::collection::count list_impact::_001GetGroupItemCount(::collection::index iGroup)
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
   //         ::pointer<::xml::node>pnode = get_document()->m_pnodePlaylist->get_child_at("playlist", iGroup, -1);
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

   void list_impact::_001GetItemText(::user::mesh_item * pitem)
   {

      simple_form_list_impact::_001GetItemText(pitem);

      if(pitem->m_bOk)
         return;

      ASSERT_VALID(this);
      ::pointer<::mediaplaylist::document>pdocument = get_document();
      ::file::path wstrSongPath;

      if(pdocument->get_song_at(wstrSongPath, pitem->m_item.m_iItem, true))
      {
         if(pitem->m_item.m_iSubItem == 0)
         {
            pitem->m_strText = wstrSongPath;
         }
         else if(pitem->m_item.m_iSubItem == 1)
         {
            pitem->m_strText = wstrSongPath;
         }
         else if(pitem->m_item.m_iSubItem == 2)
         {
            pitem->m_strText = wstrSongPath.name();
         }
         else if(pitem->m_item.m_iSubItem == 3)
         {
            pitem->m_strText = wstrSongPath;
         }
      }
      /*    else
          {
            if(iSubItem == 0)
            {
                 str.formatf(L"?????");
            }
            else if(iSubItem == 1)
            {
                 str.formatf(L"?????");
            }
            else if(iSubItem == 2)
            {
                  str = wstrSongPath;
              }
          }*/
      pitem->m_bOk = true;
      /*    if(pDataCentral->IsWorking()
            &&   pdocument->GetSongPath(wstrSongPath, iItem)
            &&   pSongsSet->FindPath(wstrSongPath))
          {
            if(iSubItem == 0)
            {
               pSongsSet->GetData(1);
               str.formatf(L"%d", pSongsSet->m_iCode);
            }
            else if(iSubItem == 1)
            {
               pSongsSet->GetData(1);
               str.formatf(L"%d", pSongsSet->m_iCode);
            }
            else if(iSubItem == 2)
            {
                 pSongsSet->GetData(2);
                 str = pSongsSet->m_bstrName;
             }
         }
          else
          {
            if(iSubItem == 0)
            {
                 str.formatf("?????");
            }
            else if(iSubItem == 1)
            {
                 str.formatf("?????");
            }
            else if(iSubItem == 2)
            {
                  str = wstrSongPath;
              }
          }*/
      pitem->m_bOk = true;
   }

   //::collection::count list_impact::_001GetGroupMetaItemCount(::collection::index iGroup)
   //{
   //   __UNREFERENCED_PARAMETER(iGroup);
   //   return 1;
   //}

   //void list_impact::_001GetGroupText(::user::mesh_item * pitem)
   //{
   //   if(get_document() == nullptr)
   //      return_(pitem->m_bOk, false);
   //   if(get_document()->m_pnodePlaylist == nullptr)
   //      return_(pitem->m_bOk, false);
   //   if(get_document()->is_recursive())
   //   {
   //      if(pitem->m_iGroup == m_nGroupCount - 1)
   //      {
   //         pitem->m_bOk = get_document()->m_pnodePlaylist->get_attr("name", pitem->m_strText);
   //      }
   //      else
   //      {
   //         ::pointer<::xml::node>pnode = get_document()->m_pnodePlaylist->get_child_at("playlist", pitem->m_iGroup, -1);
   //         if(pnode == nullptr)
   //            return_(pitem->m_bOk, false);
   //         pitem->m_bOk = pnode->get_attr("name", pitem->m_strText);
   //      }
   //   }
   //   else
   //   {
   //      pitem->m_bOk = get_document()->m_pnodePlaylist->get_attr("name", pitem->m_strText);
   //   }
   //}

   //void list_impact::_001GetGroupImage(::user::mesh_item * pitem)
   //{
   //   pitem->m_bOk = true;
   //   pitem->m_iImage = 0;
   //}

   void list_impact::on_change_impact()
   {
      ::pointer<::mediaplaylist::document>pdocument = get_document();
      ::user::range range;
      item_range itemrange;
      itemrange.set(pdocument->get_current_song(false),
                    pdocument->get_current_song(false),
                    0,
                    m_columna.get_count(),
                    -1,-1);
      range.add_item(itemrange);
      _001SetHighlightRange(range);
      set_need_redraw();

   }

} // namespace mediaplaylist


