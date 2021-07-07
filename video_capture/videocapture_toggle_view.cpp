#include "framework.h"


namespace video_capture
{


   toggle_view::toggle_view()
   {

      m_ptopview = nullptr;

   }


   toggle_view::~toggle_view()
   {


   }

   void toggle_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::button::install_message_routing(pchannel);

   }


   void toggle_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

   }


   bool toggle_view::keyboard_focus_is_focusable()
   {

      return ::user::button::keyboard_focus_is_focusable() ;

   }


} // namespace video_capture













