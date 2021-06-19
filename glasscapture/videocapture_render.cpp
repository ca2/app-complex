//
//  videocapture_render.cpp
//  app_core_videocapture
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//


#include "framework.h"
#include <math.h>


namespace videocapture
{


   render::render(::object * pobject):
      object(pobject),
      thread(pobject),
      m_font(e_create),
      m_pimageTemplate,
      m_pimageImage,
      
      
      
      m_pimage1,
      m_pimage2,
      m_pimageWork,

   {

      m_pview                    = nullptr;

      m_bImageEnable             = true;

      m_bDib1                    = false;

      m_bAlternate               = false;

      m_bLite                    = true;

      m_bNewLayout               = false;
      m_bHelloRender             = false;
      m_cx                       = 0;
      m_cy                       = 0;
      m_cxCache1                 = 0;
      m_cyCache1                 = 0;

      m_bVoidTransfer            = false;
      m_bFirstDone               = false;

      m_dMinRadius               = 0.0;
      m_dMaxRadius               = 0.0;

      m_rectangleClient.null();


      m_bVoidTransfer =  false;

      m_bFirstDone = true;

      m_cx = 0;

      m_cy = 0;

      m_dMinRadius = 1.0;

      m_dMaxRadius = 2.0;

      m_bNewLayout = false;

      m_bHelloRender = true;

      m_cxCache1 = 0;

      m_cyCache1 = 0;


   }


   render::~render()
   {

   }


