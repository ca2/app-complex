#pragma once



#include "app-complex/video_input/_.h"
#include "acme_windows_common/_.h"
#include "acme_windows_common/_.h"
#include "acme_windows_common/comptr.h"
#include "acme_windows_common/comptr_array.h"
#include "acme_windows_common/prop_variant.h"

#include "acme/_operating_system.h"

#include <Strsafe.h>

//#include "acme/operating_system/windows_common/cotaskptr.h"





#ifdef _video_input_media_capture_project
#define CLASS_DECL_VIDEO_INPUT_MEDIA_CAPTURE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_VIDEO_INPUT_MEDIA_CAPTURE  CLASS_DECL_IMPORT
#endif


namespace video_input_media_capture
{


   class device;
   class media_format;
   class video_input;
   class render;



} // namespace video_input_media_capture