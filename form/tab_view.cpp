#include "framework.h"
#include "aura/update.h"



namespace simple_form
{


   tab_view::tab_view()
   {

      m_pviewLast = NULL;

   }


   tab_view::~tab_view()
   {

   }


   void tab_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void tab_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void tab_view::install_message_routing(::channel * pchannel)
   {

      ::user::tab_view::install_message_routing(pchannel);
      //::userex::pane_tab_view::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &tab_view::_001OnCreate);

   }


   void tab_view::_001OnCreate(::message::message * pmessage)
   {

      if(pmessage->previous())
         return;

      add_tab("Menu",MENU_IMPACT);
      add_tab("001", "form1");
      add_tab("002", "form2");
      add_tab("Open", FILEMANAGER_IMPACT);

      string strForm;

      strForm = Application.value("tab");

      string_array straForm;

      straForm.add("form1");
      straForm.add("form2");

      if(straForm.contains(strForm))
      {

         set_cur_tab_by_id(strForm);

      }
      else
      {

         set_cur_tab_by_id("form1");

      }

   }


   void tab_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //::userex::pane_tab_view::_001OnNcDraw(pgraphics);
      ::user::tab_view::_001OnNcDraw(pgraphics);

   }


   void tab_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::tab_view::_001OnDraw(pgraphics);
      //::userex::pane_tab_view::_001OnDraw(pgraphics);

   }


   void tab_view::on_change_cur_sel()
   {

      //::userex::pane_tab_view::on_change_cur_sel();
      ::user::tab_view::on_change_cur_sel();
      string strId = get_view_id();
      string_array stra;

      stra.explode("->:<-",strId);

      if (get_view_id() == MENU_IMPACT)
      {

         //__pointer(::user::menu_list_view) pmenuview = get_view_uie();

         //pmenuview->load_xml_menu("matter://simple_menu.xml");

         //pmenuview->create_inline_menu(m_pimpactdataOld->m_puserinteraction, m_pimpactdata->m_pplaceholder);

         //}

         //hide_all_except({ get_view_id(), ::impact_karaoke });

      }


      if(get_view_id() == ::impact_simple_form)
      {

         if(get_pane_by_id(FILEMANAGER_IMPACT) != nullptr
               && get_pane_by_id(FILEMANAGER_IMPACT)->m_pplaceholder != nullptr)
         {

            get_pane_by_id(FILEMANAGER_IMPACT)->m_pplaceholder->hide();

         }

         if (get_pane_by_id(FONTSEL_IMPACT) != nullptr
               && get_pane_by_id(FONTSEL_IMPACT)->m_pplaceholder != nullptr)
         {

            get_pane_by_id(FONTSEL_IMPACT)->m_pplaceholder->hide();

         }

         m_pviewLast = nullptr;

      }


   }


   void tab_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_id)
      {
      case MENU_IMPACT:
      {

         ::user::impact::create_view < ::user::menu_list_view >(pimpactdata);

      }
      break;
      }

      string strId = pimpactdata->m_id;

      if(::str::begins_eat_ci(strId, "form"))
      {

         __pointer(simple_form) pform;

         index iId = atoi(strId);

         switch (iId)
         {
         case 1:

            pform = create_view<simple_form_001>(pimpactdata);

            break;

         case 2:

            pform = create_view<simple_form_002>(pimpactdata);

            break;

         default:

            break;

         }

         pform->m_ptabview = this;

         pform->m_iId = (int)iId;

         pform->m_id = pimpactdata->m_id;

      }

      ::user::tab_view::on_create_impact(pimpactdata);
//      ::userex::pane_tab_view::on_create_impact(pimpactdata);

      pimpactdata->m_eflag.add(::user::flag_hide_all_others_on_show);

   }


   bool tab_view::BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent)
   {

      if(m_pdocMenu != nullptr
            && dynamic_cast < ::user::impact * > (pview) == m_pdocMenu->get_view(0)
            && pevent->m_puie != nullptr)
      {

         if(pevent->m_eevent == ::user::event_after_change_text)
         {


         }
         else if (pevent->m_eevent == ::user::event_set_check && pevent->m_puie != NULL)
         {

            string strCheck = pevent->m_puie->m_id;


            if (::str::begins_eat_ci(strCheck, "bilbo"))
            {

               if (pevent->m_puie != NULL && pevent->m_actioncontext.is_user_source())
               {

                  //int iCheck = atoi(strCheck);

                  //__pointer(::user::check) pcheck = pevent->m_puie;

               }

            }

         }

      }

      return false;

   }


   void tab_view::update(::update * pupdate)
   {

      //////__update(::update)
      //{

      //   if (pupdate->m_id == id_control_event
      //         && pupdate->m_puserinteraction == m_pfontview
      //         && m_pviewLast != NULL)
      //   {

      //      if(pupdate->m_pcontrolevent->m_eevent == ::user::event_after_change_cur_sel)
      //      {

      //         string strFont = m_pfontview->m_pview->get_cur_sel_face_name();

      //      }
      //      else if (pupdate->m_pcontrolevent->m_eevent == ::user::event_after_change_cur_hover)
      //      {

      //         string strFont = m_pfontview->m_pview->get_cur_hover_face_name();

      //      }

      //   }

      //}

//      ::userex::pane_tab_view::update(pupdate);
      ::user::tab_view::update(pupdate);

   }


} // namespace simple_form





