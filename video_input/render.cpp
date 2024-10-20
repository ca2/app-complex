// Created on 2021-07-07 by camilo 14:11 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "render.h"
#include "device.h"
#include "media_format.h"
#include "acme/parallelization/manual_reset_event.h"


namespace video_input
{

   render::render()
   {

      defer_create_synchronization();

      m_pevRenderEnd = nullptr;

   }


   render::~render()
   {

   }


   void render::initialize_video_input_render(device * pdevice)
   {



   }

   void render::prepare_image()
   {


   }

   //void render::assert_ok() const
   //{

   //   object::assert_ok();

   //}


   //void render::dump(dump_context& dumpcontext) const
   //{

   //   object::dump(dumpcontext);

   //}



   void render::on_create()
   {

   }


   void render::destroy()
   {

      m_pevRenderEnd = ___new manual_reset_event();

      set_finish();

      m_pevRenderEnd->wait(15_s);

      delete m_pevRenderEnd;

   }


   void render::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

   }


   void render::handle(::topic * ptopic, ::context * pcontext)
   {


   }

   bool render::start_capture()
   {


      return true;

   }


   void device::create_render() 
   {

      if (m_prender)
      {

         return;

      }

      __construct(m_prender);

      m_prender->initialize_video_input_render(this);

   }


} // namespace video_input



