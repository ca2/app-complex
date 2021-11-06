#include "framework.h"
#include <math.h>


namespace video_capture
{


   impact::impact()
   {

      m_flagNonClient.erase(non_client_background);
      m_flagNonClient.erase(non_client_focus_rect);

   }

   impact::~impact()
   {
   }

   void impact::assert_valid() const
   {
      user::box::assert_valid();
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

      __pointer(::message::create) pcreate(pmessage);

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


   void impact::handle(::subject * psubject, ::context * pcontext)
   {

      if(psubject->m_id == INITIAL_UPDATE)
      {

         __pointer(::userex::pane_tab_view) ppaneview = GetTypedParent < ::userex::pane_tab_view >();
         //if(ppaneview.is_set())
         //{
         //   ppaneview->m_pflagview = this;
         //}

      }
      __UNREFERENCED_PARAMETER(psubject);
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


} // namespace video_capture

















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
