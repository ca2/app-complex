#include "framework.h"
#include "base/user/user/tab_pane.h"


namespace app_complex_video_capture
{

   
   pane_view::pane_view()
   {

   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void pane_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_view::install_message_routing(::channel * pchannel)
   {

      ::userex::pane_tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::on_message_create);

   }


   void pane_view::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      set_tab("Options",OPTIONS_IMPACT);
      set_tab("app_complex_video_capture", MAIN_IMPACT);
      set_tab("Open", FILEMANAGER_IMPACT);

      set_current_tab_by_id(MAIN_IMPACT);

   }

   void pane_view::on_change_cur_sel()
   {

      ::userex::pane_tab_view::on_change_cur_sel();

      string strId = get_view_id();

      if(get_view_id() == GCOM_IMPACT
            || get_view_id() == MAIN_IMPACT
            || get_view_id() == MAIN_SWITCHER_IMPACT)
      {



      }
      //else if (get_view_id() == MENU_IMPACT)
      //{

      //   auto ptabpaneMenu = get_current_tab_index();

      //   ::file::path path = prepare_menu_view();

      //   m_pdocMenu->open_document(path);


      //}
   


   }



   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_atom)
      {
//      case MENU_IMPACT:
//      {
//
//         auto puser = user()->m_pcoreuser;
//
//         m_pdocMenu = puser->create_child_form(this, this, pimpactdata->m_pplaceholder);
//
//         pimpactdata->m_eflag.add(::user::e_flag_hide_on_kill_focus);
//
//
//         //::file::path path = prepare_menu_view();
//
//         //m_pdocMenu->open_document(path);
//
//
////         m_prollspf = pview->get_child_by_id("roll_spf");
//         //try
//         //{
//         //   pform->get_child_by_id("clockverse_auto")->_001SetCheck(papplication->should_auto_launch_clockverse_on_hover(),::e_source_initialize);
//         //}
//         //catch(...)
//         //{
//         //}
//
//         //try
//         //{
//         //   pform->get_child_by_id("flag")->_001SetCheck(papplication->should_bind_flag_country_ca2_domain_image_on_hover(),::e_source_initialize);
//         //}
//         //catch(...)
//         //{
//         //}
//
//         //try
//         //{
//         //   pform->get_child_by_id("flag_auto")->_001SetCheck(papplication->should_auto_launch_flag_on_hover(),::e_source_initialize);
//         //}
//         //catch(...)
//         //{
//         //}
//
//
//
//      }
//      break;
      case MAIN_IMPACT:
      {
         auto pcreate = m_pusersystem->m_pcreate;

         auto pcommandline = pcreate->m_pcommandline;

         auto& payloadFile = pcommandline->m_varFile;

         auto papplication = get_application();

         papplication->m_ptemplateVideoCaptureImpact->open_document_file(papplication, payloadFile, true, pimpactdata->m_pplaceholder);

      }

      break;




      }

      ::userex::pane_tab_view::on_create_impact(pimpactdata);

   }


   void pane_view::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->get_extended_topic()->user_interaction() && ptopic->get_extended_topic()->user_interaction()->is_ascendant(m_pdocumentMenu, true))
      {


         if (ptopic->m_atom == ::id_load_form_data)
         {

            ::user::impact * pview = m_pdocumentMenu->get_view(0);

            string strDevice = get_application()->get_current_video_input_device();

            for (auto & pdevice : get_application()->m_pvideoinput->devicea())
            {

               string strId = pdevice->get_id2();

               string strCheck = "video_input_" + strId;

               __pointer(::user::interaction) pcheck = pview->get_child_by_id(strCheck);

               pcheck->add_handler(this);

               bool bSetCheck = strId == strDevice;

               pcheck->_001SetCheck(bSetCheck, ::e_source_sync);

               pcheck->add_handler(this);

            }

            ptopic->get_extended_topic()->m_bOk = true;

            ptopic->get_extended_topic()->m_bRet = true;

            return;

         }

         if (ptopic->m_atom == ::id_set_check && ptopic->get_extended_topic()->user_interaction() != nullptr)
         {

            string strCheck = ptopic->get_extended_topic()->user_element_id();

            INFORMATION(strCheck);

            string strId;

            if (strCheck.begins_eaten_ci(strId, "video_input_"))
            {

               get_application()->set_current_video_input_device(strId);

            }

            ptopic->get_extended_topic()->m_bOk = true;

            ptopic->get_extended_topic()->m_bRet = true;

            return;

         }


         if(ptopic->m_atom == ::id_after_change_text)
         {


         //if(ptopic->user_element_id() == "clockverse")
         //   {
         //      papplication->set_binding_clockverse_country_time_zone_set_on_hover(ptopic->get_extended_topic()->user_interaction()->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_element_id() == "clockverse_auto")
         //   {
         //      papplication->set_auto_launch_clockverse_on_hover(ptopic->get_extended_topic()->user_interaction()->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_element_id() == "flag")
         //   {
         //      papplication->set_binding_flag_country_ca2_domain_image_on_hover(ptopic->get_extended_topic()->user_interaction()->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_element_id() == "flag_auto")
         //   {
         //      papplication->set_auto_launch_flag_on_hover(ptopic->get_extended_topic()->user_interaction()->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         }
      }

      
   }





} // namespace app_complex_video_capture





