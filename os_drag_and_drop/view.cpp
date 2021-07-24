#include "framework.h"
#include <math.h>


namespace simple_os_drag_and_drop
{


   view::view()
   {

      payload(FONTSEL_IMPACT) = true;

      m_flagNonClient.erase(non_client_background);

      m_flagNonClient.erase(non_client_focus_rect);


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


   int64_t view::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t view::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

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

      auto estatus = __construct_new(m_psimpleosdraganddrop);

      if (!estatus)
      {

         pcreate->set_fail();


         return;


      }

      m_psimpleosdraganddrop->m_pview = this;

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      string strText;

      if(GetTypedParent<::user::split_view>() != nullptr)
      {

         if(GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != nullptr)
         {

            auto pinteraction = GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view");

            pinteraction->_001SetText(strText,::e_source_initialize);

         }

      }

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

      m_psimpleosdraganddrop->_001OnDraw(pgraphics);

   }


   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      m_psimpleosdraganddrop->m_rectangle = rectangleClient;

   }


} // namespace simple_os_drag_and_drop



