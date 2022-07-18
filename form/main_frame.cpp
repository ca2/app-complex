#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_app_complex_form.h"
#endif



namespace app_complex_form
{


   main_frame::main_frame()
   {

      //m_bDefaultCreateToolbar = false;

      window_enable_full_screen();

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


   ::experience::frame * main_frame::frame_experience()
   {

      auto pframe = ::simple_main_frame::frame_experience(nullptr, "008", "LightBlue");

      return pframe;

   }


   bool main_frame::has_pending_graphical_update()
   {

      return true;

   }


   //bool main_frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::style_context * pcontext)
   //{

   //   if (m_bExplicitTranslucency)
   //   {

   //      etranslucency = m_etranslucency;

   //      return true;

   //   }

   //   //if (userstyle() != NULL)
   //   //{

   //   //   if (m_puserstyle->_001GetMainFrameTranslucency(etranslucency))
   //   //      return true;

   //   //}
   //   //etranslucency = ::user::e_translucency_present;

   //   ////      etranslucency = ::user::e_translucency_none;

   //   //return true;

   //   return ::user::style::get_translucency(etranslucency, eelement, pcontext);

   //}


} // namespace app_complex_form







