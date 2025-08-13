#pragma once


namespace simple_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_DRAG_AND_DROP simple_drag_and_drop :
      virtual public ::object
   {
   public:


      int_rectangle                                m_rectangle;
      ::user::impact *                    m_pimpact;
      string                              m_strFont;
      int                                 m_iDrawing;
      string_map_base < ::image::image_pointer >                m_pimagemap;


      simple_drag_and_drop();
      virtual ~simple_drag_and_drop();


      virtual long long increment_reference_count()
      {
         return ::object::increment_reference_count();
      }
      virtual long long decrement_reference_count()
      {
         return ::object::decrement_reference_count();
      }

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDrawArcs(::draw2d::graphics_pointer & pgraphics, bool bPath);

      virtual void draw_arc(::draw2d::graphics_pointer & pgraphics, int_rectangle & r, double dStart, double dAngle, bool bPath);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace simple_drag_and_drop


