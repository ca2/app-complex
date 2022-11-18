#pragma once


#include "core/user/userex/pane_tab_impact.h"
#include "app-simple/drawing/tab_impact.h"


namespace app_complex_drawing
{


   class CLASS_DECL_APP_COMPLEX_DRAWING pane_impact :
      virtual public application_pane_tab_impact < application, ::userex::pane_tab_impact, ::app_simple_drawing::tab_impact >
   {
   public:


      pane_impact();
      ~pane_impact() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      void on_change_cur_sel() override;

      void handle(::topic * ptopic, ::context * pcontext) override;


   };


} // namespace complex_drawing





