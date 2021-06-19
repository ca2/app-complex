#include "framework.h"

//void throw_a_::exception::exception_through_one_single_function_boundary(string str)
//{
//
//   __throw(::exception::exception(str + " this is also a very artificial simple exception to test if exception can be safely thrown and caught at this environment (in this specific case: Android)... but across a single function boundary (thrown in function, should be caught in caller...) ..."));
//
//}

namespace videocapture
{





   int debug_filling_holding()
   {

      hold<int> p(this);

      p.work([]()
      {
         output_debug_string("B: waiting fifteen seconds (I am sluggish... (and may be not enough... but some training and sweating...))\n");
         sleep(1_s);
         output_debug_string("B: setting 17\n");
         int i = 17;
         output_debug_string("B: 17 was set\n");
         output_debug_string("B: returnin 17\n");
         return i;
      });

      output_debug_string("A: waiting for future result\n");
      auto r = p.get();
      output_debug_string("A: got " + __str(r) + "\n");
      p.work([]()
      {
         output_debug_string("B2: waiting 1 second\n");
         sleep(1_s);
         output_debug_string("B2: setting 17\n");
         int i = 17;
         __throw(::exception::exception("test"));
         output_debug_string("B2: 17 was set\n");
         output_debug_string("B2: returnin 17\n");
         return i;
      });

      try
      {

         output_debug_string("A2: waiting for another future result\n");
         auto r = p.get();
         output_debug_string("A2: got " + __str(r) + "\n");
      }
      catch (const ::exception::exception & e)
      {
         output_debug_string("A2: didn\1 got anything from second job, error ='" + e.get_message()+"'\n");
      }

      return 0;
   }



