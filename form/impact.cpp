#include "framework.h"
#include "impact.h"
#include "document.h"
#include "main_impact.h"
#include "application.h"
#include "base/user/user/impact_system.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"


namespace app_complex_form
{


   impact::impact()
   {

      payload(FONTSEL_IMPACT) = true;

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   impact::~impact()
   {

   }


   //void impact::assert_ok() const
   //{

   //   user::box::assert_ok();

   //}


   //void impact::dump(dump_context & dumpcontext) const
   //{

   //   user::box::dump(dumpcontext);

   //}


#ifdef _DEBUG


   int64_t impact::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t impact::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }
   

#endif

   
   void impact::install_message_routing(::channel * psender)
   {

      ::user::impact::install_message_routing(psender);

      MESSAGE_LINK(MESSAGE_CREATE,psender,this,&impact::on_message_create);

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      string strId = get_document()->m_pimpactsystem->m_atom;

      string strText;

      if(get_typed_parent<::user::split_impact>() != nullptr)
      {

         if(get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact") != nullptr)
         {

            auto pinteraction = get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact");

            pinteraction->_001SetText(strText,::e_source_initialize);


         }

      }

   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);
   }


   ::user::document * impact::get_document()
   {

      return ::user::impact::get_document();

   }


   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      pgraphics->fill_rectangle(rectangleClient, argb(127, 255, 255, 255));

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      if (rectangleClient.area() <= 0)
      {

         return;

      }

   }


} // namespace app_complex_form



