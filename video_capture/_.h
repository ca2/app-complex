#pragma once


#include "core/_.h"
#include "core/user/simple/_.h"


#ifdef _APP_COMPLEX_VIDEO_CAPTURE_LIBRARY
   #define CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE  CLASS_DECL_IMPORT
#endif



namespace video_capture
{

   class application;
   class top_view;
   class main_impact;
   class document;
   class impact;

} // namespace video_capture

