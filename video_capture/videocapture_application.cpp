#include "framework.h"

//void throw_a_::exception::exception_through_one_single_function_boundary(string str)
//{
//
//   __throw(::exception::exception(str + " this is also a very artificial simple exception to test if exception can be safely thrown and caught at this environment (in this specific case: Android)... but across a single function boundary (thrown in function, should be caught in caller...) ..."));
//
//}

namespace video_capture
{


   application::application() 
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


      m_strAppId = "app-complex/video_capture";

      m_strAppName = "app-complex/video_capture";

      m_strBaseSupportId = "app-complex/video_capture";


      m_bLicense              = false;

      m_etype                 = type_normal;

      m_strHelloMultiverseDefault             = "Video Capture!!";
      m_strAlternateHelloMultiverseDefault    = "Video Capture!!";

      m_strHelloMultiverse             = m_strHelloMultiverseDefault;
      m_strAlternateHelloMultiverse    = m_strAlternateHelloMultiverseDefault;

      m_bMultiverseChat = true;

      m_bMFStartup = false;

   }


   application::~application()
   {

   }


   ::e_status application::init_instance()
   {
      
      create_factory <::video_capture::document >();
      create_factory <::video_capture::frame >();
      create_factory <::video_capture::main_frame >();
      create_factory <::video_capture::edit_view >();
      create_factory <::user::button_view >();
      create_factory <::video_capture::view >();
      create_factory <::video_capture::main_view >();
      create_factory <::video_capture::pane_view >();
      create_factory <::video_capture::top_view >();
      create_factory <::video_capture::toggle_view >();

      if (!::aura::application::init_instance())
      {

         return false;

      }

      
      auto pDocTemplate = __new(::user::single_document_template(
                          "main",
                          __type(document),
                          __type(main_frame),
                          __type(pane_view)));

      add_document_template(pDocTemplate);

      m_ptemplateHelloMultiverseMain = pDocTemplate;

      pDocTemplate = __new(::user::single_document_template(
                          "main",
                          __type(document),
                          __type(frame),
                          __type(main_view)));
      add_document_template(pDocTemplate);
      
      m_ptemplateHelloMultiverseView = pDocTemplate;


      m_bMFStartup = true;

      return true;
   }

   //i32 application::exit_application()
   //{

   //   return ::aura::application::exit_application();
   //}

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


   }




   i64 application::add_ref()
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }

   i64 application::dec_ref()
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }

} // namespace video_capture