   application::application(::object * pobject) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject),
      ::sphere::application(pobject):
      m_mutexAiFont(this)
   {


      //m_ptopviewLast                          = nullptr;
      //m_pviewLast                            = nullptr;

      //m_ptopviewMain                          = nullptr;
      //m_pviewMain                          = nullptr;
      //m_ptoggleviewMain= nullptr;
      //m_peditMain= nullptr;

      //m_ptopviewSwitcher                          = nullptr;
      //m_pviewSwitcher                          = nullptr;
      //m_ptoggleviewSwitcher= nullptr;
      //m_peditSwitcher= nullptr;

      //m_ptopviewFont                          = nullptr;
      //m_pfontlistview                          = nullptr;
      //m_ptoggleviewFontSel= nullptr;
      //m_peditFontSel = nullptr;

      m_ptemplateHelloMultiverseMain = nullptr;
      m_ptemplateHelloMultiverseView = nullptr;
      m_ptemplateHelloMultiverseSwitcher = nullptr;

      m_strAppName            = "videocapture";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

      m_etype                 = type_normal;

      m_strHelloMultiverseDefault             = "Hello Multiverse!!";
      m_strAlternateHelloMultiverseDefault    = "Hello!!";

      m_strHelloMultiverse             = m_strHelloMultiverseDefault;
      m_strAlternateHelloMultiverse    = m_strAlternateHelloMultiverseDefault;

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_faceAi = nullptr; // FT_Face m_faceAi;

      m_bMultiverseChat = true;

      m_bMFStartup = false;

   }


   application::~application()
   {
   }


   ::e_status application::init_instance()
   {

      //try
      //{

      //   __throw(::exception::exception( "this is a very artificial simple exception to test if exception can be safely thrown and caught at this environment (in this specific case: Android)..."));

      //}
      //catch (...)
      //{


      //}

      //try
      //{

      //   throw_a_::exception::exception_through_one_single_function_boundary("... catch");

      //}
      //catch (...)
      //{


      //}

      //try
      //{

      //   __throw(::exception::exception( "specific catch 1..."));

      //}
      //catch (const ::exception::exception & e)
      //{


      //}

      //try
      //{

      //   throw_a_::exception::exception_through_one_single_function_boundary("specific catch 2");

      //}
      //catch (const ::exception::exception & e)
      //{


      //}

      create_factory <::videocapture::document >();
      create_factory <::videocapture::frame >();
      create_factory <::videocapture::main_frame >();
      create_factory <::videocapture::edit_view >();
//      create_factory <::videocapture::user::button_view >();
      create_factory <::user::button_view >();
//      create_factory <::videocapture::user::split_view >();
//      create_factory <::videocapture::lite_view >();
//      create_factory <::videocapture::full_view >();
      create_factory <::videocapture::view >();
      create_factory <::videocapture::main_view >();
      create_factory <::videocapture::switcher_view >();
      create_factory <::videocapture::pane_view >();
      create_factory <::user::font_list >();
      create_factory <::user::font_list_view >();
      create_factory <::videocapture::font_view >();
      create_factory <::videocapture::top_view >();
      create_factory <::videocapture::toggle_view >();
      create_factory <::videocapture::gcom >();

      if(!::aura::application::init_instance())
         return false;

//      if(has_property("install"))
//      {
//         ::message_box(nullptr, "HelloMultiverse install", "HelloMultiverse install", 0);
//      }


      string str = m_varTopicQuery["videocapture"];

      if (str.has_char())
      {

         m_strHelloMultiverse = str;

      }

      set_local_data_key_modifier();

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = __new(::user::single_document_template(
                          this,
                          "main",
                          __type(document),
                          __type(main_frame),
                          __type(pane_view)));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
      pDocTemplate = __new(::user::single_document_template(
                          this,
                          "main",
                          __type(document),
                          __type(frame),
                          __type(main_view)));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseView = pDocTemplate;
      pDocTemplate = __new(::user::single_document_template(
                          this,
                          "switcher",
                          __type(document),
                          __type(frame),
                          __type(switcher_view)));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseSwitcher = pDocTemplate;


      m_ptemplateHelloMultiverseFontSel = __new(::user::single_document_template(
                                          this,
                                          "main",
                                          __type(::user::document),
                                          __type(::simple_frame_window),       // top level SDI frame::user::interaction_impl
                                          __type(font_view)));

      add_document_template(m_ptemplateHelloMultiverseFontSel);

      //if (!mf_startup())
      //{

      //   return false;

      //}

      m_bMFStartup = true;

      return true;
   }

   i32 application::exit_application()
   {

      return ::aura::application::exit_application();
   }

   void application::on_request(::create * pcreate)
   {
      //debug_filling_holding();

#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(false);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      m_bMultiverseChat = !m_varTopicQuery["no_hello_edit"].is_set();

      if(m_ptemplateHelloMultiverseMain->get_document_count() == 0)
      {

         m_ptemplateHelloMultiverseMain->do_request(pcreate);

      }

      if(pcreate->m_pcommandline->m_varFile.has_char())
      {

         m_ptemplateHelloMultiverseView->do_request(pcreate);

      }

      //rectangle_i32 r(20, 20, 20, 20);

      //ClipCursor(rectangle);

      if (m_varTopicQuery["wfi_maximize"].is_set())
      {

         pcreate->m_pcommandline->m_varQuery["document"].cast < document >()->get_typed_view < ::userex::pane_tab_view >()->top_level_frame()->_001WindowMaximize();

      }

      //pcreate->m_pcommandline->m_varQuery["document"].cast < document >()->get_typed_view < pane_view >()->get_parent_frame()->display(e_display_restore);

   }



   void application::load_ai_font()
   {

      if(m_bLoadAiFont)
         return ;

      m_bLoadAiFont = true;

      m_iErrorAiFont = -1;

      __begin_thread(get_application(),&thread_proc_load_ai_font,this,::priority_normal,0,0,nullptr);

   }


   ::u32 application::thread_proc_load_ai_font(void * pparam)
   {

      application * pview = (application *)pparam;

      pview->m_iErrorAiFont = -1;

      //pview->m_iErrorAiFont = FT_New_Face((FT_Library)Sys(pview->get_application()).ftlibrary(),Sess(pview->get_application()).dir().matter_file("font/truetype/arialuni.ttf"),0,(FT_Face *)&pview->m_faceAi);

      return pview->m_iErrorAiFont;

   }
   //void application::on_create_impact(::user::impact_data * pimpactdata)
   //{

   //   switch(pimpactdata->m_id)
   //   {
   //   case impact_menu:
   //   {
   //      m_pdocMenu = papplication->create_child_form(this,pimpactdata->m_pplaceholder);

   //      m_pdocMenu->open_document("matter://menu.html");

   //      __pointer(::user::impact) pview = m_pdocMenu->get_view();

   //      m_prollfps = dynamic_cast < ::calculator::plain_edit_view * > (pview->get_child_by_id("roll_fps"));
   //      //         m_prollspf = pview->get_child_by_id("roll_spf");
   //      //try
   //      //{
   //      //   pform->get_child_by_id("clockverse_auto")->_001SetCheck(papplication->should_auto_launch_clockverse_on_hover(),::e_source_initialize);
   //      //}
   //      //catch(...)
   //      //{
   //      //}

   //      //try
   //      //{
   //      //   pform->get_child_by_id("flag")->_001SetCheck(papplication->should_bind_flag_country_ca2_domain_image_on_hover(),::e_source_initialize);
   //      //}
   //      //catch(...)
   //      //{
   //      //}

   //      //try
   //      //{
   //      //   pform->get_child_by_id("flag_auto")->_001SetCheck(papplication->should_auto_launch_flag_on_hover(),::e_source_initialize);
   //      //}
   //      //catch(...)
   //      //{
   //      //}



   //   }
   //   break;
   //   case MAIN_IMPACT:
   //   {
   //      __pointer(::user::document) pdocument =  papplication->m_ptemplateHelloMultiverseView->open_document_file(this, nullptr,true,pimpactdata->m_pplaceholder);


   //   }

   //   break;

   //   case PaneViewHelloMultiverseSwitcher:
   //   {

   //      papplication->m_ptemplateHelloMultiverseSwitcher->open_document_file(this, nullptr,true,pimpactdata->m_pplaceholder);



   //   }

   //   break;
   //   case PaneViewFontSel:
   //   {
   //      papplication->m_ptemplateHelloMultiverseFontSel->open_document_file(this, nullptr,true,pimpactdata->m_pplaceholder);


   //   }

   //   break;



   //   }

   //   //::userex::pane_tab_view::on_create_impact(pimpactdata);

   //}



