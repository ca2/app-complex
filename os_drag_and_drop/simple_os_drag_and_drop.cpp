#include "framework.h"
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


   int64_t simple_os_drag_and_drop::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t simple_os_drag_and_drop::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   void simple_os_drag_and_drop::initialize_drag_and_drop(int iDragAndDrop)
   {

      m_iDragAndDrop = iDragAndDrop;

   }

   void simple_os_drag_and_drop::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void simple_os_drag_and_drop::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //INFO("simple_os_drag_and_drop::_001OnDraw (%d, %d)", m_rectangle.width(), m_rectangle.height());

      if(m_iDragAndDrop <= 3)
      {

         _001OnDraw1Through3(pgraphics);

      }
      else if(m_iDragAndDrop == 4)
      {

         _001OnDrawArcs(pgraphics, false);

      }
      else
      {

         _001OnDrawArcs(pgraphics, true);

      }

   }


   void simple_os_drag_and_drop::_001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::pen_pointer pen(e_create);

      ::draw2d::brush_pointer brush(e_create);

      ::write_text::font_pointer font(e_create);

      font->create_pixel_font(pnode->font_name(e_font_sans_ex), 100.0, 800);

      pgraphics->set(font);

      pen->create_solid(4.0, argb(255, 50, 180, 255));

      rectangle_i32 rectangle;

      int iSize = minimum(m_rectangle.width(), m_rectangle.height());

      iSize = iSize * 3 / 4;

      rectangle.set_size(iSize, iSize);

      rectangle.Align(e_align_center, m_rectangle);

      rectangle.offset_x(-iSize/5 * 3);

      rectangle.offset_x(iSize/5 * m_iDragAndDrop);

      if(m_iDragAndDrop == 3)
      {

         brush->CreatePatternBrush(get_image("matter://pat1.jpg"));

      }
      else
      {

         brush->CreateLinearGradientBrush(rectangle.top_left(), rectangle.bottom_right(), argb(255, 255, 255, 200), argb(255, 255, 125, 100));

      }

      pgraphics->set(pen);

      pgraphics->set(brush);

      pgraphics->ellipse(rectangle);

      if(m_iDragAndDrop >= 2)
      {

         ::rectangle_i32 rectText(rectangle);

         rectText.inflate(100, 100);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         if(m_iDragAndDrop == 3)
         {

            if(m_pimagemap["pat1grayed"]->is_null())
            {

               auto pimage1 = get_image("matter://pat1.jpg");
               
               /**pimage1 += { success, [this](auto & result)
               {
                  
                  ::image_pointer pimage = result;

                  m_pimpact->set_need_redraw();

                  ::image_pointer pimpl = pimage->clone();

                  ::image_pointer imageClone = pimpl;

                  m_pimagemap["pat1grayed"] = imageClone;

                  m_pimagemap["pat1grayed"]->saturation(0->0);

                  m_pimpact->set_need_redraw();
                  
                  m_pimpact->post_redraw();

                  return ::success;

               }};*/

            }

            brush->CreatePatternBrush(m_pimagemap["pat1grayed"]);

         }
         else
         {

            brush->CreateLinearGradientBrush(rectText.top_left(), rectText.bottom_right(), argb(255, 55, 210, 120), argb(255, 255, 255, 200));

         }

         pgraphics->set(brush);

         //pgraphics->draw_text("Simple Drawing", rectText, e_align_center);

      }

   }


   void simple_os_drag_and_drop::_001OnDrawArcs(::draw2d::graphics_pointer & pgraphics, bool bPath)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      double_array daStart;

      double_array daAngle;

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

      ::rectangle_i32 rClient(m_rectangle);

      pgraphics->fill_rectangle(rClient, argb(255, 192, 192, 185));

      int iColumnCount = 8;

      rectangle_i32 r;

      r.top = 0;

      r.left = 0;

      r.bottom = rClient.center().y;

      int i = 0;

      int iColumnWidth = rClient.width() / iColumnCount;

      for (i = 0; i < iColumnCount && i < daStart.get_size(); i++)
      {

         r.right = r.left + iColumnWidth;

         draw_arc(pgraphics, r, daStart[i], daAngle[i], bPath);

         r.left = r.right;

      }

      r.top = r.bottom;

      r.left = 0;

      r.bottom = rClient.bottom;

      for (; i < iColumnCount * 2 && i < daStart.get_size(); i++)
      {

         r.right = r.left + iColumnWidth;

         draw_arc(pgraphics, r, daStart[i], daAngle[i], bPath);

         r.left = r.right;

      }

   }


   void simple_os_drag_and_drop::draw_arc(::draw2d::graphics_pointer & pgraphics, rectangle_i32 & r, double dStart, double dAngle, bool bPath)
   {


      ::write_text::font_pointer font(e_create);

      font->create_point_font(pnode->font_name(e_font_sans), 14.0, FW_LIGHT);

      pgraphics->set_text_color(argb(255, 0, 0, 0));

      pgraphics->set(font);

      string str;

      str.Format("Start: %d", dStart);

      pgraphics->text_out(r.left, r.top, str);

      str.Format("Angle: %d", dAngle);

      pgraphics->text_out(r.left, r.top + 20, str);

      ::draw2d::pen_pointer pen(e_create);

      if (dAngle < 0.0)
      {

         if (bPath)
         {

            pen->create_solid(4.0, dk_red());

         }
         else
         {

            pen->create_solid(4.0, argb(255, 255, 230, 155));


         }

      }
      else
      {

         if (bPath)
         {

            pen->create_solid(4.0, argb(255, 255, 255, 255));

         }
         else
         {

            pen->create_solid(4.0, argb(255, 50, 180, 255));

         }

      }

      pgraphics->set(pen);

      pgraphics->Arc(r, dStart, dAngle);


   }



} // namespace simple_os_drag_and_drop


