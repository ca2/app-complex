#pragma once


#include "asynchronous_cache.h"
#include "_function.h"


#define OBS_SOURCE_FRAME_LINEAR_ALPHA (1 << 0)

/**
 * Source asynchronous video output structure.  Used with
 * obs_source_output_video to output asynchronous video.  Video is buffered as
 * necessary to play according to timestamps.  When used with audio output,
 * audio is synced to video as it is played.
 *
 * If a YUV format is specified, it will be automatically upsampled and
 * converted to RGB via shader on the graphics processor.
 *
 * NOTE: Non-YUV formats will always be treated as full range with this
 * structure!  Use obs_source_frame2 along with obs_source_output_video2
 * instead if partial range support is desired for non-YUV video formats.
 */

namespace video
{


   class frame
   {
   public:

      unsigned char * m_data[MAX_AV_PLANES];
      unsigned int m_linesize[MAX_AV_PLANES];
      unsigned int m_width;
      unsigned int m_height;
      huge_natural m_timestamp;

      enum_video_format m_eformat;
      float m_color_matrix[16];
      bool m_full_range;
      float m_color_range_min[3];
      float m_color_range_max[3];
      bool m_flip;
      unsigned char m_flags;

      /* used internally by video */
      volatile long m_refs;
      bool m_prev_frame;


      frame() {memory_set(this, 0, sizeof(*this));}
      frame(enum_video_format format, uint32_t width, uint32_t height);

      ~frame();

      void video_frame_init(enum_video_format eformat, uint32_t width, uint32_t height);
      void copy_from(const frame *src, enum_video_format eformat, uint32_t cy);

      inline bool set_packed422_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_packed444_alpha_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_planar444_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_planar444_alpha_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_planar420_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_planar420_alpha_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_planar422_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_planar422_alpha_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_nv12_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_y800_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_rgb_limited_sizes(asynchronous_cache * pasynchronouscache) const;
      inline bool set_bgr3_sizes(asynchronous_cache * pasynchronouscache) const;

      inline bool init_gpu_conversion(asynchronous_cache * pasynchronouscache) const;


      inline void copy_data_line_from(const frame * src, uint32_t asynchronous_cache, uint32_t y);

      inline void copy_data_plane_from(const frame * src, uint32_t asynchronous_cache, uint32_t lines);

      void copy_frame_data(const frame * src);

      void copy_from(const frame * src);

   };


   bool frame::set_packed422_sizes(asynchronous_cache * pasynchronouscache) const
   {
      const uint32_t width = m_width;
      const uint32_t height = m_height;
      const uint32_t half_width = (width + 1) / 2;
      pasynchronouscache->m_convert_width[0] = half_width;
      pasynchronouscache->m_convert_height[0] = height;
      pasynchronouscache->m_texture_formats[0] = GS_BGRA;
      pasynchronouscache->m_channel_count = 1;
      return true;
   }


   bool frame::set_packed444_alpha_sizes(asynchronous_cache * pasynchronouscache) const
   {
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_height[0] = m_height;
      pasynchronouscache->m_texture_formats[0] = GS_BGRA;
      pasynchronouscache->m_channel_count = 1;
      return true;
   }

   inline bool frame::set_planar444_sizes(asynchronous_cache * pasynchronouscache) const
   {
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_width[1] = m_width;
      pasynchronouscache->m_convert_width[2] = m_width;
      pasynchronouscache->m_convert_height[0] = m_height;
      pasynchronouscache->m_convert_height[1] = m_height;
      pasynchronouscache->m_convert_height[2] = m_height;
      pasynchronouscache->m_texture_formats[0] = GS_R8;
      pasynchronouscache->m_texture_formats[1] = GS_R8;
      pasynchronouscache->m_texture_formats[2] = GS_R8;
      pasynchronouscache->m_channel_count = 3;
      return true;
   }


   inline bool frame::set_planar444_alpha_sizes(asynchronous_cache * pasynchronouscache) const
   {
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_width[1] = m_width;
      pasynchronouscache->m_convert_width[2] = m_width;
      pasynchronouscache->m_convert_width[3] = m_width;
      pasynchronouscache->m_convert_height[0] = m_height;
      pasynchronouscache->m_convert_height[1] = m_height;
      pasynchronouscache->m_convert_height[2] = m_height;
      pasynchronouscache->m_convert_height[3] = m_height;
      pasynchronouscache->m_texture_formats[0] = GS_R8;
      pasynchronouscache->m_texture_formats[1] = GS_R8;
      pasynchronouscache->m_texture_formats[2] = GS_R8;
      pasynchronouscache->m_texture_formats[3] = GS_R8;
      pasynchronouscache->m_channel_count = 4;
      return true;
   }