//   void application::on_create_split_view(::user::split_view * psplit)
//   {
//
//      if(::str::ends(psplit->m_id.m_psz,"_top"))
//      {
//
//         psplit->m_bHideOnTransparentFrame = true;
//
//         if(psplit->get_pane_count() > 0)
//            return;
//
//         psplit->SetPaneCount(2);
//
//         psplit->SetSplitOrientation(e_orientation_vertical);
//
//         psplit->set_position_rate(0,0.84);
//
//         psplit->initialize_split_layout();
//
//         if(psplit->m_id == "videocapture_top")
//         {
//
//            m_peditMain = psplit->create_view < ::user::plain_edit_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(0),"videocapture_edit");
//
//            if(m_peditMain == nullptr)
//            {
//
//               message_box(nullptr,"Could not create folder edit view");
//
//            }
//
//            m_ptoggleviewMain = psplit->create_view < ::user::button_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(1),"videocapture_toggle");
//
//            if(m_ptoggleviewMain == nullptr)
//            {
//
//               message_box(nullptr,"Could not create file list ::user::impact");
//
//            }
//
//
//         }
//         else if(psplit->m_id == "switcher_top")
//         {
//
//            m_peditSwitcher = psplit->create_view < ::user::plain_edit_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(0),"switcher_edit");
//
//            if(m_peditSwitcher == nullptr)
//            {
//
//               message_box(nullptr,"Could not create folder edit view");
//
//            }
//
//            m_ptoggleviewSwitcher = psplit->create_view < ::user::button_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(1),"switcher_toggle");
//
//            if(m_ptoggleviewSwitcher == nullptr)
//            {
//
//               message_box(nullptr,"Could not create file list ::user::impact");
//
//            }
//
//
//         }
//         else if(psplit->m_id == "fontsel_top")
//         {
//
//            m_peditFontSel =psplit-> create_view < ::user::plain_edit_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(0),"fontsel_edit");
//
//            if(m_peditFontSel == nullptr)
//            {
//
//               message_box(nullptr,"Could not create folder edit view");
//
//            }
//
//            m_ptoggleviewFontSel = psplit->create_view < ::user::button_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(1),"fontsel_toggle");
//
//            if(m_ptoggleviewFontSel == nullptr)
//            {
//
//               message_box(nullptr,"Could not create file list ::user::impact");
//
//            }
//
//
//         }
//
//
//
//
//      }
//      else if(psplit->get_document()->get_document_template() == m_ptemplateHelloMultiverseFontSel)
//      {
//
//
//         if(psplit->get_pane_count() > 0)
//            return;
//
//         psplit->SetPaneCount(2);
//
//         psplit->SetSplitOrientation(e_orientation_horizontal);
//
//         psplit->set_position(0,24);
//
//         psplit->initialize_split_layout();
//
//         m_ptopviewFont = psplit->create_view < ::user::split_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(0),"fontsel_top");
//
//         if(m_ptopviewFont == nullptr)
//         {
//
//            message_box(nullptr,"Could not create folder edit view");
//
//         }
//
//         //SetPane(0,m_ptopview,false);
//
//         m_pfontlistview = psplit->create_view < ::user::font_list_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(1),"fontsel_view");
//
//         if(m_pfontlistview == nullptr)
//         {
//
//            message_box(nullptr,"Could not create file list ::user::impact");
//
//         }
//
//         //SetPane(1,m_pview,false);
//
//      }
//      else if(psplit->get_document()->get_document_template() == m_ptemplateHelloMultiverseSwitcher)
//      {
//
//
//         if(psplit->get_pane_count() > 0)
//            return;
//
//         psplit->SetPaneCount(2);
//
//         psplit->SetSplitOrientation(e_orientation_horizontal);
//
//         psplit->set_position(0,24);
//
//         psplit->initialize_split_layout();
//
//         m_ptopviewSwitcher = psplit->create_view < ::user::split_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(0),"switcher_top");
//
//         if(m_ptopviewSwitcher == nullptr)
//         {
//
//            message_box(nullptr,"Could not create folder edit view");
//
//         }
//
//         //SetPane(0,m_ptopview,false);
//
//         m_pviewSwitcher = psplit->create_view < view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(1),"switcher_view");
//
//         m_pviewSwitcher->m_prender->m_bAlternate = true;
//
//         if(m_pviewSwitcher == nullptr)
//         {
//
//            message_box(nullptr,"Could not create file list ::user::impact");
//
//         }
//
//         if(m_pviewSwitcher != nullptr)
//         {
//
//            string strText;
//
//            m_pviewSwitcher->data_get("cur_text",strText);
//
//            m_peditSwitcher->_001SetText(strText, ::e_source_initialize);
//
//         }
//
//
//         //m_ptopviewSwitcher->m_pview = m_pview;
//
//
//         //SetPane(1,m_pview,false);
//
//      }
//      else if(psplit->get_document()->get_document_template() == m_ptemplateHelloMultiverseView)
//      {
//         if(psplit->get_pane_count() > 0)
//            return;
//
//         int iPane;
//
//         if(m_bMultiverseChat)
//         {
//
//            psplit->SetPaneCount(2);
//
//            psplit->SetSplitOrientation(e_orientation_horizontal);
//
//            psplit->set_position(0,31);
//
//            psplit->initialize_split_layout();
//
//            m_ptopviewMain = psplit->create_view < ::user::split_view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(0),"videocapture_top");
//
//            if(m_ptopviewMain == nullptr)
//            {
//
//               message_box(nullptr,"Could not create folder edit view");
//
//            }
//
//            //SetPane(0,m_ptopview,false);
//
//            iPane = 1;
//
//         }
//         else
//         {
//
//            psplit->SetPaneCount(1);
//
//            psplit->initialize_split_layout();
//
//            iPane = 0;
//
//         }
//
//         //m_pview = create_view < lite_view >();
//
//         m_pviewMain = psplit->create_view < view >(nullptr,::rectangle_i32(),psplit->get_pane_holder(iPane),"videocapture_view");
//
//         if(m_pviewMain == nullptr)
//         {
//
//            message_box(nullptr,"Could not create file list ::user::impact");
//
//         }
//
//
//         if(m_peditMain != nullptr)
//         {
//
//            string strText;
//
//            m_pviewMain->data_get("cur_text",strText);
//
//            m_peditMain->_001SetText(strText,::e_source_initialize);
//
//         }
//
//
//
//         if(m_ptopviewMain != nullptr)
//         {
//
//            //m_ptopviewMain->m_pview = m_pviewMain;
//
//         }
//
//         //SetPane(iPane,m_pview,false);
//
//      }
//
//
//
//   }
//
//
//   void application::on_control_event(::user::control_event * pevent)
//   {
//
//      if(pevent->m_eevent == ::user::e_event_on_create_tab)
//      {
//
//         if(pevent->m_ptab != nullptr && pevent->get_impact_matter() == "main")
//         {
//
//
//            pevent->m_ptab->set_tab("Menu",MENU_IMPACT);
//            pevent->m_ptab->set_tab("videocapture",MAIN_IMPACT);
//            pevent->m_ptab->set_tab("switcher",MAIN_SWITCHER_IMPACT);
//            pevent->m_ptab->set_tab("Font",FONTSEL_IMPACT);
//#if 1
//            pevent->m_ptab->set_tab("Open",FILEMANAGER_IMPACT);
//#endif
//
//            //set_cur_tab_by_id(MAIN_SWITCHER_IMPACT);
//            pevent->m_ptab->set_cur_tab_by_id(MAIN_IMPACT);
//
//         }
//
//
//      }
//
//      else if(pevent->m_eevent == ::user::e_event_button_clicked)
//      {
//
//         if(pevent->m_puie->m_id == "switcher_toggle")
//         {
//
//            __pointer(view) pview = m_pviewSwitcher;
//
//            pview->m_prender->m_bLite = !pview->m_prender->m_bLite;
//
//         }
//         else if(pevent->m_puie->m_id == "videocapture_toggle")
//         {
//
//            if(m_pviewMain->m_prender->m_bLite && !papplication->m_bLoadAiFont)
//            {
//
//               papplication->load_ai_font();
//
//            }
//
//            m_pviewMain->m_prender->m_bLite = !m_pviewMain->m_prender->m_bLite;
//
//
//            m_pviewMain->on_layout(::draw2d::graphics_pointer & pgraphics);
//
//         }
//
//
//      }
//      else if(pevent->m_eevent == ::user::e_event_after_change_text)
//      {
//
//         if(pevent->m_puie->m_id.is_text() && ::str::ends(pevent->m_puie->m_id.m_psz,"_edit"))
//         {
//
//            string strText;
//
//            pevent->m_puie->_001GetText(strText);
//
//            if(pevent->m_puie->m_id == "videocapture_edit")
//            {
//
//               if(m_pviewMain != nullptr)
//               {
//
//                  {
//
//                     synchronous_lock synchronouslock(&m_pviewMain->m_mutexText);
//
//                     m_pviewMain->data_set("cur_text",strText);
//
//                     m_pviewMain->m_strNewHelloMultiverse = strText;
//
//                  }
//
//                  m_pviewMain->post_message(message_view_update);
//
//               }
//
//               pevent->m_bRet = true;
//
//               pevent->m_bProcessed = true;
//
//               return true;
//
//            }
//            else if(pevent->m_puie->m_id == "switcher_edit")
//            {
//
//               if(m_pviewSwitcher != nullptr)
//               {
//
//                  {
//
//                     synchronous_lock synchronouslock(&m_pviewSwitcher->m_mutexText);
//
//                     m_pviewSwitcher->data_set("cur_text",strText);
//
//                     m_pviewSwitcher->m_strNewHelloMultiverse = strText;
//
//                  }
//
//                  m_pviewSwitcher->post_message(message_view_update);
//
//               }
//
//               pevent->m_bRet = true;
//
//               pevent->m_bProcessed = true;
//
//               return true;
//            }
//            else if(pevent->m_puie->m_id == "fontsel_edit")
//            {
//
//               if(m_pfontlistview != nullptr)
//               {
//
//                  {
//
//                     synchronous_lock synchronouslock(m_pfontlistview->mutex());
//
//                     m_pfontlistview->m_strText = strText;
//
//                  }
//
//
//               }
//
//            }
//
//
//         }
//
//      }
//      else if(pevent->m_eevent == ::user::e_event_after_change_cur_sel)
//      {
//
//         if(m_pfontlistview == pevent->m_puie)
//         {
//
//            if(m_pviewLast != nullptr)
//            {
//
//               string strFont = m_pfontlistview->get_cur_sel_face_name();
//
//               if(strFont.has_char())
//               {
//
//                  m_pviewLast->m_strNewFont = strFont;
//
//                  m_pviewLast->on_layout(::draw2d::graphics_pointer & pgraphics);
//
//               }
//
//            }
//
//         }
//
//      }
//
//      return true;
//
//   }
//
//   void application::on_control_event(::user::control_event * pevent)
//   {
//
//      if(m_pdocMenu != nullptr && pview == m_pdocMenu->get_view(0))
//      {
//
//         if(pevent->m_eevent == ::user::e_event_after_change_text && pevent->m_puie != nullptr)
//         {
//
//            if(m_prollfps != nullptr && pevent->m_puie->m_id == "roll_fps" && !pevent->m_context.is_source(::e_source_initialize)
//               && !pevent->m_context.is_source(::e_source_database))
//            {
//
//               try
//               {
//                  string str;
//                  double d = m_prollfps->m_val.m_dR;
//
//                  {
//
//                     string str;
//
//                     m_prollfps->_001GetText(str);
//
//                     m_pviewLast->data_set("cur_fps_text",str);
//
//                  }
//
//                  {
//
//                     ::payload v;
//
//                     v = d;
//
//                     m_pviewLast->data_set("cur_fps",v);
//
//                  }
//
//                  m_pviewLast->m_dFps = d;
//                  m_pviewLast->m_dwRoll= ::millis::now();
//                  //if(fabs(d) < 0.0000000001)
//                  //{
//                  //   m_prollspf->_001SetText("",::e_source_initialize);
//                  //}
//                  //else
//                  //{
//                  //   m_prollspf->_001SetText(__str(1.0/d),::e_source_initialize);
//                  //}
//               }
//               catch(...)
//               {
//               }
//
//            }
//            //else if(pevent->m_puie->m_id == "roll_spf" && !pevent->m_context.is_source(::e_source_initialize))
//            //{
//
//            //   try
//            //   {
//            //      string str;
//            //      m_prollspf->_001GetText(str);
//            //      double d = atof(str);
//            //      if(fabs(d) < 0.0000000001)
//            //      {
//            //         m_prollfps->_001SetText("",::e_source_initialize);
//            //      }
//            //      else
//            //      {
//            //         m_pflagview->m_dFps = 1.0/ d;
//            //         m_pflagview->m_dwRoll= ::millis::now();
//            //         m_prollfps->_001SetText(__str(1.0 / d),::e_source_initialize);
//            //      }
//            //   }
//            //   catch(...)
//            //   {
//            //   }
//
//            //}
//
//
//         }
//
//         //   if(pevent->m_puie->m_id == "clockverse")
//         //   {
//         //      papplication->set_binding_clockverse_country_time_zone_set_on_hover(pevent->m_puie->_001GetCheck() == ::check_checked);
//         //      return true;
//         //   }
//         //   else if(pevent->m_puie->m_id == "clockverse_auto")
//         //   {
//         //      papplication->set_auto_launch_clockverse_on_hover(pevent->m_puie->_001GetCheck() == ::check_checked);
//         //      return true;
//         //   }
//         //   else if(pevent->m_puie->m_id == "flag")
//         //   {
//         //      papplication->set_binding_flag_country_ca2_domain_image_on_hover(pevent->m_puie->_001GetCheck() == ::check_checked);
//         //      return true;
//         //   }
//         //   else if(pevent->m_puie->m_id == "flag_auto")
//         //   {
//         //      papplication->set_auto_launch_flag_on_hover(pevent->m_puie->_001GetCheck() == ::check_checked);
//         //      return true;
//         //   }
//         //}
//      }
//
//      return false;
//   }
//
//
//
//   void application::on_change_cur_sel(::user::tab * ptab)
//   {
//
//      __pointer(::userex::pane_tab_view) ptabview = ptab;
//
//      if(ptabview.is_set() && (ptabview->get_document()->get_document_template()->m_strMatter == "main"
//         || ::str::ends(ptabview->get_document()->get_document_template()->m_strMatter, "_main")))
//      {
//
//
////         ptabview->::userex::pane_tab_view::on_change_cur_sel();
//
//         string strId = ptabview->get_view_id();
//         string_array stra;
//         stra.explode("->:<-",strId);
//         if(ptabview->get_view_id() == MAIN_IMPACT
//            || ptabview->get_view_id() == MAIN_SWITCHER_IMPACT
//            || stra.contains(__str((int)MAIN_IMPACT))
//            || stra.contains(__str((int)MAIN_SWITCHER_IMPACT)))
//         {
//            if(ptabview->get_pane_by_id(MENU_IMPACT)->m_pholder != nullptr)
//            {
//               ptabview->get_pane_by_id(MENU_IMPACT)->m_pholder->ShowWindow(SW_HIDE);
//            }
//            if(ptabview->get_pane_by_id(FILEMANAGER_IMPACT) != nullptr && ptabview->get_pane_by_id(FILEMANAGER_IMPACT)->m_pholder != nullptr)
//            {
//               ptabview->get_pane_by_id(FILEMANAGER_IMPACT)->m_pholder->ShowWindow(SW_HIDE);
//            }
//            if(ptabview->get_pane_by_id(FONTSEL_IMPACT)->m_pholder != nullptr)
//            {
//               ptabview->get_pane_by_id(FONTSEL_IMPACT)->m_pholder->ShowWindow(SW_HIDE);
//            }
//         }
//         else if(ptabview->get_view_id() == MENU_IMPACT)
//         {
//
//            if(m_pviewLast != nullptr)
//            {
//
//               string str;
//
//               m_pviewLast->data_get("cur_fps_text",str);
//
//               m_prollfps->_001SetText(str, ::e_source_database);
//
//            }
//
//         }
//
//         if(ptabview->get_view_id() == MAIN_IMPACT)
//         {
//
//            m_pviewLast = m_pviewMain;
//
//         }
//         else if(ptabview->get_view_id() == MAIN_SWITCHER_IMPACT)
//         {
//
//            m_pviewLast = m_pviewSwitcher;
//
//         }
//         //else if(ptabview->get_view_id() != FONTSEL_IMPACT)
//         //{
//         //
//         //   m_pviewLast = nullptr;
//
//         //}
//
//         if(m_pviewLast != nullptr && m_pfontlistview != nullptr)
//         {
//
//            m_pfontlistview->set_sel_by_name(m_pviewLast->m_strFont);
//
//         }
//
//      }
//
//   }

   i64 application::add_ref()
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }

   i64 application::dec_ref()
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }

} // namespace videocapture




extern "C"
::acme::library * app_core_videocapture_get_new_library(::object * pobject)
{

   return new ::apex::single_application_library < ::videocapture::application > (pobject, "app-core");

}




