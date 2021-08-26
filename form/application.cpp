#include "framework.h"
#include "aura/application.h"


#define new ACME_NEW

namespace simple_form
{


   application::application()
   {

      m_ptemplateBeatMapperMain  = NULL;
      m_ptemplateBeatMapperView  = NULL;

      m_strAppId                 = "app-simple/form";
      m_strAppName               = "app-simple/form";
      m_strBaseSupportId         = "ca2_flag";
      m_bLicense                 = false;

      m_bMultiverseChat          = true;

//auto test = new int;

   }


   application::~application()
   {
   }


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }



   ::e_status application::init_instance()
   {

      set_local_data();

      ::aura::session * pcoression = &Session;

      pcoression->will_use_view_hint(FONTSEL_IMPACT);

      create_factory <::simple_form::document >();
      create_factory <::simple_form::frame >();
      create_factory <::simple_form::main_frame >();
      create_factory <::user::button_view >();
      create_factory <::simple_form::impact >();
      create_factory <::simple_form::main_impact >();
      create_factory <::simple_form::tab_view >();
      create_factory <::simple_form::simple_form_001 >();
      create_factory <::simple_form::simple_form_002 >();

      if (!::aura::application::init_instance())
      {

         return false;

      }

      auto pdoctemplate = __new(::user::single_document_template(
                               "main",
                               __type(document),
                               __type(main_frame),
                               __type(tab_view)));
      m_ptemplateBeatMapperMain = pdoctemplate;
      add_document_template(pdoctemplate);


      pdoctemplate = __new(::user::single_document_template(
                          "main",
                          __type(document),
                          __type(frame),
                          __type(main_impact)));
      m_ptemplateBeatMapperView = pdoctemplate;
      add_document_template(pdoctemplate);




      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

//#if 1
      if (pcreate->m_pcommandline->m_varQuery.has_property("m"))
      {

         message_box("m=1");

         set_finish();

         return;

      }
//#endif
#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(false);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      m_bMultiverseChat = !is_true("no_hello_edit");

      if (m_ptemplateBeatMapperMain->get_document_count() == 0)
      {

         m_ptemplateBeatMapperMain->do_request(pcreate);

      }

      if (pcreate->m_pcommandline->m_varFile.has_char())
      {

         m_ptemplateBeatMapperView->do_request(pcreate);

      }

      if (is_true("wfi_maximize"))
      {

         pcreate->m_pcommandline->m_varQuery["document"].cast < document >()->get_typed_view < ::user::tab_view >()->top_level_frame()->prodevian_prepare_window_maximize();

      }

      output_debug_string("\nfinished simple_form::on_request");

   }


   string application::preferred_experience()
   {

      return "tranquillum";

   }



   
   __namespace_application_factory("app-simple/form");


} // namespace simple_form


//
//extern "C"
//::acme::library * app_simple_form_get_new_library()
//{
//
//   return new ::apex::single_application_library < ::simple_form::application >("app-simple/form");
//
//}
//
//
//aura_app aura_app_simple_form("app-simple/form", &app_simple_form_get_new_library);
//
//
