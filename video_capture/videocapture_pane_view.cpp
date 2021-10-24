#include "framework.h"
#include "base/user/user/tab_pane.h"



namespace video_capture
{

   
   pane_view::pane_view()
   {

      m_pviewLast = nullptr;
      
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

      ::userex::pane_tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::on_message_create);

   }


   void pane_view::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      set_tab("Menu",MENU_IMPACT);
      set_tab("video_capture", MAIN_IMPACT);
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
      else if (get_view_id() == MENU_IMPACT)
      {

         auto ptabpaneMenu = get_current_tab_index();

         ::file::path path = prepare_menu_view();

         m_pdocMenu->open_document(path);


      }
   


   }



   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_id)
      {
      case MENU_IMPACT:
      {

         auto puser = user()->m_pcoreuser;

         m_pdocMenu = puser->create_child_form(this, this, pimpactdata->m_pplaceholder);

         pimpactdata->m_eflag.add(::user::e_flag_hide_on_kill_focus);


         //::file::path path = prepare_menu_view();

         //m_pdocMenu->open_document(path);


//         m_prollspf = pview->get_child_by_id("roll_spf");
         //try
         //{
         //   pform->get_child_by_id("clockverse_auto")->_001SetCheck(papplication->should_auto_launch_clockverse_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag")->_001SetCheck(papplication->should_bind_flag_country_ca2_domain_image_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag_auto")->_001SetCheck(papplication->should_auto_launch_flag_on_hover(),::e_source_initialize);
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

         auto& payloadFile = pcommandline->m_varFile;

         auto papplication = get_application();

         papplication->m_ptemplateHelloMultiverseView->open_document_file(papplication, payloadFile, true, pimpactdata->m_pplaceholder);

      }

      break;




      }

      ::userex::pane_tab_view::on_create_impact(pimpactdata);

   }


   void pane_view::handle(::subject * psubject, ::context * pcontext)
   {

      if(m_pdocMenu != nullptr && dynamic_cast < ::user::impact * > (psubject->get_form()) == m_pdocMenu->get_view(0) && psubject->user_interaction() != nullptr)
      {

         if(psubject->m_id == ::e_subject_after_change_text)
         {


            if (psubject->m_id == ::e_subject_set_check && psubject->user_interaction() != nullptr)
            {

               string strCheck = psubject->user_element_id();


            }
         //if(psubject->user_element_id() == "clockverse")
         //   {
         //      papplication->set_binding_clockverse_country_time_zone_set_on_hover(psubject->user_interaction()->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //   else if(psubject->user_element_id() == "clockverse_auto")
         //   {
         //      papplication->set_auto_launch_clockverse_on_hover(psubject->user_interaction()->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //   else if(psubject->user_element_id() == "flag")
         //   {
         //      papplication->set_binding_flag_country_ca2_domain_image_on_hover(psubject->user_interaction()->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //   else if(psubject->user_element_id() == "flag_auto")
         //   {
         //      papplication->set_auto_launch_flag_on_hover(psubject->user_interaction()->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         }
      }

      
   }


   ::file::path pane_view::prepare_menu_view()
   {

      string str;

      string strBilbo;

      auto pcontext = m_pcontext;

      str = pcontext->m_papexcontext->file().as_string("matter://menu.html");

      str.replace("***bilbo***", strBilbo);

      ::file::path path;

      path = pcontext->m_papexcontext->dir().appdata() / "videocapture_menu.html";

      pcontext->m_papexcontext->file().put_contents(path, str);

      return path;

   }


} // namespace video_capture





