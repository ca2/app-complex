#pragma once



#include "app-core/video_input/_.h"
//#include "acme_windows_common/_.h"



#ifdef _VIDEO_INPUT_MEDIA_FOUNDATION_LIBRARY
#define CLASS_DECL_VIDEO_INPUT_AVFOUNDATION  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_VIDEO_INPUT_AVFOUNDATION  CLASS_DECL_IMPORT
#endif
