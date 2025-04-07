#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE pane_impact :
      virtual public ::app_consumer < application, ::userex::pane_tab_impact, ::user::form_callback >
   {
   public:


      ::user::split_impact *                            m_ptopviewLast;
      impact_base *                                   m_pimpactLast;

      ::pointer<::user::document>                    m_pdocMenu;


      pane_impact();
      virtual ~pane_impact();


      void on_create_impact(::user::impact_data * pimpactdata);

      void install_message_routing(::channel * pchannel) override;

      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::handler_context * phandlercontext);
      void on_change_cur_sel();

      virtual ::file::path prepare_menu_impact();

   };


} // namespace app_complex_video_capture













