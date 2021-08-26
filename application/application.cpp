#include "framework.h"
#include "aura/application.h"
#include "aura/update.h"



namespace simple_application
{


   application::application()
   {

      m_ppaneview = nullptr;

      m_strAppId = "app-simple/application";

      m_strAppName = "app-simple/application";

      m_strBaseSupportId = "app_simple_application";

      m_bLicense = false;

   }


   application::~application()
   {

   }


   ::e_status application::init_instance()
   {

      set_local_data();

      create_factory <::simple_application::document >();
      create_factory <::simple_application::main_frame >();
      create_factory <::simple_application::impact >();

      if (!::aura::application::init_instance())
      {

         return false;

      }

      auto pdoctemplate = __new(::user::single_document_template(
                               "main",
                               __type(document),
                               __type(main_frame),
                               __type(impact)));

      __compose(m_ptemplateSimpleDrawingMain, pdoctemplate);

      add_document_template(pdoctemplate);

      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

      if (m_ptemplateSimpleDrawingMain->get_document_count() == 0)
      {

         if(pcreate->m_bMakeVisible)
         {

            INFO("pcreate->m_bMakeVisible");

         }
         else
         {

            INFO("NOT pcreate->m_bMakeVisible");

         }

         m_ptemplateSimpleDrawingMain->do_request(pcreate);

      }

      if (is_true("wfi_maximize"))
      {

         pcreate->m_pcommandline->m_varQuery["document"].cast < document >()->get_typed_view < ::user::tab_view >()->top_level_frame()->prodevian_prepare_window_maximize();

      }

      output_debug_string("\nfinished simple_application::on_request");

   }


   string application::preferred_experience()
   {

      return ::aura::application::preferred_experience();

   }


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   __namespace_application_factory("app-simple/application");


} // namespace simple_application



