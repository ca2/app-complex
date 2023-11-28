#include "framework.h"



namespace mediaplaylist
{


   playlist_list_impact::playlist_list_impact(::particle * pparticle):
      ::object(pparticle),
      ::user::interaction(pparticle),
      simple_form_list_impact(pparticle),
      m_listing(pparticle)
   {

      m_emode = mode_normal;
      m_eview = impact_report;
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
      MESSAGE_LINK(e_message_size,pchannel,this,&playlist_list_impact::on_message_size);
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

   ::pointer<::mediaplaylist::document>playlist_list_impact::get_document() const// non-debug version is inline
   {
      if(::user::impact::get_document() == nullptr)
         return nullptr;
      ASSERT(base_class <::mediaplaylist::document >::bases(::user::impact::get_document()));
      return  (::user::impact::get_document());
   }


   void playlist_list_impact::SetMode(e_mode emode)
   {

      m_emode = emode;

      _001UpdateColumns();

   }


   void playlist_list_impact::on_insert_columns()
   {


      {

         class ::user::control_descriptor control;

         control.m_bTransparent              = true;
         control.m_type                  = ::type < ::user::button >();
         control.m_atom                        = "play_button";
         control.add_function(::user::e_control_function_action);
         control.set_type(::user::e_control_type_button);

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth                     = 18;
         pcolumn->m_iSubItem                   = 1;
         pcolumn->m_iControl                   = _001AddControl(control);
         pcolumn->m_bCustomDraw                = true;
         _001AddColumn(column);

      }


      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth            = 300;
         pcolumn->m_uiText            = "Name";
         pcolumn->m_iSubItem          = 2;
         _001AddColumn(column);

      }



      e_mode emode = m_emode;

      if(emode == mode_verbose)
      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth            = 300;
         pcolumn->m_uiText            = "<string atom='mediaplaylist:playlist_list_impact:file_name'>file name</string>";
         pcolumn->m_iSubItem          = 3;
         pcolumn->m_iSmallImageWidth  = 16;
         pcolumn->m_colorSmallMask       = rgb(255,0,255);
         _001AddColumn(column);
      }


   }

   void playlist_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {
      UNREFERENCED_PARAMETER(pimpact);

      if(eupdate == 0)
      {

         _001UpdateColumns();

      }
      else if(eupdate == (5000))
      {

         m_listing.erase_all();

         papp->mediaplaylist()->GetPath(m_listing);

         _001OnUpdateItemCount();
      }



   }


   void playlist_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      simple_form_list_impact::handle(::topic * ptopic, ::context * pcontext);

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

      index iItem;

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
      ::point_i32 point = pcontextmenu->GetPoint();
      index iItem;
      ::point_i32 ptClient = point;
      screen_to_client(&ptClient);
      if(_001HitTest_(ptClient,iItem))
      {
         //     SimpleMenu menu(BaseMenuCentral::GetMenuCentral(this));
         /*      if (menu.LoadMenu(IDR_POPUP_PLAYLIST_ITEM))
         {
         SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
         ASSERT(pPopup != nullptr);
         frame_window * pframe = get_parent_frame();
         pPopup->TrackPopupMenu(
         point.x(), point.y(),
         (::user::interaction_impl *) pframe);
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
         (::user::interaction_impl *) pframe);
         }*/
      }
   }


   void playlist_list_impact::_001OnEditRemove(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
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
      UNREFERENCED_PARAMETER(pmessage);
      ::user::range range;
      get_selection(range);
      if(range.get_item_count() > 0)
      {
         index iItem = range.ItemAt(0).get_lower_bound();

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


   void playlist_list_impact::_001OnInitializeForm(::pointer<::user::interaction>pinteraction)
   {
      simple_form_list_impact::_001OnInitializeForm(pinteraction);
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

   ::count playlist_list_impact::_001GetItemCount()
   {

      return m_listing.get_count();

   }


   void playlist_list_impact::on_message_create(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);

      pmessage->previous();


      m_pimagelistSubItemHover   = __new< image_list >(this);
      m_pimagelistNormal         = __new< image_list >(this);
      m_pimagelistItemHover      = __new< image_list >(this);

      m_pimagelistSubItemHover->create(16,16,0,10,10);
      m_pimagelistSubItemHover->add_matter("mediaplaylist/execute_play_16.png");


      ::draw2d::graphics_pointer spgraphics(e_create);
      spgraphics->CreateCompatibleDC(nullptr);

      psystem->imaging().CreateHueImageList(
      spgraphics,
      m_pimagelistNormal,
      m_pimagelistSubItemHover,
      rgb(220,220,215),
      0.50);

      psystem->imaging().Createcolor_blend_ImageList(
      m_pimagelistItemHover,
      m_pimagelistSubItemHover,
      rgb(220,220,215),
      127);

      m_pimagelistGroupHover   = __new< image_list >(this);

      m_pimagelistGroupHover->create(96,96,0,10,10);
      m_pimagelistGroupHover->add_matter("mediaplaylist/playlist_96.png");
      m_pimagelistGroup = m_pimagelistGroupHover;


   }

   //::count playlist_list_impact::_001GetGroupCount()
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

   //::count playlist_list_impact::_001GetGroupItemCount(index iGroup)
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

   void playlist_list_impact::_001GetItemText(::user::mesh_item * pitem)
   {

      simple_form_list_impact::_001GetItemText(pitem);

      if(pitem->m_bOk)
         return;

      if(pitem->m_item.m_iItem < 0)
      {
         pitem->m_bOk = false;
         return;
      }

      if(pitem->m_item.m_iItem >= m_listing.get_size())
      {
         pitem->m_bOk = false;
         return;
      }

      ASSERT_VALID(this);
      //::pointer<::mediaplaylist::document>pdocument = get_document();
      //::file::path wstrSongPath;
      if(pitem->m_item.m_iSubItem == 0)
      {
         pitem->m_strText = m_listing[pitem->m_item.m_iItem];
      }
      else if(pitem->m_item.m_iSubItem == 1)
      {
         pitem->m_strText = m_listing[pitem->m_item.m_iItem];
      }
      else if(pitem->m_item.m_iSubItem == 2)
      {
         pitem->m_strText = m_listing[pitem->m_item.m_iItem].title();
      }
      else if(pitem->m_item.m_iSubItem == 3)
      {
         pitem->m_strText = m_listing[pitem->m_item.m_iItem];
      }

      pitem->m_bOk = true;
   }


   void playlist_list_impact::on_selection_change()
   {

      ::user::range range;
      get_selection(range);
      if(range.get_item_count() > 0)
      {
         index iItem = range.ItemAt(0).get_lower_bound();

         playlist_select(iItem);

      }

   }

   bool playlist_list_impact::playlist_play(int iItem)
   {

      if(!playlist_select(iItem))
      {

         return false;

      }


      info info;

      info.m_position.m_number   = get_document()->m_impact.get_int("current_song_position",0);
      info.m_iCurrentSong        = get_document()->m_impact.get_int("current_song",0);;
      info.m_ehint               = id_do_play;
      info.m_bMakeVisible        = true;
      info.m_context       += ::e_source_user;

      get_document()->play(&info);

      return true;

   }

   bool playlist_list_impact::playlist_select(int iItem)
   {

      if(iItem < 0 || iItem >= m_listing.get_count())
         return false;

      papp->mediaplaylist()->OpenPlaylist(m_listing[iItem],true);

      return true;

   }

   bool playlist_list_impact::playlist_erase(int iItem)
   {

      //::pointer<::mediaplaylist::document>pdocument = get_document();
      //return pdocument->RemoveSong(iItem);
      return true;

   }

} // namespace mediaplaylist


