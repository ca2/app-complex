#pragma once


namespace simple_os_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_OS_DRAG_AND_DROP simple_os_drag_and_drop :
      virtual public ::object
   {
   public:


      rectangle_i32                                m_rectangle;
      ::user::impact *                    m_pview;
      string                              m_strFont;
      int                                 m_iDragAndDrop;
      string_map < ::image_pointer >                m_pimagemap;


      simple_os_drag_and_drop();
      virtual ~simple_os_drag_and_drop();


#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

      virtual void initialize_drag_and_drop(int iDragAndDrop);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDrawArcs(::draw2d::graphics_pointer & pgraphics, bool bPath);

      virtual void draw_arc(::draw2d::graphics_pointer & pgraphics, rectangle_i32 & r, double dStart, double dAngle, bool bPath);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace simple_os_drag_and_drop


