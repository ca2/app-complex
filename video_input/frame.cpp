//
// Created by camilo on 07/02/2022.
//

/******************************************************************************
    Copyright (C) 2013-2014 by Hugh Bailey <obs.jim@gmail.com>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#include "framework.h"
#include "frame.h"


//#include "video_frame.h"
//#include <inttypes.h>
//#include <math.h>

//#include "media-io/format-conversion.h"
//#include "media-io/video-frame.h"
//#include "media-io/audio-io.h"
//#include "util/threading.h"
//#include "util/platform.h"
//#include "util/util_uint64.h"
//#include "callback/callm_data.h"
//#include "graphics/matrix3.h"
//#include "graphics/vec3.h"
//
//#include "obs.h"
//#include "obs-internal.h"
//
//#define get_weak(source) ((obs_weak_source_t *)source->context.control)

namespace video
{


frame::frame(enum_video_format eformat, uint32_t width, uint32_t height)
{
   //frame vid_frame;

   //if (!obs_ptr_valid(frame, "video_frame_init"))
   // return;

   video_frame_init(eformat, width, height);

   m_eformat = eformat;
   m_width = width;
   m_height = height;

//   for (size_t i = 0; i < MAX_AV_PLANES; i++)
//   {
//      m_data[i] = vid_frame.m_data[i];
//      m_linesize[i] = vid_frame.m_linesize[i];
//   }


}


frame::~frame()
{

   //static inline void video_frame_destroy(struct video_frame *frame)
   //{
      ///if (frame) {
   ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->free(m_data[0]);
         //bfree(frame);
      ///}
   //}

}

#define ALIGN_SIZE(size, align) size = (((size) + (align - 1)) & (~(align - 1)))

/* messy code alarm */
   void frame::video_frame_init(enum_video_format eformat, uint32_t width, uint32_t height)
   {
      size_t size;
      size_t offsets[MAX_AV_PLANES];
      //int alignment = base_get_alignment();

      int alignment = 16;

      auto pframe = this;


      memory_set(pframe, 0, sizeof(frame));
      memory_set(offsets, 0, sizeof(offsets));

      switch (eformat) {
         case e_video_format_none:
            return;

         case e_video_format_i420: {
            size = width * height;
            ALIGN_SIZE(size, alignment);
            offsets[0] = size;
            const uint32_t half_width = (width + 1) / 2;
            const uint32_t half_height = (height + 1) / 2;
            const uint32_t quarter_area = half_width * half_height;
            size += quarter_area;
            ALIGN_SIZE(size, alignment);
            offsets[1] = size;
            size += quarter_area;
            ALIGN_SIZE(size, alignment);
            m_data[0] =(::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_data[1] = (uint8_t *)m_data[0] + offsets[0];
            m_data[2] = (uint8_t *)m_data[0] + offsets[1];
            m_linesize[0] = width;
            m_linesize[1] = half_width;
            m_linesize[2] = half_width;
            break;
         }

         case e_video_format_nv12: {
            size = width * height;
            ALIGN_SIZE(size, alignment);
            offsets[0] = size;
            const uint32_t cbcr_width = (width + 1) & (UINT32_MAX - 1);
            size += cbcr_width * ((height + 1) / 2);
            ALIGN_SIZE(size, alignment);
            m_data[0] = (::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_data[1] = (uint8_t *)m_data[0] + offsets[0];
            m_linesize[0] = width;
            m_linesize[1] = cbcr_width;
            break;
         }

         case e_video_format_y800:
            size = width * height;
            ALIGN_SIZE(size, alignment);
            m_data[0] = (::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_linesize[0] = width;
            break;

         case e_video_format_yvyu:
         case e_video_format_yuy2:
         case e_video_format_uyvy: {
            const uint32_t double_width =
               ((width + 1) & (UINT32_MAX - 1)) * 2;
            size = double_width * height;
            ALIGN_SIZE(size, alignment);
            m_data[0] =(::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_linesize[0] = double_width;
            break;
         }

         case e_video_format_rgba:
         case e_video_format_bgra:
         case e_video_format_bgrx:
         case e_video_format_ayuv:
            size = width * height * 4;
            ALIGN_SIZE(size, alignment);
            m_data[0] =(::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_linesize[0] = width * 4;
            break;

         case e_video_format_i444:
            size = width * height;
            ALIGN_SIZE(size, alignment);
            m_data[0] =(::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size * 3, nullptr, alignment);
            m_data[1] = (uint8_t *)m_data[0] + size;
            m_data[2] = (uint8_t *)m_data[1] + size;
            m_linesize[0] = width;
            m_linesize[1] = width;
            m_linesize[2] = width;
            break;

         case e_video_format_bgr3:
            size = width * height * 3;
            ALIGN_SIZE(size, alignment);
            m_data[0] =(::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_linesize[0] = width * 3;
            break;

         case e_video_format_i422: {
            size = width * height;
            ALIGN_SIZE(size, alignment);
            offsets[0] = size;
            const uint32_t half_width = (width + 1) / 2;
            const uint32_t half_area = half_width * height;
            size += half_area;
            ALIGN_SIZE(size, alignment);
            offsets[1] = size;
            size += half_area;
            ALIGN_SIZE(size, alignment);
            m_data[0] =(::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_data[1] = (uint8_t *)m_data[0] + offsets[0];
            m_data[2] = (uint8_t *)m_data[0] + offsets[1];
            m_linesize[0] = width;
            m_linesize[1] = half_width;
            m_linesize[2] = half_width;
            break;
         }

         case e_video_format_i40a: {
            size = width * height;
            ALIGN_SIZE(size, alignment);
            offsets[0] = size;
            const uint32_t half_width = (width + 1) / 2;
            const uint32_t half_height = (height + 1) / 2;
            const uint32_t quarter_area = half_width * half_height;
            size += quarter_area;
            ALIGN_SIZE(size, alignment);
            offsets[1] = size;
            size += quarter_area;
            ALIGN_SIZE(size, alignment);
            offsets[2] = size;
            size += width * height;
            ALIGN_SIZE(size, alignment);
            m_data[0] =(::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_data[1] = (uint8_t *)m_data[0] + offsets[0];
            m_data[2] = (uint8_t *)m_data[0] + offsets[1];
            m_data[3] = (uint8_t *)m_data[0] + offsets[2];
            m_linesize[0] = width;
            m_linesize[1] = half_width;
            m_linesize[2] = half_width;
            m_linesize[3] = width;
            break;
         }

         case e_video_format_i42a: {
            size = width * height;
            ALIGN_SIZE(size, alignment);
            offsets[0] = size;
            const uint32_t half_width = (width + 1) / 2;
            const uint32_t half_area = half_width * height;
            size += half_area;
            ALIGN_SIZE(size, alignment);
            offsets[1] = size;
            size += half_area;
            ALIGN_SIZE(size, alignment);
            offsets[2] = size;
            size += width * height;
            ALIGN_SIZE(size, alignment);
            m_data[0] =(::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_data[1] = (uint8_t *)m_data[0] + offsets[0];
            m_data[2] = (uint8_t *)m_data[0] + offsets[1];
            m_data[3] = (uint8_t *)m_data[0] + offsets[2];
            m_linesize[0] = width;
            m_linesize[1] = half_width;
            m_linesize[2] = half_width;
            m_linesize[3] = width;
            break;
         }

         case e_video_format_yuva:
            size = width * height;
            ALIGN_SIZE(size, alignment);
            offsets[0] = size;
            size += width * height;
            ALIGN_SIZE(size, alignment);
            offsets[1] = size;
            size += width * height;
            ALIGN_SIZE(size, alignment);
            offsets[2] = size;
            size += width * height;
            ALIGN_SIZE(size, alignment);
            m_data[0] =(::u8 *) ::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, nullptr, alignment);
            m_data[1] = (uint8_t *)m_data[0] + offsets[0];
            m_data[2] = (uint8_t *)m_data[0] + offsets[1];
            m_data[3] = (uint8_t *)m_data[0] + offsets[2];
            m_linesize[0] = width;
            m_linesize[1] = width;
            m_linesize[2] = width;
            m_linesize[3] = width;
            break;
      }
   }

   void frame::copy_from(const frame *src, enum_video_format eformat, uint32_t cy)
   {
      switch (eformat) {
         case e_video_format_none:
            return;

         case e_video_format_i420:
            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy / 2);
            memory_copy(m_data[2], src->m_data[2], src->m_linesize[2] * cy / 2);
            break;

         case e_video_format_nv12:
            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy / 2);
            break;

         case e_video_format_y800:
         case e_video_format_yvyu:
         case e_video_format_yuy2:
         case e_video_format_uyvy:
         case e_video_format_rgba:
         case e_video_format_bgra:
         case e_video_format_bgrx:
         case e_video_format_bgr3:
         case e_video_format_ayuv:
            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
            break;

         case e_video_format_i444:
         case e_video_format_i422:
            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy);
            memory_copy(m_data[2], src->m_data[2], src->m_linesize[2] * cy);
            break;

         case e_video_format_i40a:
            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy / 2);
            memory_copy(m_data[2], src->m_data[2], src->m_linesize[2] * cy / 2);
            memory_copy(m_data[3], src->m_data[3], src->m_linesize[3] * cy);
            break;

         case e_video_format_i42a:
         case e_video_format_yuva:
            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy);
            memory_copy(m_data[2], src->m_data[2], src->m_linesize[2] * cy);
            memory_copy(m_data[3], src->m_data[3], src->m_linesize[3] * cy);
            break;
      }
   }

//   void frame::copy_from(const frame *src, enum_video_format eformat, uint32_t cy)
//   {
//      switch (eformat) {
//         case e_video_format_none:
//            return;
//
//         case e_video_format_i420:
//            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
//            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy / 2);
//            memory_copy(m_data[2], src->m_data[2], src->m_linesize[2] * cy / 2);
//            break;
//
//         case e_video_format_nv12:
//            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
//            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy / 2);
//            break;
//
//         case e_video_format_y800:
//         case e_video_format_yvyu:
//         case e_video_format_yuy2:
//         case e_video_format_uyvy:
//         case e_video_format_rgba:
//         case e_video_format_bgra:
//         case e_video_format_bgrx:
//         case e_video_format_bgr3:
//         case e_video_format_ayuv:
//            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
//            break;
//
//         case e_video_format_i444:
//         case e_video_format_i422:
//            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
//            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy);
//            memory_copy(m_data[2], src->m_data[2], src->m_linesize[2] * cy);
//            break;
//
//         case e_video_format_i40a:
//            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
//            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy / 2);
//            memory_copy(m_data[2], src->m_data[2], src->m_linesize[2] * cy / 2);
//            memory_copy(m_data[3], src->m_data[3], src->m_linesize[3] * cy);
//            break;
//
//         case e_video_format_i42a:
//         case e_video_format_yuva:
//            memory_copy(m_data[0], src->m_data[0], src->m_linesize[0] * cy);
//            memory_copy(m_data[1], src->m_data[1], src->m_linesize[1] * cy);
//            memory_copy(m_data[2], src->m_data[2], src->m_linesize[2] * cy);
//            memory_copy(m_data[3], src->m_data[3], src->m_linesize[3] * cy);
//            break;
//      }
//   }

bool asynchronous_cache::set_texture_size(const frame * frame)
{

//   enum_convert_type cur = get_convert_type(m_eformat, m_full_range);
//
//   if (source->async_width == m_width &&
//       source->async_height == m_height &&
//       source->async_format == m_format &&
//       source->async_full_range == m_full_range)
//      return true;
//
//   source->async_width = m_width;
//   source->async_height = m_height;
//   source->async_format = m_format;
//   source->async_full_range = m_full_range;
//
//   gs_enter_context(obs->video.graphics);
//
//   for (size_t c = 0; c < MAX_AV_PLANES; c++)
//   {
//      gs_texture_destroy(source->async_textures[c]);
//      source->async_textures[c] = NULL;
//      gs_texture_destroy(source->async_prev_textures[c]);
//      source->async_prev_textures[c] = NULL;
//   }
//
//   gs_texrender_destroy(source->async_texrender);
//   gs_texrender_destroy(source->async_prev_texrender);
//   source->async_texrender = NULL;
//   source->async_prev_texrender = NULL;
//
//   const enum gs_color_format format = convert_video_format(m_format);
//   const bool async_gpu_conversion = (cur != CONVERT_NONE) &&
//                                     init_gpu_conversion(source, frame);
//   source->async_gpu_conversion = async_gpu_conversion;
//   if (async_gpu_conversion)
//   {
//      source->async_texrender =
//         gs_texrender_create(format, GS_ZS_NONE);
//
//      for (int c = 0; c < source->async_channel_count; ++c)
//         source->async_textures[c] = gs_texture_create(
//            source->async_convert_width[c],
//            source->async_convert_height[c],
//            source->async_texture_formats[c], 1, NULL,
//            GS_DYNAMIC);
//   }
//   else
//   {
//      source->async_textures[0] =
//         gs_texture_create(m_width, m_height, format,
//                           1, NULL, GS_DYNAMIC);
//   }
//
//   if (deinterlacing_enabled(source))
//      set_deinterlace_texture_size(source);
//
//   gs_leave_context();
//
//   return source->async_textures[0] != NULL;

return false;
}

//static void upload_raw_frame(gs_texture_t * tex[MAX_AV_PLANES],
//                             const frame * frame)
//{
//   switch (get_convert_type(m_format, m_full_range))
//   {
//      case CONVERT_422_PACK:
//      case CONVERT_800:
//      case CONVERT_RGB_LIMITED:
//      case CONVERT_BGR3:
//      case CONVERT_420:
//      case CONVERT_422:
//      case CONVERT_NV12:
//      case CONVERT_444:
//      case CONVERT_420_A:
//      case CONVERT_422_A:
//      case CONVERT_444_A:
//      case CONVERT_444_A_PACK:
//         for (size_t c = 0; c < MAX_AV_PLANES; c++)
//         {
//            if (tex[c])
//               gs_texture_set_image(tex[c], m_data[c],
//                                    m_linesize[c], false);
//         }
//         break;
//
//      case CONVERT_NONE:
//         assert(false && "No conversion requested");
//         break;
//   }
//}
//
//static const char * select_conversion_technique(enum_video_format format,
//                                                bool full_range)
//{
//   switch (format)
//   {
//      case e_video_format_UYVY:
//         return "UYVY_Reverse";
//
//      case e_video_format_YUY2:
//         return "YUY2_Reverse";
//
//      case e_video_format_YVYU:
//         return "YVYU_Reverse";
//
//      case e_video_format_I420:
//         return "I420_Reverse";
//
//      case e_video_format_NV12:
//         return "NV12_Reverse";
//
//      case e_video_format_I444:
//         return "I444_Reverse";
//
//      case e_video_format_Y800:
//         return full_range ? "Y800_Full" : "Y800_Limited";
//
//      case e_video_format_BGR3:
//         return full_range ? "BGR3_Full" : "BGR3_Limited";
//
//      case e_video_format_I422:
//         return "I422_Reverse";
//
//      case e_video_format_I40A:
//         return "I40A_Reverse";
//
//      case e_video_format_I42A:
//         return "I42A_Reverse";
//
//      case e_video_format_YUVA:
//         return "YUVA_Reverse";
//
//      case e_video_format_AYUV:
//         return "AYUV_Reverse";
//
//      case e_video_format_BGRA:
//      case e_video_format_BGRX:
//      case e_video_format_RGBA:
//      case e_video_format_NONE:
//         if (full_range)
//            assert(false && "No conversion requested");
//         else
//            return "RGB_Limited";
//         break;
//   }
//   return NULL;
//}

//static inline void set_eparam(gs_effect_t * effect, const char * name, float val)
//{
//   gs_eparam_t * param = gs_effect_get_param_by_name(effect, name);
//   gs_effect_set_float(param, val);
//}
//
//static inline void set_eparami(gs_effect_t * effect, const char * name, int val)
//{
//   gs_eparam_t * param = gs_effect_get_param_by_name(effect, name);
//   gs_effect_set_int(param, val);
//}
//
//static bool update_async_texrender(struct obs_source * source,
//                                   const frame * frame,
//                                   gs_texture_t * tex[MAX_AV_PLANES],
//                                   gs_texrender_t * texrender)
//{
//   GS_DEBUG_MARKER_BEGIN(GS_DEBUG_COLOR_CONVERT_FORMAT, "Convert Format");
//
//   gs_texrender_reset(texrender);
//
//   upload_raw_frame(tex, frame);
//
//   uint32_t cx = source->async_width;
//   uint32_t cy = source->async_height;
//
//   gs_effect_t * conv = obs->video.conversion_effect;
//   const char * tech_name =
//      select_conversion_technique(m_format, m_full_range);
//   gs_technique_t * tech = gs_effect_get_technique(conv, tech_name);
//
//   const bool success = gs_texrender_begin(texrender, cx, cy);
//
//   if (success)
//   {
//      gs_enable_blending(false);
//
//      gs_technique_begin(tech);
//      gs_technique_begin_pass(tech, 0);
//
//      if (tex[0])
//         gs_effect_set_texture(
//            gs_effect_get_param_by_name(conv, "image"),
//            tex[0]);
//      if (tex[1])
//         gs_effect_set_texture(
//            gs_effect_get_param_by_name(conv, "image1"),
//            tex[1]);
//      if (tex[2])
//         gs_effect_set_texture(
//            gs_effect_get_param_by_name(conv, "image2"),
//            tex[2]);
//      if (tex[3])
//         gs_effect_set_texture(
//            gs_effect_get_param_by_name(conv, "image3"),
//            tex[3]);
//      set_eparam(conv, "width", (float) cx);
//      set_eparam(conv, "height", (float) cy);
//      set_eparam(conv, "width_d2", (float) cx * 0.5f);
//      set_eparam(conv, "height_d2", (float) cy * 0.5f);
//      set_eparam(conv, "width_x2_i", 0.5f / (float) cx);
//
//      struct vec4 vec0, vec1, vec2;
//      vec4_set(&vec0, m_color_matrix[0], m_color_matrix[1],
//               m_color_matrix[2], m_color_matrix[3]);
//      vec4_set(&vec1, m_color_matrix[4], m_color_matrix[5],
//               m_color_matrix[6], m_color_matrix[7]);
//      vec4_set(&vec2, m_color_matrix[8], m_color_matrix[9],
//               m_color_matrix[10], m_color_matrix[11]);
//      gs_effect_set_vec4(
//         gs_effect_get_param_by_name(conv, "color_vec0"), &vec0);
//      gs_effect_set_vec4(
//         gs_effect_get_param_by_name(conv, "color_vec1"), &vec1);
//      gs_effect_set_vec4(
//         gs_effect_get_param_by_name(conv, "color_vec2"), &vec2);
//      if (!m_full_range)
//      {
//         gs_eparam_t * min_param = gs_effect_get_param_by_name(
//            conv, "color_range_min");
//         gs_effect_set_val(min_param, m_color_range_min,
//                           sizeof(float) * 3);
//         gs_eparam_t * max_param = gs_effect_get_param_by_name(
//            conv, "color_range_max");
//         gs_effect_set_val(max_param, m_color_range_max,
//                           sizeof(float) * 3);
//      }
//
//      gs_draw(GS_TRIS, 0, 3);
//
//      gs_technique_end_pass(tech);
//      gs_technique_end(tech);
//
//      gs_enable_blending(true);
//
//      gs_texrender_end(texrender);
//   }
//
//   GS_DEBUG_MARKER_END();
//   return success;
//}

//bool update_async_texture(struct obs_source * source,
//                          const frame * frame,
//                          gs_texture_t * tex, gs_texrender_t * texrender)
//{
//   gs_texture_t * tex3[MAX_AV_PLANES] = {tex, NULL, NULL, NULL,
//                                         NULL, NULL, NULL, NULL};
//   return update_async_textures(source, frame, tex3, texrender);
//}
//
//bool update_async_textures(struct obs_source * source,
//                           const frame * frame,
//                           gs_texture_t * tex[MAX_AV_PLANES],
//                           gs_texrender_t * texrender)
//{
//   enum convert_type type;
//
//   source->async_flip = m_flip;
//   source->async_linear_alpha =
//      (m_flags & OBS_SOURCE_FRAME_LINEAR_ALPHA) != 0;
//
//   if (source->async_gpu_conversion && texrender)
//      return update_async_texrender(source, frame, tex, texrender);
//
//   type = get_convert_type(m_format, m_full_range);
//   if (type == CONVERT_NONE)
//   {
//      gs_texture_set_image(tex[0], m_data[0], m_linesize[0],
//                           false);
//      return true;
//   }
//
//   return false;
//}
//
//static inline void obs_source_draw_texture(struct obs_source * source,
//                                           gs_effect_t * effect)
//{
//   gs_texture_t * tex = source->async_textures[0];
//   gs_eparam_t * param;
//
//   if (source->async_texrender)
//      tex = gs_texrender_get_texture(source->async_texrender);
//
//   param = gs_effect_get_param_by_name(effect, "image");
//
//   const bool linear_srgb = gs_get_linear_srgb();
//
//   const bool previous = gs_framebuffer_srgb_enabled();
//   gs_enable_framebuffer_srgb(linear_srgb);
//
//   if (linear_srgb)
//   {
//      gs_effect_set_texture_srgb(param, tex);
//   }
//   else
//   {
//      gs_effect_set_texture(param, tex);
//   }
//
//   gs_draw_sprite(tex, source->async_flip ? GS_FLIP_V : 0, 0, 0);
//
//   gs_enable_framebuffer_srgb(previous);
//}
//
//static void obs_source_draw_async_texture(struct obs_source * source)
//{
//   gs_effect_t * effect = gs_get_effect();
//   bool def_draw = (!effect);
//   bool premultiplied = false;
//   gs_technique_t * tech = NULL;
//
//   if (def_draw)
//   {
//      effect = obs_get_base_effect(OBS_EFFECT_DEFAULT);
//      const bool nonlinear_alpha = gs_get_linear_srgb() &&
//                                   !source->async_linear_alpha;
//      const char * tech_name = nonlinear_alpha ? "DrawNonlinearAlpha"
//                                               : "Draw";
//      premultiplied = nonlinear_alpha;
//      tech = gs_effect_get_technique(effect, tech_name);
//      gs_technique_begin(tech);
//      gs_technique_begin_pass(tech, 0);
//   }
//
//   if (premultiplied)
//   {
//      gs_blend_state_push();
//      gs_blend_function(GS_BLEND_ONE, GS_BLEND_INVSRCALPHA);
//   }
//
//   obs_source_draw_texture(source, effect);
//
//   if (premultiplied)
//   {
//      gs_blend_state_pop();
//   }
//
//   if (def_draw)
//   {
//      gs_technique_end_pass(tech);
//      gs_technique_end(tech);
//   }
//}

//static void recreate_async_texture(obs_source_t * source,
//enum gs_color_format format
//)
//{
//uint32_t cx = gs_texture_get_width(source->async_textures[0]);
//uint32_t cy = gs_texture_get_height(source->async_textures[0]);
//gs_texture_destroy(source
//->async_textures[0]);
//source->async_textures[0] =
//gs_texture_create(cx, cy, format,
//1, NULL, GS_DYNAMIC);
//}
//
//static inline void check_to_swap_bgrx_bgra(obs_source_t * source,
//frame * frame
//)
//{
//enum gs_color_format format =
//   gs_texture_get_color_format(source->async_textures[0]);
//if (format ==
//GS_BGRX && frame
//->format == e_video_format_BGRA) {
//recreate_async_texture(source, GS_BGRA
//);
//} else if (format ==
//GS_BGRA && frame
//->format == e_video_format_BGRX) {
//recreate_async_texture(source, GS_BGRX
//);
//}
//}
//
//static void obs_source_update_async_video(obs_source_t * source)
//{
//   if (!source->async_rendered)
//   {
//      frame * frame = obs_source_get_frame(source);
//
//      if (frame)
//         frame = filter_async_video(source, frame);
//
//      source->async_rendered = true;
//      if (frame)
//      {
//         check_to_swap_bgrx_bgra(source, frame);
//
//         if (!source->async_decoupled ||
//             !source->async_unbuffered)
//         {
//            source->timing_adjust = obs->video.video_time -
//                                    m_timestamp;
//            source->timing_set = true;
//         }
//
//         if (source->async_update_texture)
//         {
//            update_async_textures(source, frame,
//                                  source->async_textures,
//                                  source->async_texrender);
//            source->async_update_texture = false;
//         }
//
//         obs_source_release_frame(source, frame);
//      }
//   }
//}
//
//static void rotate_async_video(obs_source_t * source, long
//rotation)
//{
//float x = 0;
//float y = 0;
//
//switch (rotation) {
//case 90:
//y = (float) source->async_width;
//break;
//case 270:
//case -90:
//x = (float) source->async_height;
//break;
//case 180:
//x = (float) source->async_width;
//y = (float) source->async_height;
//}
//
//gs_matrix_translate3f(x, y,
//0);
//gs_matrix_rotaa4f(0.0f, 0.0f, -1.0f, RAD((float)rotation));
//}
//
//static inline void obs_source_render_async_video(obs_source_t * source)
//{
//   if (source->async_textures[0] && source->async_active)
//   {
//      long rotation = source->async_rotation;
//      if (rotation)
//      {
//         gs_matrix_push();
//         rotate_async_video(source, rotation);
//      }
//      obs_source_draw_async_texture(source);
//      if (rotation)
//      {
//         gs_matrix_pop();
//      }
//   }
//}
//
//static inline void obs_source_render_filters(obs_source_t * source)
//{
//   obs_source_t * first_filter;
//
//   pthread_mutex_lock(&source->filter_mutex);
//   first_filter = obs_source_get_ref(source->filters.array[0]);
//   pthread_mutex_unlock(&source->filter_mutex);
//
//   source->rendering_filter = true;
//   obs_source_video_render(first_filter);
//   source->rendering_filter = false;
//
//   obs_source_release(first_filter);
//}
//
//void obs_source_default_render(obs_source_t * source)
//{
//   gs_effect_t * effect = obs->video.default_effect;
//   gs_technique_t * tech = gs_effect_get_technique(effect, "Draw");
//   size_t passes, i;
//
//   passes = gs_technique_begin(tech);
//   for (i = 0; i < passes; i++)
//   {
//      gs_technique_begin_pass(tech, i);
//      if (source->context.m_data)
//         source->info.video_render(source->context.m_data, effect);
//      gs_technique_end_pass(tech);
//   }
//   gs_technique_end(tech);
//}
//
//static inline void obs_source_main_render(obs_source_t * source)
//{
//   uint32_t flags = source->info.output_flags;
//   bool custom_draw = (flags & OBS_SOURCE_CUSTOM_DRAW) != 0;
//   bool srgb_aware = (flags & OBS_SOURCE_SRGB) != 0;
//   bool default_effect = !source->filter_parent &&
//                         source->filters.num == 0 && !custom_draw;
//   bool previous_srgb = false;
//
//   if (!srgb_aware)
//   {
//      previous_srgb = gs_get_linear_srgb();
//      gs_set_linear_srgb(false);
//   }
//
//   if (default_effect)
//      obs_source_default_render(source);
//   else if (source->context.m_data)
//      source->info.video_render(source->context.m_data,
//                                custom_draw ? NULL : gs_get_effect());
//
//   if (!srgb_aware)
//      gs_set_linear_srgb(previous_srgb);
//}
//
//static bool ready_async_frame(obs_source_t * source, uint64_t
//sys_time);
//
//#if GS_USE_DEBUG_MARKERS
//static const char *get_type_format(enum obs_source_type type)
//{
//   switch (type) {
//   case OBS_SOURCE_TYPE_INPUT:
//      return "Input: %s";
//   case OBS_SOURCE_TYPE_FILTER:
//      return "Filter: %s";
//   case OBS_SOURCE_TYPE_TRANSITION:
//      return "Transition: %s";
//   case OBS_SOURCE_TYPE_SCENE:
//      return "Scene: %s";
//   default:
//      return "[Unknown]: %s";
//   }
//}
//#endif
//
//static inline void render_video(obs_source_t * source)
//{
//   if (source->info.type != OBS_SOURCE_TYPE_FILTER &&
//       (source->info.output_flags & OBS_SOURCE_VIDEO) == 0)
//   {
//      if (source->filter_parent)
//         obs_source_skip_video_filter(source);
//      return;
//   }
//
//   if (source->info.type == OBS_SOURCE_TYPE_INPUT &&
//       (source->info.output_flags & OBS_SOURCE_ASYNC) != 0 &&
//       !source->rendering_filter)
//   {
//      if (deinterlacing_enabled(source))
//         deinterlace_update_async_video(source);
//      obs_source_update_async_video(source);
//   }
//
//   if (!source->context.m_data || !source->enabled)
//   {
//      if (source->filter_parent)
//         obs_source_skip_video_filter(source);
//      return;
//   }
//
//   GS_DEBUG_MARKER_BEGIN_FORMAT(GS_DEBUG_COLOR_SOURCE,
//                                get_type_format(source->info.type),
//                                obs_source_get_name(source));
//
//   if (source->filters.num && !source->rendering_filter)
//      obs_source_render_filters(source);
//
//   else if (source->info.video_render)
//      obs_source_main_render(source);
//
//   else if (source->filter_target)
//      obs_source_video_render(source->filter_target);
//
//   else if (deinterlacing_enabled(source))
//      deinterlace_render(source);
//
//   else
//      obs_source_render_async_video(source);
//
//   GS_DEBUG_MARKER_END();
//}
//
//void obs_source_video_render(obs_source_t * source)
//{
//   if (!obs_source_valid(source, "obs_source_video_render"))
//      return;
//
//   source = obs_source_get_ref(source);
//   if (source)
//   {
//      render_video(source);
//      obs_source_release(source);
//   }
//}
//
//static inline uint32_t get_async_width(const obs_source_t * source)
//{
//   return ((source->async_rotation % 180) == 0) ? source->async_width
//                                                : source->async_height;
//}
//
//static inline uint32_t get_async_height(const obs_source_t * source)
//{
//   return ((source->async_rotation % 180) == 0) ? source->async_height
//                                                : source->async_width;
//}
//
//static uint32_t get_base_width(const obs_source_t * source)
//{
//   bool is_filter = !!source->filter_parent;
//   bool func_valid = source->context.m_data && source->info.get_width;
//
//   if (source->info.type == OBS_SOURCE_TYPE_TRANSITION)
//   {
//      return source->enabled ? source->transition_actual_cx : 0;
//
//   }
//   else if (func_valid && (!is_filter || source->enabled))
//   {
//      return source->info.get_width(source->context.m_data);
//
//   }
//   else if (is_filter)
//   {
//      return get_base_width(source->filter_target);
//   }
//
//   return source->async_active ? get_async_width(source) : 0;
//}
//
//static uint32_t get_base_height(const obs_source_t * source)
//{
//   bool is_filter = !!source->filter_parent;
//   bool func_valid = source->context.m_data && source->info.get_height;
//
//   if (source->info.type == OBS_SOURCE_TYPE_TRANSITION)
//   {
//      return source->enabled ? source->transition_actual_cy : 0;
//
//   }
//   else if (func_valid && (!is_filter || source->enabled))
//   {
//      return source->info.get_height(source->context.m_data);
//
//   }
//   else if (is_filter)
//   {
//      return get_base_height(source->filter_target);
//   }
//
//   return source->async_active ? get_async_height(source) : 0;
//}
//
//static uint32_t get_recurse_width(obs_source_t * source)
//{
//   uint32_t width;
//
//   pthread_mutex_lock(&source->filter_mutex);
//
//   width = (source->filters.num) ? get_base_width(source->filters.array[0])
//                                 : get_base_width(source);
//
//   pthread_mutex_unlock(&source->filter_mutex);
//
//   return width;
//}
//
//static uint32_t get_recurse_height(obs_source_t * source)
//{
//   uint32_t height;
//
//   pthread_mutex_lock(&source->filter_mutex);
//
//   height = (source->filters.num)
//            ? get_base_height(source->filters.array[0])
//            : get_base_height(source);
//
//   pthread_mutex_unlock(&source->filter_mutex);
//
//   return height;
//}
//
//uint32_t obs_source_get_width(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_get_width"))
//      return 0;
//
//   return (source->info.type != OBS_SOURCE_TYPE_FILTER)
//          ? get_recurse_width(source)
//          : get_base_width(source);
//}
//
//uint32_t obs_source_get_height(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_get_height"))
//      return 0;
//
//   return (source->info.type != OBS_SOURCE_TYPE_FILTER)
//          ? get_recurse_height(source)
//          : get_base_height(source);
//}
//
//uint32_t obs_source_get_base_width(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_get_base_width"))
//      return 0;
//
//   return get_base_width(source);
//}
//
//uint32_t obs_source_get_base_height(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_get_base_height"))
//      return 0;
//
//   return get_base_height(source);
//}
//
//obs_source_t * obs_filter_get_parent(const obs_source_t * filter)
//{
//   return obs_ptr_valid(filter, "obs_filter_get_parent")
//          ? filter->filter_parent
//          : NULL;
//}
//
//obs_source_t * obs_filter_get_target(const obs_source_t * filter)
//{
//   return obs_ptr_valid(filter, "obs_filter_get_target")
//          ? filter->filter_target
//          : NULL;
//}
//
//#define OBS_SOURCE_AV (OBS_SOURCE_ASYNC_VIDEO | OBS_SOURCE_AUDIO)
//
//static bool filter_compatible(obs_source_t * source, obs_source_t * filter)
//{
//   uint32_t s_caps = source->info.output_flags & OBS_SOURCE_AV;
//   uint32_t f_caps = filter->info.output_flags & OBS_SOURCE_AV;
//
//   if ((f_caps & OBS_SOURCE_AUDIO) != 0 &&
//       (f_caps & OBS_SOURCE_VIDEO) == 0)
//      f_caps &= ~OBS_SOURCE_ASYNC;
//
//   return (s_caps & f_caps) == f_caps;
//}
//
//void obs_source_filter_add(obs_source_t * source, obs_source_t * filter)
//{
//   struct callm_data cd;
//   uint8_t stack[128];
//
//   if (!obs_source_valid(source, "obs_source_filter_add"))
//      return;
//   if (!obs_ptr_valid(filter, "obs_source_filter_add"))
//      return;
//
//   pthread_mutex_lock(&source->filter_mutex);
//
//   if (da_find(source->filters, &filter, 0) != DARRAY_INVALID)
//   {
//      blog(LOG_WARNING, "Tried to add a filter that was already "
//                        "present on the source");
//      pthread_mutex_unlock(&source->filter_mutex);
//      return;
//   }
//
//   if (!source->owns_info_id && !filter_compatible(source, filter))
//   {
//      pthread_mutex_unlock(&source->filter_mutex);
//      return;
//   }
//
//   filter = obs_source_get_ref(filter);
//   if (!obs_ptr_valid(filter, "obs_source_filter_add"))
//      return;
//
//   filter->filter_parent = source;
//   filter->filter_target = !source->filters.num ? source
//                                                : source->filters.array[0];
//
//   da_insert(source->filters, 0, &filter);
//
//   pthread_mutex_unlock(&source->filter_mutex);
//
//   callm_data_init_fixed(&cd, stack, sizeof(stack));
//   callm_data_set_ptr(&cd, "source", source);
//   callm_data_set_ptr(&cd, "filter", filter);
//
//   signal_handler_signal(source->context.signals, "filter_add", &cd);
//
//   blog(LOG_DEBUG, "- filter '%s' (%s) added to source '%s'",
//        filter->context.name, filter->info.id, source->context.name);
//}
//
//static bool obs_source_filter_remove_refless(obs_source_t * source,
//                                             obs_source_t * filter)
//{
//   struct callm_data cd;
//   uint8_t stack[128];
//   size_t idx;
//
//   pthread_mutex_lock(&source->filter_mutex);
//
//   idx = da_find(source->filters, &filter, 0);
//   if (idx == DARRAY_INVALID)
//   {
//      pthread_mutex_unlock(&source->filter_mutex);
//      return false;
//   }
//
//   if (idx > 0)
//   {
//      obs_source_t * prev = source->filters.array[idx - 1];
//      prev->filter_target = filter->filter_target;
//   }
//
//   da_erase(source->filters, idx);
//
//   pthread_mutex_unlock(&source->filter_mutex);
//
//   callm_data_init_fixed(&cd, stack, sizeof(stack));
//   callm_data_set_ptr(&cd, "source", source);
//   callm_data_set_ptr(&cd, "filter", filter);
//
//   signal_handler_signal(source->context.signals, "filter_remove", &cd);
//
//   blog(LOG_DEBUG, "- filter '%s' (%s) removed from source '%s'",
//        filter->context.name, filter->info.id, source->context.name);
//
//   if (filter->info.filter_remove)
//      filter->info.filter_remove(filter->context.m_data,
//                                 filter->filter_parent);
//
//   filter->filter_parent = NULL;
//   filter->filter_target = NULL;
//   return true;
//}
//
//void obs_source_filter_remove(obs_source_t * source, obs_source_t * filter)
//{
//   if (!obs_source_valid(source, "obs_source_filter_remove"))
//      return;
//   if (!obs_ptr_valid(filter, "obs_source_filter_remove"))
//      return;
//
//   if (obs_source_filter_remove_refless(source, filter))
//      obs_source_release(filter);
//}
//
//static size_t find_next_filter(obs_source_t * source, obs_source_t * filter,
//                               size_t
//cur_idx)
//{
//bool curAsync = (filter->info.output_flags & OBS_SOURCE_ASYNC) != 0;
//bool nextAsync;
//obs_source_t * next;
//
//if (cur_idx == source->filters.num - 1)
//return
//DARRAY_INVALID;
//
//next = source->filters.array[cur_idx + 1];
//nextAsync = (next->info.output_flags & OBS_SOURCE_ASYNC);
//
//if (nextAsync == curAsync)
//return cur_idx + 1;
//else
//return
//find_next_filter(source, filter, cur_idx
//+ 1);
//}
//
//static size_t find_prev_filter(obs_source_t * source, obs_source_t * filter,
//                               size_t
//cur_idx)
//{
//bool curAsync = (filter->info.output_flags & OBS_SOURCE_ASYNC) != 0;
//bool prevAsync;
//obs_source_t * prev;
//
//if (cur_idx == 0)
//return
//DARRAY_INVALID;
//
//prev = source->filters.array[cur_idx - 1];
//prevAsync = (prev->info.output_flags & OBS_SOURCE_ASYNC);
//
//if (prevAsync == curAsync)
//return cur_idx - 1;
//else
//return
//find_prev_filter(source, filter, cur_idx
//- 1);
//}
//
///* moves filters above/below matching filter types */
//static bool move_filter_dir(obs_source_t * source, obs_source_t * filter,
//enum obs_order_movement movement
//)
//{
//size_t idx;
//
//idx = da_find(source->filters, &filter, 0);
//if (idx == DARRAY_INVALID)
//return false;
//
//if (movement == OBS_ORDER_MOVE_UP) {
//size_t next_id = find_next_filter(source, filter, idx);
//if (next_id == DARRAY_INVALID)
//return false;
//da_move_item(source
//->filters, idx, next_id);
//
//} else if (movement == OBS_ORDER_MOVE_DOWN) {
//size_t prev_id = find_prev_filter(source, filter, idx);
//if (prev_id == DARRAY_INVALID)
//return false;
//da_move_item(source
//->filters, idx, prev_id);
//
//} else if (movement == OBS_ORDER_MOVE_TOP) {
//if (idx == source->filters.num - 1)
//return false;
//da_move_item(source
//->filters, idx, source->filters.num - 1);
//
//} else if (movement == OBS_ORDER_MOVE_BOTTOM) {
//if (idx == 0)
//return false;
//da_move_item(source
//->filters, idx, 0);
//}
//
///* reorder filter targets, not the nicest way of dealing with things */
//for (
//size_t i = 0;
//i<source->filters.
//num;
//i++) {
//obs_source_t * next_filter =
//   (i == source->filters.num - 1)
//   ? source
//   : source->filters.array[i + 1];
//
//source->filters.array[i]->
//filter_target = next_filter;
//}
//
//return true;
//}
//
//void obs_source_filter_set_order(obs_source_t * source, obs_source_t * filter,
//enum obs_order_movement movement
//)
//{
//bool success;
//
//if (!
//obs_source_valid(source,
//"obs_source_filter_set_order"))
//return;
//if (!
//obs_ptr_valid(filter,
//"obs_source_filter_set_order"))
//return;
//
//pthread_mutex_lock(& source
//->filter_mutex);
//success = move_filter_dir(source, filter, movement);
//pthread_mutex_unlock(& source
//->filter_mutex);
//
//if (success)
//obs_source_dosignal(source, NULL,
//"reorder_filters");
//}
//
//obs_m_data_t * obs_source_get_settings(const obs_source_t * source)
//{
//   if (!obs_source_valid(source, "obs_source_get_settings"))
//      return NULL;
//
//   obs_m_data_addref(source->context.settings);
//   return source->context.settings;
//}
//
//frame * filter_async_video(obs_source_t * source,
//frame * in
//)
//{
//size_t i;
//
//pthread_mutex_lock(& source
//->filter_mutex);
//
//for (
//i = source->filters.num;
//i > 0; i--) {
//struct obs_source * filter = source->filters.array[i - 1];
//
//if (!filter->enabled)
//continue;
//
//if (filter->context.
//m_data && filter
//->info.filter_video) {
//in = filter->info.filter_video(filter->context.m_data,
//                               in);
//if (!in)
//break;
//}
//}
//
//pthread_mutex_unlock(& source
//->filter_mutex);
//
//return
//in;
//}
//

void frame::copy_frame_data(const frame * src)
{
   m_flip = src->m_flip;
   m_flags = src->m_flags;
   m_full_range = src->m_full_range;
   m_timestamp = src->m_timestamp;
   memory_copy(m_color_matrix, src->m_color_matrix, sizeof(float) * 16);
   if (!m_full_range)
   {
      size_t const size = sizeof(float) * 3;
      memory_copy(m_color_range_min, src->m_color_range_min, size);
      memory_copy(m_color_range_max, src->m_color_range_max, size);
   }

   switch (src->m_eformat)
   {
      case e_video_format_i420:
      {
         const uint32_t height = m_height;
         const uint32_t half_height = (height + 1) / 2;
         copy_data_plane_from(src, 0, height);
         copy_data_plane_from(src, 1, half_height);
         copy_data_plane_from(src, 2, half_height);
         break;
      }

      case e_video_format_nv12:
      {
         const uint32_t height = m_height;
         const uint32_t half_height = (height + 1) / 2;
         copy_data_plane_from(src, 0, m_height);
         copy_data_plane_from(src, 1, half_height);
         break;
      }

      case e_video_format_i444:
      case e_video_format_i422:
         copy_data_plane_from(src, 0, m_height);
         copy_data_plane_from(src, 1, m_height);
         copy_data_plane_from(src, 2, m_height);
         break;

      case e_video_format_yvyu:
      case e_video_format_yuy2:
      case e_video_format_uyvy:
      case e_video_format_none:
      case e_video_format_rgba:
      case e_video_format_bgra:
      case e_video_format_bgrx:
      case e_video_format_y800:
      case e_video_format_bgr3:
      case e_video_format_ayuv:
         copy_data_plane_from(src, 0, m_height);
         break;

      case e_video_format_i40a:
      {
         const uint32_t height = m_height;
         const uint32_t half_height = (height + 1) / 2;
         copy_data_plane_from(src, 0, height);
         copy_data_plane_from(src, 1, half_height);
         copy_data_plane_from(src, 2, half_height);
         copy_data_plane_from(src, 3, height);
         break;
      }

      case e_video_format_i42a:
      case e_video_format_yuva:
         copy_data_plane_from(src, 0, m_height);
         copy_data_plane_from(src, 1, m_height);
         copy_data_plane_from(src, 2, m_height);
         copy_data_plane_from(src, 3, m_height);
         break;
   }

}


void frame::copy_from(const frame * src)
{

   copy_frame_data(src);

}


//static inline void free_async_cache(struct obs_source * source)
//{
//   for (size_t i = 0; i < source->async_cache.num; i++)
//      video_frame_decref(source->async_cache.array[i].frame);
//
//   da_resize(source->async_cache, 0);
//   da_resize(source->async_frames, 0);
//   source->cur_async_frame = NULL;
//   source->prev_async_frame = NULL;
//}

#define MAX_UNUSED_FRAME_DURATION 5

///* frees frame allocations if they haven't been used for a specific period
// * of time */
//static void clean_cache(obs_source_t * source)
//{
//   for (size_t i = source->async_cache.num; i > 0; i--)
//   {
//      struct async_frame * af = &source->async_cache.array[i - 1];
//      if (!af->used)
//      {
//         if (++af->unused_count == MAX_UNUSED_FRAME_DURATION)
//         {
//            video_frame_destroy(af->frame);
//            da_erase(source->async_cache, i - 1);
//         }
//      }
//   }
//}

#define MAX_ASYNC_FRAMES 30


//static void
//   obs_source_output_video_internal(obs_source_t * source,
//const frame * frame
//)
//{
//if (!
//obs_source_valid(source,
//"obs_source_output_video"))
//return;
//
//if (!frame) {
//pthread_mutex_lock(& source
//->async_mutex);
//source->
//async_active = false;
//source->
//last_frame_ts = 0;
//free_async_cache(source);
//pthread_mutex_unlock(& source
//->async_mutex);
//return;
//}
//
//frame * output = cache_video(source, frame);
//
///* ------------------------------------------- */
//pthread_mutex_lock(& source
//->async_mutex);
//if (output) {
//if (
//os_atomic_dec_long(& output
//->refs) == 0) {
//video_frame_destroy(output);
//output = NULL;
//} else {
//da_push_back(source
//->async_frames, &output);
//source->
//async_active = true;
//}
//}
//pthread_mutex_unlock(& source
//->async_mutex);
//}
//
//void obs_source_output_video(obs_source_t * source,
//const frame * frame
//)
//{
//if (
//destroying(source)
//)
//return;
//if (!frame) {
//obs_source_output_video_internal(source, NULL
//);
//return;
//}
//
//frame new_frame = *frame;
//new_frame.
//full_range =
//format_is_yuv(m_format) ? new_frame.full_range : true;
//
//obs_source_output_video_internal(source, & new_frame
//);
//}
//
//void obs_source_output_video2(obs_source_t * source,
//const frame2 * frame
//)
//{
//if (
//destroying(source)
//)
//return;
//if (!frame) {
//obs_source_output_video_internal(source, NULL
//);
//return;
//}
//
//frame new_frame;
//enum video_range_type range =
//   resolve_video_range(m_format, m_range);
//
//for (
//size_t i = 0;
//i<MAX_AV_PLANES;
//i++) {
//new_frame.m_data[i] = m_data[i];
//new_frame.m_linesize[i] = m_linesize[i];
//}
//
//new_frame.
//width = m_width;
//new_frame.
//height = m_height;
//new_frame.
//timestamp = m_timestamp;
//new_frame.
//format = m_format;
//new_frame.
//full_range = range == VIDEO_RANGE_FULL;
//new_frame.
//flip = m_flip;
//new_frame.
//flags = m_flags;
//
//memory_copy(& new_frame
//.color_matrix, &m_color_matrix,
//sizeof(m_color_matrix));
//memory_copy(& new_frame
//.color_range_min, &m_color_range_min,
//sizeof(m_color_range_min));
//memory_copy(& new_frame
//.color_range_max, &m_color_range_max,
//sizeof(m_color_range_max));
//
//obs_source_output_video_internal(source, & new_frame
//);
//}
//
//void obs_source_set_async_rotation(obs_source_t * source, long
//rotation)
//{
//if (source)
//source->
//async_rotation = rotation;
//}
//
//void obs_source_output_cea708(obs_source_t * source,
//const struct obs_source_cea_708 * captions
//)
//{
//if (
//destroying(source)
//)
//return;
//if (!captions) {
//return;
//}
//
//pthread_mutex_lock(& source
//->caption_cb_mutex);
//
//for (
//size_t i = source->caption_cb_list.num;
//i > 0; i--) {
//struct caption_cb_info info =
//   source->caption_cb_list.array[i - 1];
//info.
//callback(info
//.param, source, captions);
//}
//
//pthread_mutex_unlock(& source
//->caption_cb_mutex);
//}
//
//void obs_source_add_caption_callback(obs_source_t * source,
//                                     obs_source_caption_t
//callback,
//void * param
//)
//{
//struct caption_cb_info info = {callback, param};
//
//if (!
//obs_source_valid(source,
//"obs_source_add_caption_callback"))
//return;
//
//pthread_mutex_lock(& source
//->caption_cb_mutex);
//da_push_back(source
//->caption_cb_list, &info);
//pthread_mutex_unlock(& source
//->caption_cb_mutex);
//}
//
//void obs_source_remove_caption_callback(obs_source_t * source,
//                                        obs_source_caption_t
//callback,
//void * param
//)
//{
//struct caption_cb_info info = {callback, param};
//
//if (!
//obs_source_valid(source,
//"obs_source_remove_caption_callback"))
//return;
//
//pthread_mutex_lock(& source
//->caption_cb_mutex);
//da_erase_item(source
//->caption_cb_list, &info);
//pthread_mutex_unlock(& source
//->caption_cb_mutex);
//}
//
//static inline bool preload_frame_changed(obs_source_t * source,
//const frame * in
//)
//{
//if (!source->async_preload_frame)
//return true;
//
//return in->width != source->async_preload_m_width ||
//in->height != source->async_preload_m_height ||
//in->format != source->async_preload_m_
//format;
//}
//
//static void
//   obs_source_preload_video_internal(obs_source_t * source,
//const frame * frame
//)
//{
//if (!
//obs_source_valid(source,
//"obs_source_preload_video"))
//return;
//if (
//destroying(source)
//)
//return;
//if (!frame)
//return;
//
//if (
//preload_frame_changed(source, frame
//)) {
//video_frame_destroy(source
//->async_preload_frame);
//source->
//async_preload_frame = video_frame_create(
//   m_format, m_width, m_height);
//}
//
//copy_frame_m_data(source
//->async_preload_frame, frame);
//
//source->
//last_frame_ts = m_timestamp;
//}
//
//void obs_source_preload_video(obs_source_t * source,
//const frame * frame
//)
//{
//if (
//destroying(source)
//)
//return;
//if (!frame) {
//obs_source_preload_video_internal(source, NULL
//);
//return;
//}
//
//frame new_frame = *frame;
//new_frame.
//full_range =
//format_is_yuv(m_format) ? new_frame.full_range : true;
//
//obs_source_preload_video_internal(source, & new_frame
//);
//}
//
//void obs_source_preload_video2(obs_source_t * source,
//const frame2 * frame
//)
//{
//if (
//destroying(source)
//)
//return;
//if (!frame) {
//obs_source_preload_video_internal(source, NULL
//);
//return;
//}
//
//frame new_frame;
//enum video_range_type range =
//   resolve_video_range(m_format, m_range);
//
//for (
//size_t i = 0;
//i<MAX_AV_PLANES;
//i++) {
//new_frame.m_data[i] = m_data[i];
//new_frame.m_linesize[i] = m_linesize[i];
//}
//
//new_frame.
//width = m_width;
//new_frame.
//height = m_height;
//new_frame.
//timestamp = m_timestamp;
//new_frame.
//format = m_format;
//new_frame.
//full_range = range == VIDEO_RANGE_FULL;
//new_frame.
//flip = m_flip;
//new_frame.
//flags = m_flags;
//
//memory_copy(& new_frame
//.color_matrix, &m_color_matrix,
//sizeof(m_color_matrix));
//memory_copy(& new_frame
//.color_range_min, &m_color_range_min,
//sizeof(m_color_range_min));
//memory_copy(& new_frame
//.color_range_max, &m_color_range_max,
//sizeof(m_color_range_max));
//
//obs_source_preload_video_internal(source, & new_frame
//);
//}
//
//void obs_source_show_preloaded_video(obs_source_t * source)
//{
//   uint64_t sys_ts;
//
//   if (!obs_source_valid(source, "obs_source_show_preloaded_video"))
//      return;
//   if (destroying(source))
//      return;
//   if (!source->async_preload_frame)
//      return;
//
//   obs_enter_graphics();
//
//   set_async_texture_size(source, source->async_preload_frame);
//   update_async_textures(source, source->async_preload_frame,
//                         source->async_textures, source->async_texrender);
//   source->async_active = true;
//
//   obs_leave_graphics();
//
//   pthread_mutex_lock(&source->audio_buf_mutex);
//   sys_ts = (source->monitoring_type != OBS_MONITORING_TYPE_MONITOR_ONLY)
//            ? os_gettime_ns()
//            : 0;
//   reset_audio_timing(source, source->last_frame_ts, sys_ts);
//   reset_audio_m_data(source, sys_ts);
//   pthread_mutex_unlock(&source->audio_buf_mutex);
//}
//
//static void
//   obs_source_set_video_frame_internal(obs_source_t * source,
//const frame * frame
//)
//{
//if (!
//obs_source_valid(source,
//"obs_source_set_video_frame"))
//return;
//if (!frame)
//return;
//
//obs_enter_graphics();
//
//if (
//preload_frame_changed(source, frame
//)) {
//video_frame_destroy(source
//->async_preload_frame);
//source->
//async_preload_frame = video_frame_create(
//   m_format, m_width, m_height);
//}
//
//copy_frame_m_data(source
//->async_preload_frame, frame);
//set_async_texture_size(source, source
//->async_preload_frame);
//update_async_textures(source, source
//->async_preload_frame,
//source->async_textures, source->async_texrender);
//
//source->
//last_frame_ts = m_timestamp;
//
//obs_leave_graphics();
//
//}
//
//void obs_source_set_video_frame(obs_source_t * source,
//const frame * frame
//)
//{
//if (
//destroying(source)
//)
//return;
//if (!frame) {
//obs_source_preload_video_internal(source, NULL
//);
//return;
//}
//
//frame new_frame = *frame;
//new_frame.
//full_range =
//format_is_yuv(m_format) ? new_frame.full_range : true;
//
//obs_source_set_video_frame_internal(source, & new_frame
//);
//}
//
//void obs_source_set_video_frame2(obs_source_t * source,
//const frame2 * frame
//)
//{
//if (
//destroying(source)
//)
//return;
//if (!frame) {
//obs_source_preload_video_internal(source, NULL
//);
//return;
//}
//
//frame new_frame;
//enum video_range_type range =
//   resolve_video_range(m_format, m_range);
//
//for (
//size_t i = 0;
//i<MAX_AV_PLANES;
//i++) {
//new_frame.m_data[i] = m_data[i];
//new_frame.m_linesize[i] = m_linesize[i];
//}
//
//new_frame.
//width = m_width;
//new_frame.
//height = m_height;
//new_frame.
//timestamp = m_timestamp;
//new_frame.
//format = m_format;
//new_frame.
//full_range = range == VIDEO_RANGE_FULL;
//new_frame.
//flip = m_flip;
//new_frame.
//flags = m_flags;
//
//memory_copy(& new_frame
//.color_matrix, &m_color_matrix,
//sizeof(m_color_matrix));
//memory_copy(& new_frame
//.color_range_min, &m_color_range_min,
//sizeof(m_color_range_min));
//memory_copy(& new_frame
//.color_range_max, &m_color_range_max,
//sizeof(m_color_range_max));
//
//obs_source_set_video_frame_internal(source, & new_frame
//);
//}
//
//static inline struct obs_audio_m_data *
//   filter_async_audio(obs_source_t * source,
//struct obs_audio_m_data * in
//)
//{
//size_t i;
//for (
//i = source->filters.num;
//i > 0; i--) {
//struct obs_source * filter = source->filters.array[i - 1];
//
//if (!filter->enabled)
//continue;
//
//if (filter->context.
//m_data && filter
//->info.filter_audio) {
//in = filter->info.filter_audio(filter->context.m_data,
//                               in);
//if (!in)
//return
//NULL;
//}
//}
//
//return
//in;
//}
//
//static inline void reset_resampler(obs_source_t * source,
//const struct obs_source_audio * audio
//)
//{
//const struct audio_output_info * obs_info;
//struct resample_info output_info;
//
//obs_info = audio_output_get_info(obs->audio.audio);
//
//output_info.
//format = obs_info->format;
//output_info.
//samples_per_sec = obs_info->samples_per_sec;
//output_info.
//speakers = obs_info->speakers;
//
//source->sample_info.
//format = audio->format;
//source->sample_info.
//samples_per_sec = audio->samples_per_sec;
//source->sample_info.
//speakers = audio->speakers;
//
//audio_resampler_destroy(source
//->resampler);
//source->
//resampler = NULL;
//source->
//resample_offset = 0;
//
//if (source->sample_info.samples_per_sec == obs_info->
//samples_per_sec &&
//   source
//->sample_info.format == obs_info->
//format &&
//   source
//->sample_info.speakers == obs_info->speakers) {
//source->
//audio_failed = false;
//return;
//}
//
//source->
//resampler =
//audio_resampler_create(&output_info, &source->sample_info);
//
//source->
//audio_failed = source->resampler == NULL;
//if (source->resampler == NULL)
//blog(LOG_ERROR,
//"creation of resampler failed");
//}
//
//static void copy_audio_m_data(obs_source_t * source,
//const uint8_t * const m_data[],
//   uint32_t
//frames,
//uint64_t ts
//)
//{
//size_t planes = audio_output_get_planes(obs->audio.audio);
//size_t blocksize = audio_output_get_block_size(obs->audio.audio);
//size_t size = (size_t) frames * blocksize;
//bool resize = source->audio_storage_size < size;
//
//source->audio_m_data.
//frames = frames;
//source->audio_m_data.
//timestamp = ts;
//
//for (
//size_t i = 0;
//i<planes;
//i++) {
///* ensure audio storage capacity */
//if (resize) {
//bfree(source
//->audio_m_data.m_data[i]);
//source->audio_m_data.m_data[i] =
//::system()->m_pheapmanagement->memory(::heap::e_memory_secondary)->aligned_allocate(size, alignment);
//}
//
//memory_copy(source
//->audio_m_data.m_data[i], m_data[i], size);
//}
//
//if (resize)
//source->
//audio_storage_size = size;
//}
//
///* TODO: SSE optimization */
//static void downmix_to_mono_planar(struct obs_source * source, uint32_t frames)
//{
//   size_t channels = audio_output_get_channels(obs->audio.audio);
//   const float channels_i = 1.0f / (float) channels;
//   float ** m_data = (float **) source->audio_m_data.m_data;
//
//   for (size_t channel = 1; channel < channels; channel++)
//   {
//      for (uint32_t frame = 0; frame < frames; frame++)
//         m_data[0][frame] += m_data[channel][frame];
//   }
//
//   for (uint32_t frame = 0; frame < frames; frame++)
//      m_data[0][frame] *= channels_i;
//
//   for (size_t channel = 1; channel < channels; channel++)
//   {
//      for (uint32_t frame = 0; frame < frames; frame++)
//         m_data[channel][frame] = m_data[0][frame];
//   }
//}
//
//static void process_audio_balancing(struct obs_source * source, uint32_t frames,
//                                    float balance, enum obs_balance_type type)
//{
//   float ** m_data = (float **) source->audio_m_data.m_data;
//
//   switch (type)
//   {
//      case OBS_BALANCE_TYPE_SINE_LAW:
//         for (uint32_t frame = 0; frame < frames; frame++)
//         {
//            m_data[0][frame] = m_data[0][frame] *
//                             sinf((1.0f - balance) * (M_PI / 2.0f));
//            m_data[1][frame] =
//               m_data[1][frame] * sinf(balance * (M_PI / 2.0f));
//         }
//         break;
//      case OBS_BALANCE_TYPE_SQUARE_LAW:
//         for (uint32_t frame = 0; frame < frames; frame++)
//         {
//            m_data[0][frame] = m_data[0][frame] * sqrtf(1.0f - balance);
//            m_data[1][frame] = m_data[1][frame] * sqrtf(balance);
//         }
//         break;
//      case OBS_BALANCE_TYPE_LINEAR:
//         for (uint32_t frame = 0; frame < frames; frame++)
//         {
//            m_data[0][frame] = m_data[0][frame] * (1.0f - balance);
//            m_data[1][frame] = m_data[1][frame] * balance;
//         }
//         break;
//      default:
//         break;
//   }
//}
//
///* resamples/remixes ___new audio to the designated main audio output format */
//static void process_audio(obs_source_t * source,
//const struct obs_source_audio * audio
//)
//{
//uint32_t frames = audio->frames;
//bool mono_output;
//
//if (source->sample_info.samples_per_sec != audio->samples_per_sec ||
//source->sample_info.format != audio->format ||
//source->sample_info.speakers != audio->speakers)
//reset_resampler(source, audio
//);
//
//if (source->audio_failed)
//return;
//
//if (source->resampler) {
//uint8_t * output[MAX_AV_PLANES];
//
//memory_set(output,
//0, sizeof(output));
//
//audio_resampler_resample(source
//->resampler, output, &frames,
//&source->resample_offset, audio->m_data,
//audio->frames);
//
//copy_audio_m_data(source,
//(const uint8_t *const *)output, frames,
//audio->timestamp);
//} else {
//copy_audio_m_data(source, audio
//->m_data, audio->frames,
//audio->timestamp);
//}
//
//mono_output = audio_output_get_channels(obs->audio.audio) == 1;
//
//if (!
//mono_output && source
//->sample_info.speakers ==
//SPEAKERS_STEREO &&
//(source
//->balance > 0.51f || source->balance < 0.49f)) {
//process_audio_balancing(source, frames, source
//->balance,
//OBS_BALANCE_TYPE_SINE_LAW);
//}
//
//if (!
//mono_output && (source
//->
//flags & OBS_SOURCE_FLAG_FORCE_MONO
//) != 0)
//downmix_to_mono_planar(source, frames
//);
//}
//
//void obs_source_output_audio(obs_source_t * source,
//const struct obs_source_audio * audio_in
//)
//{
//struct obs_audio_m_data * output;
//
//if (!
//obs_source_valid(source,
//"obs_source_output_audio"))
//return;
//if (
//destroying(source)
//)
//return;
//if (!
//obs_ptr_valid(audio_in,
//"obs_source_output_audio"))
//return;
//
///* sets unused m_data pointers to NULL automatically because apparently
//	 * some filter plugins aren't checking the actual channel count, and
//	 * instead are checking to see whether the pointer is non-zero. */
//struct obs_source_audio audio = *audio_in;
//size_t channels = get_audio_planes(audio.format, audio.speakers);
//for (
//size_t i = channels;
//i<MAX_AUDIO_CHANNELS;
//i++)
//audio.m_data[i] =
//NULL;
//
//process_audio(source, & audio
//);
//
//pthread_mutex_lock(& source
//->filter_mutex);
//output = filter_async_audio(source, &source->audio_m_data);
//
//if (output) {
//struct audio_m_data m_data;
//
//for (
//int i = 0;
//i<MAX_AV_PLANES;
//i++)
//m_data.m_data[i] = output->m_data[i];
//
//m_data.
//frames = output->frames;
//m_data.
//timestamp = output->timestamp;
//
//pthread_mutex_lock(& source
//->audio_mutex);
//source_output_audio_m_data(source, & m_data
//);
//pthread_mutex_unlock(& source
//->audio_mutex);
//}
//
//pthread_mutex_unlock(& source
//->filter_mutex);
//}
//
//void remove_async_frame(obs_source_t * source,
//frame * frame
//)
//{
//if (frame)
//m_
//prev_frame = false;
//
//for (
//size_t i = 0;
//i<source->async_cache.
//num;
//i++) {
//struct async_frame * f = &source->async_cache.array[i];
//
//if (f->frame == frame) {
//f->
//used = false;
//break;
//}
//}
//}
//
///* #define DEBUG_ASYNC_FRAMES 1 */
//
//static bool ready_async_frame(obs_source_t * source, uint64_t
//sys_time)
//{
//frame * next_frame = source->async_frames.array[0];
//frame * frame = NULL;
//uint64_t sys_offset = sys_time - source->last_sys_timestamp;
//uint64_t frame_time = next_m_timestamp;
//uint64_t frame_offset = 0;
//
//if (source->async_unbuffered) {
//while (source->async_frames.num > 1) {
//da_erase(source
//->async_frames, 0);
//remove_async_frame(source, next_frame
//);
//next_frame = source->async_frames.array[0];
//}
//
//source->
//last_frame_ts = next_m_timestamp;
//return true;
//}
//
//#if DEBUG_ASYNC_FRAMES
//blog(LOG_DEBUG,
//        "source->last_frame_ts: %llu, frame_time: %llu, "
//        "sys_offset: %llu, frame_offset: %llu, "
//        "number of frames: %lu",
//        source->last_frame_ts, frame_time, sys_offset,
//        frame_time - source->last_frame_ts,
//        (unsigned long)source->async_frames.num);
//#endif
//
///* account for timestamp invalidation */
//if (
//frame_out_of_bounds(source, frame_time
//)) {
//#if DEBUG_ASYNC_FRAMES
//blog(LOG_DEBUG, "timing jump");
//#endif
//source->
//last_frame_ts = next_m_timestamp;
//return true;
//} else {
//frame_offset = frame_time - source->last_frame_ts;
//source->last_frame_ts +=
//sys_offset;
//}
//
//while (source->last_frame_ts > next_m_timestamp) {
//
///* this tries to reduce the needless frame duplication, also
//		 * helps smooth out async rendering to frame boundaries.  In
//		 * other words, tries to keep the framerate as smooth as
//		 * possible */
//if ((source->last_frame_ts - next_m_timestamp) < 2000000)
//break;
//
//if (frame)
//da_erase(source
//->async_frames, 0);
//
//#if DEBUG_ASYNC_FRAMES
//blog(LOG_DEBUG,
//           "___new frame, "
//           "source->last_frame_ts: %llu, "
//           "next_m_timestamp: %llu",
//           source->last_frame_ts, next_m_timestamp);
//#endif
//
//remove_async_frame(source, frame
//);
//
//if (source->async_frames.num == 1)
//return true;
//
//frame = next_frame;
//next_frame = source->async_frames.array[1];
//
///* more timestamp checking and compensating */
//if ((next_m_timestamp - frame_time) > MAX_TS_VAR) {
//#if DEBUG_ASYNC_FRAMES
//blog(LOG_DEBUG, "timing jump");
//#endif
//source->
//last_frame_ts =
//next_m_timestamp - frame_offset;
//}
//
//frame_time = next_m_timestamp;
//frame_offset = frame_time - source->last_frame_ts;
//}
//
//#if DEBUG_ASYNC_FRAMES
//if (!frame)
//      blog(LOG_DEBUG, "no frame!");
//#endif
//
//return frame !=
//NULL;
//}
//
//static inline frame * get_closest_frame(obs_source_t * source,
//                                                          uint64_t
//sys_time)
//{
//if (!source->async_frames.num)
//return
//NULL;
//
//if (!source->last_frame_ts ||
//ready_async_frame(source, sys_time
//)) {
//frame * frame = source->async_frames.array[0];
//da_erase(source
//->async_frames, 0);
//
//if (!source->last_frame_ts)
//source->
//last_frame_ts = m_timestamp;
//
//return
//frame;
//}
//
//return
//NULL;
//}
//
///*
// * Ensures that cached frames are displayed on time.  If multiple frames
// * were cached between renders, then releases the unnecessary frames and uses
// * the frame with the closest timing to ensure sync.  Also ensures that timing
// * with audio is synchronized.
// */
//frame * obs_source_get_frame(obs_source_t * source)
//{
//   frame * frame = NULL;
//
//   if (!obs_source_valid(source, "obs_source_get_frame"))
//      return NULL;
//
//   pthread_mutex_lock(&source->async_mutex);
//
//   frame = source->cur_async_frame;
//   source->cur_async_frame = NULL;
//
//   if (frame)
//   {
//      os_atomic_inc_long(&m_refs);
//   }
//
//   pthread_mutex_unlock(&source->async_mutex);
//
//   return frame;
//}
//
//void obs_source_release_frame(obs_source_t * source,
//frame * frame
//)
//{
//if (!frame)
//return;
//
//if (!source) {
//video_frame_destroy(frame);
//} else {
//pthread_mutex_lock(& source
//->async_mutex);
//
//if (
//os_atomic_dec_long(& frame
//->refs) == 0)
//video_frame_destroy(frame);
//else
//remove_async_frame(source, frame
//);
//
//pthread_mutex_unlock(& source
//->async_mutex);
//}
//}
//
//const char * obs_source_get_name(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_name")
//          ? source->context.name
//          : NULL;
//}
//
//void obs_source_set_name(obs_source_t * source,
//const char * name
//)
//{
//if (!
//obs_source_valid(source,
//"obs_source_set_name"))
//return;
//
//if (!name || !*name || !source->context.name ||
//strcmp(name, source
//->context.name) != 0) {
//struct callm_data m_data;
//char * prev_name = bstrdup(source->context.name);
//obs_context_m_data_setname(& source
//->context, name);
//
//callm_data_init(& m_data);
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_string(& m_data,
//"new_name", source->context.name);
//callm_data_set_string(& m_data,
//"prev_name", prev_name);
//if (!source->context.private)
//signal_handler_signal(obs
//->signals, "source_rename",
//&m_data);
//signal_handler_signal(source
//->context.signals, "rename", &m_data);
//callm_data_free(& m_data);
//bfree(prev_name);
//}
//}
//
//enum obs_source_type obs_source_get_type(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_type")
//          ? source->info.type
//          : OBS_SOURCE_TYPE_INPUT;
//}
//
//const char * obs_source_get_id(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_id") ? source->info.id
//                                                        : NULL;
//}
//
//const char * obs_source_get_unversioned_id(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_unversioned_id")
//          ? source->info.unversioned_id
//          : NULL;
//}
//
//static inline void render_filter_bypass(obs_source_t * target,
//                                        gs_effect_t * effect,
//const char * tech_name
//)
//{
//gs_technique_t * tech = gs_effect_get_technique(effect, tech_name);
//size_t passes, i;
//
//passes = gs_technique_begin(tech);
//for (
//i = 0;
//i<passes;
//i++) {
//gs_technique_begin_pass(tech, i
//);
//obs_source_video_render(target);
//gs_technique_end_pass(tech);
//}
//gs_technique_end(tech);
//}
//
//static inline void render_filter_tex(gs_texture_t * tex, gs_effect_t * effect,
//                                     uint32_t width, uint32_t height,
//                                     const char * tech_name)
//{
//   gs_technique_t * tech = gs_effect_get_technique(effect, tech_name);
//   gs_eparam_t * image = gs_effect_get_param_by_name(effect, "image");
//   size_t passes, i;
//
//   const bool linear_srgb = gs_get_linear_srgb();
//
//   const bool previous = gs_framebuffer_srgb_enabled();
//   gs_enable_framebuffer_srgb(linear_srgb);
//
//   if (linear_srgb)
//      gs_effect_set_texture_srgb(image, tex);
//   else
//      gs_effect_set_texture(image, tex);
//
//   passes = gs_technique_begin(tech);
//   for (i = 0; i < passes; i++)
//   {
//      gs_technique_begin_pass(tech, i);
//      gs_draw_sprite(tex, 0, width, height);
//      gs_technique_end_pass(tech);
//   }
//   gs_technique_end(tech);
//
//   gs_enable_framebuffer_srgb(previous);
//}
//
//static inline bool can_bypass(obs_source_t * target, obs_source_t * parent,
//                              uint32_t
//filter_flags,
//uint32_t parent_flags,
//enum obs_allow_direct_render allow_direct
//)
//{
//return (target == parent) &&
//(allow_direct == OBS_ALLOW_DIRECT_RENDERING) &&
//((
//parent_flags & OBS_SOURCE_CUSTOM_DRAW
//) == 0) &&
//((
//parent_flags & OBS_SOURCE_ASYNC
//) == 0) &&
//((
//filter_flags & OBS_SOURCE_SRGB
//) ==
//(
//parent_flags & OBS_SOURCE_SRGB
//));
//}
//
//bool obs_source_process_filter_begin(obs_source_t * filter,
//enum gs_color_format format,
//enum obs_allow_direct_render allow_direct
//)
//{
//obs_source_t * target, * parent;
//uint32_t filter_flags, parent_flags;
//int cx, cy;
//
//if (!
//obs_ptr_valid(filter,
//"obs_source_process_filter_begin"))
//return false;
//
//target = obs_filter_get_target(filter);
//parent = obs_filter_get_parent(filter);
//
//if (!target) {
//blog(LOG_INFO,
//"filter '%s' being processed with no target!",
//filter->context.name);
//return false;
//}
//if (!parent) {
//blog(LOG_INFO,
//"filter '%s' being processed with no parent!",
//filter->context.name);
//return false;
//}
//
//filter_flags = filter->info.output_flags;
//parent_flags = parent->info.output_flags;
//cx = get_base_width(target);
//cy = get_base_height(target);
//
//filter->
//allow_direct = allow_direct;
//
///* if the parent does not use any custom effects, and this is the last
//	 * filter in the chain for the parent, then render the parent directly
//	 * using the filter effect instead of rendering to texture to reduce
//	 * the total number of passes */
//if (
//can_bypass(target, parent, filter_flags, parent_flags,
//   allow_direct
//)) {
//return true;
//}
//
//if (!cx || !cy) {
//obs_source_skip_video_filter(filter);
//return false;
//}
//
//if (!filter->filter_texrender)
//filter->
//filter_texrender =
//gs_texrender_create(format, GS_ZS_NONE);
//
//if (
//gs_texrender_begin(filter
//->filter_texrender, cx, cy)) {
//gs_blend_state_push();
//
//gs_blend_function_separate(GS_BLEND_SRCALPHA,
//   GS_BLEND_INVSRCALPHA, GS_BLEND_ONE,
//   GS_BLEND_INVSRCALPHA
//);
//
//bool custom_draw = (parent_flags & OBS_SOURCE_CUSTOM_DRAW) != 0;
//bool async = (parent_flags & OBS_SOURCE_ASYNC) != 0;
//struct vec4 clear_color;
//
//vec4_zero(& clear_color);
//gs_clear(GS_CLEAR_COLOR, & clear_color,
//0.0f, 0);
//gs_ortho(0.0f, (float)cx, 0.0f, (float)cy, -100.0f, 100.0f);
//
//if (target == parent && !custom_draw && !async)
//obs_source_default_render(target);
//else
//obs_source_video_render(target);
//
//gs_blend_state_pop();
//
//gs_texrender_end(filter
//->filter_texrender);
//}
//return true;
//}
//
//void obs_source_process_filter_tech_end(obs_source_t * filter,
//                                        gs_effect_t * effect, uint32_t
//width,
//uint32_t height,
//const char * tech_name
//)
//{
//obs_source_t * target, * parent;
//gs_texture_t * texture;
//uint32_t filter_flags, parent_flags;
//
//if (!filter)
//return;
//
//target = obs_filter_get_target(filter);
//parent = obs_filter_get_parent(filter);
//
//if (!target || !parent)
//return;
//
//filter_flags = filter->info.output_flags;
//parent_flags = parent->info.output_flags;
//
//const bool previous =
//   gs_set_linear_srgb((filter_flags & OBS_SOURCE_SRGB) != 0);
//
//const char * tech = tech_name ? tech_name : "Draw";
//
//if (
//can_bypass(target, parent, filter_flags, parent_flags,
//   filter
//->allow_direct)) {
//render_filter_bypass(target, effect, tech
//);
//} else {
//texture = gs_texrender_get_texture(filter->filter_texrender);
//if (texture) {
//render_filter_tex(texture, effect, width, height, tech
//);
//}
//}
//
//gs_set_linear_srgb(previous);
//}
//
//void obs_source_process_filter_end(obs_source_t * filter, gs_effect_t * effect,
//                                   uint32_t
//width,
//uint32_t height
//)
//{
//if (!
//obs_ptr_valid(filter,
//"obs_source_process_filter_end"))
//return;
//
//obs_source_process_filter_tech_end(filter, effect, width, height,
//"Draw");
//}
//
//void obs_source_skip_video_filter(obs_source_t * filter)
//{
//   obs_source_t * target, *parent;
//   bool custom_draw, async;
//   uint32_t parent_flags;
//
//   if (!obs_ptr_valid(filter, "obs_source_skip_video_filter"))
//      return;
//
//   target = obs_filter_get_target(filter);
//   parent = obs_filter_get_parent(filter);
//   parent_flags = parent->info.output_flags;
//   custom_draw = (parent_flags & OBS_SOURCE_CUSTOM_DRAW) != 0;
//   async = (parent_flags & OBS_SOURCE_ASYNC) != 0;
//
//   if (target == parent)
//   {
//      if (!custom_draw && !async)
//         obs_source_default_render(target);
//      else if (target->info.video_render)
//         obs_source_main_render(target);
//      else if (deinterlacing_enabled(target))
//         deinterlace_render(target);
//      else
//         obs_source_render_async_video(target);
//
//   }
//   else
//   {
//      obs_source_video_render(target);
//   }
//}
//
//signal_handler_t * obs_source_get_signal_handler(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_signal_handler")
//          ? source->context.signals
//          : NULL;
//}
//
//proc_handler_t * obs_source_get_proc_handler(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_proc_handler")
//          ? source->context.procs
//          : NULL;
//}
//
//void obs_source_set_volume(obs_source_t * source, float
//volume)
//{
//if (
//obs_source_valid(source,
//"obs_source_set_volume")) {
//struct audio_action action = {.timestamp = os_gettime_ns(),
//   .type = AUDIO_ACTION_VOL,
//   .vol = volume};
//
//struct callm_data m_data;
//uint8_t stack[128];
//
//callm_data_init_fixed(& m_data, stack,
//sizeof(stack));
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_float(& m_data,
//"volume", volume);
//
//signal_handler_signal(source
//->context.signals, "volume", &m_data);
//if (!source->context.private)
//signal_handler_signal(obs
//->signals, "source_volume",
//&m_data);
//
//volume = (float) callm_data_float(&m_data, "volume");
//
//pthread_mutex_lock(& source
//->audio_actions_mutex);
//da_push_back(source
//->audio_actions, &action);
//pthread_mutex_unlock(& source
//->audio_actions_mutex);
//
//source->
//user_volume = volume;
//}
//}
//
//float obs_source_get_volume(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_volume")
//          ? source->user_volume
//          : 0.0f;
//}
//
//void obs_source_set_sync_offset(obs_source_t * source, int64_t
//offset)
//{
//if (
//obs_source_valid(source,
//"obs_source_set_sync_offset")) {
//struct callm_data m_data;
//uint8_t stack[128];
//
//callm_data_init_fixed(& m_data, stack,
//sizeof(stack));
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_int(& m_data,
//"offset", offset);
//
//signal_handler_signal(source
//->context.signals, "audio_sync",
//&m_data);
//
//source->
//sync_offset = callm_data_int(&m_data, "offset");
//}
//}
//
//int64_t obs_source_get_sync_offset(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_sync_offset")
//          ? source->sync_offset
//          : 0;
//}
//
//struct source_enum_data
//{
//   obs_source_enum_proc_t enum_callback;
//   void * param;
//};
//
//static void enum_source_active_tree_callback(obs_source_t * parent,
//                                             obs_source_t * child, void * param)
//{
//   struct source_enum_data * m_data = param;
//   bool is_transition = child->info.type == OBS_SOURCE_TYPE_TRANSITION;
//
//   if (is_transition)
//      obs_transition_enum_sources(
//         child, enum_source_active_tree_callback, param);
//   if (child->info.enum_active_sources)
//   {
//      if (child->context.m_data)
//      {
//         child->info.enum_active_sources(
//            child->context.m_data,
//            enum_source_active_tree_callback, m_data);
//      }
//   }
//
//   m_data->enum_callback(parent, child, m_data->param);
//}
//
//void obs_source_enum_active_sources(obs_source_t * source,
//                                    obs_source_enum_proc_t
//enum_callback,
//void * param
//)
//{
//bool is_transition;
//if (!
//m_data_valid(source,
//"obs_source_enum_active_sources"))
//return;
//
//is_transition = source->info.type == OBS_SOURCE_TYPE_TRANSITION;
//if (!is_transition && !source->info.enum_active_sources)
//return;
//
//source = obs_source_get_ref(source);
//if (!
//m_data_valid(source,
//"obs_source_enum_active_sources"))
//return;
//
//if (is_transition)
//obs_transition_enum_sources(source, enum_callback, param
//);
//if (source->info.enum_active_sources)
//source->info.
//enum_active_sources(source
//->context.m_data,
//enum_callback, param);
//
//obs_source_release(source);
//}
//
//void obs_source_enum_active_tree(obs_source_t * source,
//                                 obs_source_enum_proc_t
//enum_callback,
//void * param
//)
//{
//struct source_enum_data m_data = {enum_callback, param};
//bool is_transition;
//
//if (!
//m_data_valid(source,
//"obs_source_enum_active_tree"))
//return;
//
//is_transition = source->info.type == OBS_SOURCE_TYPE_TRANSITION;
//if (!is_transition && !source->info.enum_active_sources)
//return;
//
//source = obs_source_get_ref(source);
//if (!
//m_data_valid(source,
//"obs_source_enum_active_tree"))
//return;
//
//if (source->info.type == OBS_SOURCE_TYPE_TRANSITION)
//obs_transition_enum_sources(
//   source, enum_source_active_tree_callback, & m_data
//);
//if (source->info.enum_active_sources)
//source->info.
//enum_active_sources(
//   source
//->context.m_data, enum_source_active_tree_callback,
//&m_data);
//
//obs_source_release(source);
//}
//
//static void enum_source_full_tree_callback(obs_source_t * parent,
//                                           obs_source_t * child, void * param)
//{
//   struct source_enum_data * m_data = param;
//   bool is_transition = child->info.type == OBS_SOURCE_TYPE_TRANSITION;
//
//   if (is_transition)
//      obs_transition_enum_sources(
//         child, enum_source_full_tree_callback, param);
//   if (child->info.enum_all_sources)
//   {
//      if (child->context.m_data)
//      {
//         child->info.enum_all_sources(
//            child->context.m_data,
//            enum_source_full_tree_callback, m_data);
//      }
//   }
//   else if (child->info.enum_active_sources)
//   {
//      if (child->context.m_data)
//      {
//         child->info.enum_active_sources(
//            child->context.m_data,
//            enum_source_full_tree_callback, m_data);
//      }
//   }
//
//   m_data->enum_callback(parent, child, m_data->param);
//}
//
//void obs_source_enum_full_tree(obs_source_t * source,
//                               obs_source_enum_proc_t
//enum_callback,
//void * param
//)
//{
//struct source_enum_data m_data = {enum_callback, param};
//bool is_transition;
//
//if (!
//m_data_valid(source,
//"obs_source_enum_full_tree"))
//return;
//
//is_transition = source->info.type == OBS_SOURCE_TYPE_TRANSITION;
//if (!is_transition && !source->info.enum_active_sources)
//return;
//
//source = obs_source_get_ref(source);
//if (!
//m_data_valid(source,
//"obs_source_enum_full_tree"))
//return;
//
//if (source->info.type == OBS_SOURCE_TYPE_TRANSITION)
//obs_transition_enum_sources(
//   source, enum_source_full_tree_callback, & m_data
//);
//
//if (source->info.enum_all_sources) {
//source->info.
//enum_all_sources(source
//->context.m_data,
//enum_source_full_tree_callback,
//&m_data);
//
//} else if (source->info.enum_active_sources) {
//source->info.
//enum_active_sources(source
//->context.m_data,
//enum_source_full_tree_callback,
//&m_data);
//}
//
//obs_source_release(source);
//}
//
//struct descendant_info
//{
//   bool exists;
//   obs_source_t * target;
//};
//
//static void check_descendant(obs_source_t * parent, obs_source_t * child,
//                             void * param)
//{
//   struct descendant_info * info = param;
//   if (child == info->target || parent == info->target)
//      info->exists = true;
//}
//
//bool obs_source_add_active_child(obs_source_t * parent, obs_source_t * child)
//{
//   struct descendant_info info = {false, parent};
//
//   if (!obs_ptr_valid(parent, "obs_source_add_active_child"))
//      return false;
//   if (!obs_ptr_valid(child, "obs_source_add_active_child"))
//      return false;
//   if (parent == child)
//   {
//      blog(LOG_WARNING, "obs_source_add_active_child: "
//                        "parent == child");
//      return false;
//   }
//
//   obs_source_enum_full_tree(child, check_descendant, &info);
//   if (info.exists)
//      return false;
//
//   for (int i = 0; i < parent->show_refs; i++)
//   {
//      enum view_type type;
//      type = (i < parent->activate_refs) ? MAIN_VIEW : AUX_VIEW;
//      obs_source_activate(child, type);
//   }
//
//   return true;
//}
//
//void obs_source_remove_active_child(obs_source_t * parent, obs_source_t * child)
//{
//   if (!obs_ptr_valid(parent, "obs_source_remove_active_child"))
//      return;
//   if (!obs_ptr_valid(child, "obs_source_remove_active_child"))
//      return;
//
//   for (int i = 0; i < parent->show_refs; i++)
//   {
//      enum view_type type;
//      type = (i < parent->activate_refs) ? MAIN_VIEW : AUX_VIEW;
//      obs_source_deactivate(child, type);
//   }
//}
//
//void obs_source_save(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_save"))
//      return;
//
//   obs_source_dosignal(source, "source_save", "save");
//
//   if (source->info.save)
//      source->info.save(source->context.m_data,
//                        source->context.settings);
//}
//
//void obs_source_load(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_load"))
//      return;
//   if (source->info.load)
//      source->info.load(source->context.m_data,
//                        source->context.settings);
//
//   obs_source_dosignal(source, "source_load", "load");
//}
//
//void obs_source_load2(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_load2"))
//      return;
//
//   obs_source_load(source);
//
//   for (size_t i = source->filters.num; i > 0; i--)
//   {
//      obs_source_t * filter = source->filters.array[i - 1];
//      obs_source_load(filter);
//   }
//}
//
//bool obs_source_active(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_active")
//          ? source->activate_refs != 0
//          : false;
//}
//
//bool obs_source_showing(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_showing")
//          ? source->show_refs != 0
//          : false;
//}
//
//static inline void signal_flags_updated(obs_source_t * source)
//{
//   struct callm_data m_data;
//   uint8_t stack[128];
//
//   callm_data_init_fixed(&m_data, stack, sizeof(stack));
//   callm_data_set_ptr(&m_data, "source", source);
//   callm_data_set_int(&m_data, "flags", source->flags);
//
//   signal_handler_signal(source->context.signals, "update_flags", &m_data);
//}
//
//void obs_source_set_flags(obs_source_t * source, uint32_t
//flags)
//{
//if (!
//obs_source_valid(source,
//"obs_source_set_flags"))
//return;
//
//if (flags != source->flags) {
//source->
//flags = flags;
//signal_flags_updated(source);
//}
//}
//
//void obs_source_set_default_flags(obs_source_t * source, uint32_t
//flags)
//{
//if (!
//obs_source_valid(source,
//"obs_source_set_default_flags"))
//return;
//
//source->
//default_flags = flags;
//}
//
//uint32_t obs_source_get_flags(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_flags") ? source->flags
//                                                           : 0;
//}
//
//void obs_source_set_audio_mixers(obs_source_t * source, uint32_t
//mixers)
//{
//struct callm_data m_data;
//uint8_t stack[128];
//
//if (!
//obs_source_valid(source,
//"obs_source_set_audio_mixers"))
//return;
//if ((source->info.
//output_flags & OBS_SOURCE_AUDIO
//) == 0)
//return;
//
//if (source->audio_mixers == mixers)
//return;
//
//callm_data_init_fixed(& m_data, stack,
//sizeof(stack));
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_int(& m_data,
//"mixers", mixers);
//
//signal_handler_signal(source
//->context.signals, "audio_mixers", &m_data);
//
//mixers = (uint32_t) callm_data_int(&m_data, "mixers");
//
//source->
//audio_mixers = mixers;
//}
//
//uint32_t obs_source_get_audio_mixers(const obs_source_t * source)
//{
//   if (!obs_source_valid(source, "obs_source_get_audio_mixers"))
//      return 0;
//   if ((source->info.output_flags & OBS_SOURCE_AUDIO) == 0)
//      return 0;
//
//   return source->audio_mixers;
//}
//
//void obs_source_draw_set_color_matrix(const struct matrix4 * color_matrix,
//                                      const struct vec3 * color_range_min,
//                                      const struct vec3 * color_range_max)
//{
//   struct vec3 color_range_min_def;
//   struct vec3 color_range_max_def;
//
//   vec3_set(&color_range_min_def, 0.0f, 0.0f, 0.0f);
//   vec3_set(&color_range_max_def, 1.0f, 1.0f, 1.0f);
//
//   gs_effect_t * effect = gs_get_effect();
//   gs_eparam_t * matrix;
//   gs_eparam_t * range_min;
//   gs_eparam_t * range_max;
//
//   if (!effect)
//   {
//      blog(LOG_WARNING, "obs_source_draw_set_color_matrix: no "
//                        "active effect!");
//      return;
//   }
//
//   if (!obs_ptr_valid(color_matrix, "obs_source_draw_set_color_matrix"))
//      return;
//
//   if (!color_range_min)
//      color_range_min = &color_range_min_def;
//   if (!color_range_max)
//      color_range_max = &color_range_max_def;
//
//   matrix = gs_effect_get_param_by_name(effect, "color_matrix");
//   range_min = gs_effect_get_param_by_name(effect, "color_range_min");
//   range_max = gs_effect_get_param_by_name(effect, "color_range_max");
//
//   gs_effect_set_matrix4(matrix, color_matrix);
//   gs_effect_set_val(range_min, color_range_min, sizeof(float) * 3);
//   gs_effect_set_val(range_max, color_range_max, sizeof(float) * 3);
//}
//
//void obs_source_draw(gs_texture_t * texture, int x, int y, uint32_t cx,
//                     uint32_t cy, bool flip)
//{
//   if (!obs_ptr_valid(texture, "obs_source_draw"))
//      return;
//
//   gs_effect_t * effect = gs_get_effect();
//   if (!effect)
//   {
//      blog(LOG_WARNING, "obs_source_draw: no active effect!");
//      return;
//   }
//
//   const bool linear_srgb = gs_get_linear_srgb();
//
//   const bool previous = gs_framebuffer_srgb_enabled();
//   gs_enable_framebuffer_srgb(linear_srgb);
//
//   gs_eparam_t * image = gs_effect_get_param_by_name(effect, "image");
//   if (linear_srgb)
//      gs_effect_set_texture_srgb(image, texture);
//   else
//      gs_effect_set_texture(image, texture);
//
//   const bool change_pos = (x != 0 || y != 0);
//   if (change_pos)
//   {
//      gs_matrix_push();
//      gs_matrix_translate3f((float) x, (float) y, 0.0f);
//   }
//
//   gs_draw_sprite(texture, flip ? GS_FLIP_V : 0, cx, cy);
//
//   if (change_pos)
//      gs_matrix_pop();
//
//   gs_enable_framebuffer_srgb(previous);
//}
//
//void obs_source_inc_showing(obs_source_t * source)
//{
//   if (obs_source_valid(source, "obs_source_inc_showing"))
//      obs_source_activate(source, AUX_VIEW);
//}
//
//void obs_source_inc_active(obs_source_t * source)
//{
//   if (obs_source_valid(source, "obs_source_inc_active"))
//      obs_source_activate(source, MAIN_VIEW);
//}
//
//void obs_source_dec_showing(obs_source_t * source)
//{
//   if (obs_source_valid(source, "obs_source_dec_showing"))
//      obs_source_deactivate(source, AUX_VIEW);
//}
//
//void obs_source_dec_active(obs_source_t * source)
//{
//   if (obs_source_valid(source, "obs_source_dec_active"))
//      obs_source_deactivate(source, MAIN_VIEW);
//}
//
//void obs_source_enum_filters(obs_source_t * source,
//                             obs_source_enum_proc_t
//callback,
//void * param
//)
//{
//if (!
//obs_source_valid(source,
//"obs_source_enum_filters"))
//return;
//if (!
//obs_ptr_valid(callback,
//"obs_source_enum_filters"))
//return;
//
//pthread_mutex_lock(& source
//->filter_mutex);
//
//for (
//size_t i = source->filters.num;
//i > 0; i--) {
//struct obs_source * filter = source->filters.array[i - 1];
//callback(source, filter, param
//);
//}
//
//pthread_mutex_unlock(& source
//->filter_mutex);
//}
//
//void obs_source_set_hidden(obs_source_t * source, bool
//hidden)
//{
//source->
//temp_removed = hidden;
//}
//
//bool obs_source_is_hidden(obs_source_t * source)
//{
//   return source->temp_removed;
//}
//
//obs_source_t * obs_source_get_filter_by_name(obs_source_t * source,
//const char * name
//)
//{
//obs_source_t * filter = NULL;
//
//if (!
//obs_source_valid(source,
//"obs_source_get_filter_by_name"))
//return
//NULL;
//if (!
//obs_ptr_valid(name,
//"obs_source_get_filter_by_name"))
//return
//NULL;
//
//pthread_mutex_lock(& source
//->filter_mutex);
//
//for (
//size_t i = 0;
//i<source->filters.
//num;
//i++) {
//struct obs_source * cur_filter = source->filters.array[i];
//if (
//strcmp(cur_filter
//->context.name, name) == 0) {
//filter = obs_source_get_ref(cur_filter);
//break;
//}
//}
//
//pthread_mutex_unlock(& source
//->filter_mutex);
//
//return
//filter;
//}
//
//size_t obs_source_filter_count(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_filter_count")
//          ? source->filters.num
//          : 0;
//}
//
//bool obs_source_enabled(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_enabled") ? source->enabled
//                                                         : false;
//}
//
//void obs_source_set_enabled(obs_source_t * source, bool
//enabled)
//{
//struct callm_data m_data;
//uint8_t stack[128];
//
//if (!
//obs_source_valid(source,
//"obs_source_set_enabled"))
//return;
//
//source->
//enabled = enabled;
//
//callm_data_init_fixed(& m_data, stack,
//sizeof(stack));
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_bool(& m_data,
//"enabled", enabled);
//
//signal_handler_signal(source
//->context.signals, "enable", &m_data);
//}
//
//bool obs_source_muted(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_muted") ? source->user_muted
//                                                       : false;
//}
//
//void obs_source_set_muted(obs_source_t * source, bool
//muted)
//{
//struct callm_data m_data;
//uint8_t stack[128];
//struct audio_action action = {.timestamp = os_gettime_ns(),
//   .type = AUDIO_ACTION_MUTE,
//   .set = muted};
//
//if (!
//obs_source_valid(source,
//"obs_source_set_muted"))
//return;
//
//source->
//user_muted = muted;
//
//callm_data_init_fixed(& m_data, stack,
//sizeof(stack));
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_bool(& m_data,
//"muted", muted);
//
//signal_handler_signal(source
//->context.signals, "mute", &m_data);
//
//pthread_mutex_lock(& source
//->audio_actions_mutex);
//da_push_back(source
//->audio_actions, &action);
//pthread_mutex_unlock(& source
//->audio_actions_mutex);
//}
//
//static void source_signal_push_to_changed(obs_source_t * source,
//const char * signal,
//bool enabled
//)
//{
//struct callm_data m_data;
//uint8_t stack[128];
//
//callm_data_init_fixed(& m_data, stack,
//sizeof(stack));
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_bool(& m_data,
//"enabled", enabled);
//
//signal_handler_signal(source
//->context.signals, signal, &m_data);
//}
//
//static void source_signal_push_to_delay(obs_source_t * source,
//const char * signal, uint64_t
//delay)
//{
//struct callm_data m_data;
//uint8_t stack[128];
//
//callm_data_init_fixed(& m_data, stack,
//sizeof(stack));
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_int(& m_data,
//"delay", delay);
//
//signal_handler_signal(source
//->context.signals, signal, &m_data);
//}
//
//bool obs_source_push_to_mute_enabled(obs_source_t * source)
//{
//   bool enabled;
//   if (!obs_source_valid(source, "obs_source_push_to_mute_enabled"))
//      return false;
//
//   pthread_mutex_lock(&source->audio_mutex);
//   enabled = source->push_to_mute_enabled;
//   pthread_mutex_unlock(&source->audio_mutex);
//
//   return enabled;
//}
//
//void obs_source_enable_push_to_mute(obs_source_t * source, bool
//enabled)
//{
//if (!
//obs_source_valid(source,
//"obs_source_enable_push_to_mute"))
//return;
//
//pthread_mutex_lock(& source
//->audio_mutex);
//bool changed = source->push_to_mute_enabled != enabled;
//if (
//obs_source_get_output_flags(source)
//&
//OBS_SOURCE_AUDIO && changed
//)
//blog(LOG_INFO,
//"source '%s' %s push-to-mute",
//obs_source_get_name(source),
//   enabled
//? "enabled" : "disabled");
//
//source->
//push_to_mute_enabled = enabled;
//
//if (changed)
//source_signal_push_to_changed(source,
//"push_to_mute_changed",
//enabled);
//pthread_mutex_unlock(& source
//->audio_mutex);
//}
//
//uint64_t obs_source_get_push_to_mute_delay(obs_source_t * source)
//{
//   uint64_t delay;
//   if (!obs_source_valid(source, "obs_source_get_push_to_mute_delay"))
//      return 0;
//
//   pthread_mutex_lock(&source->audio_mutex);
//   delay = source->push_to_mute_delay;
//   pthread_mutex_unlock(&source->audio_mutex);
//
//   return delay;
//}
//
//void obs_source_set_push_to_mute_delay(obs_source_t * source, uint64_t
//delay)
//{
//if (!
//obs_source_valid(source,
//"obs_source_set_push_to_mute_delay"))
//return;
//
//pthread_mutex_lock(& source
//->audio_mutex);
//source->
//push_to_mute_delay = delay;
//
//source_signal_push_to_delay(source,
//"push_to_mute_delay", delay);
//pthread_mutex_unlock(& source
//->audio_mutex);
//}
//
//bool obs_source_push_to_talk_enabled(obs_source_t * source)
//{
//   bool enabled;
//   if (!obs_source_valid(source, "obs_source_push_to_talk_enabled"))
//      return false;
//
//   pthread_mutex_lock(&source->audio_mutex);
//   enabled = source->push_to_talk_enabled;
//   pthread_mutex_unlock(&source->audio_mutex);
//
//   return enabled;
//}
//
//void obs_source_enable_push_to_talk(obs_source_t * source, bool
//enabled)
//{
//if (!
//obs_source_valid(source,
//"obs_source_enable_push_to_talk"))
//return;
//
//pthread_mutex_lock(& source
//->audio_mutex);
//bool changed = source->push_to_talk_enabled != enabled;
//if (
//obs_source_get_output_flags(source)
//&
//OBS_SOURCE_AUDIO && changed
//)
//blog(LOG_INFO,
//"source '%s' %s push-to-talk",
//obs_source_get_name(source),
//   enabled
//? "enabled" : "disabled");
//
//source->
//push_to_talk_enabled = enabled;
//
//if (changed)
//source_signal_push_to_changed(source,
//"push_to_talk_changed",
//enabled);
//pthread_mutex_unlock(& source
//->audio_mutex);
//}
//
//uint64_t obs_source_get_push_to_talk_delay(obs_source_t * source)
//{
//   uint64_t delay;
//   if (!obs_source_valid(source, "obs_source_get_push_to_talk_delay"))
//      return 0;
//
//   pthread_mutex_lock(&source->audio_mutex);
//   delay = source->push_to_talk_delay;
//   pthread_mutex_unlock(&source->audio_mutex);
//
//   return delay;
//}
//
//void obs_source_set_push_to_talk_delay(obs_source_t * source, uint64_t
//delay)
//{
//if (!
//obs_source_valid(source,
//"obs_source_set_push_to_talk_delay"))
//return;
//
//pthread_mutex_lock(& source
//->audio_mutex);
//source->
//push_to_talk_delay = delay;
//
//source_signal_push_to_delay(source,
//"push_to_talk_delay", delay);
//pthread_mutex_unlock(& source
//->audio_mutex);
//}
//
//void * obs_source_get_type_m_data(obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_type_m_data")
//          ? source->info.type_m_data
//          : NULL;
//}
//
//static float get_source_volume(obs_source_t * source, uint64_t
//os_time)
//{
//if (source->
//push_to_mute_enabled && source
//->push_to_mute_pressed)
//source->
//push_to_mute_stop_time =
//os_time + source->push_to_mute_delay * 1000000;
//
//if (source->
//push_to_talk_enabled && source
//->push_to_talk_pressed)
//source->
//push_to_talk_stop_time =
//os_time + source->push_to_talk_delay * 1000000;
//
//bool push_to_mute_active = source->push_to_mute_pressed ||
//                           os_time < source->push_to_mute_stop_time;
//bool push_to_talk_active = source->push_to_talk_pressed ||
//                           os_time < source->push_to_talk_stop_time;
//
//bool muted = !source->enabled || source->muted ||
//             (source->push_to_mute_enabled && push_to_mute_active) ||
//             (source->push_to_talk_enabled && !push_to_talk_active);
//
//if (muted ||
//close_float(source
//->volume, 0.0f, 0.0001f))
//return 0.0f;
//if (
//close_float(source
//->volume, 1.0f, 0.0001f))
//return 1.0f;
//
//return source->
//volume;
//}
//
//static inline void multiply_output_audio(obs_source_t * source, size_t
//mix,
//size_t channels,
//float vol
//)
//{
//register float * out = source->audio_output_buf[mix][0];
//register float * end = out + AUDIO_OUTPUT_FRAMES * channels;
//
//while (out<end)
//*(out++) *=
//vol;
//}
//
//static inline void multiply_vol_m_data(obs_source_t * source, size_t
//mix,
//size_t channels,
//float * vol_m_data
//)
//{
//for (
//size_t ch = 0;
//ch<channels;
//ch++) {
//register float * out = source->audio_output_buf[mix][ch];
//register float * end = out + AUDIO_OUTPUT_FRAMES;
//register float * vol = vol_m_data;
//
//while (out<end)
//*(out++) *= *(vol++);
//}
//}
//
//static inline void apply_audio_action(obs_source_t * source,
//const struct audio_action * action
//)
//{
//switch (action->type) {
//case AUDIO_ACTION_VOL:
//source->
//volume = action->vol;
//break;
//case AUDIO_ACTION_MUTE:
//source->
//muted = action->set;
//break;
//case AUDIO_ACTION_PTT:
//source->
//push_to_talk_pressed = action->set;
//break;
//case AUDIO_ACTION_PTM:
//source->
//push_to_mute_pressed = action->set;
//break;
//}
//}
//
//static void apply_audio_actions(obs_source_t * source, size_t
//channels,
//size_t sample_rate
//)
//{
//float vol_m_data[AUDIO_OUTPUT_FRAMES];
//float cur_vol = get_source_volume(source, source->audio_ts);
//size_t frame_num = 0;
//
//pthread_mutex_lock(& source
//->audio_actions_mutex);
//
//for (
//size_t i = 0;
//i<source->audio_actions.
//num;
//i++) {
//struct audio_action action = source->audio_actions.array[i];
//uint64_t timestamp = action.timestamp;
//size_t new_frame_num;
//
//if (timestamp<source->audio_ts)
//timestamp = source->audio_ts;
//
//new_frame_num = conv_time_to_frames(
//   sample_rate, timestamp - source->audio_ts);
//
//if (new_frame_num >= AUDIO_OUTPUT_FRAMES)
//break;
//
//da_erase(source
//->audio_actions, i--);
//
//apply_audio_action(source, & action
//);
//
//if (new_frame_num > frame_num) {
//for (;
//frame_num<new_frame_num;
//frame_num++)
//vol_m_data[frame_num] =
//cur_vol;
//}
//
//cur_vol = get_source_volume(source, timestamp);
//}
//
//for (;
//frame_num<AUDIO_OUTPUT_FRAMES;
//frame_num++)
//vol_m_data[frame_num] =
//cur_vol;
//
//pthread_mutex_unlock(& source
//->audio_actions_mutex);
//
//for (
//size_t mix = 0;
//mix<MAX_AUDIO_MIXES;
//mix++) {
//if ((source->audio_mixers & (1 << mix)) != 0)
//multiply_vol_m_data(source, mix, channels, vol_m_data
//);
//}
//}
//
//static void apply_audio_volume(obs_source_t * source, uint32_t
//mixers,
//size_t channels, size_t
//sample_rate)
//{
//struct audio_action action;
//bool actions_pending;
//float vol;
//
//pthread_mutex_lock(& source
//->audio_actions_mutex);
//
//actions_pending = source->audio_actions.num > 0;
//if (actions_pending)
//action = source->audio_actions.array[0];
//
//pthread_mutex_unlock(& source
//->audio_actions_mutex);
//
//if (actions_pending) {
//uint64_t time =
//   conv_frames_to_time(sample_rate, AUDIO_OUTPUT_FRAMES);
//
//if (action.timestamp < (source->audio_ts + time)) {
//apply_audio_actions(source, channels, sample_rate
//);
//return;
//}
//}
//
//vol = get_source_volume(source, source->audio_ts);
//if (vol == 1.0f)
//return;
//
//if (vol == 0.0f || mixers == 0) {
//memory_set(source
//->audio_output_buf[0][0], 0,
//AUDIO_OUTPUT_FRAMES * sizeof(float) *
//MAX_AUDIO_CHANNELS * MAX_AUDIO_MIXES
//);
//return;
//}
//
//for (
//size_t mix = 0;
//mix<MAX_AUDIO_MIXES;
//mix++) {
//uint32_t mix_and_val = (1 << mix);
//if ((source->
//audio_mixers & mix_and_val
//) != 0 &&
//(
//mixers & mix_and_val
//) != 0)
//multiply_output_audio(source, mix, channels, vol
//);
//}
//}
//
//static void custom_audio_render(obs_source_t * source, uint32_t
//mixers,
//size_t channels, size_t
//sample_rate)
//{
//struct obs_source_audio_mix audio_m_data;
//bool success;
//uint64_t ts;
//
//for (
//size_t mix = 0;
//mix<MAX_AUDIO_MIXES;
//mix++) {
//for (
//size_t ch = 0;
//ch<channels;
//ch++) {
//audio_m_data.output[mix].m_data[ch] =
//source->audio_output_buf[mix][ch];
//}
//
//if ((source->
//audio_mixers & mixers
//& (1 << mix)) != 0) {
//memory_set(source
//->audio_output_buf[mix][0], 0,
//sizeof(float) *
//AUDIO_OUTPUT_FRAMES * channels
//);
//}
//}
//
//success = source->info.audio_render(source->context.m_data, &ts,
//                                    &audio_m_data, mixers, channels,
//                                    sample_rate);
//source->
//audio_ts = success ? ts : 0;
//source->
//audio_pending = !success;
//
//if (!success || !source->audio_ts || !mixers)
//return;
//
//for (
//size_t mix = 0;
//mix<MAX_AUDIO_MIXES;
//mix++) {
//uint32_t mix_bit = 1 << mix;
//
//if ((
//mixers & mix_bit
//) == 0)
//continue;
//
//if ((source->
//audio_mixers & mix_bit
//) == 0) {
//memory_set(source
//->audio_output_buf[mix][0], 0,
//sizeof(float) *
//AUDIO_OUTPUT_FRAMES * channels
//);
//}
//}
//
//apply_audio_volume(source, mixers, channels, sample_rate
//);
//}
//
//static void audio_submix(obs_source_t * source, size_t
//channels,
//size_t sample_rate
//)
//{
//struct audio_output_m_data audio_m_data;
//struct obs_source_audio audio = {0};
//bool success;
//uint64_t ts;
//
//for (
//size_t ch = 0;
//ch<channels;
//ch++) {
//audio_m_data.m_data[ch] = source->audio_mix_buf[ch];
//}
//
//memory_set(source
//->audio_mix_buf[0], 0,
//sizeof(float) *
//AUDIO_OUTPUT_FRAMES * channels
//);
//
//success = source->info.audio_mix(source->context.m_data, &ts, &audio_m_data,
//                                 channels, sample_rate);
//
//if (!success)
//return;
//
//for (
//size_t i = 0;
//i<channels;
//i++)
//audio.m_data[i] = (const uint8_t *)audio_m_data.m_data[i];
//
//audio.
//samples_per_sec = (uint32_t) sample_rate;
//audio.
//frames = AUDIO_OUTPUT_FRAMES;
//audio.
//format = AUDIO_FORMAT_FLOAT_PLANAR;
//audio.
//speakers = (enum speaker_layout) channels;
//audio.
//timestamp = ts;
//
//obs_source_output_audio(source, & audio
//);
//}
//
//static inline void process_audio_source_tick(obs_source_t * source,
//                                             uint32_t
//mixers,
//size_t channels,
//   size_t
//sample_rate,
//size_t size
//)
//{
//bool audio_submix = !!(source->info.output_flags & OBS_SOURCE_SUBMIX);
//
//pthread_mutex_lock(& source
//->audio_buf_mutex);
//
//if (source->audio_input_buf[0].size<size) {
//source->
//audio_pending = true;
//pthread_mutex_unlock(& source
//->audio_buf_mutex);
//return;
//}
//
//for (
//size_t ch = 0;
//ch<channels;
//ch++)
//circlebuf_peek_front(& source
//->audio_input_buf[ch],
//source->audio_output_buf[0][ch], size);
//
//pthread_mutex_unlock(& source
//->audio_buf_mutex);
//
//for (
//size_t mix = 1;
//mix<MAX_AUDIO_MIXES;
//mix++) {
//uint32_t mix_and_val = (1 << mix);
//
//if (audio_submix) {
//if (mix > 1)
//break;
//
//mixers = 1;
//mix_and_val = 1;
//}
//
//if ((source->
//audio_mixers & mix_and_val
//) == 0 ||
//(
//mixers & mix_and_val
//) == 0) {
//memory_set(source
//->audio_output_buf[mix][0], 0,
//size * channels
//);
//continue;
//}
//
//for (
//size_t ch = 0;
//ch<channels;
//ch++)
//memory_copy(source
//->audio_output_buf[mix][ch],
//source->audio_output_buf[0][ch], size);
//}
//
//if (audio_submix) {
//source->
//audio_pending = false;
//return;
//}
//
//if ((source->audio_mixers & 1) == 0 || (mixers & 1) == 0)
//memory_set(source
//->audio_output_buf[0][0], 0,
//size * channels
//);
//
//apply_audio_volume(source, mixers, channels, sample_rate
//);
//source->
//audio_pending = false;
//}
//
//void obs_source_audio_render(obs_source_t * source, uint32_t
//mixers,
//size_t channels, size_t
//sample_rate,
//size_t size
//)
//{
//if (!source->audio_output_buf[0][0]) {
//source->
//audio_pending = true;
//return;
//}
//
//if (source->info.audio_render) {
//if (!source->context.m_data) {
//source->
//audio_pending = true;
//return;
//}
//custom_audio_render(source, mixers, channels, sample_rate
//);
//return;
//}
//
//if (source->info.audio_mix) {
//audio_submix(source, channels, sample_rate
//);
//}
//
//if (!source->audio_ts) {
//source->
//audio_pending = true;
//return;
//}
//
//process_audio_source_tick(source, mixers, channels, sample_rate, size
//);
//}
//
//bool obs_source_audio_pending(const obs_source_t * source)
//{
//   if (!obs_source_valid(source, "obs_source_audio_pending"))
//      return true;
//
//   return (is_composite_source(source) || is_audio_source(source))
//          ? source->audio_pending
//          : true;
//}
//
//uint64_t obs_source_get_audio_timestamp(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_audio_timestamp")
//          ? source->audio_ts
//          : 0;
//}
//
//void obs_source_get_audio_mix(const obs_source_t * source,
//                              struct obs_source_audio_mix * audio)
//{
//   if (!obs_source_valid(source, "obs_source_get_audio_mix"))
//      return;
//   if (!obs_ptr_valid(audio, "audio"))
//      return;
//
//   for (size_t mix = 0; mix < MAX_AUDIO_MIXES; mix++)
//   {
//      for (size_t ch = 0; ch < MAX_AUDIO_CHANNELS; ch++)
//      {
//         audio->output[mix].m_data[ch] =
//            source->audio_output_buf[mix][ch];
//      }
//   }
//}
//
//void obs_source_add_audio_capture_callback(obs_source_t * source,
//                                           obs_source_audio_capture_t
//callback,
//void * param
//)
//{
//struct audio_cb_info info = {callback, param};
//
//if (!
//obs_source_valid(source,
//"obs_source_add_audio_capture_callback"))
//return;
//
//pthread_mutex_lock(& source
//->audio_cb_mutex);
//da_push_back(source
//->audio_cb_list, &info);
//pthread_mutex_unlock(& source
//->audio_cb_mutex);
//}
//
//void obs_source_remove_audio_capture_callback(
//   obs_source_t * source, obs_source_audio_capture_t
//callback,
//void * param
//)
//{
//struct audio_cb_info info = {callback, param};
//
//if (!
//obs_source_valid(source,
//"obs_source_remove_audio_capture_callback"))
//return;
//
//pthread_mutex_lock(& source
//->audio_cb_mutex);
//da_erase_item(source
//->audio_cb_list, &info);
//pthread_mutex_unlock(& source
//->audio_cb_mutex);
//}
//
//void obs_source_set_monitoring_type(obs_source_t * source,
//enum obs_monitoring_type type
//)
//{
//struct callm_data m_data;
//uint8_t stack[128];
//bool was_on;
//bool now_on;
//
//if (!
//obs_source_valid(source,
//"obs_source_set_monitoring_type"))
//return;
//if (source->monitoring_type == type)
//return;
//
//callm_data_init_fixed(& m_data, stack,
//sizeof(stack));
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_int(& m_data,
//"type", type);
//
//signal_handler_signal(source
//->context.signals, "audio_monitoring",
//&m_data);
//
//was_on = source->monitoring_type != OBS_MONITORING_TYPE_NONE;
//now_on = type != OBS_MONITORING_TYPE_NONE;
//
//if (was_on != now_on) {
//if (!was_on) {
//source->
//monitor = audio_monitor_create(source);
//} else {
//audio_monitor_destroy(source
//->monitor);
//source->
//monitor = NULL;
//}
//}
//
//source->
//monitoring_type = type;
//}
//
//enum obs_monitoring_type
//obs_source_get_monitoring_type(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_monitoring_type")
//          ? source->monitoring_type
//          : OBS_MONITORING_TYPE_NONE;
//}
//
//void obs_source_set_async_unbuffered(obs_source_t * source, bool
//unbuffered)
//{
//if (!
//obs_source_valid(source,
//"obs_source_set_async_unbuffered"))
//return;
//
//source->
//async_unbuffered = unbuffered;
//}
//
//bool obs_source_async_unbuffered(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_async_unbuffered")
//          ? source->async_unbuffered
//          : false;
//}
//
//obs_m_data_t * obs_source_get_private_settings(obs_source_t * source)
//{
//   if (!obs_ptr_valid(source, "obs_source_get_private_settings"))
//      return NULL;
//
//   obs_m_data_addref(source->private_settings);
//   return source->private_settings;
//}
//
//void obs_source_set_async_decoupled(obs_source_t * source, bool
//decouple)
//{
//if (!
//obs_ptr_valid(source,
//"obs_source_set_async_decoupled"))
//return;
//
//source->
//async_decoupled = decouple;
//if (decouple) {
//pthread_mutex_lock(& source
//->audio_buf_mutex);
//source->
//timing_set = false;
//reset_audio_m_data(source,
//0);
//pthread_mutex_unlock(& source
//->audio_buf_mutex);
//}
//}
//
//bool obs_source_async_decoupled(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_async_decoupled")
//          ? source->async_decoupled
//          : false;
//}
//
///* hidden/undocumented export to allow source type redefinition for scripts */
//EXPORT void obs_enable_source_type(const char * name, bool enable)
//{
//   struct obs_source_info * info = get_source_info(name);
//   if (!info)
//      return;
//
//   if (enable)
//      info->output_flags &= ~OBS_SOURCE_CAP_DISABLED;
//   else
//      info->output_flags |= OBS_SOURCE_CAP_DISABLED;
//}
//
//enum speaker_layout obs_source_get_speaker_layout(obs_source_t * source)
//{
//   if (!obs_source_valid(source, "obs_source_get_audio_channels"))
//      return SPEAKERS_UNKNOWN;
//
//   return source->sample_info.speakers;
//}
//
//void obs_source_set_balance_value(obs_source_t * source, float
//balance)
//{
//if (
//obs_source_valid(source,
//"obs_source_set_balance_value")) {
//struct callm_data m_data;
//uint8_t stack[128];
//
//callm_data_init_fixed(& m_data, stack,
//sizeof(stack));
//callm_data_set_ptr(& m_data,
//"source", source);
//callm_data_set_float(& m_data,
//"balance", balance);
//
//signal_handler_signal(source
//->context.signals, "audio_balance",
//&m_data);
//
//source->
//balance = (float) callm_data_float(&m_data, "balance");
//}
//}
//
//float obs_source_get_balance_value(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_balance_value")
//          ? source->balance
//          : 0.5f;
//}
//
//void obs_source_set_audio_active(obs_source_t * source, bool
//active)
//{
//if (!
//obs_source_valid(source,
//"obs_source_set_audio_active"))
//return;
//
//if (
//os_atomic_set_bool(& source
//->audio_active, active) == active)
//return;
//
//if (active)
//obs_source_dosignal(source,
//"source_audio_activate",
//"audio_activate");
//else
//obs_source_dosignal(source,
//"source_audio_deactivate",
//"audio_deactivate");
//}
//
//bool obs_source_audio_active(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_audio_active")
//          ? os_atomic_load_bool(&source->audio_active)
//          : false;
//}
//
//uint32_t obs_source_get_last_obs_version(const obs_source_t * source)
//{
//   return obs_source_valid(source, "obs_source_get_last_obs_version")
//          ? source->last_obs_ver
//          : 0;
//}
//
//enum obs_icon_type obs_source_get_icon_type(const char * id)
//{
//   const struct obs_source_info * info = get_source_info(id);
//   return (info) ? info->icon_type : OBS_ICON_TYPE_UNKNOWN;
//}
//
//void obs_source_media_play_pause(obs_source_t * source, bool
//pause)
//{
//if (!
//m_data_valid(source,
//"obs_source_media_play_pause"))
//return;
//
//if (!source->info.media_play_pause)
//return;
//
//source->info.
//media_play_pause(source
//->context.m_data, pause);
//
//if (pause)
//obs_source_dosignal(source, NULL,
//"media_pause");
//else
//obs_source_dosignal(source, NULL,
//"media_play");
//}
//
//void obs_source_media_restart(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_media_restart"))
//      return;
//
//   if (!source->info.media_restart)
//      return;
//
//   source->info.media_restart(source->context.m_data);
//
//   obs_source_dosignal(source, NULL, "media_restart");
//}
//
//void obs_source_media_stop(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_media_stop"))
//      return;
//
//   if (!source->info.media_stop)
//      return;
//
//   source->info.media_stop(source->context.m_data);
//
//   obs_source_dosignal(source, NULL, "media_stopped");
//}
//
//void obs_source_media_next(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_media_next"))
//      return;
//
//   if (!source->info.media_next)
//      return;
//
//   source->info.media_next(source->context.m_data);
//
//   obs_source_dosignal(source, NULL, "media_next");
//}
//
//void obs_source_media_previous(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_media_previous"))
//      return;
//
//   if (!source->info.media_previous)
//      return;
//
//   source->info.media_previous(source->context.m_data);
//
//   obs_source_dosignal(source, NULL, "media_previous");
//}
//
//int64_t obs_source_media_get_time(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_media_get_time"))
//      return 0;
//
//   if (source->info.media_get_time)
//      return source->info.media_get_time(source->context.m_data);
//   else
//      return 0;
//}
//
//int64_t obs_source_media_get_time(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_media_get_time"))
//      return 0;
//
//   if (source->info.media_get_time)
//      return source->info.media_get_time(source->context.m_data);
//   else
//      return 0;
//}
//
//void obs_source_media_set_time(obs_source_t * source, int64_t
//ms)
//{
//if (!
//m_data_valid(source,
//"obs_source_media_set_time"))
//return;
//
//if (source->info.media_set_time)
//source->info.
//media_set_time(source
//->context.m_data, ms);
//}
//
//enum obs_media_state obs_source_media_get_state(obs_source_t * source)
//{
//   if (!m_data_valid(source, "obs_source_media_get_state"))
//      return OBS_MEDIA_STATE_NONE;
//
//   if (source->info.media_get_state)
//      return source->info.media_get_state(source->context.m_data);
//   else
//      return OBS_MEDIA_STATE_NONE;
//}
//
//void obs_source_media_started(obs_source_t * source)
//{
//   if (!obs_source_valid(source, "obs_source_media_started"))
//      return;
//
//   obs_source_dosignal(source, NULL, "media_started");
//}
//
//void obs_source_media_ended(obs_source_t * source)
//{
//   if (!obs_source_valid(source, "obs_source_media_ended"))
//      return;
//
//   obs_source_dosignal(source, NULL, "media_ended");
//}
//
//obs_m_data_array_t * obs_source_backup_filters(obs_source_t * source)
//{
//   if (!obs_source_valid(source, "obs_source_backup_filters"))
//      return NULL;
//
//   obs_m_data_array_t * array = obs_m_data_array_create();
//
//   pthread_mutex_lock(&source->filter_mutex);
//   for (size_t i = 0; i < source->filters.num; i++)
//   {
//      struct obs_source * filter = source->filters.array[i];
//      obs_m_data_t * m_data = obs_save_source(filter);
//      obs_m_data_array_push_back(array, m_data);
//      obs_m_data_release(m_data);
//   }
//   pthread_mutex_unlock(&source->filter_mutex);
//
//   return array;
//}
//
//void obs_source_restore_filters(obs_source_t * source, obs_m_data_array_t * array)
//{
//   if (!obs_source_valid(source, "obs_source_restore_filters"))
//      return;
//   if (!obs_ptr_valid(array, "obs_source_restore_filters"))
//      return;
//
//   DARRAY(obs_source_t * )
//   cur_filters;
//   DARRAY(obs_source_t * )
//   new_filters;
//   obs_source_t * prev = NULL;
//
//   da_init(cur_filters);
//   da_init(new_filters);
//
//   pthread_mutex_lock(&source->filter_mutex);
//
//   /* clear filter list */
//   da_reserve(cur_filters, source->filters.num);
//   da_reserve(new_filters, source->filters.num);
//   for (size_t i = 0; i < source->filters.num; i++)
//   {
//      obs_source_t * filter = source->filters.array[i];
//      da_push_back(cur_filters, &filter);
//      filter->filter_parent = NULL;
//      filter->filter_target = NULL;
//   }
//
//   da_free(source->filters);
//   pthread_mutex_unlock(&source->filter_mutex);
//
//   /* add backed up filters */
//   size_t count = obs_m_data_array_count(array);
//   for (size_t i = 0; i < count; i++)
//   {
//      obs_m_data_t * m_data = obs_m_data_array_item(array, i);
//      const char * name = obs_m_data_get_string(m_data, "name");
//      obs_source_t * filter = NULL;
//
//      /* if backed up filter already exists, don't create */
//      for (size_t j = 0; j < cur_filters.num; j++)
//      {
//         obs_source_t * cur = cur_filters.array[j];
//         const char * cur_name = cur->context.name;
//         if (cur_name && strcmp(cur_name, name) == 0)
//         {
//            filter = obs_source_get_ref(cur);
//            break;
//         }
//      }
//
//      if (!filter)
//         filter = obs_load_source(m_data);
//
//      /* add filter */
//      if (prev)
//         prev->filter_target = filter;
//      prev = filter;
//      filter->filter_parent = source;
//      da_push_back(new_filters, &filter);
//
//      obs_m_data_release(m_data);
//   }
//
//   if (prev)
//      prev->filter_target = source;
//
//   pthread_mutex_lock(&source->filter_mutex);
//   da_move(source->filters, new_filters);
//   pthread_mutex_unlock(&source->filter_mutex);
//
//   /* release filters */
//   for (size_t i = 0; i < cur_filters.num; i++)
//   {
//      obs_source_t * filter = cur_filters.array[i];
//      obs_source_release(filter);
//   }
//
//   da_free(cur_filters);
//}


} // namespace video
