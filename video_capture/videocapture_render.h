//
//  videocapture_render.h
//  app_core_videocapture
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//


#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE render :
      virtual public ::thread
   {
   public:


      ::image_pointer         m_pimage;

      impact *                  m_pimpact;


      render();
      virtual ~render();


      virtual ::e_status run();


      virtual void full_render();
      virtual void videocapture_render();
      virtual void videocapture_draw();
      virtual void videocapture_render(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace video_capture


