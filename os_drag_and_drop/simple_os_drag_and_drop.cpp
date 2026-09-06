#include "platform.h"
#include <math.h>

CLASS_DECL_AURA color32_t dk_red(); // <3 tbs

namespace simple_os_drag_and_drop
{



   simple_os_drag_and_drop::simple_os_drag_and_drop()
   {

      m_iDragAndDrop = 1;

   }


   simple_os_drag_and_drop::~simple_os_drag_and_drop()
   {

   }


   ::i64 simple_os_drag_and_drop::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   ::i64 simple_os_drag_and_drop::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }

   void simple_os_drag_and_drop::initialize_drag_and_drop(int iDragAndDrop)
   {

      m_iDragAndDrop = iDragAndDrop;

   }

   void simple_os_drag_and_drop::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {


   }


   void simple_os_drag_and_drop::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      //informationf("simple_os_drag_and_drop::_001OnDraw (%d, %d)", m_rectangle.width(), m_rectangle.height());

      if(m_iDragAndDrop <= 3)
      {

         _001OnDraw1Through3(pdraw2dgraphics);

      }
      else if(m_iDragAndDrop == 4)
      {

         _001OnDrawArcs(pdraw2dgraphics, false);

      }
      else
      {

         _001OnDrawArcs(pdraw2dgraphics, true);

      }

   }


   void simple_os_drag_and_drop::_001OnDraw1Through3(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto ppen = createø < ::draw2d::pen > ();

      auto pbrush = createø < ::draw2d::brush >();

      auto pfont = createø < ::write_text::font > ();

      pfont->create_pixel_font(pnode->font_name(e_font_sans_ex), 100.0, 800);

      pdraw2dgraphics->set(pfont);

      ppen->create_solid(4.0, argb(255, 50, 180, 255));

      i32_rectangle rectangle;

      int iSize = minimum(m_rectangle.width(), m_rectangle.height());

      iSize = iSize * 3 / 4;

      rectangle.set_size(iSize, iSize);

      rectangle.Align(e_align_center, m_rectangle);

      rectangle.offset_x(-iSize/5 * 3);

      rectangle.offset_x(iSize/5 * m_iDragAndDrop);

      if(m_iDragAndDrop == 3)
      {

         pbrush->CreatePatternBrush(get_image("matter://pat1.jpg"));

      }
      else
      {

         pbrush->CreateLinearGradientBrush(rectangle.top_left(), rectangle.bottom_right(), argb(255, 255, 255, 200), argb(255, 255, 125, 100));

      }

      pdraw2dgraphics->set(ppen);

      pdraw2dgraphics->set(pbrush);

      pdraw2dgraphics->ellipse(rectangle);

      if(m_iDragAndDrop >= 2)
      {

         ::i32_rectangle rectangleText(rectangle);

         rectangleText.inflate(100, 100);

         pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         if(m_iDragAndDrop == 3)
         {

            if(m_pimagemap["pat1grayed"]->is_null())
            {

               auto pimage1 = get_image("matter://pat1.jpg");
               
               /**pimage1 += { success, [this](auto & result)
               {
                  
                  ::image::image_pointer pimage = result;

                  m_pimpact->set_need_redraw();

                  ::image::image_pointer pimpl = pimage->clone();

                  ::image::image_pointer pimageClone = pimpl;

                  m_pimagemap["pat1grayed"] = imageClone;

                  m_pimagemap["pat1grayed"]->saturation(0->0);

                  m_pimpact->set_need_redraw();
                  
                  m_pimpact->post_redraw();

                  return ::success;

               }};*/

            }

            pbrush->CreatePatternBrush(m_pimagemap["pat1grayed"]);

         }
         else
         {

            pbrush->CreateLinearGradientBrush(rectangleText.top_left(), rectangleText.bottom_right(), argb(255, 55, 210, 120), argb(255, 255, 255, 200));

         }

         pdraw2dgraphics->set(pbrush);

         //pdraw2dgraphics->draw_text("Simple Drawing", rectangleText, e_align_center);

      }

   }


   void simple_os_drag_and_drop::_001OnDrawArcs(::draw2d::graphics_pointer & pdraw2dgraphics, bool bPath)
   {

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      f64_array daStart;

      f64_array daAngle;

      daStart.add(0.0);
      daAngle.add(100.0);

      daStart.add(90.0);
      daAngle.add(100.0);

      daStart.add(180.0);
      daAngle.add(100.0);

      daStart.add(270.0);
      daAngle.add(100.0);

      daStart.add(-90.0);
      daAngle.add(100.0);

      daStart.add(-180.0);
      daAngle.add(100.0);

      daStart.add(-270.0);
      daAngle.add(100.0);

      daStart.add(45.0);
      daAngle.add(100.0);


      daStart.add(0.0);
      daAngle.add(-100.0);

      daStart.add(90.0);
      daAngle.add(-100.0);

      daStart.add(180.0);
      daAngle.add(-100.0);

      daStart.add(270.0);
      daAngle.add(-100.0);

      daStart.add(-90.0);
      daAngle.add(-100.0);

      daStart.add(-180.0);
      daAngle.add(-100.0);

      daStart.add(-270.0);
      daAngle.add(-100.0);

      daStart.add(45.0);
      daAngle.add(-100.0);

      ::i32_rectangle rClient(m_rectangle);

      pdraw2dgraphics->fill_rectangle(rClient, argb(255, 192, 192, 185));

      int iColumnCount = 8;

      i32_rectangle r;

      r.top = 0;

      r.left = 0;

      r.bottom = rClient.center().y;

      int i = 0;

      int iColumnWidth = rClient.width() / iColumnCount;

      for (i = 0; i < iColumnCount && i < daStart.get_size(); i++)
      {

         r.right = r.left + iColumnWidth;

         draw_arc(pdraw2dgraphics, r, daStart[i], daAngle[i], bPath);

         r.left = r.right;

      }

      r.top = r.bottom;

      r.left = 0;

      r.bottom = rClient.bottom;

      for (; i < iColumnCount * 2 && i < daStart.get_size(); i++)
      {

         r.right = r.left + iColumnWidth;

         draw_arc(pdraw2dgraphics, r, daStart[i], daAngle[i], bPath);

         r.left = r.right;

      }

   }


   void simple_os_drag_and_drop::draw_arc(::draw2d::graphics_pointer & pdraw2dgraphics, i32_rectangle & r, ::f64 dStart, ::f64 dAngle, bool bPath)
   {


      auto pfont = createø < ::write_text::font > ();

      pfont->create_point_font(pnode->font_name(e_font_sans), 14.0, FW_LIGHT);

      pdraw2dgraphics->set_solid_color(argb(255, 0, 0, 0));

      pdraw2dgraphics->set(pfont);

      string str;

      str.formatf("Start: %d", dStart);

      pdraw2dgraphics->text_out(r.left, r.top, str);

      str.formatf("Angle: %d", dAngle);

      pdraw2dgraphics->text_out(r.left, r.top + 20, str);

      auto ppen = createø < ::draw2d::pen > ();

      if (dAngle < 0.0)
      {

         if (bPath)
         {

            ppen->create_solid(4.0, dk_red());

         }
         else
         {

            ppen->create_solid(4.0, argb(255, 255, 230, 155));


         }

      }
      else
      {

         if (bPath)
         {

            ppen->create_solid(4.0, argb(255, 255, 255, 255));

         }
         else
         {

            ppen->create_solid(4.0, argb(255, 50, 180, 255));

         }

      }

      pdraw2dgraphics->set(ppen);

      pdraw2dgraphics->arc(r, dStart, dAngle);


   }



} // namespace simple_os_drag_and_drop


