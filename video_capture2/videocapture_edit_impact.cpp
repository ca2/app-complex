#include "framework.h"


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

      MESSAGE_LINK(MESSAGE_CREATE,pchannel,this,&edit_impact::on_message_create);

   }


   void edit_impact::on_message_create(::message::message * pmessage)
   {
      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;


      m_ptopimpact = get_typed_parent < top_impact >();
   }


   void edit_impact::handle(::topic * ptopic, ::context * pcontext)
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

      _001GetText(strText);

      impact_base * pimpact = dynamic_cast < impact_base * > (m_ptopimpact->get_typed_parent<::user::split_impact>()->get_child_by_id("videocapture_impact"));



   }


   bool edit_impact::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


} // namespace app_complex_video_capture




