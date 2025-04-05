#include "framework.h"

#include "base/update.h"


namespace mediaplaylist
{


   list_impact::list_impact()
   {

      create_int(::user::int_list_item_draw_text_flags, e_align_left_center | DT_SINGLELINE | DT_END_ELLIPSIS);

      m_bPendingEnsureVisible = false;

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

      //SetCacheInterface(&m_listcache);

      m_emode = mode_normal;
      //::type typeinfo = ::type < list_impact >();
      //m_dataid = typeinfo->name();
      //m_bGroup = true;
      //m_bLateralGroup = true;

      papp->mediaplaylist()->m_plistview = this;


      //////////////////////////////////////////
      //
      // m_bMultiSelect default is true
      //
      // m_bMultiSelect             = true;
      //
      //create_point_font(::user::font_list_item, "Arial Unicode", 16.0);

   }


   list_impact::~list_impact()
   {
   }

   void list_impact::install_message_routing(::channel * pchannel)
   {
      simple_form_list_impact::install_message_routing(pchannel);

      //MESSAGE_LINK(e_message_context_menu, pchannel, this, &list_impact::on_message_context_menu);
      MESSAGE_LINK(e_message_size, pchannel, this, &list_impact::on_message_size);
      MESSAGE_LINK(e_message_create, pchannel, this, &list_impact::on_message_create);
      MESSAGE_LINK(e_message_scroll_y, pchannel, this, &list_impact::on_message_scroll_y);

      add_command_handler("edit_delete", &list_impact::_001OnEditRemove);
      add_command_prober("edit_delete", &list_impact::_001OnUpdateEditRemove);
      add_command_handler("execute_play", &list_impact::_001OnPlaylistExecutePlay);
      add_command_prober("execute_play", &list_impact::_001OnUpdatePlaylistExecutePlay);
      add_command_handler("get_uri", &list_impact::_001OnGetUri);
   }



   void list_impact::assert_ok() const
   {
      simple_form_list_impact::assert_ok();
   }

   void list_impact::dump(dump_context & dumpcontext) const
   {
      simple_form_list_impact::dump(dumpcontext);
   }


