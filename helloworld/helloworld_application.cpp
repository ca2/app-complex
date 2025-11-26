#include "framework.h"


namespace helloworld
{


   __IMPLEMENT_APPLICATION_RELEASE_TIME();


   application::application()
   {

      m_strAppName                     = "app-simple/helloworld";
      m_strBaseSupportId               = "app-simple/helloworld";
      m_bLicense                       = false;
      m_pimpactsystem    = NULL;

   }


   application::~application()
   {

   }


   bool application::initialize_application()
   {

      add_factory_item <::helloworld::document >();
      add_factory_item <::helloworld::frame >();
      add_factory_item <::helloworld::impact >();

      if(!::aura::application::initialize_application())
         return false;

      m_dataid += ".local://";

	   ::user::single_document_template* pdocumenttemplate;

      pdocumenttemplate = ___new ::user::single_document_template(
         this,
		   "main",
         ::as_type < ::helloworld::document >(),
		   ::as_type < ::helloworld::frame >(),
		   ::as_type < ::helloworld::impact >());

      add_document_template(pdocumenttemplate);

      m_pimpactsystem = pdocumenttemplate;

      return true;

   }


   int32_t application::exit_application()
   {

      return ::aura::application::exit_application();

   }


   void application::on_request(::request * prequest)
   {

      m_pimpactsystem->request_create(pcreate);

   }


} // namespace helloworld




extern "C"
::acme::library * app_simple_helloworld_get_new_library(::particle * pparticle)
{

   return ___new ::apex::single_application_library < ::helloworld::application >(papp, "app-simple/helloworld");

}


