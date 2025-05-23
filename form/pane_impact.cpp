#include "framework.h"
#include "pane_impact.h"
#include "document.h"
#include "application.h"
#include "form_001.h"
#include "form_002.h"
#include "acme/constant/id.h"
#include "acme/constant/impact.h"
#include "acme/handler/topic.h"
#include "base/user/user/tab_pane.h"



namespace app_complex_form
{


   pane_impact::pane_impact()
   {

      m_pimpactLast = NULL;

   }


   pane_impact::~pane_impact()
   {

   }


   void pane_impact::install_message_routing(::channel * pchannel)
   {

      ::app_simple_form::tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_impact::on_message_create);

   }


   void pane_impact::on_message_create(::message::message * pmessage)
   {

      pmessage->m_iRouteIndex--;

      if(pmessage->previous())
      {

         return;

      }

      add_tab("Menu",MENU_IMPACT);
      add_tab("001", "form1");
      add_tab("002", "form2");

      string strForm;

      auto papp = get_app();

      strForm = papp->payload("tab");

      string_array straForm;

      straForm.add("form1");
      straForm.add("form2");

      if(straForm.contains(strForm))
      {

         set_current_tab_by_id(strForm);

      }
      else
      {

         set_current_tab_by_id("form1");

      }

   }


   void pane_impact::on_change_cur_sel()
   {

      //::userex::pane_pane_impact::on_change_cur_sel();
      ::app_simple_form::tab_impact::on_change_cur_sel();

      string strId = get_impact_id();
      string_array stra;

      stra.explode("->:<-",strId);

      if(get_impact_id() == ::e_impact_simple_form)
      {

         auto ptabpaneFileManager = get_tab_by_id(FILEMANAGER_IMPACT);

         if(ptabpaneFileManager != nullptr
               && ptabpaneFileManager->m_pplaceholder != nullptr)
         {

            ptabpaneFileManager->m_pplaceholder->hide();

         }

         auto ptabpaneFontSel = get_tab_by_id(FONTSEL_IMPACT);

         if (ptabpaneFontSel != nullptr
               && ptabpaneFontSel->m_pplaceholder != nullptr)
         {

            ptabpaneFontSel->m_pplaceholder->hide();

         }

         m_pimpactLast = nullptr;

      }

   }


   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      string strId = pimpactdata->id();

      if(strId.case_insensitive_begins_eat("form"))
      {

         ::pointer<form>pform;

         ::collection::index iId = atoi(strId);

         switch (iId)
         {
         case 1:

            pform = create_impact < form_001 >(pimpactdata);

            break;

         case 2:

            pform = create_impact < form_002 >(pimpactdata);

            break;

         default:

            break;

         }

         pform->m_ptabimpact = this;

         pform->m_iId = (int)iId;

         pform->id() = pimpactdata->id();

         return;

      }

      ::app_simple_form::tab_impact::on_create_impact(pimpactdata);
      
      if(pimpactdata->m_pplaceholder->children()->count() <= 0)
      {
         
         ::userex::pane_tab_impact::on_create_impact(pimpactdata);
         
      }

      pimpactdata->m_eflag.add(::user::e_flag_hide_all_others_on_show);

   }


   void pane_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (m_pdocMenu != nullptr && ptopic->is_about(m_pdocMenu->get_impact(0)))
      {

         if (ptopic->id() == ::id_after_change_text)
         {


         }
         else if (ptopic->id() == ::id_set_check && ::is_set(ptopic->m_puserelement))
         {

            string strCheck = ptopic->m_puserelement->user_interaction()->id();

            if (strCheck.case_insensitive_begins_eat("bilbo"))
            {

               if (::is_set(ptopic->m_puserelement) && ptopic->m_actioncontext.is_user_source())
               {

                  //int iCheck = atoi(strCheck);

                  //::pointer<::user::check>pcheck = ptopic->user_interaction();

               }

            }

         }

      }

      ::app_simple_form::tab_impact::handle(ptopic, phandlercontext);

   }


} // namespace app_complex_form



