#include "framework.h"
#include <math.h>


namespace notify_drawing
{


   view::view()
   {


   }


   view::~view()
   {

   }


   void view::assert_valid() const
   {

      user::box::assert_valid();

   }


   void view::dump(dump_context & dumpcontext) const
   {

      user::box::dump(dumpcontext);

   }


   void view::install_message_routing(::channel * psender)
   {

      ::simple_drawing::view::install_message_routing(psender);

   }






   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectClient = get_client_rect();

      if(rectClient.is_empty())
      {

         return;

      }

      m_prender->m_rect = rectClient * (351.0 / 1024.0);

   }


} // namespace notify_drawing



