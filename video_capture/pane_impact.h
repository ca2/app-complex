#pragma once


#include "core/user/userex/pane_tab_impact.h"


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE pane_impact :
      virtual public ::app_consumer < application, ::userex::pane_tab_impact, ::user::form_callback >
   {
   public:



      pane_impact();
      ~pane_impact() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      void on_change_cur_sel() override;
      ::i32_rectangle hosting_rectangle(::user::enum_layout elayout = ::user::e_layout_design) override;
      void on_perform_top_down_layout(::draw2d::graphics_pointer & pdraw2dgraphics) override;


   };


} // namespace app_complex_video_capture













