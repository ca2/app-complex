#include "platform.h"
#include "video_input.h"
#include "render.h"
// #include "media_format.h"
#include "device.h"



__FACTORY_EXPORT void video_input_direct_show_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::video_input_direct_show::video_input, ::video_input::video_input >();

   pfactory->add_factory_item < ::video_input_direct_show::render, ::video_input::render >();

   // pfactory->add_factory_item < ::video_input_direct_show::media_format, ::video_input::media_format >();
   
}
