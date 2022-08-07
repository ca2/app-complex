#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_app_complex_form.h"
#endif
#include <math.h>


namespace app_complex_form
{


   impact::impact()
   {

      payload(FONTSEL_IMPACT) = true;

      m_flagNonClient.erase(non_client_background);
      m_flagNonClient.erase(non_client_focus_rect);

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

      MESSAGE_LINK(e_message_create,psender,this,&impact::on_message_create);

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      string strId = get_document()->m_pimpactsystem->m_atom;

      string strText;

      if(GetTypedParent<::user::split_impact>() != nullptr)
      {

         if(GetTypedParent<::user::split_impact>()->get_child_by_id("top_edit_impact") != nullptr)
         {

            auto pinteraction = GetTypedParent<::user::split_impact>()->get_child_by_id("top_edit_impact");

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

      auto rectangleClient = get_client_rect();

      pgraphics->fill_rectangle(rectangleClient, argb(127, 255, 255, 255));

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if (rectangleClient.area() <= 0)
      {

         return;

      }

   }


} // namespace app_complex_form



