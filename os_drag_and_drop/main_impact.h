#pragma once


namespace simple_os_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_OS_DRAG_AND_DROP main_impact:
      virtual public ::user::split_impact
   {
   public:


      // ::userex::top_impact* m_ptopview;
      impact *                  m_pimpact;


      main_impact();
      virtual ~main_impact();


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact() override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      virtual bool BaseOnControlEvent(::user::control_event * pevent);


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;



   };


} // namespace simple_os_drag_and_drop





