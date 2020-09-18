#include "framework.h"


namespace helloworld
{


   application::application()
   {

      m_strAppName                     = "app-simple/helloworld";
      m_strBaseSupportId               = "app-simple/helloworld";
      m_bLicense                       = false;
      m_pdocumenttemplate    = NULL;

   }


   application::~application()
   {

   }


   bool application::initialize_application()
   {

      create_factory <::helloworld::document >();
      create_factory <::helloworld::frame >();
      create_factory <::helloworld::view >();

      if(!::aura::application::initialize_application())
         return false;

      m_dataid += ".local://";

	   ::user::single_document_template* pdocumenttemplate;

      pdocumenttemplate = new ::user::single_document_template(
         this,
		   "main",
         __type(::helloworld::document),
		   __type(::helloworld::frame),
		   __type(::helloworld::view));

      add_document_template(pdocumenttemplate);

      m_pdocumenttemplate = pdocumenttemplate;

      return true;

   }


   int32_t application::exit_application()
   {

      return ::aura::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

      m_pdocumenttemplate->request_create(pcreate);

   }


} // namespace helloworld




extern "C"
::apex::library * app_simple_helloworld_get_new_library(::layered * pobjectContext)
{

   return new ::apex::single_application_library < ::helloworld::application >(papp, "app-simple/helloworld");

}


