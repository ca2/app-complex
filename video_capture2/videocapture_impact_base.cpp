#include "framework.h"
#include <math.h>


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace app_complex_video_capture
{


   impact_base::impact_base()
   {

   }


   impact_base::~impact_base()
   {

   }


   void impact_base::assert_ok() const
   {

      user::box::assert_ok();

   }


   void impact_base::dump(dump_context & dumpcontext) const
   {

      user::box::dump(dumpcontext);

   }


   void impact_base::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &impact_base::on_message_create);

   }


   void impact_base::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void impact_base::defer_check_on_draw_layout()
   {

   }

   void impact_base::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


      defer_check_on_draw_layout();

      auto rectangleX = this->rectangle();

      if (rectangleX.area() <= 0)
         return;

/*      m_pimagePost = create_image(rectangleX->size());

      m_pimagePost->Fill(00, 00, 00, 00);


      on_draw_image_layer(pgraphicsParam);

/*      ::image::image_pointer pimage = m_pimagePost;

/*      _006OnDraw(pimage->g());


/*      m_pimageTime = create_image(m_pimagePost->get_size());

      m_pimageTime->Fill(0, 0, 0, 0);


      unsigned int xOffset;

      xOffset = m_pimageTime->width() * m_frequencyFramesPerSecond * (double)(m_timeRoll->elapsed()) / 1000->0; // x = v->t; f=fps  1920 * 1FPS * t

      xOffset %= m_pimageTime->width();

      m_pimageTime->from(int_point(xOffset, 0), m_pimagePost, ::int_point(), ::int_size(m_pimagePost->width() - xOffset, m_pimagePost->height()));
      m_pimageTime->from(::int_point(), m_pimagePost, int_point(m_pimagePost->width() - xOffset, 0), int_size(xOffset, m_pimagePost->height()));

      //m_pimagePost->from(m_pimageTime);
      _001OnPostProcess(m_pimageTime->get_graphics());

      ::draw2d::graphics * pdcParam = pgraphicsParam;

      pdcParam->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //      m_pimagePost->get_graphics()->FillSolidRect(110,110,100,100,argb(184,177,184,60));


      /*  m_dwaFrame.add(::get_tick());

        for (::collection::index i = 0; i < m_dwaFrame.get_size();)
        {

           if (m_tickaFrame[i].elapsed() > 1000)
           {
              m_dwaFrame.erase_at(i);
           }
           else
           {
              i++;
           }

        }

        pdcParam->set_text_color(argb(255, 255, 255, 0));

        ::write_text::font_pointer f(e_create);

        f->create_point_font("Arial", 20, 800);

        pdcParam->set_font(f);

        pdcParam->TextOutA(0, 0, as_string(m_dwaFrame.get_size()));*/


      //int_size s = m_pimageTime->get_size();

      //::draw2d::graphics_pointer & pgraphics = m_pimageTime->get_graphics();

      //pdcParam->from(s, pgraphics);

      //pdcScreen->FillSolidRect(10,10,100,100,argb(184,49,184,60));

      //pdcScreen->Draw3dRect(200,200,100,100,argb(255,0,255,0),argb(255,0,0,255));
      //huge_natural endTime = get_nanos();

      //huge_natural microsecond = (endTime - startTime) / 1000;

      //char sz[512];

      //informationf("impact:");
      //::ansi_from_huge_natural(sz, microsecond, 10);
      //::information(sz);
      //informationf(", ");

      //image d(e_create);

      //d->create(rectangleX.size());

      //d->get_graphics()->BitBlt(rectangleX, pimage->g());

      //d.save_to_file(         auto psystem = system();

         //auto pdirectorysystem = pdirectorysystem->system() / "obs.png");


   }

   void impact_base::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void impact_base::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }



} // namespace app_complex_video_capture

















