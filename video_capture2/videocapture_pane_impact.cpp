#include "framework.h"
#include "berg/user/user/tab_pane.h"



namespace app_complex_video_capture
{

   
   pane_impact::pane_impact()
   {

      m_pimpactLast = nullptr;
      
   }


   pane_impact::~pane_impact()
   {

   }


   void pane_impact::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void pane_impact::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_impact::install_message_routing(::channel * pchannel)
   {

      ::userex::pane_tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_impact::on_message_create);

   }


   void pane_impact::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      set_tab("Menu",MENU_IMPACT);
      set_tab("app_complex_video_capture", MAIN_IMPACT);
      set_tab("Open", FILEMANAGER_IMPACT);

      set_current_tab_by_id(MAIN_IMPACT);

   }

   void pane_impact::on_change_cur_sel()
   {

      ::userex::pane_tab_impact::on_change_cur_sel();

      string strId = get_impact_id();

      if(get_impact_id() == GCOM_IMPACT
            || get_impact_id() == MAIN_IMPACT
            || get_impact_id() == MAIN_SWITCHER_IMPACT)
      {



      }
      else if (get_impact_id() == MENU_IMPACT)
      {

         auto ptabpaneMenu = get_current_tab_index();

         ::file::path path = prepare_menu_impact();

         m_pdocMenu->open_document(path);


      }
   


   }



   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->id())
      {
      case MENU_IMPACT:
      {

         auto puser = user();

         m_pdocMenu = puser->create_child_form(this, this, pimpactdata->m_pplaceholder);

         pimpactdata->m_eflag.add(::user::e_flag_hide_on_kill_focus);


         //::file::path path = prepare_menu_impact();

         //m_pdocMenu->open_document(path);


//         m_prollspf = pimpact->get_child_by_id("roll_spf");
         //try
         //{
         //   pform->get_child_by_id("clockverse_auto")->set_check(papp->should_auto_launch_clockverse_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag")->set_check(papp->should_bind_flag_country_ca2_domain_image_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag_auto")->set_check(papp->should_auto_launch_flag_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}



      }
      break;
      case MAIN_IMPACT:
      {
         auto pcreate = m_pusersystem->m_pcreate;

         auto pcommandline = pcreate->m_pcommandline;

         auto& payloadFile = pcommandline->m_payloadFile;

         auto papp = get_app();

         papp->m_ptemplateHelloMultiverseImpact->open_document_file(papp, payloadFile, true, pimpactdata->m_pplaceholder);

      }

      break;




      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(m_pdocMenu != nullptr && ptopic->is_about(m_pdocMenu->get_impact(0)))
      {

         if(ptopic->id() == ::id_after_change_text)
         {


            if (ptopic->id() == ::id_set_check && ptopic->user_interaction() != nullptr)
            {

               string strCheck = ptopic->user_interaction_id();


            }
         //if(ptopic->user_interaction_id() == "clockverse")
         //   {
         //      papp->set_binding_clockverse_country_time_zone_set_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_interaction_id() == "clockverse_auto")
         //   {
         //      papp->set_auto_launch_clockverse_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_interaction_id() == "flag")
         //   {
         //      papp->set_binding_flag_country_ca2_domain_image_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_interaction_id() == "flag_auto")
         //   {
         //      papp->set_auto_launch_flag_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         }
      }

      
   }


   ::file::path pane_impact::prepare_menu_impact()
   {

      string str;

      string strBilbo;

      str = file()->as_string("matter://menu.html");

      str.find_replace("***bilbo***", strBilbo);

      ::file::path path;

      path = directory()->appdata() / "videocapture_menu.html";

      file()->put_text(path, str);

      return path;

   }


} // namespace app_complex_video_capture





