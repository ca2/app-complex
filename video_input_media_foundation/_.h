#pragma once



#include "app-complex/video_input/_.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme_windows_common/_.h"
//#include "windowing_win32/_.h"
#include "acme_windows_common/_.h"
#include "acme/operating_system/windows_common/com/comptr.h"
#include "acme/operating_system/windows_common/com/comptr_array.h"
#include "acme/operating_system/windows_common/com/prop_variant.h"
//#include "windowing_win32/_.h"

#include "acme/_operating_system.h"

#include <Strsafe.h>

//#include "acme/operating_system/windows_common/cotaskptr.h"


#undef Context
#include <Mfapi.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfobjects.h>
#include <Shlwapi.h>
#include <mfapi.h>
#include <mfplay.h>
#include <mfapi.h>
#include <string.h>
#include <Strmif.h>
#include <Mfobjects.h>
#include <Mfidl.h>
#undef Context



#ifdef _video_input_media_foundation_project
#define CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION  CLASS_DECL_IMPORT
#endif


namespace video_input_media_foundation
{


   class device;
   class media_format;
   class video_input;
   class render;



} // namespace video_input_media_foundation