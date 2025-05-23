#include "framework.h"
#include "aura/application.h"


namespace notify_drawing
{


   __IMPLEMENT_APPLICATION_RELEASE_TIME();
IMPLEMENT_APPLICATION_FACTORY();


   application::application()
   {

      m_ptemplateNotifyDrawingMain = NULL;

      m_strAppId = "app-simple/notify_drawing";
      m_strAppName = "app-simple/notify_drawing";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

   }


   application::~application()
   {
   }


   void application::init_instance()
   {

      set_local_data();

      ::aura::session * pcoression = &Session;

      puser->will_use_impact_hint(FONTSEL_IMPACT);

      add_factory_item <::notify_drawing::main_frame >();
      add_factory_item <::notify_drawing::impact >();

      if (!::simple_drawing::application::init_instance())
      {

         return false;

      }

      add_matter_locator("app-simple/drawing");

      auto pdoctemplate = __initialize_new ::user::single_document_template(
                               "main",
                               ::type < simple_drawing::document >(),
                               ::type < main_frame >(),
                               ::type < simple_drawing::tab_impact >()));
      m_ptemplateNotifyDrawingMain = pdoctemplate;
      add_document_template(pdoctemplate);


//      pdoctemplate = __initialize_new ::user::single_document_template(
//                          this,
//                          "main",
//                          ::type < simple_drawing::document >(),
//                          ::type < simple_drawing::frame >(),
//                          ::type < simple_drawing::main_impact >()));
//
//      m_ptemplateNotifyDrawingImpact = pdoctemplate;
//
//      add_document_template(pdoctemplate);

      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::request * prequest)
   {

#if 0
      {

         auto pthread = fork([this]()
            {

               informationf("test");

            });

      }
#endif

#if 0

#ifdef _DEBUG

      informationf("_DEBUG build? (basis)");

      ASSERT(false);

#else

      informationf("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      m_bMultiverseChat = !is_true("no_hello_edit");

      if (m_ptemplateNotifyDrawingMain->get_document_count() == 0)
      {

         m_ptemplateNotifyDrawingMain->do_request(pcreate);

      }

      if (is_true("wfi_maximize"))
      {

         pcreate->payload("document").cast < simple_drawing::document >()->get_typed_impact < ::user::tab_impact >()->top_level_frame()->prodevian_prepare_window_maximize();

      }

      informationf("\nfinished notify_drawing::on_request");

   }


   string application::preferred_experience()
   {

      //return "aura";

      return ::aura::application::preferred_experience();

   }


   long long application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   long long application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


   ::pointer<simple_drawing::impact>application::create_simple_drawing_impact(::user::impact* pimpactParent, ::user::impact_data* pimpactdata)
   {

      return pimpactParent->create_impact < impact >(pimpactdata);

   }

   
   __namespace_application_factory("app-simple/notify_drawing");


} // namespace notify_drawing





//extern "C"
//::acme::library * app_simple_notify_drawing_get_new_library()
//{
//
//   return ___new ::apex::single_application_library < ::notify_drawing::application >("app-simple/notify_drawing");
//
//}
//
//
//aura_app aura_app_simple_notify_drawing("app-simple/notify_drawing", &app_simple_notify_drawing_get_new_library);
//

