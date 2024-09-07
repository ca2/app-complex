#pragma once


namespace simple_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_DRAG_AND_DROP simple_drag_and_drop :
      virtual public ::object
   {
   public:


      rectangle_i32                                m_rectangle;
      ::user::impact *                    m_pimpact;
      string                              m_strFont;
      int                                 m_iDrawing;
      string_map < ::image::image_pointer >                m_pimagemap;


      simple_drag_and_drop();
      virtual ~simple_drag_and_drop();


      virtual int64_t increment_reference_count()
      {
         return ::object::increment_reference_count();
      }
      virtual int64_t decrement_reference_count()
      {
         return ::object::decrement_reference_count();
      }

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDrawArcs(::draw2d::graphics_pointer & pgraphics, bool bPath);

      virtual void draw_arc(::draw2d::graphics_pointer & pgraphics, rectangle_i32 & r, double dStart, double dAngle, bool bPath);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace simple_drag_and_drop


