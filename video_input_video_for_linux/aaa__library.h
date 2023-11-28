#pragma once


#include "app-core/video_input/_library.h"
#include "acme/operating_system.h"
//#include "acme_windows_common/_acme_windows_common.h"
//#include "acme/operating_system/windows_common/prop_variant.h"
//#include <Strsafe.h>

//#include "acme/operating_system/windows_common/cotaskptr.h"

/* The aaa_primitive_new dv timing api was introduced in Linux 3.4
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

#include "device.h"


#include "format_reader.h"
#include "thread.h"
#include "callback.h"


#include "render.h"


#include "video_input.h"



