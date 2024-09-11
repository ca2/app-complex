#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_complex_form::application g_app_complex_form;


//int __implement()
//{
//
//   auto papp = new app_complex_form::application();
//
//   int iExitCode = papp->__implement();
//
//   return iExitCode;
//
//}





::i32 application_main(::platform::platform * pplatform)
{

   auto papplication = new app_complex_form::application();

   int iExitCode = papplication->application_main(pplatform);

   return iExitCode;

}






