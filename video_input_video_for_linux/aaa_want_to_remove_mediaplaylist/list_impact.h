#pragma once


namespace mediaplaylist
{


   class document;


   class CLASS_DECL_APP_CORE_AUDIO list_impact   :
      public simple_form_list_impact
   {
   public:


      


      enum e_mode
      {
         mode_minimum    = 1,
         mode_normal     = 2
      };

      enum e_subitem
      {

         subitem_play = 1,
         subitem_name,
         subitem_artist,
         subitem_album,
         subitem_path,


      };

      ::user::list_cache         m_listcache;
#ifdef WINDOWS
      HENHMETAFILE               m_enhmetafile;
      ENHMETAHEADER              m_emh;
#endif
      ::pointer<image_list>            m_pimagelistSubItemHover;
      ::pointer<image_list>            m_pimagelistItemHover;
      ::pointer<image_list>            m_pimagelistNormal;

      e_mode                     m_emode;
      string                     m_str;
      bool                       m_bPendingEnsureVisible;
      index                      m_iItemHilite;


      list_impact();
      virtual ~list_impact();


      void install_message_routing(::channel * pchannel) override;


      ::mediaplaylist::document * get_document();


      virtual void _001OnGetUri(::message::message * pmessage);
      virtual void _001OnButtonAction(::pointer<user::interaction>pinteraction) override;
      virtual void _001OnInitializeControl(::pointer<user::interaction>pinteraction) override;
      virtual void on_insert_columns() override;
      virtual void _001DrawBackground(::draw2d::graphics *pdc, ::rectangle_i32 * lprect);
      virtual bool _001OnRemoveItem(index iItem) override;
      void update_drawing_objects();
      virtual void _001GetItemImage(::user::mesh_item * pitem) override;
      e_mode GetMode();

      void SetMode(e_mode emode);

      virtual void _001GetItemText(::user::mesh_item * pitem) override;
      virtual count _001GetItemCount() override;
      virtual void handle(::topic * ptopic, ::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
      virtual bool WndFrameworkDownUpGetUpEnable();
      virtual bool WndFrameworkDownUpGetDownEnable();
      virtual bool TransparentFrameWndDownUpGetDownEnable();
      virtual bool TransparentFrameWndDownUpGetUpEnable();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnEditRemove);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditRemove);
      DECLARE_MESSAGE_HANDLER(_001OnPlaylistExecutePlay);
      DECLARE_MESSAGE_HANDLER(_001OnUpdatePlaylistExecutePlay);
      DECLARE_MESSAGE_HANDLER(_001OnVScroll);



      virtual bool on_click(::item * pitem) override; 
      //virtual bool on_click(::item * pitem) override;
      virtual bool on_right_click(const ::item & item) override;

      //virtual count _001GetGroupCount();
      //virtual count _001GetGroupItemCount(index iGroup);

      //virtual ::count _001GetGroupMetaItemCount(index iGroup);
      //virtual void _001GetGroupText(::user::mesh_item * pitem);
      //virtual void _001GetGroupImage(::user::mesh_item * pitem);

      virtual void on_change_impact();

      virtual i32 _001CalcItemHeight(int iBaseHeight) override;

      virtual i32 _001GetDrawTextFlags(::user::list::enum_impact eview) override;

      virtual void defer_update_track_hilite();

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   };



} // namespace mediaplaylist
