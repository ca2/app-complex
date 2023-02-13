//
// From _library.h by camilo on 2022-09-10 00:03 <3ThomasBorregaardSørensen!! ThomasLikesNumber5 ThomasMonth?!
//
#pragma once



extern "C"
{


   #include <libavutil/avconfig.h>


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



