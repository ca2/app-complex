#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_complex_form::application g_app_complex_form;


//int __implement()
//{
//
//   auto papp = __new app_complex_form::application();
//
//   int iExitCode = papp->__implement();
//
//   return iExitCode;
//
//}





void application_main()
{

   auto papplication = __new app_complex_form::application();

   papplication->application_main();

}






