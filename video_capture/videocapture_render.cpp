//
//  videocapture_render.cpp
//  app_core_videocapture
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//


#include "framework.h"
#include <math.h>


namespace video_capture
{


   render::render()
   {

      m_pview                    = nullptr;

   }


   render::~render()
   {

   }


   void render::full_render()
   {


   }

   ::e_status render::run()
   {

      while(task_get_run())
      {

         try
         {

               full_render();

            sleep(100_ms);

         }
         catch(...)
         {

            break;

         }

      }

      return 0;

   }

   void render::videocapture_render()
   {


   }


   void render::videocapture_render(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void render::videocapture_draw()
   {

   }



} // namespace video_capture



