#include "framework.h"



namespace mediaplaylist
{


   edit_impact::edit_impact()
   {

   }


   edit_impact::~edit_impact()
   {

   }


   void edit_impact::install_message_routing(::channel * pchannel)
   {

      ::user::show < ::user::plain_edit >::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &edit_impact::on_message_create);

   }


   void edit_impact::on_message_create(::message::message * pmessage)
   {
      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

   }


   void edit_impact::handle(::topic * ptopic, ::context * pcontext)
   {

   }

   void edit_impact::on_timer(::timer * ptimer)
   {

      if (ptimer->m_uEvent == 123)
      {

         KillTimer(123);

         string strText;

         get_text(strText);

         if (strText.has_character())
         {

            string strCommandLine = "a.exe \"https://api.spotify.com/v1/search?q=" + purl->url_encode(strText) + "&type=track\"";

            papp->request({strCommandLine});

         }

      }

   }

   void edit_impact::_001OnAfterChangeText(const ::action_context & context)
   {

      if (context & ::e_source_sync)
         return;

      //list_impact * plistview = get_document()->get_typed_impact < list_impact >();

      //if (pimpact != nullptr)
      //{

      //KillTimer(123);
      // SetTimer(123, 3000, nullptr);




      //   {

      //      synchronous_lock synchronouslock(&pimpact->m_pmutexText);

      //      pimpact->datastream()->set("cur_text", strText);

      //      pimpact->m_strNewHelloMultiverse = strText;

      //   }

      //   pimpact->post_message(message_impact_update);

      //}

   }


   /*bool edit_impact::keyboard_focus_is_focusable()
   {

   return is_window_enabled() && is_window_visible();

   }

   bool edit_impact::is_window_visible()
   {

   return ::user::show < ::user::plain_edit >::is_window_visible() && !get_top_level()->frame_is_transparent();

   }


   huge_integer edit_impact::increment_reference_count()
   {
   return ::object::increment_reference_count();
   }
   huge_integer edit_impact::decrement_reference_count()
   {
   return ::object::decrement_reference_count();
   }


   */
} // namespace mediaplaylist