   void render::full_render()
   {

      size_i32 sizeNew = size_i32(m_cx,m_cy);

      if(m_bNewLayout)
      {

         synchronous_lock sl2(&m_mutexWork);
         synchronous_lock sl3(&m_mutexDraw);
         synchronous_lock sl4(&m_mutexSwap);

/*         bool bNewSize = m_pimage->width() != sizeNew.cx || m_pimage->m_size.cy != sizeNew.cy;

         m_bNewLayout = false;

/*         m_pimageWork = create_image(sizeNew);

         if(bNewSize)
         {

/*            m_pimage1 = create_image(sizeNew);

/*            m_pimage2 = create_image(sizeNew);

         }

      }


      videocapture_render();

      if(m_bFirstDone)
      {

         videocapture_draw();

      }
      else
      {
         //TRACE("XXX123546");
      }

   }

   i32 render::run()
   {

      while(task_get_run())
      {

         try
         {

            if(m_bHelloRender)
            {

               full_render();

            }

            sleep(100_ms);

         }
         catch(...)
         {

            break;

         }

      }

      if (m_pview != nullptr && m_pview->m_pevRenderEnd != nullptr)
      {

         m_pview->m_pevRenderEnd->SetEvent();

      }

      return 0;

   }

   void render::videocapture_render()
   {

      {

         synchronous_lock synchronouslock(&m_mutexWork);

/*         ::image_pointer pimage = m_pimageWork;

/*         pimage->Fill(0,0,0,0);

/*         videocapture_render(pimage->g());


      }

   }

   void render::videocapture_render(::draw2d::graphics_pointer & pgraphics)
   {



      //   if(m_bLite)
      {

         videocapture_render_lite_view(pgraphics);

      }
      //   else
      //   {
      //
      //      videocapture_render_full_view(pimage->g());
      //
      //   }

   }


   void render::videocapture_draw()
   {

      if(m_bVoidTransfer)
         return;

      //_001OnPostProcess(m_pimageWork);

      synchronous_lock slDraw(&m_mutexDraw);

      if(m_bDib1)
      {

         *m_pimage2 = *m_pimageWork;

      }
      else
      {

         *m_pimage1 = *m_pimageWork;

      }

      synchronous_lock slSwap(&m_mutexSwap);

      if(m_bDib1)
      {

         m_bDib1 = false;

      }
      else
      {

         m_bDib1 = true;

      }

   }

   void render::videocapture_render_lite_view(::draw2d::graphics_pointer & pgraphics)
   {

      //if(m_pimage->area() <= 0)
      //   return;

      if(m_pimageWork->area() <= 0)
         return;

      ::rectangle_i32 rectangleClient;

      rectangleClient.left = 0;

      rectangleClient.top = 0;

      rectangleClient.right = m_cx;

      rectangleClient.bottom = m_cy;

      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      //pgraphics->FillSolidRect(rectangleClient,argb(0, 0, 0, 0));

      //      i32 iCount = 30;

      ::draw2d::brush_pointer brushText(e_create);

      double T = 2.3;

      if(false)
      {

         T = 2.3;

      }
      else if(m_bAlternate)
      {

         T = 1.2;

      }
      else
      {

         T = 2.3;

      }

      double t= ::millis::now() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

      ::size_i32 size;



      synchronous_lock slText(m_pmutexText);

      string strHelloMultiverse(get_videocapture().c_str()); // rationale : string allocation fork *for parallelization*

      slText.unlock();

      pgraphics->set_font(m_font);

      size = pgraphics->get_text_extent(strHelloMultiverse);

      if(!m_bFirstDone)
      {

         if(psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
         {

            sleep(47_ms);

         }
         else
         {

            m_cxCache1 = m_cx;

            m_cyCache1 = m_cy;

/*            m_pimage->initialize(m_cxCache1,m_cyCache1,m_dMaxRadius);

            //m_pimage->defer_realize(pgraphics);

/*            m_pimage->Fill(0,0,0,0);

/*            m_pimage->g()->set_font(m_font);

/*            m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

/*            m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

            brushText->create_solid(argb(255,255,255,255));

/*            m_pimage->g()->set(brushText);

/*            m_pimage->g()->text_out((m_cxCache1 - size_i32->cx) / 2,(m_cyCache1 - size_i32->cy) / 2,strHelloMultiverse);

/*            m_pimage->map();

/*            psystem->imaging().spread(m_pimage->g(), ::point_i32(), m_pimage->get_size(), m_pimage->g(), ::point_i32(), m_dMaxRadius);

/*            m_pimage->blur();

/*            m_pimageTemplate = create_image(m_pimage->get_size());

            m_pimageTemplate->Fill(0,0,0,0);

/*            m_pimageTemplate->channel_copy(::color::e_channel_alpha,::color::e_channel_green,m_pimage);

         }

      }

      slText.lock();

      if(strHelloMultiverse != get_videocapture() || m_cxCache1 != m_cx || m_cyCache1 != m_cy || m_pimageTemplate->area() <= 0)
         return;

      slText.unlock();

      ::color::color ca;


      if(false)
      {

         double dPeriod = (5000) * 11;

         ca.set_hls(fmod(__double(::get_tick()),dPeriod) / dPeriod,0.49,0.84);

      }
      else if(m_bAlternate)
      {

         double dPeriod = (5100) * 8;

         ca.set_hls(fmod(__double(::get_tick()),dPeriod) / dPeriod,0.49,0.84);

      }
      else
      {

         double dPeriod = (4900) * 11;

         ca.set_hls(fmod(__double(::get_tick()),dPeriod) / dPeriod,0.23,0.84);

      }

      if(!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         //m_pimageTemplate->set_rgb_pre_alpha(ca->m_iR,ca->m_iG,ca->m_iB, 140 + 220 * r);
         m_pimageTemplate->set_rgb_pre_alpha(ca->m_iR, ca->m_iG, ca->m_iB);

      }

      pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      psystem->imaging().bitmap_blend(pgraphics,::point_i32(),rectangleClient.size(),m_pimageTemplate->get_graphics(),::point_i32(),140 + 220 * r);

      //pgraphics->from(rectangleClient.top_left(),m_pimageTemplate, ::point_i32(), rectangleClient>si);

      pgraphics->set_font(m_font);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if(psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         brushText->create_solid(argb(255,ca.m_iR,ca.m_iG,ca.m_iB));

      }
      else
      {

         if(m_bAlternate)
         {

            brushText->create_solid(argb(255,184,184,177));

         }
         else
         {

            brushText->create_solid(argb(255,255,255,255));

         }

      }

      pgraphics->set(brushText);

      //if(!m_bAlternate)
      {

         pgraphics->text_out((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

      }
      //      pgraphics->FillSolidRect(200,00,100,100,argb(128,128,128,255));

      //    pgraphics->FillSolidRect(200,200,100,100,argb(128,128,128,0));

      slText.lock();

      if(strHelloMultiverse == get_videocapture() && m_cxCache1 == m_cx && m_cyCache1 == m_cy)
      {

         m_bFirstDone = true;

      }

   }


   void render::videocapture_render_full_view(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_pimageWork->area() <= 0)
         return;

      ::rectangle_i32 rectangleClient;

      rectangleClient.left = 0;

      rectangleClient.top = 0;

      rectangleClient.right = m_cx;

      rectangleClient.bottom = m_cy;

      if(rectangleClient.area() <= 0)
         return;

      //      i32 iCount = 30;

      ::draw2d::brush_pointer brushText(e_create);

      double T = 2.3;

      if(false)
      {

         T = 2.3;

      }
      else if(m_bAlternate)
      {

         T = 1.2;

      }
      else
      {

         T = 2.3;

      }

      double t= ::millis::now() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;

      ::color::color ca;

      if(false)
      {

         double dPeriod = (5000) * 11;

         ca.set_hls(fmod(__double(::get_tick()),dPeriod) / dPeriod,0.49,0.84);

      }
      else if(m_bAlternate)
      {

         double dPeriod = (5100) * 8;

         ca.set_hls(fmod(__double(::get_tick()),dPeriod) / dPeriod,0.49,0.84);

      }
      else
      {

         double dPeriod = (4900) * 11;

         ca.set_hls(fmod(__double(::get_tick()),dPeriod) / dPeriod,0.23,0.84);

      }



      pgraphics->set_font(m_font);

      string strHelloMultiverse = get_videocapture();

      ::size_i32 size = pgraphics->get_text_extent(strHelloMultiverse);

      if(!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         if(m_dMinRadius > 3.0)
         {

/*            m_pimage->initialize(m_cx,m_cy,dBlur);

         }
         else
         {

/*            m_pimage->initialize(m_cx,m_cy,5);

         }

/*         m_pimage->defer_realize(pgraphics);

/*         m_pimage->Fill(0,0,0,0);

/*         m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

/*         m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

         brushText->create_solid(argb(255,255,255,255));

/*         m_pimage->g()->set(brushText);

/*         m_pimage->g()->set_font(m_font);

/*         m_pimage->g()->text_out((m_cx - size_i32->cx) / 2,(m_cy - size_i32->cy) / 2,strHelloMultiverse);

         if(m_dMinRadius > 3.0)
         {

/*            m_pimage->blur(m_cx,m_cy);

         }
         else
         {

            for(i32 i = 0; i < dBlur * 2; i++)
            {

/*               m_pimage->blur(m_cx,m_cy);

            }

         }

         if(!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
         {

/*            m_pimage->channel_copy(::color::e_channel_alpha,::color::e_channel_green);

/*            m_pimage->set_rgb_pre_alpha(ca->m_iR,ca->m_iG,ca->m_iB);

         }

         pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

/*         pgraphics->BitBlt(rectangleClient,m_pimage->g());

      }

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if(psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         brushText->create_solid(argb(255,ca.m_iR,ca.m_iG,ca.m_iB));

      }
      else
      {

         if(m_bAlternate)
         {

            brushText->create_solid(argb(255,184,184,177));

         }
         else
         {

            brushText->create_solid(argb(255,255,255,255));

         }

      }

      pgraphics->set(brushText);

      pgraphics->text_out((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

      byte a,R,g,b;

      if(m_bAlternate)
      {
         a = 184;
         R = 177;
         g = 77;
         b = 184;
      }
      else
      {
         a = 184;
         R = 77;
         g = 184;
         b = 84;
      }

#if 0
      if(papplication->m_iErrorAiFont == 0)
      {

         synchronous_lock slAiFont(&papplication->m_mutexAiFont);

         FT_Face & face = (FT_Face &)papplication->m_faceAi;

         i32 error;

         error = FT_Set_Char_Size(face,        /* handle to face object */
                                  0,          /* char_width in 1/64th of points */
                                  800 * 64,          /* char_height in 1/64th of points */
                                  72,         /* horizontal device resolution */
                                  72);         /* vertical device resolution */

         if(error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if(error == 0)
            {

               i64 iChar =  ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

               i32 glyph_index = FT_Get_Char_Index(face,(i32)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if(error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if(error == 0)
                  {

/*                     ::image_pointer & pimage = m_pimageAi1;

/*                     pimage = create_image({face->glyph->bitmap.width, face->glyph->bitmap.rows});

/*                     pimage->realize(pgraphics);

/*                     draw_freetype_bitmap(pimage->m_p,0,0,&face->glyph->bitmap,0,0,a,R,g,b);

                     pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

/*                     pgraphics->StretchBlt(0,0,pimage->width() / 40,pimage->height() / 40,pimage->get_graphics(),0,0,pimage->width(),pimage->height());

/*                     pgraphics->StretchBlt(0,m_cy - pimage->height() / 40,pimage->width() / 40,pimage->height() / 40,pimage->get_graphics(),0,0,pimage->width(),pimage->height());

                  }

               }

            }

         }


         error = FT_Set_Char_Size(face,        /* handle to face object */
                                  0,          /* char_width in 1/64th of points */
                                  640 * 64,          /* char_height in 1/64th of points */
                                  72,         /* horizontal device resolution */
                                  72);         /* vertical device resolution */

         if(error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if(error == 0)
            {

               i64 iChar =  ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

               i32 glyph_index = FT_Get_Char_Index(face,(i32)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if(error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if(error == 0)
                  {

/*                     ::image_pointer & pimage = m_pimageAi2;

/*                     pimage = create_image({face->glyph->bitmap.width, face->glyph->bitmap.rows});

/*                     pimage->realize(pgraphics);

/*                     draw_freetype_bitmap(pimage->m_p,0,0,&face->glyph->bitmap,0,0,a,R,g,b);

                     pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

/*                     pgraphics->StretchBlt(m_cx - pimage->width() / 32,0,pimage->width() / 32,pimage->height() / 32,pimage->get_graphics(),0,0,pimage->width(),pimage->height());

/*                     pgraphics->StretchBlt(m_cx - pimage->width() / 32,m_cy - pimage->height() / 32,pimage->width() / 32,pimage->height() / 32,pimage->get_graphics(),0,0,pimage->width(),pimage->height());

                  }

               }

            }

         }

      }

#endif

      if(strHelloMultiverse == get_videocapture() && m_cx == m_rectangleClient.width() && m_cy == m_rectangleClient.height())
      {

         m_bFirstDone = true;

      }

   }



} // namespace videocapture



