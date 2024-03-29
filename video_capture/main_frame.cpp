#include "framework.h"
#include "main_frame.h"
#include "aura/message/user.h"


namespace app_complex_video_capture
{


   main_frame::main_frame()
   {


      window_enable_full_screen();

      


   }


   main_frame::~main_frame()
   {

   }

   void main_frame::install_message_routing(::channel * pchannel)
   {

      simple_frame_window::install_message_routing(pchannel);

      MESSAGE_LINK(WM_APP + 975, pchannel, this, &main_frame::_001OnCaptureEvent);

   }

   void main_frame::_001OnCaptureEvent(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      //if (m_pimpact != nullptr)
      //{

      //   m_pimpact->OnCaptureEvent(pusermessage->m_wparam, pusermessage->m_lparam);

      //}

   }


   //void main_frame::assert_ok() const
   //{

   //   simple_frame_window::assert_ok();

   //}


   //void main_frame::dump(dump_context & dumpcontext) const
   //{

   //   simple_frame_window::dump(dumpcontext);

   //}


   ::pointer < ::experience::frame > main_frame::frame_experience()
   {

      auto pframe = ::simple_frame_window::frame_experience(nullptr, "022", "LightBlue");

      return pframe;

   }


   //bool main_frame::has_pending_graphical_update()
   //{

   //   return true;

   //}


   ::user::enum_translucency main_frame::get_translucency(::user::style * pstyle)
   {


      return ::user::e_translucency_present;

   }


} // namespace app_complex_video_capture







