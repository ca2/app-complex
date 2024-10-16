#include "framework.h"
#include "application.h"
#include "acme/application.h"


//app_complex_video_capture::application g_app_complex_video_capture;


//int __implement()
//{
//
//   auto papp = __new app_complex_video_capture::application();
//
//   int iExitCode = papp->__implement();
//
//   return iExitCode;
//
//}





void application_main()
{

   auto papplication = __new app_complex_video_capture::application();

   papplication->application_main(pplatform);

}
