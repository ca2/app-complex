#include "framework.h"


namespace app_complex_video_capture
{


   edit_view::edit_view()
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


   void edit_view::handle(::topic * ptopic, ::context * pcontext)
   {

   }


   void edit_view::_001OnAfterChangeText(const ::action_context & context)
   {

      if (context.is(::e_source_sync))
      {

         return;

      }

      if (m_ptopview == nullptr)
      {

         return;

      }

      string strText;

      _001GetText(strText);

      impact_base * pview = dynamic_cast < impact_base * > (m_ptopview->GetTypedParent<::user::split_view>()->get_child_by_id("videocapture_view"));



   }


   bool edit_view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


} // namespace app_complex_video_capture




