// Created by camilo on 2022-09-01 05:12 <3ThomasBorregaardSorensen!!
// Global enums from video.h by camilo on 2022-09-08 22:10 <3ThomasBorregaardSorensen!!
// Graphics Enums From graphics.h by camilo on 2022-09-08 22:35 <3ThomasBorregaardSorensen!!
#pragma once



namespace video
{


   enum enum_convert_type
   {
      e_convert_none,
      e_convert_nv12,
      e_convert_420,
      e_convert_420_a,
      e_convert_422,
      e_convert_422_a,
      e_convert_422_pack,
      e_convert_444,
      e_convert_444_a,
      e_convert_444_a_pack,
      e_convert_800,
      e_convert_rgb_limited,
      e_convert_bgr3,
   };


} // namespace video


namespace video_input
{


	enum enum_format
	{

		e_format_none,

	};



	enum enum_lock
	{
		e_lock_media_source,

		e_lock_raw_data,

		e_lock_open

	};


} // namespace video_input



#define MAX_AV_PLANES 8


enum enum_video_format {
   e_video_format_none,

   /* planar 420 format */
   e_video_format_i420, /* three-plane */
   e_video_format_nv12, /* two-plane, luma and packed chroma */

   /* packed 422 formats */
   e_video_format_yvyu,
   e_video_format_yuy2, /* yuyv */
   e_video_format_uyvy,

   /* packed uncompressed formats */
   e_video_format_rgba,
   e_video_format_bgra,
   e_video_format_bgrx,
   e_video_format_y800, /* grayscale */

   /* planar 4:4:4 */
   e_video_format_i444,

   /* more packed uncompressed formats */
   e_video_format_bgr3,

   /* planar 4:2:2 */
   e_video_format_i422,

   /* planar 4:2:0 with alpha */
   e_video_format_i40a,

   /* planar 4:2:2 with alpha */
   e_video_format_i42a,

   /* planar 4:4:4 with alpha */
   e_video_format_yuva,

   /* packed 4:4:4 with alpha */
   e_video_format_ayuv,
};

enum enum_video_colorspace {
   e_video_cs_default,
   e_video_cs_601,
   e_video_cs_709,
   e_video_cs_srgb,
};

enum enum_video_range_type {
   e_video_range_default,
   e_video_range_partial,
   e_video_range_full
};


enum enum_video_scale_type {
   e_video_scale_default,
   e_video_scale_point,
   e_video_scale_fast_bilinear,
   e_video_scale_bilinear,
   e_video_scale_bicubic,
};




// Graphics Enums From graphics.h by camilo on 2022-09-08 22:35 <3ThomasBorregaardSorensen!!
//
// Created by camilo on 07/02/2022.
//


enum gs_draw_mode {
   GS_POINTS,
   GS_LINES,
   GS_LINESTRIP,
   GS_TRIS,
   GS_TRISTRIP,
};

enum gs_color_format {
   GS_UNKNOWN,
   GS_A8,
   GS_R8,
   GS_RGBA,
   GS_BGRX,
   GS_BGRA,
   GS_R10G10B10A2,
   GS_RGBA16,
   GS_R16,
   GS_RGBA16F,
   GS_RGBA32F,
   GS_RG16F,
   GS_RG32F,
   GS_R16F,
   GS_R32F,
   GS_DXT1,
   GS_DXT3,
   GS_DXT5,
   GS_R8G8,
   GS_RGBA_UNORM,
   GS_BGRX_UNORM,
   GS_BGRA_UNORM,
   GS_RG16,
};

enum gs_zstencil_format {
   GS_ZS_NONE,
   GS_Z16,
   GS_Z24_S8,
   GS_Z32F,
   GS_Z32F_S8X24,
};

enum gs_index_type {
   GS_UNSIGNED_SHORT,
   GS_UNSIGNED_LONG,
};

enum gs_cull_mode {
   GS_BACK,
   GS_FRONT,
   GS_NEITHER,
};

enum gs_blend_type {
   GS_BLEND_ZERO,
   GS_BLEND_ONE,
   GS_BLEND_SRCCOLOR,
   GS_BLEND_INVSRCCOLOR,
   GS_BLEND_SRCALPHA,
   GS_BLEND_INVSRCALPHA,
   GS_BLEND_DSTCOLOR,
   GS_BLEND_INVDSTCOLOR,
   GS_BLEND_DSTALPHA,
   GS_BLEND_INVDSTALPHA,
   GS_BLEND_SRCALPHASAT,
};

enum gs_blend_op_type {
   GS_BLEND_OP_ADD,
   GS_BLEND_OP_SUBTRACT,
   GS_BLEND_OP_REVERSE_SUBTRACT,
   GS_BLEND_OP_MIN,
   GS_BLEND_OP_MAX
};

enum gs_depth_test {
   GS_NEVER,
   GS_LESS,
   GS_LEQUAL,
   GS_EQUAL,
   GS_GEQUAL,
   GS_GREATER,
   GS_NOTEQUAL,
   GS_ALWAYS,
};

enum gs_stencil_side {
   GS_STENCIL_FRONT = 1,
   GS_STENCIL_BACK,
   GS_STENCIL_BOTH,
};

enum gs_stencil_op_type {
   GS_KEEP,
   GS_ZERO,
   GS_REPLACE,
   GS_INCR,
   GS_DECR,
   GS_INVERT,
};

enum gs_cube_sides {
   GS_POSITIVE_X,
   GS_NEGATIVE_X,
   GS_POSITIVE_Y,
   GS_NEGATIVE_Y,
   GS_POSITIVE_Z,
   GS_NEGATIVE_Z,
};

enum gs_sample_filter {
   GS_FILTER_POINT,
   GS_FILTER_LINEAR,
   GS_FILTER_ANISOTROPIC,
   GS_FILTER_MIN_MAG_POINT_MIP_LINEAR,
   GS_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
   GS_FILTER_MIN_POINT_MAG_MIP_LINEAR,
   GS_FILTER_MIN_LINEAR_MAG_MIP_POINT,
   GS_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
   GS_FILTER_MIN_MAG_LINEAR_MIP_POINT,
};

enum gs_address_mode {
   GS_ADDRESS_CLAMP,
   GS_ADDRESS_WRAP,
   GS_ADDRESS_MIRROR,
   GS_ADDRESS_BORDER,
   GS_ADDRESS_MIRRORONCE,
};

enum gs_texture_type {
   GS_TEXTURE_2D,
   GS_TEXTURE_3D,
   GS_TEXTURE_CUBE,
};



/// End Graphics Enums From graphics.h by camilo on 2022-09-08 22:35 <3ThomasBorregaardSorensen!!