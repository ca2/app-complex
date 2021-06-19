#include "framework.h"


namespace videocapture
{


   edit_view::edit_view(::object * pobject):
      object(pobject),
      ::user::interaction(pobject),
      ::user::plain_edit(pobject)
   {

      m_ptopview = nullptr;

   }

   edit_view::~edit_view()
   {

   }
   void edit_view::install_message_routing(::channel * pchannel)
   {

      ::user::show < ::user::plain_edit >::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&edit_view::on_message_create);

   }


   void edit_view::on_message_create(::message::message * pmessage)
   {
      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;


      m_ptopview = GetTypedParent < top_view >();
   }


   void edit_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

   }


   void edit_view::_001OnAfterChangeText(const ::action_context & context)
   {

      if(context.is_source(::e_source_sync))
         return;

      if(m_ptopview == nullptr)
         return;



      string strText;

      _001GetText(strText);

      impact_base * pview = dynamic_cast < impact_base * > (m_ptopview->GetTypedParent<::user::split_view>()->get_child_by_id("videocapture_view"));

      if (pview != nullptr)
      {
         {

            synchronous_lock synchronouslock(&pview->m_mutexText);

            pview->data_set("cur_text", strText);

            pview->m_strNewHelloMultiverse = strText;

         }


         pview->post_message(message_view_update);

      }
      else
      {
         ::user::font_list * pview = dynamic_cast < ::user::font_list * > (m_ptopview->GetTypedParent<::user::split_view>()->get_child_by_id("font_list_view"));

         if (pview != nullptr)
         {
            synchronous_lock synchronouslock(pview->mutex());
            pview->m_strText = strText;
//               pview->update();

         }

      }



   }


   bool edit_view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }

   bool edit_view::is_window_visible()
   {

      return ::user::show < ::user::plain_edit >::is_window_visible() && !get_top_level()->frame_is_transparent();

   }

   /*
   i64 edit_view::add_ref()
   {
      return ::object::add_ref(OBJ_REF_DBG_ARGS);
   }
   i64 edit_view::dec_ref()
   {
      return ::object::dec_ref(OBJ_REF_DBG_ARGS);
   }


   */
} // namespace videocapture




