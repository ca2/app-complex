#include "framework.h"



__FACTORY_EXPORT void video_input_avfoundation_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::video_input_video_avfoundation::video_input, ::video_input::video_input >();

   pfactory->add_factory_item < ::video_input_video_avfoundation::render, ::video_input::render >();
   
}
