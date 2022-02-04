#pragma once


namespace app_complex_drawing
{


   class CLASS_DECL_APP_COMPLEX_DRAWING pane_view :
      virtual public application_pane_tab_view < application, ::userex::pane_tab_view, ::app_simple_drawing::tab_view >
   {
   public:


      pane_view();
      ~pane_view() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      void on_change_cur_sel() override;

      virtual void handle(::topic * psubject, ::context * pcontext) override;


   };


} // namespace complex_drawing





