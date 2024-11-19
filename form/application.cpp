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
#include "acme/handler/request.h"
#include "aura/user/user/button.h"
#include "base/user/user/single_document_template.h"


//

__IMPLEMENT_APPLICATION_RELEASE_TIME(app_complex_form);


namespace app_complex_form
{


   // __IMPLEMENT_APPLICATION_RELEASE_TIME1(app_complex_form));


   application::application()
   {

      //m_ptemplateBeatMapperMain  = NULL;
      //m_ptemplateBeatMapperImpact  = NULL;

      m_strAppId                 = "app-complex/form";
      m_strBaseSupportId         = "app-complex/form";
      m_strAppName               = "Complex Form";
      m_bLicense                 = false;

      //m_bMultiverseChat          = true;

//auto test = ___new int();

   }


   application::~application()
   {
   }


#ifdef _DEBUG


   huge_integer application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   huge_integer application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif


   void application::init_instance()
   {

      //set_local_data();

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

      ::app_simple_form::application::init_instance();

      //if (!::base::application::init_instance())
      //{

      //   return false;

      //}

      
      add_impact_system("main", __initialize_new ::user::single_document_template(
                               "main",
                               ::type < document >(),
                               ::type < main_frame >(),
                               ::type < pane_impact >()));
      //m_ptemplateBeatMapperMain = pdoctemplate;
      //add_document_template(m_ptemplateAppSimpleFormMain);


      add_impact_system(
         "impact", __initialize_new ::user::single_document_template(
                          "main",
                          ::type < document >(),
                          ::type < frame >(),
                          ::type < main_impact >()));
      // m_ptemplateBeatMapperImpact = pdoctemplate;
      //add_document_template(m_ptemplateAppSimpleFormImpact);

      //return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::request * prequest)
   {

//#if 1
      if (prequest->has_property("m"))
      {

         //output_error_message("m=1");

         _001TryCloseApplication();

         return;

      }
//#endif
#if 0

#ifdef _DEBUG

      informationf("_DEBUG build? (basis)");

      ASSERT(false);

#else

      informationf("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      app_simple_form::application::on_request(prequest);
      ////m_bMultiverseChat = !is_true("no_hello_edit");

      //if (m_ptemplateBeatMapperMain->get_document_count() == 0)
      //{

      //   m_ptemplateBeatMapperMain->request(prequest);

      //}

      //if (prequest->m_payloadFile.has_character())
      //{

      //   m_ptemplateBeatMapperImpact->request(prequest);

      //}

      //if (is_true("wfi_maximize"))
      //{

      //   prequest->payload("document").cast < document >()->get_typed_impact < ::user::tab_impact >()->top_level_frame()->design_window_maximize();

      //}

      //informationf("\nfinished simple_form::on_request");

   }


   string application::preferred_experience()
   {
      
      return "tranquillum";
      
      //return "core";

//      return "tranquillum";

   }


} // namespace app_complex_form



