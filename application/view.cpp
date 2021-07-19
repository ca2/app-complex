#include "framework.h"
#include <math.h>
#include "acme/const/id.h"


CLASS_DECL_AURA color32_t dk_red(); // <3 tbs


namespace simple_application
{


   view::view()
   {

   }


   view::~view()
   {

   }


   int64_t view::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::user::impact::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t view::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::user::impact::add_ref(OBJ_REF_DBG_ARGS);

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

      ::user::impact::install_message_routing(psender);

      MESSAGE_LINK(e_message_create,psender,this,&view::on_message_create);
      MESSAGE_LINK(e_message_destroy, psender, this, &view::on_message_destroy);

   }


   void view::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      m_pfontThomasBS_ = ::write_text::point_font("Fira Code", 24);

   }


   void view::on_message_destroy(::message::message * pmessage)
   {

   }


   void view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

   }


   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }


   void view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::color::color color_dk(dk_red());

      color_dk.m_iA = 127;

      pgraphics->set_text_color(color_dk);

      pgraphics->set(m_pfontThomasBS_);

      pgraphics->text_out({ 10, 10 }, "psimpleapplication->m_pview->_001OnDraw(pgraphics);");

   }


   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      ::user::impact::on_layout(pgraphics);

   }


} // namespace simple_application



