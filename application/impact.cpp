#include "framework.h"
#include <math.h>
#include "acme/constant/identification.h"


CLASS_DECL_AURA color32_t dk_red(); // <3 tbs


namespace simple_application
{


   impact::impact()
   {

   }


   impact::~impact()
   {

   }


   long long impact::increment_reference_count()
   {

      return ::user::impact::increment_reference_count();

   }


   long long impact::decrement_reference_count()
   {

      return ::user::impact::increment_reference_count();

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

      ::user::impact::install_message_routing(psender);

      MESSAGE_LINK(e_message_create,psender,this,&impact::on_message_create);
      MESSAGE_LINK(e_message_destroy, psender, this, &impact::on_message_destroy);

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      m_pfontThomasBS_ = ::write_text::point_font("Fira Code", 24);

   }


   void impact::on_message_destroy(::message::message * pmessage)
   {

   }


   void impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::impact::handle(ptopic, phandlercontext);

   }


   ::user::document * impact::get_document()
   {

      return ::user::impact::get_document();

   }


   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::color::color color_dk(dk_red());

      color_dk.m_iA = 127;

      pgraphics->set_text_color(color_dk);

      pgraphics->set(m_pfontThomasBS_);

      pgraphics->text_out({ 10, 10 }, "psimpleapplication->m_pimpact->_001OnDraw(pgraphics);");

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if(rectangleX.is_empty())
      {

         return;

      }

      ::user::impact::on_layout(pgraphics);

   }


} // namespace simple_application



