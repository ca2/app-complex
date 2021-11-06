#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE pane_view :
      virtual public ::application_consumer < application, ::userex::pane_tab_view, ::user::form_callback >
   {
   public:


      ::user::split_view *                            m_ptopviewLast;
      impact_base *                                   m_pviewLast;

      __pointer(::user::document)                     m_pdocMenu;


      pane_view();
      virtual ~pane_view();


      void on_create_impact(::user::impact_data * pimpactdata);

      void install_message_routing(::channel * pchannel) override;

      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::subject * psubject, ::context * pcontext);
      void on_change_cur_sel();

      virtual ::file::path prepare_menu_view();

   };


} // namespace video_capture













