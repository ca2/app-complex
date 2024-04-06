#pragma once



#include "app-complex/video_input/_.h"
//#include "acme_windows_common/_.h"



#if defined(_video_input_media_foundation_project)
#define CLASS_DECL_VIDEO_INPUT_AVFOUNDATION  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_VIDEO_INPUT_AVFOUNDATION  CLASS_DECL_IMPORT
#endif
