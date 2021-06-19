//
//  videocapture_render.h
//  app_core_videocapture
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//


#pragma once


namespace videocapture
{


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE render :
      virtual public ::thread
   {
   public:

      bool                    m_bDib1;

      bool                    m_bAlternate;

      bool                    m_bLite;

      bool                    m_bImageEnable;

      ::mutex                   m_mutexWork;
      ::mutex                   m_mutexDraw;
      ::mutex                   m_mutexSwap;

      bool                    m_bNewLayout;
      bool                    m_bHelloRender;
      int                     m_cx;
      int                     m_cy;
      int                     m_cxCache1;
      int                     m_cyCache1;

      ::draw2d::fastblur      m_pimageImage;
      ::image_pointer        m_pimage1;
      ::image_pointer        m_pimage2;
      ::image_pointer        m_pimageWork;
/*      ::draw2d::fastblur      m_pimage;
      ::image_pointer        m_pimageTemplate;

      bool                    m_bVoidTransfer;
      bool                    m_bFirstDone;

      ::write_text::font_pointer       m_font;

      double                  m_dMinRadius;
      double                  m_dMaxRadius;

      string                  m_strHelloMultiverse;

      ::rectangle_i32                  m_rectangleClient;


      ::mutex *                 m_pmutexText;

      view *                  m_pview;


      render(::object * pobject);
      virtual ~render();


      string get_videocapture() { synchronous_lock slText(m_pmutexText);  string str(m_strHelloMultiverse.c_str()); return str; }


      virtual i32 run();


      virtual void full_render();
      virtual void videocapture_render();
      virtual void videocapture_draw();
      virtual void videocapture_render(::draw2d::graphics_pointer & pgraphics);
      //virtual void videocapture_render(::draw2d::graphics_pointer & pgraphics);

      virtual void videocapture_render_full_view(::draw2d::graphics_pointer & pgraphics);
      virtual void videocapture_render_lite_view(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace videocapture


