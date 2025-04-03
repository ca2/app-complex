#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_complex_drawing::application g_app_complex_drawing;

//int __implement()
//{
//
//   auto papp = ___new app_complex_drawing::application();
//
//   int iExitCode = papp->__implement();
//
//   return iExitCode;
//
//}
//
//
//


void application_main(::platform::system * psystem)
{

   app_complex_drawing::application application;

   application.application_main();

}



