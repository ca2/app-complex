#include "framework.h"
#include "application.h"
#include "__implement.h"


int __implement()
{

   auto papp = new app_complex_video_capture::application();

   int iExitCode = papp->__implement();

   return iExitCode;

}


