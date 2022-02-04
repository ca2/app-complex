#pragma once


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM pane_view :
      virtual public application_pane_tab_view < application, ::userex::pane_tab_view, ::app_simple_form::tab_view >
   {
   public:


      pane_view();
      ~pane_view() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;


      DECLARE_MESSAGE_HANDLER(on_message_create);


      void handle(::topic * psubject, ::context * pcontext) override;
      void on_change_cur_sel() override;


   };


} // namespace app_complex_form



