#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


namespace app_complex_video_capture
{


   edit_impact::edit_impact()
   {

      m_ptopview = nullptr;

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
      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;


      m_ptopview = GetTypedParent < top_impact >();
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

      if (m_ptopview == nullptr)
      {

         return;

      }

      string strText;

      _001GetText(strText);



   }


   bool edit_impact::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


} // namespace app_complex_video_capture




