#include "framework.h"


namespace video_capture
{


   frame::frame()
   {


   }


   frame::~frame()
   {

   }


   void frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   ::user::enum_translucency frame::get_translucency(::user::style* pstyle) const
   {

      return ::user::e_translucency_present;

   }


} // namespace video_capture







