#pragma once


namespace simple_os_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_OS_DRAG_AND_DROP simple_os_drag_and_drop :
      virtual public ::object
   {
   public:


      int_rectangle                                m_rectangle;
      ::user::impact *                    m_pimpact;
      string                              m_strFont;
      int                                 m_iDragAndDrop;
      string_map_base < ::image::image_pointer >                m_pimagemap;


      simple_os_drag_and_drop();
      virtual ~simple_os_drag_and_drop();


#ifdef _DEBUG
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
#endif

      virtual void initialize_drag_and_drop(int iDragAndDrop);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDrawArcs(::draw2d::graphics_pointer & pgraphics, bool bPath);

      virtual void draw_arc(::draw2d::graphics_pointer & pgraphics, int_rectangle & r, double dStart, double dAngle, bool bPath);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace simple_os_drag_and_drop


