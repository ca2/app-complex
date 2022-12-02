#include "framework.h"
#include "application.h"
#include "document.h"
#include "frame.h"
#include "main_frame.h"
#include "impact.h"
#include "main_impact.h"
#include "pane_impact.h"
#include "form_001.h"
#include "form_002.h"
#include "acme/platform/request.h"
#include "aura/user/user/button.h"
#include "base/user/user/single_document_template.h"


////#define memory_new ACME_NEW

//IMPLEMENT_APPLICATION(app_complex_form);


namespace app_complex_form
{


   application::application()
   {

      m_ptemplateBeatMapperMain  = NULL;
      m_ptemplateBeatMapperImpact  = NULL;

      m_strAppId                 = "app-complex/form";
      m_strBaseSupportId         = "app-complex/form";
      m_strAppName               = "Complex Form";
      m_bLicense                 = false;

      m_bMultiverseChat          = true;

//auto test = memory_new int;

   }


   application::~application()
   {
   }


#ifdef _DEBUG


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void application::init_instance()
   {

      set_local_data();

      //puser->will_use_impact_hint(FONTSEL_IMPACT);

      factory()->add_factory_item <::app_complex_form::document >();
      factory()->add_factory_item <::app_complex_form::frame >();
      factory()->add_factory_item <::app_complex_form::main_frame >();
      factory()->add_factory_item <::user::button_impact >();
      factory()->add_factory_item <::app_complex_form::impact >();
      factory()->add_factory_item <::app_complex_form::main_impact >();
      factory()->add_factory_item <::app_complex_form::pane_impact >();
      factory()->add_factory_item <::app_complex_form::form_001 >();
      factory()->add_factory_item <::app_complex_form::form_002 >();

      ::base::application::init_instance();

      //if (!::base::application::init_instance())
      //{

      //   return false;

      //}

      auto pdoctemplate = __new(::user::single_document_template(
                               "main",
                               __type(document),
                               __type(main_frame),
                               __type(pane_impact)));
      m_ptemplateBeatMapperMain = pdoctemplate;
      add_document_template(pdoctemplate);


      pdoctemplate = __new(::user::single_document_template(
                          "main",
                          __type(document),
                          __type(frame),
                          __type(main_impact)));
      m_ptemplateBeatMapperImpact = pdoctemplate;
      add_document_template(pdoctemplate);

      //return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::request * prequest)
   {

//#if 1
      if (pcreate->has_property("m"))
      {

         //output_error_message("m=1");

         _001TryCloseApplication();

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

      if (pcreate->m_payloadFile.has_char())
      {

         m_ptemplateBeatMapperImpact->do_request(pcreate);

      }

      if (is_true("wfi_maximize"))
      {

         pcreate->payload("document").cast < document >()->get_typed_impact < ::user::tab_impact >()->top_level_frame()->design_window_maximize();

      }

      output_debug_string("\nfinished simple_form::on_request");

   }


   string application::preferred_experience()
   {
      
      return "tranquillum";
      
      //return "core";

//      return "tranquillum";

   }


} // namespace app_complex_form



