#include "framework.h"
#include "edit_impact.h"
#include "top_impact.h"
#include "aura/message/user.h"


namespace app_complex_video_capture
{


   edit_impact::edit_impact()
   {

      m_ptopimpact = nullptr;

   }

   edit_impact::~edit_impact()
   {

   }
   void edit_impact::install_message_routing(::channel * pchannel)
   {

      ::user::show < ::user::plain_edit >::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&edit_impact::on_message_create);

   }


   void edit_impact::on_message_create(::message::message * pmessage)
   {
      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;


      m_ptopimpact = get_typed_parent < top_impact >();
   }


   void edit_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

   }


   void edit_impact::_001OnAfterChangeText(const ::action_context & context)
   {

      if (context.is(::e_source_sync))
      {

         return;

      }

      if (m_ptopimpact == nullptr)
      {

         return;

      }

      string strText;

      get_text(strText);



   }


   bool edit_impact::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


} // namespace app_complex_video_capture




