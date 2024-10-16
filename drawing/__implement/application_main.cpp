#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_complex_drawing::application g_app_complex_drawing;

//int __implement()
//{
//
//   auto papp = __new app_complex_drawing::application();
//
//   int iExitCode = papp->__implement();
//
//   return iExitCode;
//
//}
//
//
//


void application_main()
{

   auto papplication = __new app_complex_drawing::application();

   papplication->application_main(pplatform);

}



