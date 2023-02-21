#pragma once



#include "app-complex/video_input/_.h"
#include "helpers.h"


#if defined(_video_input_media_foundation_project)
#define CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION  CLASS_DECL_IMPORT
#endif


#if !defined(VIDIOC_ENUM_DV_TIMINGS) || !defined(V4L2_IN_CAP_DV_TIMINGS)
#define V4L2_IN_CAP_DV_TIMINGS 0
#endif

#define V4L2_DATA(voidptr) struct v4l2_data *data = voidptr;

#define timeval2ns(tv) \
	(((::u64)tv.tv_sec * 1000000000) + ((::u64)tv.tv_usec * 1000))

#define V4L2_FOURCC_STR(code)                                         \
	(char[5])                                                     \
	{                                                             \
		code & 0xFF, (code >> 8) & 0xFF, (code >> 16) & 0xFF, \
			(code >> 24) & 0xFF, 0                        \
	}

#include "helpers.h"
#include "mjpeg_decoder.h"
#define HAVE_UDEV 1



namespace video_input_video_for_linux
{


   class device;
   class mjpeg_decoder;


} // namespace video_input_video_for_linux


#if defined(ANDROID) || defined(MACOS)
#define FFMPEG_DST_PIXEL_FORMAT AV_PIX_FMT_BGR32
#else
#define FFMPEG_DST_PIXEL_FORMAT AV_PIX_FMT_RGB32
#endif

