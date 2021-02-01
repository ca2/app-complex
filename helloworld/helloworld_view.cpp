#include "framework.h"
#include <math.h>


namespace helloworld
{


   view::view(::layered * pobjectContext) :
      ::object(papp)
   {


   }


   view::~view()
   {

   }


   void view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void view::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::impact::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(e_message_create,pdispatch,this,&view::_001OnCreate);

   }


   void view::_001OnCreate(signal_details * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

   }


   void view::on_update(::user::impact * pimpact, ::user::e_update eupdate, ::object * pobject)
   {

      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(psubject);

   }


   void view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      rectangle_i32 rectClient;

      GetClientRect(rectClient);

      ::draw2d::font_pointer font(this_create);

      font->create_point_font(os_font_name(e_font_sans), min(rectClient.height() / 5.0, rectClient.width() / 10.0), 800);

      pgraphics->SelectObject(font);

      pgraphics->draw_text("Hello World!!", rectClient, e_align_center);

   }



} // namespace helloworld



