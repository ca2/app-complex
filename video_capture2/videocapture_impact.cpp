#include "framework.h"
#include <math.h>


namespace app_complex_video_capture
{


   impact::impact()
   {

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

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

   void impact::install_message_routing(::channel * pchannel)
   {

      impact_base::install_message_routing(pchannel);

      
      MESSAGE_LINK(e_message_create,pchannel,this,&impact::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &impact::on_message_destroy);

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

   }


   void impact::on_message_destroy(::message::message * pmessage)
   {

      if (m_prender)
      {

         m_prender->on_destroy();

         m_prender.release();

      }

   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if(ptopic->id() == id_initial_update)
      {

         ::pointer<::userex::pane_tab_impact>ppaneimpact = get_typed_parent < ::userex::pane_tab_impact >();
         //if(ppaneimpact.is_set())
         //{
         //   ppaneimpact->m_pflagview = this;
         //}

      }
      __UNREFERENCED_PARAMETER(ptopic);
   }


   ::user::document * impact::get_document()
   {

      return  (::user::impact::get_document());

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_prender)
      {

         m_prender->on_layout(pgraphics);

      }

   }


   void impact::defer_check_on_draw_layout()
   {

      if (m_prender != nullptr)
      {
      }

   }


   void impact::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
   {

   }


   bool impact::start_capture()
   {

      if (!m_prender)
      {

         return false;

      }

      m_prender->start_capture();

      return true;

   }


} // namespace app_complex_video_capture

















//
//int c_video_capture_enum_encoders(wchar_t *** pppszName, wchar_t *** pppszPath);
//
//
//int video_capture_enum_encoders(string_array & straName, string_array & straPath)
//{
//
//   wchar_t ** ppszName;
//   wchar_t ** ppszPath;
//
//   int iCount = c_video_capture_enum_encoders(&ppszName, &ppszPath);
//
//   straName.c_add(ppszName, iCount);
//
//   straPath.c_add(ppszPath, iCount);
//
//   return straName.get_count();
//
//}
//
