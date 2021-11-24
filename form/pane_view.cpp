#include "framework.h"
#include "base/user/user/tab_pane.h"
#include "aura/update.h"


namespace app_complex_form
{


   pane_view::pane_view()
   {

      m_pviewLast = NULL;

   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void pane_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_view::install_message_routing(::channel * pchannel)
   {

      ::app_simple_form::tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::on_message_create);

   }


   void pane_view::on_message_create(::message::message * pmessage)
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

      auto papplication = get_application();

      strForm = papplication->payload("tab");

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


   void pane_view::on_change_cur_sel()
   {

      //::userex::pane_pane_view::on_change_cur_sel();
      ::app_simple_form::tab_view::on_change_cur_sel();

      string strId = get_view_id();
      string_array stra;

      stra.explode("->:<-",strId);

      if(get_view_id() == ::impact_simple_form)
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

         m_pviewLast = nullptr;

      }

   }


   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      string strId = pimpactdata->m_id;

      if(::str::begins_eat_ci(strId, "form"))
      {

         __pointer(form) pform;

         index iId = atoi(strId);

         switch (iId)
         {
         case 1:

            pform = create_view < form_001 >(pimpactdata);

            break;

         case 2:

            pform = create_view < form_002 >(pimpactdata);

            break;

         default:

            break;

         }

         pform->m_ptabview = this;

         pform->m_iId = (int)iId;

         pform->m_id = pimpactdata->m_id;

         return;

      }

      ::app_simple_form::tab_view::on_create_impact(pimpactdata);

      ::userex::pane_tab_view::on_create_impact(pimpactdata);

      pimpactdata->m_eflag.add(::user::e_flag_hide_all_others_on_show);

   }


   void pane_view::handle(::subject * psubject, ::context * pcontext)
   {

      if (m_pdocMenu != nullptr
         && psubject->get_form() == m_pdocMenu->get_view(0)
         && ::is_set(psubject->m_puserelement))
      {

         if (psubject->m_id == ::e_subject_after_change_text)
         {


         }
         else if (psubject->m_id == ::e_subject_set_check && ::is_set(psubject->m_puserelement))
         {

            string strCheck = psubject->m_puserelement->m_id;

            if (::str::begins_eat_ci(strCheck, "bilbo"))
            {

               if (::is_set(psubject->m_puserelement) && psubject->m_actioncontext.is_user_source())
               {

                  //int iCheck = atoi(strCheck);

                  //__pointer(::user::check) pcheck = psubject->user_interaction();

               }

            }

         }

      }

      ::app_simple_form::tab_view::handle(psubject, pcontext);

   }


} // namespace app_complex_form


