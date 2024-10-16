#include "framework.h"

//void throw_a_::exception::exception_through_one_single_function_boundary(string str)
//{
//
//   throw ::exception(::exception(str + " this is also a very artificial simple exception to test if exception can be safely thrown and caught at this environment (in this specific case: Android)... but across a single function boundary (thrown in function, should be caught in caller...) ..."));
//
//}

namespace app_complex_video_capture
{


   __IMPLEMENT_APPLICATION_RELEASE_TIME();


   application::application() 
   {


      //m_ptopviewLast                          = nullptr;
      //m_pimpactLast                            = nullptr;

      //m_ptopviewMain                          = nullptr;
      //m_pviewMain                          = nullptr;
      //m_ptoggleimpactMain= nullptr;
      //m_peditMain= nullptr;

      //m_ptopviewSwitcher                          = nullptr;
      //m_pviewSwitcher                          = nullptr;
      //m_ptoggleimpactSwitcher= nullptr;
      //m_peditSwitcher= nullptr;

      //m_ptopviewFont                          = nullptr;
      //m_pfontlistview                          = nullptr;
      //m_ptoggleimpactFontSel= nullptr;
      //m_peditFontSel = nullptr;

      m_ptemplateHelloMultiverseMain = nullptr;
      m_ptemplateHelloMultiverseImpact = nullptr;


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


   void application::init_instance()
   {
      
      factory()->add_factory_item <::app_complex_video_capture::document >();
      factory()->add_factory_item <::app_complex_video_capture::frame >();
      factory()->add_factory_item <::app_complex_video_capture::main_frame >();
      factory()->add_factory_item <::app_complex_video_capture::edit_impact >();
      factory()->add_factory_item <::user::button_impact >();
      factory()->add_factory_item <::app_complex_video_capture::impact >();
      factory()->add_factory_item <::app_complex_video_capture::main_impact >();
      factory()->add_factory_item <::app_complex_video_capture::pane_impact >();
      factory()->add_factory_item <::app_complex_video_capture::top_impact >();
      factory()->add_factory_item <::app_complex_video_capture::toggle_impact >();


      ::aura::application::init_instance();


      //if (!::aura::application::init_instance())
      //{

      //   return false;

      //}

      
      auto pDocTemplate = __initialize_new ::user::single_document_template(
                          "main",
                          ::type < document >(),
                          ::type < main_frame >(),
                          ::type < pane_impact >()));

      add_document_template(pDocTemplate);

      m_ptemplateHelloMultiverseMain = pDocTemplate;

      pDocTemplate = __initialize_new ::user::single_document_template(
                          "main",
                          ::type < document >(),
                          ::type < frame >(),
                          ::type < main_impact >()));
      add_document_template(pDocTemplate);
      
      m_ptemplateHelloMultiverseImpact = pDocTemplate;


      m_bMFStartup = true;

      //return true;

   }

   //i32 application::exit_application()
   //{

   //   return ::aura::application::exit_application();
   //}

   void application::on_request(::request * prequest)
   {
      //debug_filling_holding();

#if 0

#ifdef _DEBUG

      informationf("_DEBUG build? (basis)");

      ASSERT(false);

#else

      informationf("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      if(m_ptemplateHelloMultiverseMain->get_document_count() == 0)
      {

         m_ptemplateHelloMultiverseMain->do_request(pcreate);

      }

      if(pcreate->m_payloadFile.has_char())
      {

         m_ptemplateHelloMultiverseImpact->do_request(pcreate);

      }

      //rectangle_i32 r(20, 20, 20, 20);

      //ClipCursor(rectangle);


   }




   i64 application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }

   i64 application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }

} // namespace app_complex_video_capture







