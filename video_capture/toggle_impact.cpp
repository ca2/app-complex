#include "framework.h"



namespace app_complex_video_capture
{


   toggle_impact::toggle_impact()
   {

      m_ptopview = nullptr;

   }


   toggle_impact::~toggle_impact()
   {


   }

   void toggle_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::button::install_message_routing(pchannel);

   }


   void toggle_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

   }


   bool toggle_impact::keyboard_focus_is_focusable()
   {

      return ::user::button::keyboard_focus_is_focusable() ;

   }


} // namespace app_complex_video_capture













