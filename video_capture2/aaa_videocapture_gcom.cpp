#include "framework.h"

namespace video_capture
{



   gcom::gcom()
   {

      m_bBkLoaded = false;

      if (papplication->m_varTopicQuery["hello_bk"].get_string().has_char())
      {

         property_set payloadFile;

         payloadFile["url"] = papplication->m_varTopicQuery["hello_bk"];
         payloadFile["http_set"]["raw_http"] = true;
         payloadFile["http_set"]["disable_common_name_cert_check"] = true;

         ::fork(papp, [=]()
         {

/*            m_bBkLoaded = m_pimage->load_from_file(payloadFile);

         });

      }

      m_bEnableShowGcomBackground = true;

   }

   gcom::~gcom()
   {
   }

   void gcom::assert_valid() const
   {
      user::box::assert_valid();
   }

   void gcom::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void gcom::install_message_routing(::channel * pchannel)
   {

      impact_base::install_message_routing(pchannel);
      ::backview::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &gcom::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &gcom::on_message_destroy);

   }


   void gcom::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      m_id = "videocapture_gcom";

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      show_gcom_background(true);

   }

   void gcom::on_message_destroy(::message::message * pmessage)
   {


   }


   void gcom::handle(::topic * psubject, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(psubject);

   }


   void gcom::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      impact_base::_001OnDraw(pgraphics);

   }


   void gcom::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

/*      if (m_bBkLoaded && m_pimage->is_set() && m_pimage->area() > 0)
      {

         m_pimagePost->get_graphics()->BitBlt(
/*         0, 0, minimum(rectangleClient.width(), m_pimage->width()),
/*         minimum(rectangleClient.height(), m_pimage->height()),
/*         m_pimage->get_graphics());
         return;

      }

      if (rectangleClient.area() <= 0)
      {

         return;

      }

      backview::user::impact::BackViewRender(pgraphics, rectangleClient);

   }


   ::user::document * gcom::get_document()
   {

      return  (::user::impact::get_document());

   }





   void gcom::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::backview::user::impact::on_layout(pgraphics);

   }




} // namespace video_capture

