   inline bool frame::set_planar420_sizes(asynchronous_cache * pasynchronouscache) const
   {
      const uint32_t width = m_width;
      const uint32_t height = m_height;
      const uint32_t half_width = (width + 1) / 2;
      const uint32_t half_height = (height + 1) / 2;
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_width[1] = half_width;
      pasynchronouscache->m_convert_width[2] = half_width;
      pasynchronouscache->m_convert_height[0] = height;
      pasynchronouscache->m_convert_height[1] = half_height;
      pasynchronouscache->m_convert_height[2] = half_height;
      pasynchronouscache->m_texture_formats[0] = GS_R8;
      pasynchronouscache->m_texture_formats[1] = GS_R8;
      pasynchronouscache->m_texture_formats[2] = GS_R8;
      pasynchronouscache->m_channel_count = 3;
      return true;
   }
   

   inline bool frame::set_planar420_alpha_sizes(asynchronous_cache * pasynchronouscache) const
   {
      const uint32_t width = m_width;
      const uint32_t height = m_height;
      const uint32_t half_width = (width + 1) / 2;
      const uint32_t half_height = (height + 1) / 2;
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_width[1] = half_width;
      pasynchronouscache->m_convert_width[2] = half_width;
      pasynchronouscache->m_convert_width[3] = m_width;
      pasynchronouscache->m_convert_height[0] = height;
      pasynchronouscache->m_convert_height[1] = half_height;
      pasynchronouscache->m_convert_height[2] = half_height;
      pasynchronouscache->m_convert_height[3] = height;
      pasynchronouscache->m_texture_formats[0] = GS_R8;
      pasynchronouscache->m_texture_formats[1] = GS_R8;
      pasynchronouscache->m_texture_formats[2] = GS_R8;
      pasynchronouscache->m_texture_formats[3] = GS_R8;
      pasynchronouscache->m_channel_count = 4;
      return true;
   }


   inline bool frame::set_planar422_sizes(asynchronous_cache * pasynchronouscache) const
   {
      const uint32_t width = m_width;
      const uint32_t height = m_height;
      const uint32_t half_width = (width + 1) / 2;
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_width[1] = half_width;
      pasynchronouscache->m_convert_width[2] = half_width;
      pasynchronouscache->m_convert_height[0] = height;
      pasynchronouscache->m_convert_height[1] = height;
      pasynchronouscache->m_convert_height[2] = height;
      pasynchronouscache->m_texture_formats[0] = GS_R8;
      pasynchronouscache->m_texture_formats[1] = GS_R8;
      pasynchronouscache->m_texture_formats[2] = GS_R8;
      pasynchronouscache->m_channel_count = 3;
      return true;
   }


   inline bool frame::set_planar422_alpha_sizes(asynchronous_cache * pasynchronouscache) const
   {
      const uint32_t width = m_width;
      const uint32_t height = m_height;
      const uint32_t half_width = (width + 1) / 2;
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_width[1] = half_width;
      pasynchronouscache->m_convert_width[2] = half_width;
      pasynchronouscache->m_convert_width[3] = m_width;
      pasynchronouscache->m_convert_height[0] = height;
      pasynchronouscache->m_convert_height[1] = height;
      pasynchronouscache->m_convert_height[2] = height;
      pasynchronouscache->m_convert_height[3] = height;
      pasynchronouscache->m_texture_formats[0] = GS_R8;
      pasynchronouscache->m_texture_formats[1] = GS_R8;
      pasynchronouscache->m_texture_formats[2] = GS_R8;
      pasynchronouscache->m_texture_formats[3] = GS_R8;
      pasynchronouscache->m_channel_count = 4;
      return true;
   }


   inline bool frame::set_nv12_sizes(asynchronous_cache * pasynchronouscache) const
   {
      const uint32_t width = m_width;
      const uint32_t height = m_height;
      const uint32_t half_width = (width + 1) / 2;
      const uint32_t half_height = (height + 1) / 2;
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_width[1] = half_width;
      pasynchronouscache->m_convert_height[0] = height;
      pasynchronouscache->m_convert_height[1] = half_height;
      pasynchronouscache->m_texture_formats[0] = GS_R8;
      pasynchronouscache->m_texture_formats[1] = GS_R8G8;
      pasynchronouscache->m_channel_count = 2;
      return true;
   }


   inline bool frame::set_y800_sizes(asynchronous_cache * pasynchronouscache) const
   {
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_height[0] = m_height;
      pasynchronouscache->m_texture_formats[0] = GS_R8;
      pasynchronouscache->m_channel_count = 1;
      return true;
   }


   inline bool frame::set_rgb_limited_sizes(asynchronous_cache * pasynchronouscache) const
   {
      pasynchronouscache->m_convert_width[0] = m_width;
      pasynchronouscache->m_convert_height[0] = m_height;
      pasynchronouscache->m_texture_formats[0] = convert_video_format(m_eformat);
      pasynchronouscache->m_channel_count = 1;
      return true;
   }


   inline bool frame::set_bgr3_sizes(asynchronous_cache * pasynchronouscache) const
   {
      pasynchronouscache->m_convert_width[0] = m_width * 3;
      pasynchronouscache->m_convert_height[0] = m_height;
      pasynchronouscache->m_texture_formats[0] = GS_R8;
      pasynchronouscache->m_channel_count = 1;
      return true;
   }

   struct frame2
   {
      unsigned char * m_data[MAX_AV_PLANES];
      unsigned int m_linesize[MAX_AV_PLANES];
      unsigned int m_width;
      unsigned int m_height;
      huge_natural m_timestamp;

