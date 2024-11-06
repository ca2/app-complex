#pragma once


namespace mediaplaylist
{


   class document;


   class CLASS_DECL_APP_CORE_AUDIO playlist_list_impact:
      public simple_form_list_impact
   {
   public:


      


      enum e_mode
      {
         mode_normal       = 1,
         mode_verbose      = 2
      };


      ::collection::index                         m_iLastClickItem;
      count                         m_cSameItemClick;


      ::pointer<::file::listing>   m_plisting;
      ::image::image_list_pointer         m_pimagelistSubItemHover;
      ::image::image_list_pointer         m_pimagelistItemHover;
      ::image::image_list_pointer         m_pimagelistNormal;

      e_mode                        m_emode;
      string                        m_str;


      playlist_list_impact();
      virtual ~playlist_list_impact();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;


      ::mediaplaylist::document * get_document() const;


      virtual void _001OnButtonAction(::pointer<user::interaction>pinteraction) override;
      virtual void _001OnInitializeControl(::pointer<user::interaction>pinteraction) override;
      virtual void on_insert_columns() override;
      virtual void _001GetItemImage(::user::mesh_item * pitem) override;
      e_mode GetMode();

      void SetMode(e_mode emode);

      virtual void _001GetItemColor(::user::mesh_item * pitem) override;
      virtual void _001GetItemText(::user::mesh_item * pitem) override;
      virtual count _001GetItemCount() override;
      virtual void handle(::topic * ptopic, ::context * pcontext) override;
      virtual bool WndFrameworkDownUpGetUpEnable();
      virtual bool WndFrameworkDownUpGetDownEnable();
      virtual bool TransparentFrameWndDownUpGetDownEnable();
      virtual bool TransparentFrameWndDownUpGetUpEnable();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      DECLARE_MESSAGE_HANDLER(_001OnEditRemove);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditRemove);
      DECLARE_MESSAGE_HANDLER(_001OnPlaylistExecutePlay);
      DECLARE_MESSAGE_HANDLER(_001OnUpdatePlaylistExecutePlay);

      virtual ::collection::index playlist_index();

      virtual bool playlist_previous();
      virtual bool playlist_next();

      virtual bool playlist_roulette();

      virtual bool playlist_play(::collection::index iItem);
      virtual bool playlist_select(::collection::index iItem);
      virtual bool playlist_erase(::collection::index iItem);

      virtual bool on_click(::item * pitem) override;
      //void on_selection_change() override;

      ::collection::index playlist_index(const ::file::path & pathName);
      void update_playlist_hilite(const ::file::path & pathPlaylist);

      int _001CalcItemHeight(int iBaseHeight) override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace mediaplaylist



