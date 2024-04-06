#include "framework.h"
#include "video_input.h"
#include "render.h"
#include "media_format.h"
#include "device.h"



__FACTORY_EXPORT void video_input_media_capture_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::video_input_media_capture::video_input, ::video_input::video_input >();

   pfactory->add_factory_item < ::video_input_media_capture::render, ::video_input::render >();

   pfactory->add_factory_item < ::video_input_media_capture::media_format, ::video_input::media_format >();
   
}
