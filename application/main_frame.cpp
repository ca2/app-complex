#include "framework.h"


namespace simple_application
{


   main_frame::main_frame()
   {

      set_bitmap_source("Simple papplication!!");

      m_bDefaultCreateToolbar = false;

      window_enable_full_screen();

      m_etranslucencyFrame = ::user::e_translucency_total;

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


   ::experience::frame * main_frame::frame_experience()
   {

      auto & user = User;

      auto pframe = ::simple_main_frame::frame_experience(nullptr, "013", "LightBlue");

      return pframe;

   }


   bool main_frame::has_pending_graphical_update()
   {

      return ::simple_frame_window::has_pending_graphical_update();

   }



} // namespace simple_application



