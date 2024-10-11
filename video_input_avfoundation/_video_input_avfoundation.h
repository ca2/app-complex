#pragma once


#include "app-complex/video_input/_.h"
#include "acme/_operating_system.h"
//#include "acme_windows_common/_acme_windows_common.h"
//#include "acme/operating_system/windows_common/prop_variant.h"
//#include <Strsafe.h>

//#include "acme/operating_system/windows_common/cotaskptr.h"

/* The __new dv timing api was introduced in Linux 3.4
 * Currently we simply disable dv timings when this is not defined */
extern "C"
{
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"

}

static inline enum AVPixelFormat
video_format_to_avpixelformat(enum_video_format eformat)
{
   switch (eformat) {
      case e_video_format_i444:         return AV_PIX_FMT_YUV444P;
      case e_video_format_i420:         return AV_PIX_FMT_YUV420P;
      case e_video_format_nv12:         return AV_PIX_FMT_NV12;
      case e_video_format_yuy2:         return AV_PIX_FMT_YUYV422;
      case e_video_format_uyvy:         return AV_PIX_FMT_UYVY422;
      case e_video_format_rgba:         return AV_PIX_FMT_RGBA;
      case e_video_format_bgra:         return AV_PIX_FMT_BGRA;
      case e_video_format_bgrx:         return AV_PIX_FMT_BGRA;
      case e_video_format_y800:         return AV_PIX_FMT_GRAY8;
      case e_video_format_bgr3:         return AV_PIX_FMT_BGR24;
      case e_video_format_i422:         return AV_PIX_FMT_YUV422P;
      case e_video_format_i40a:         return AV_PIX_FMT_YUVA420P;
      case e_video_format_i42a:         return AV_PIX_FMT_YUVA422P;
      case e_video_format_yuva:         return AV_PIX_FMT_YUVA444P;
      case e_video_format_none:
      case e_video_format_yvyu:
      case e_video_format_ayuv:         /* not supported by FFmpeg */
         return AV_PIX_FMT_NONE;
   }

   return AV_PIX_FMT_NONE;
}

static inline enum_video_format
avpixelformat_to_video_format(enum AVPixelFormat format)
{
   switch (format) {
      case AV_PIX_FMT_YUV444P:         return e_video_format_i444;
      case AV_PIX_FMT_YUV420P:         return e_video_format_i420;
      case AV_PIX_FMT_NV12:            return e_video_format_nv12;
      case AV_PIX_FMT_YUYV422:         return e_video_format_yuy2;
      case AV_PIX_FMT_UYVY422:         return e_video_format_uyvy;
      case AV_PIX_FMT_RGBA:            return e_video_format_rgba;
      case AV_PIX_FMT_BGRA:            return e_video_format_bgra;
      case AV_PIX_FMT_GRAY8:           return e_video_format_y800;
      case AV_PIX_FMT_BGR24:           return e_video_format_bgr3;
      case AV_PIX_FMT_YUV422P:         return e_video_format_i422;
      case AV_PIX_FMT_YUVA420P:        return e_video_format_i40a;
      case AV_PIX_FMT_YUVA422P:        return e_video_format_i42a;
      case AV_PIX_FMT_YUVA444P:        return e_video_format_yuva;
      case AV_PIX_FMT_NONE:
         default:
                                       return e_video_format_none;
   }
}

#if defined(ANDROID) || defined(MACOS)
#define FFMPEG_DST_PIXEL_FORMAT AV_PIX_FMT_BGR32
#else
#define FFMPEG_DST_PIXEL_FORMAT AV_PIX_FMT_RGB32
#endif
//
//static inline enum audio_format
//convert_ffmpeg_sample_format(enum AVSampleFormat format)
//{
//   switch ((uint32_t)format) {
//      case AV_SAMPLE_FMT_U8:
//         return AUDIO_FORMAT_U8BIT;
//      case AV_SAMPLE_FMT_S16:
//         return AUDIO_FORMAT_16BIT;
//      case AV_SAMPLE_FMT_S32:
//         return AUDIO_FORMAT_32BIT;
//      case AV_SAMPLE_FMT_FLT:
//         return AUDIO_FORMAT_FLOAT;
//      case AV_SAMPLE_FMT_U8P:
//         return AUDIO_FORMAT_U8BIT_PLANAR;
//      case AV_SAMPLE_FMT_S16P:
//         return AUDIO_FORMAT_16BIT_PLANAR;
//      case AV_SAMPLE_FMT_S32P:
//         return AUDIO_FORMAT_32BIT_PLANAR;
//      case AV_SAMPLE_FMT_FLTP:
//         return AUDIO_FORMAT_FLOAT_PLANAR;
//   }
//
//   /* shouldn't get here */
//   return AUDIO_FORMAT_16BIT;
//}
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

//#include "helpers.h"
//#include "mjpeg_decoder.h"
//#define HAVE_UDEV 1


//#undef Context
//#include <Mfapi.h>
//#include <mfapi.h>
//#include <mfidl.h>
//#include <mfobjects.h>
//#include <Shlwapi.h>
//#include <mfapi.h>
//#include <mfplay.h>
//#include <mfapi.h>
//#include <string.h>
//#include <Strmif.h>
//#include <Mfobjects.h>
//#include <Mfidl.h>
//#undef Context


const char * avcapture_device_unique_id(CFTypeRef typeref);
const char * avcapture_device_localized_name(CFTypeRef typeref);


#include "device.h"


//#include "format_reader.h"
#include "thread.h"
//#include "callback.h"


#include "render.h"


#include "video_input.h"



