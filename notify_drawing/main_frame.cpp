#include "framework.h"


namespace notify_drawing
{


   main_frame::main_frame()
   {

      enable_default_notification_icon();

   }


   main_frame::~main_frame()
   {

   }


   void main_frame::assert_ok() const
   {

      simple_frame_window::assert_ok();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


} // namespace notify_drawing




