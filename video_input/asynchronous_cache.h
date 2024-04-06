//
// Created by camilo on 07/02/2022.
//

namespace video
{

   class frame;

   class asynchronous_cache
   {
   public:
   
   
      bool m_bGpuConversion;
      enum_video_format m_eformat;
      bool m_bFullRange;
      enum_video_format m_eformatCache;
      bool m_bCacheFullRange;

      ::u32 m_width;
      ::u32 m_height;
      ::u32 m_cache_width;
      ::u32 m_cache_height;
      ::u32 m_convert_width[MAX_AV_PLANES];
      ::u32 m_convert_height[MAX_AV_PLANES];

      enum gs_color_format m_texture_formats[MAX_AV_PLANES];
      int m_channel_count;


      inline bool texture_changed(const frame * frame);

      bool set_texture_size(const frame * frame);

   };




} // namespace video
