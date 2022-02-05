#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE pane_view :
      virtual public ::application_consumer < application, ::userex::pane_tab_view, ::user::form_callback >
   {
   public:



      pane_view();
      ~pane_view() override;


      void on_create_impact(::user::impact_data * pimpactdata);

      void install_message_routing(::channel * pchannel) override;

      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::context * pcontext);
      void on_change_cur_sel();


   };


} // namespace app_complex_video_capture