   ::mediaplaylist::document * list_impact::get_document()
   {
      if(::user::impact::get_document() == nullptr)
         return nullptr;
      ASSERT(base_class <::mediaplaylist::document >::bases(::user::impact::get_document()));
      return dynamic_cast <::mediaplaylist::document *> (::user::impact::get_document());
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

      {

         auto pinteraction = __allocate ::user::control_descriptor();

         pinteraction->m_bTransparent = true;
         pinteraction->m_type = ::type < ::user::button >();

         pinteraction->id() = "play_button";
         pinteraction->add_function(::user::e_control_function_action);
         pinteraction->set_control_type(::user::e_control_type_button);

         auto pcolumn = new_list_column();
         pcolumn->m_uiText = "";
         pcolumn->m_iWidth = 18;
         pcolumn->m_iSubItem = subitem_play;
         pcolumn->m_iControl = _001AddControl(pinteraction);
         pcolumn->m_bCustomDraw = true;
         

      }


      //e_mode emode = m_emode;

      ////if(emode == mode_minimum)
      //{
      //  pcolumn->m_iWidth            = 300;
      //  pcolumn->m_uiText            = "<string atom='mediaplaylist:list_impact:file_name'>file name</string>";
      //  pcolumn->m_iSubItem          = 2;
      //  pcolumn->m_iSmallImageWidth  = 16;
      //  pcolumn->m_colorSmallMask       = rgb(255, 0, 255);
      //  _001AddColumn(column);
      //}
      //else if(emode == mode_normal)
      {
         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = 300;
         pcolumn->m_uiText = "<string atom='mediaplaylist:list_impact:title'>Title</string>";
         pcolumn->m_iSubItem = subitem_name;
         pcolumn->m_iSmallImageWidth = 16;
         pcolumn->m_colorSmallMask = rgb(255, 0, 255);
         

      }

      {
         auto pcolumn = new_list_column();

         pcolumn->m_iWidth = 300;
         pcolumn->m_uiText = "<string atom='mediaplaylist:list_impact:artist'>Artist</string>";
         pcolumn->m_iSubItem = subitem_artist;
         pcolumn->m_iSmallImageWidth = 16;
         pcolumn->m_colorSmallMask = rgb(255, 0, 255);
         

      }

      {

         auto pcolumn = new_list_column();


         pcolumn->m_iWidth = 300;
         pcolumn->m_uiText = "<string atom='mediaplaylist:list_impact:album'>Album</string>";
         pcolumn->m_iSubItem = subitem_album;
         pcolumn->m_iSmallImageWidth = 16;
         pcolumn->m_colorSmallMask = rgb(255, 0, 255);
         

      }

      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth            = 400;
         pcolumn->m_uiText            = "<string atom='mediaplaylist:list_impact:file_path'>File Path</string>";
         pcolumn->m_iSubItem          = subitem_path;
         
      }

   }


   void list_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(ptopic->id() == id_initial)
      {

         set_need_redraw();

      }
      else if (ptopic->id() == id_songs_changed)
      {

         m_listcache._001Invalidate(this);

         _001OnUpdateItemCount();

      }

      if (ptopic->id() == id_ensure_visible)
      {

         m_bPendingEnsureVisible = true;

      }

      auto pdocument = get_document();

      if (ptopic->id() == id_current_song_changed
            || ptopic->id() == id_impact_playlist_changed)
      {

         m_bPendingEnsureVisible = true;

         if (::is_set(pdocument->impact_playlist()))
         {

            get_document()->impact_playlist()->m_iCurrentVScroll = -1;

         }

         set_need_layout();

      }

      if (ptopic->id() == id_playlist_list_selection_changed)
      {

         m_bHighHighLight = pdocument->impact_playlist() == pdocument->playback_playlist();

      }

      if(ptopic->id() == id_frame_down)
      {

         if (GetMode() == mode_normal)
         {

            SetMode(mode_minimum);

         }
         else
         {

            SetMode(mode_normal);

         }

      }
      else if(ptopic->id() == id_frame_up)
      {

         if (GetMode() == mode_minimum)
         {

            SetMode(mode_normal);

         }
         else
         {

            SetMode(mode_minimum);

         }

      }

      ASSERT_VALID(this);

      ////__update(::update)
      {

         bool bAllUpdates = ptopic->id() == id_full;

         if (bAllUpdates || ptopic->id() == id_current_song)
         {

            if (pdocument->impact_playlist() != nullptr && pdocument->play_playlist() != nullptr
                  && pdocument->impact_playlist()->m_path == pdocument->play_playlist()->m_path)
            {

               on_change_impact();

            }

         }

         if (bAllUpdates || ptopic->id() == id_get_attachable_impact)
         {

            pupdate->cast < pointer_array < ::user::impact > > (id_attachable)->add(this);

         }

         if(ptopic->id() == id_pop)
         {
            ::pointer<::simple_frame_window>pframewnd = (::user::list::get_parent_frame());
            OnActivateFrame(WA_INACTIVE, pframewnd);
            pframewnd->ActivateFrame(e_display_normal);
            OnActivateImpact(true, this, this);
            set_need_redraw();
         }
         else if(ptopic->id() == id_initial)
         {
            _001UpdateColumns();
            _001OnUpdateItemCount();
         }

      }

   }


   bool list_impact::WndFrameworkDownUpGetUpEnable()
   {
   
      return get_parent_frame()->get_parent() != nullptr || GetMode() == mode_minimum;

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


   bool list_impact::on_click(::item * pitem)
   {

      if (papp->mediaplaylist()->m_bProcessingQueue)
      {

         if (get_document()->play_playlist() != nullptr
               &&
               (get_document()->play_playlist()->m_strTitle != "LCTV"
                || item.m_iItem < get_document()->play_playlist()->m_iCurrentSong))
         {

            papp->mediaplaylist()->m_bProcessingQueue = false;

         }

      }

      info info;

      info.m_iCurrentSong = item.m_iItem;
      info.m_uHint = id_do_play;
      info.m_bMakeVisible = true;

      get_document()->play(&info);

      return true;

   }


   //bool list_impact::on_click(::item * pitem)
   //{

   //   index iItem;

   //   if(_001HitTest_(pt, iItem))
   //   {

   //      if (papp->mediaplaylist()->m_bProcessingQueue)
   //      {

   //         if (get_document()->play_playlist() != nullptr
   //               &&
   //               (get_document()->play_playlist()->m_strTitle != "LCTV"
   //                || iItem < get_document()->play_playlist()->m_iCurrentSong))
   //         {

   //            papp->mediaplaylist()->m_bProcessingQueue = false;

   //         }

   //      }

   //      info info;

   //      info.m_iCurrentSong = iItem;
   //      info.m_ehint = id_do_play;
   //      info.m_bMakeVisible = true;

   //      get_document()->play(&info);

   //   }

   //   return true;

   //}




   void list_impact::_001GetItemImage(::user::mesh_item * pitem)
   {
      if(pitem->m_item.m_iSubItem == subitem_play || pitem->m_item.m_iSubItem == 1)
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


   void list_impact::_001OnGetUri(::message::message * pmessage)
   {

      ::user::range range;

      get_selection(range);

      string_array stra;

      for (::collection::index i = 0; i < range.get_item_count(); i++)
      {

         for (::collection::index j = range.m_itemrangea[i].m_iLowerBound; j <= range.m_itemrangea[i].m_iUpperBound; j++)
         {

            if (get_document()->impact_playlist() != nullptr
                  && j >= 0
                  && j < get_document()->impact_playlist()->m_tracka.get_size())
            {

               string strUri = get_document()->impact_playlist()->m_tracka[j]->get_uri();

               if (strUri.has_character())
               {

                  stra.add_unique(strUri);

               }

            }




         }

      }

      if (stra.has_elements())
      {

         psession->copydesk().set_plain_text(stra.implode("\n"));

      }

   }


   bool list_impact::on_right_click(const ::item & item)
   {

      track_popup_xml_menu("matter://spotify_playlist.xml", 0, item.m_pointScreen);

      return true;

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


   void list_impact::_001OnEditRemove(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      //_001RemoveSelection();

      ::user::range range;

      get_selection(range);

      index_array ia;

      for (::collection::index i = 0; i < range.get_item_count(); i++)
      {

         for(::collection::index j = range.m_itemrangea[i].m_iLowerBound; j <= range.m_itemrangea[i].m_iUpperBound; j++)
         {

            ia.add_unique(j);

         }

      }

      ::sort::quick_sort(ia, false);

      ::pointer<::mediaplaylist::document>pdocument = get_document();

      for (auto iItem : ia)
      {

         if (pdocument->RemoveSong(iItem, nullptr, false))
         {
            if (pdocument->play_playlist() != nullptr)
            {
               ::papaya::x1_on_erase(index_array({ iItem }), pdocument->play_playlist()->m_iCurrentSong);
            }
         }

      }

      pdocument->OnRemoveSong(this);

      get_document()->on_save_document(nullptr);

      pmessage->m_bRet = true;

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
         info.m_uHint         = id_do_play;
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

   void list_impact::on_message_scroll_y(::message::message * pmessage)
   {

      ::mediaplaylist::document * pdocument = get_document();

      if (pdocument != nullptr)
      {

         ::multimedia_playlist::playlist * pplImpact = pdocument->impact_playlist();

         if (pplImpact != nullptr)
         {

            pplImpact->m_iCurrentVScroll = get_context_offset().y();

         }

      }

   }


   void list_impact::_001OnInitializeControl(::pointer<::user::interaction>pinteraction)
   {

      simple_form_list_impact::_001OnInitializeControl(pinteraction);

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
         info.m_uHint            = id_do_play;
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


      m_pimagelistSubItemHover   = __allocate image_list();
      m_pimagelistNormal         = __allocate image_list();
      m_pimagelistItemHover      = __allocate image_list();

      m_pimagelistSubItemHover->create(16, 16, 0,  10, 10);
      m_pimagelistSubItemHover->add_file("matter://mediaplaylist/execute_play_16.png");


      ::draw2d::graphics_pointer spgraphics(e_create);
      spgraphics->CreateCompatibleDC(nullptr);

      psystem->imaging().change_hue(
      m_pimagelistNormal,
      m_pimagelistSubItemHover,
      rgb(220, 220, 215),
      0.50);

      psystem->imaging().color_blend(
      m_pimagelistItemHover,
      m_pimagelistSubItemHover,
      rgb(220, 220, 215),
      127);

      m_pimagelistGroupHover = __allocate image_list();

      m_pimagelistGroupHover->create(96, 96, 0,  10, 10);
      m_pimagelistGroupHover->add_file("matter://mediaplaylist/playlist_96.png");
      m_pimagelistGroup = m_pimagelistGroupHover;

      _001UpdateColumns();

   }


   void list_impact::_001GetItemText(::user::mesh_item * pitem)
   {

      ::pointer<::mediaplaylist::document>pdocument = get_document();

      ::pointer<::multimedia_playlist::playlist>pl = pdocument->impact_playlist();

      if (pl.is_null())
      {

         return;

      }

      synchronous_lock synchronouslock(pl->m_psession->mutex());

      if (pl.is_set() && pitem->m_item.m_iItem < pl->m_tracka.get_size())
      {

         ::pointer<::multimedia_playlist::track>ptr = pl->m_tracka[pitem->m_item.m_iItem];

         if (pitem->m_item.m_iSubItem == subitem_name)
         {

            pitem->m_strText = ptr->get_name();

         }
         else if (pitem->m_item.m_iSubItem == subitem_artist)
         {

            pitem->m_strText = ptr->get_artist();

         }
         else if (pitem->m_item.m_iSubItem == subitem_album)
         {

            pitem->m_strText = ptr->get_album();

         }
         else if (pitem->m_item.m_iSubItem == subitem_path)
         {

            pitem->m_strText = ptr->get_id();

         }

      }

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
      ::mediaplaylist::document * pdocument = get_document();
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

   int list_impact::_001CalcItemHeight(int iBaseHeight)
   {

      return simple_form_list_impact::_001CalcItemHeight(iBaseHeight);

   }

   
   int list_impact::_001GetDrawTextFlags(::user::list::enum_impact eview)
   {

      return ::user::list::_001GetDrawTextFlags(eview);

   }


   void list_impact::defer_update_track_hilite()
   {

      m_rangeHighlight.clear();

      ::user::item_range itemrange;

      itemrange.m_iLowerBound = get_document()->impact_playlist()->m_iCurrentSong;

      itemrange.m_iUpperBound = get_document()->impact_playlist()->m_iCurrentSong;

      m_rangeHighlight.add_item(itemrange);

   }

   void list_impact::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


      simple_form_list_impact::_000OnDraw(pgraphics);

      //defer_check_layout();

      //defer_check_zorder();

      //if (!is_this_visible())
      //   return;

      //try
      //{

      //   if (pgraphics == nullptr)
      //   {

      //      throw ::exception(error_bad_argument);

      //   }

      //   ::draw2d::keep k(pgraphics);

      //   try
      //   {

      //      if (!is_custom_draw() && pgraphics != nullptr && pgraphics->m_pnext == nullptr)
      //      {

      //         set_context_org(pgraphics);

      //      }

      //      pgraphics->m_dFontFactor = 1.0;

      //      //try
      //      //{

      //      //   pgraphics->SelectClipRgn(nullptr);

      //      //}
      //      //catch(...)
      //      //{

      //      //   throw ::exception(::exception("no more a window"));

      //      //}

      //      {

      //         synchronous_lock synchronouslock(this->synchronization());

      //         _001OnNcDraw(pgraphics);

      //      }

      //      _001OnClip(pgraphics);

      //      ::double_rectangle rectangleTest1(100, 100, 200, 200);

      //      pgraphics->fill_rectangle(rectangleTest1, argb(255, 255, 255, 0));

      //      _001CallOnDraw(pgraphics);


      //   }
      //   catch (...)
      //   {

      //      informationf("Exception: interaction::_001DrawThis %s", ::type(this).name());

      //   }

      //   if (m_pparent != nullptr)
      //   {

      //      on_after_graphical_update();

      //   }

      //}
      //catch (...)
      //{

      //   informationf("Exception: interaction::_000OnDraw _001DrawThis %s", ::type(this).name());

      //}


      //if (m_uiptraChild.has_elements())
      //{

      //   try
      //   {

      //      _001DrawChildren(pgraphics);

      //   }
      //   catch (...)
      //   {

      //      informationf("Exception: interaction::_000OnDraw _001DrawChildren %s", ::type(this).name());

      //   }

      //}

      //try
      //{

      //   _008CallOnDraw(pgraphics);

      //}
      //catch (...)
      //{

      //   informationf("Exception: interaction::_000OnDraw _008CallOnDraw %s", ::type(this).name());

      //}

   }

   void list_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //return;

      simple_form_list_impact::_001OnDraw(pgraphics);

   }


   void list_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      simple_form_list_impact::on_layout(pgraphics);

      if (m_bPendingEnsureVisible)
      {

         if (get_document() != nullptr && get_document()->impact_playlist() != nullptr)
         {

            if (get_document()->impact_playlist()->m_iCurrentVScroll < 0)
            {

               _001EnsureVisible(get_document()->impact_playlist()->m_iCurrentSong);

               get_document()->impact_playlist()->m_iCurrentVScroll = get_context_offset().y();

            }
            else
            {

               set_context_offset_y(get_document()->impact_playlist()->m_iCurrentVScroll);

            }

         }

         m_bPendingEnsureVisible = false;

      }



   }

} // namespace mediaplaylist


