#include "framework.h"


namespace notify_drawing
{


   main_frame::main_frame()
   {

      m_bDefaultNotifyIcon = true;

   }


   main_frame::~main_frame()
   {

   }


   void main_frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


} // namespace notify_drawing




