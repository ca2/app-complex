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

      ::file::listing            m_listing;
      ::pointer<image_list>            m_pimagelistSubItemHover;
      ::pointer<image_list>            m_pimagelistItemHover;
      ::pointer<image_list>            m_pimagelistNormal;

      e_mode                     m_emode;
      string                     m_str;


      playlist_list_impact(::particle * pparticle);
      virtual ~playlist_list_impact();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel);


      ::pointer<::mediaplaylist::document>get_document() const;


      virtual void _001OnButtonAction(::pointer<user::interaction>pinteraction);
      virtual void _001OnInitializeForm(::pointer<user::interaction>pinteraction);
      virtual void _001InsertColumns();
      virtual void _001GetItemImage(::user::mesh_item * pitem);
      e_mode GetMode();

      void SetMode(e_mode emode);

      virtual void _001GetItemText(::user::mesh_item * pitem);
      virtual count _001GetItemCount();
      virtual void handle(::topic * ptopic, ::context * pcontext) override;
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

      virtual bool playlist_play(int iItem);
      virtual bool playlist_select(int iItem);
      virtual bool playlist_erase(int iItem);

      void _001OnSelectionChange();

   };



} // namespace mediaplaylist
