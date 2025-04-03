#pragma once


#include "aura/user/user/button.h"
#include "base/user/user/impact.h"


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE toggle_impact:
      virtual public ::user::impact,
      virtual public ::user::button
   {
   public:


      top_impact *           m_ptopimpact;


      toggle_impact();
      virtual ~toggle_impact();


      void install_message_routing(::channel * pchannel) override;


      void handle(::topic * ptopic, ::handler_context * pcontext) override;


      virtual bool keyboard_focus_is_focusable() override;


   };


} // namespace app_complex_video_capture




