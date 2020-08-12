#include "framework.h"
#include <math.h>
#include "aura/const/id.h"


CLASS_DECL_AURA COLORREF dk_red(); // <3 tbs


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

      IGUI_MSG_LINK(WM_CREATE,psender,this,&view::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &view::_001OnDestroy);

   }


   void view::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create,pcreate,pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      m_pfontThomasBS_ = ::draw2d::point_font("Fira Code", 24);

   }


   void view::_001OnDestroy(::message::message * pmessage)
   {

   }


   void view::update(::update * pupdate)
   {

      ::user::impact::update(pupdate);

   }


   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }


   void view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::color color_dk(dk_red());

      color_dk.m_iA = 127;

      pgraphics->set_text_color(color_dk);

      pgraphics->set(m_pfontThomasBS_);

      pgraphics->text_out({ 10, 10 }, "psimpleapplication->m_pview->_001OnDraw(pgraphics);");

   }


   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectClient = get_client_rect();

      if(rectClient.is_empty())
      {

         return;

      }

      ::user::impact::on_layout(pgraphics);

   }


} // namespace simple_application



