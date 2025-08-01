// From video.h by camilo on 2022-09-08 22:09 <3ThomasBorregaardSorensen!!
#pragma once


static inline bool format_is_yuv(enum_video_format eformat)
{
   switch (eformat) {
      case e_video_format_i420:
      case e_video_format_nv12:
      case e_video_format_i422:
      case e_video_format_yvyu:
      case e_video_format_yuy2:
      case e_video_format_uyvy:
      case e_video_format_i444:
      case e_video_format_i40a:
      case e_video_format_i42a:
      case e_video_format_yuva:
      case e_video_format_ayuv:
         return true;
      case e_video_format_none:
      case e_video_format_rgba:
      case e_video_format_bgra:
      case e_video_format_bgrx:
      case e_video_format_y800:
      case e_video_format_bgr3:
         return false;
   }

   return false;
}

static inline const_char_pointer get_e_video_format_name(enum_video_format eformat)
{
   switch (eformat) {
      case e_video_format_i420:
         return "i420";
      case e_video_format_nv12:
         return "nv12";
      case e_video_format_i422:
         return "i422";
      case e_video_format_yvyu:
         return "yvyu";
      case e_video_format_yuy2:
         return "yuy2";
      case e_video_format_uyvy:
         return "uyvy";
      case e_video_format_rgba:
         return "rgba";
      case e_video_format_bgra:
         return "bgra";
      case e_video_format_bgrx:
         return "bgrx";
      case e_video_format_i444:
         return "i444";
      case e_video_format_y800:
         return "y800";
      case e_video_format_bgr3:
         return "bgr3";
      case e_video_format_i40a:
         return "i40a";
      case e_video_format_i42a:
         return "i42a";
      case e_video_format_yuva:
         return "yuva";
      case e_video_format_ayuv:
         return "ayuv";
      case e_video_format_none:;
   }

   return "none";
}

static inline const_char_pointer get_video_colorspace_name(enum_video_colorspace ecolorspace)
{
   switch (ecolorspace) {
      case e_video_cs_default:
      case e_video_cs_709:
         return "709";
      case e_video_cs_srgb:
         return "srgb";
      case e_video_cs_601:;
   }

   return "601";
}

static inline enum_video_range_type resolve_video_range_type(enum_video_format eformat, enum_video_range_type erangetype)
{
   if (erangetype == e_video_range_default) {
      erangetype = format_is_yuv(eformat) ? e_video_range_partial
                                    : e_video_range_full;
   }

   return erangetype;
}

static inline const_char_pointer get_video_range_name(enum_video_format eformat,
                                               enum_video_range_type erangetype)
{
   erangetype = resolve_video_range_type(eformat, erangetype);
   return erangetype == e_video_range_full ? "full" : "partial";
}





static inline enum gs_color_format
convert_video_format(enum_video_format eformat)
{
   switch (eformat) {
      case e_video_format_rgba:
         return GS_RGBA;
      case e_video_format_bgra:
      case e_video_format_i40a:
      case e_video_format_i42a:
      case e_video_format_yuva:
      case e_video_format_ayuv:
         return GS_BGRA;
      default:
         return GS_BGRX;
   }
}


namespace video
{


   inline enum_convert_type get_convert_type(enum_video_format eformat, bool full_range)
   {
      switch (eformat)
      {
         case e_video_format_i420:         return e_convert_420;
         case e_video_format_nv12:         return e_convert_nv12;
         case e_video_format_i444:         return e_convert_444;
         case e_video_format_i422:         return e_convert_422;
         case e_video_format_yvyu:
         case e_video_format_yuy2:
         case e_video_format_uyvy:         return e_convert_422_pack;
         case e_video_format_y800:         return e_convert_800;
         case e_video_format_none:
         case e_video_format_rgba:
         case e_video_format_bgra:
         case e_video_format_bgrx:         return full_range ? e_convert_none : e_convert_rgb_limited;
         case e_video_format_bgr3:         return e_convert_bgr3;
         case e_video_format_i40a:         return e_convert_420_a;
         case e_video_format_i42a:         return e_convert_422_a;
         case e_video_format_yuva:         return e_convert_444_a;
         case e_video_format_ayuv:         return e_convert_444_a_pack;
      }

      return e_convert_none;
   }


} // namespace video



