#include "framework.h"
#include "frame.h"


namespace app_complex_video_capture
{


   frame::frame()
   {


   }


   frame::~frame()
   {

   }


   //void frame::assert_ok() const
   //{

   //   simple_frame_window::assert_ok();

   //}


   //void frame::dump(dump_context & dumpcontext) const
   //{

   //   simple_frame_window::dump(dumpcontext);

   //}


   ::user::enum_translucency frame::get_translucency(::user::style* pstyle)
   {

      return ::user::e_translucency_present;

   }


} // namespace app_complex_video_capture



