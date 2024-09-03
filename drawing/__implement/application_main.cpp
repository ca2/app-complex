#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_complex_drawing::application g_app_complex_drawing;

//int __implement()
//{
//
//   auto papp = new app_complex_drawing::application();
//
//   int iExitCode = papp->__implement();
//
//   return iExitCode;
//
//}
//
//
//


::i32 application_main(::platform::platform * pplatform)
{

   auto papplication = ::place(new app_complex_drawing::application());

   int iExitCode = papplication->application_main(pplatform);

   return iExitCode;

}



