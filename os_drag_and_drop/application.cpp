#include "framework.h"
#include "aura/application.h"


namespace simple_os_drag_and_drop
{


   application::application()
   {

      m_ptemplateSimpleDrawingMain = NULL;
      m_ptemplateSimpleDrawingView = NULL;

      m_strAppId = "app-simple/drag_and_drop";
      m_strAppName = "app-simple/drag_and_drop";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

   }


   application::~application()
   {
   }


   ::e_status application::init_instance()
   {

      set_local_data();

      ::aura::session * pcoression = &Session;

      pcoression->will_use_view_hint(FONTSEL_IMPACT);

      create_factory <::simple_os_drag_and_drop::document >();
      create_factory <::simple_os_drag_and_drop::frame >();
      create_factory <::simple_os_drag_and_drop::main_frame >();
      create_factory <::user::button_view >();
      create_factory <::simple_os_drag_and_drop::impact >();
      create_factory <::simple_os_drag_and_drop::main_impact >();
      create_factory <::simple_os_drag_and_drop::tab_view >();

      if (!::aura::application::init_instance())
      {

         return false;

      }

      add_matter_locator("app-simple/drawing");

      auto pdoctemplate = __new(::user::single_document_template(
                               "main",
                               __type(document),
                               __type(main_frame),
                               __type(tab_view)));

      m_ptemplateSimpleDrawingMain = pdoctemplate;
      add_document_template(pdoctemplate);


      pdoctemplate = __new(::user::single_document_template(
                          "main",
                          __type(document),
                          __type(frame),
                          __type(main_impact)));

      m_ptemplateSimpleDrawingView = pdoctemplate;
      add_document_template(pdoctemplate);




      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

//      {
//
//         auto pthread = fork([this]()
//            {
//
//               output_debug_string("test");
//
//            });
//
//      }

#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(false);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      if (m_ptemplateSimpleDrawingMain->get_document_count() == 0)
      {

         if(pcreate->m_bMakeVisible)
         {

            INFORMATION("pcreate->m_bMakeVisible");

         }
         else
         {

            INFORMATION("NOT pcreate->m_bMakeVisible");

         }

         m_ptemplateSimpleDrawingMain->do_request(pcreate);

      }

      if (pcreate->m_pcommandline->m_varFile.has_char())
      {

         m_ptemplateSimpleDrawingView->do_request(pcreate);

      }

      if (is_true("wfi_maximize"))
      {

         pcreate->m_pcommandline->m_varQuery["document"].cast < document >()->get_typed_view < ::user::tab_view >()->top_level_frame()->prodevian_prepare_window_maximize();

      }

      output_debug_string("\nfinished simple_os_drag_and_drop::on_request");

   }


   string application::preferred_experience()
   {

      return "tranquillum";

   }


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   __pointer(impact) application::create_simple_os_drag_and_drop_view(::user::impact* pimpactParent, ::user::impact_data * pimpactdata)
   {

      return pimpactParent->create_view < impact >(pimpactdata);

   }

   
   __namespace_application_factory("app-simple/os_drag_and_drop");


} // namespace simple_os_drag_and_drop




//
//extern "C"
//::acme::library * app_simple_drag_and_drop_get_new_library()
//{
//
//   return new ::apex::single_application_library < ::simple_os_drag_and_drop::application >("app-simple/drag_and_drop");
//
//}
//
//
//aura_app aura_app_simple_drag_and_drop("app-simple/drag_and_drop", &app_simple_drag_and_drop_get_new_library);
//

