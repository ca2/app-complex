#pragma once


#include "core/_.h"
#include "core/user/simple/_.h"
#include "app-core/video_input/_.h"


#ifdef _APP_COMPLEX_VIDEO_CAPTURE_LIBRARY
   #define CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE  CLASS_DECL_IMPORT
#endif



namespace app_complex_video_capture
{

   class application;
   class top_impact;
   class main_impact;
   class document;
   class impact;

   class edit_impact;
   class toggle_impact;


} // namespace app_complex_video_capture

