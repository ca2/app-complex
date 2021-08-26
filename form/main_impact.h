#pragma once


namespace simple_form
{


   class CLASS_DECL_APP_SIMPLE_FORM main_impact:
      virtual public ::user::split_view,
      virtual public __application_consumer
   {
   public:


      //::userex::top_view *    m_ptopview;
      impact *                  m_pimpact;


      main_impact();
      virtual ~main_impact();


      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact() override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual bool BaseOnControlEvent(::user::control_event * pevent);


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;



   };


} // namespace simple_form





