#include "framework.h"
#include "video_input.h"
#include "render.h"
#include "device.h"


__FACTORY_EXPORT void video_input_video_for_linux_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::video_input_video_for_linux::video_input, ::video_input::video_input >();

   pfactory->add_factory_item < ::video_input_video_for_linux::render, ::video_input::render >();
   
}
