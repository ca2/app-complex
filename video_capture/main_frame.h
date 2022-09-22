#pragma once


#include "base/user/simple/main_frame.h"


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE main_frame :
      virtual public main_frame
   {
   public:


      bool                       m_bExplicitTranslucency;
      ::user::enum_translucency      m_etranslucency;
      impact *                     m_pimpact;

      main_frame();
      virtual ~main_frame();

      DECLARE_MESSAGE_HANDLER(_001OnCaptureEvent);

      void install_message_routing(::channel * pchannel) override;

      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      ::user::enum_translucency get_translucency(::user::style * pstyle) const override;
      ::experience::frame * frame_experience() override;

      bool has_pending_graphical_update() override;

   };


} // namespace app_complex_video_capture












