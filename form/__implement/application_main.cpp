#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_complex_form::application g_app_complex_form;


//int __implement()
//{
//
//   auto papp = memory_new app_complex_form::application();
//
//   int iExitCode = papp->__implement();
//
//   return iExitCode;
//
//}





int application_main()
{

   auto papplication = __new(app_complex_form::application());

   int iExitCode = papplication->application_main();

   return iExitCode;

}






