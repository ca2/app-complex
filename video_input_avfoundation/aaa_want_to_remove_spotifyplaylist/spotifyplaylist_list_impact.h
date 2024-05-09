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


      list_impact(::particle * pparticle);
      virtual ~list_impact();


      void install_message_routing(::channel * pchannel);


      ::pointer<::mediaplaylist::document>get_document() const;


      virtual void _001OnButtonAction(::pointer<user::interaction>pinteraction);
      virtual void _001OnInitializeForm(::pointer<user::interaction>pinteraction);
      virtual void on_insert_columns();
      virtual void _001DrawBackground(::draw2d::graphics *pdc, ::rectangle_i32 * lprect);
      virtual bool _001OnRemoveItem(iptr iItem);
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      void update_drawing_objects();
      virtual void _001GetItemImage(::user::mesh_item * pitem);
      e_mode GetMode();

      void SetMode(e_mode emode);

      virtual void _001GetItemText(::user::mesh_item * pitem);
      virtual count _001GetItemCount();
      virtual void handle(::topic * ptopic, ::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem);
      virtual void handle(::topic * ptopic, ::context * pcontext) override;
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
      virtual bool WndFrameworkDownUpGetUpEnable();
      virtual bool WndFrameworkDownUpGetDownEnable();
      virtual bool TransparentFrameWndDownUpGetDownEnable();
      virtual bool TransparentFrameWndDownUpGetUpEnable();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnEditRemove);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditRemove);
      DECLARE_MESSAGE_HANDLER(_001OnPlaylistExecutePlay);
      DECLARE_MESSAGE_HANDLER(_001OnUpdatePlaylistExecutePlay);

      //virtual count _001GetGroupCount();
      //virtual count _001GetGroupItemCount(::collection::index iGroup);

      //virtual ::collection::count _001GetGroupMetaItemCount(::collection::index iGroup);
      //virtual void _001GetGroupText(::user::mesh_item * pitem);
      //virtual void _001GetGroupImage(::user::mesh_item * pitem);

      virtual void on_change_impact();

   };



} // namespace mediaplaylist