      enum_video_format m_eformat;
      enum_video_range_type m_erangetype;
      float m_color_matrix[16];
      float m_color_range_min[3];
      float m_color_range_max[3];
      bool m_flip;
      unsigned char m_flags;
   };


   inline bool frame::init_gpu_conversion(asynchronous_cache * pasynchronouscache) const
   {
      switch (get_convert_type(m_eformat, m_full_range))
      {
         case e_convert_422_pack:           return set_packed422_sizes(pasynchronouscache);

         case e_convert_420:            return set_planar420_sizes(pasynchronouscache);

         case e_convert_422:            return set_planar422_sizes(pasynchronouscache);

         case e_convert_nv12:            return set_nv12_sizes(pasynchronouscache);

         case e_convert_444:            return set_planar444_sizes(pasynchronouscache);

         case e_convert_800:            return set_y800_sizes(pasynchronouscache);

         case e_convert_rgb_limited:            return set_rgb_limited_sizes(pasynchronouscache);

         case e_convert_bgr3:            return set_bgr3_sizes(pasynchronouscache);

         case e_convert_420_a:            return set_planar420_alpha_sizes(pasynchronouscache);

         case e_convert_422_a:            return set_planar422_alpha_sizes(pasynchronouscache);

         case e_convert_444_a:            return set_planar444_alpha_sizes(pasynchronouscache);

         case e_convert_444_a_pack:            return set_packed444_alpha_sizes(pasynchronouscache);

         case e_convert_none:            //assert(false && "No conversion requested");
            break;
      }
      return false;
   }


   inline void frame::copy_data_line_from(const frame * src, uint32_t asynchronous_cache, uint32_t y)
   {

      uint32_t pos_src = y * src->m_linesize[asynchronous_cache];

      uint32_t pos_dst = y * m_linesize[asynchronous_cache];

      uint32_t bytes = m_linesize[asynchronous_cache] < src->m_linesize[asynchronous_cache]
                       ? m_linesize[asynchronous_cache]
                       : src->m_linesize[asynchronous_cache];

      memory_copy(m_data[asynchronous_cache] + pos_dst, src->m_data[asynchronous_cache] + pos_src, bytes);

   }


   inline void frame::copy_data_plane_from(const frame * src, uint32_t asynchronous_cache, uint32_t lines)
   {

      if (m_linesize[asynchronous_cache] != src->m_linesize[asynchronous_cache])
      {

         for (uint32_t y = 0; y < lines; y++)
         {

            copy_data_line_from(src, asynchronous_cache, y);

         }

      }
      else
      {

         memory_copy(m_data[asynchronous_cache], src->m_data[asynchronous_cache], (size_t) m_linesize[asynchronous_cache] * (size_t) lines);

      }

   }


   inline bool asynchronous_cache::texture_changed(const frame * pframe)
   {

      enum_convert_type prev, cur;

      prev = get_convert_type(m_eformatCache, m_bCacheFullRange);

      cur = get_convert_type(pframe->m_eformat, pframe->m_full_range);

      return m_cache_width != pframe->m_width
      ||m_cache_height != pframe->m_height
      || prev != cur;
   }



   //if return value is not null then do (os_atomic_dec_long(&output->refs) == 0) && video_frame_destroy(output)
//   inline struct video_frame * frame::cache_video(struct obs_source * source) const
//   {
//      struct video_frame * new_frame = NULL;
//
//      pthread_mutex_lock(&source->async_mutex);
//
//      if (source->async_frames.num >= MAX_ASYNC_FRAMES)
//      {
//         free_async_cache(source);
//         source->last_frame_ts = 0;
//         pthread_mutex_unlock(&source->async_mutex);
//         return NULL;
//      }
//
//      if (async_texture_changed(source, frame))
//      {
//         free_async_cache(source);
//         source->async_cache_width = frame->width;
//         source->async_cache_height = frame->height;
//      }
//
//      const enum_video_format format = frame->format;
//      source->async_cache_format = format;
//      source->async_cache_full_range = frame->full_range;
//
//      for (size_t i = 0; i < source->async_cache.num; i++)
//      {
//         struct async_frame * af = &source->async_cache.array[i];
//         if (!af->used)
//         {
//            new_frame = af->frame;
//            new_frame->format = format;
//            af->used = true;
//            af->unused_count = 0;
//            break;
//         }
//      }
//
//      clean_cache(source);
//
//      if (!new_frame)
//      {
//         struct async_frame new_af;
//
//         new_frame = video_frame_create(format, frame->width,
//                                        frame->height);
//         new_af.frame = new_frame;
//         new_af.used = true;
//         new_af.unused_count = 0;
//         new_frame->refs = 1;
//
//         da_push_back(source->async_cache, &new_af);
//      }
//
//      os_atomic_inc_long(&new_frame->refs);
//
//      pthread_mutex_unlock(&source->async_mutex);
//
//      copy_frame_data(new_frame, frame);
//
//      return new_frame;
//   }


} // namespace video



