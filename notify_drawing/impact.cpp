#include "framework.h"
#include <math.h>


namespace notify_drawing
{


   impact::impact()
   {


   }


   impact::~impact()
   {

   }


   void impact::assert_ok() const
   {

      user::box::assert_ok();

   }


   void impact::dump(dump_context & dumpcontext) const
   {

      user::box::dump(dumpcontext);

   }


   void impact::install_message_routing(::channel * psender)
   {

      ::simple_drawing::impact::install_message_routing(psender);

   }






   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      m_prender->m_rectangle = rectangleClient * (351.0 / 1024.0);

   }


} // namespace notify_drawing



