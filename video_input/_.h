#pragma once


#include "aura/_.h"


#ifdef _video_input_project
#define CLASS_DECL_VIDEO_INPUT  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_VIDEO_INPUT  CLASS_DECL_IMPORT
#endif


namespace video
{


   class asynchronous_cache;
   class frame;


} // namespace video


namespace video_input
{


	class media_foundation;
	class render;
	class video_input;
	class media_format;
	class device;

	CLASS_DECL_VIDEO_INPUT void processPixels(color32_t * src, color32_t * dst, ::u32 width, ::u32 height, ::u32 bpp, bool bRGB, bool bFlip);


} // namespace video_input


#include "_constant.h"


//#include "_struct.h"
//
//
//#include "_function.h"



