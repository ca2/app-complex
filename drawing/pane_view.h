#pragma once


namespace complex_drawing
{


   class CLASS_DECL_APP_COMPLEX_DRAWING pane_view :
      virtual public ::simple_drawing::tab_view,
      virtual public ::userex::pane_tab_view
   {
   public:


      ::user::split_view *                      m_ptopviewLast;
      __reference(::simple_drawing::view)       m_pviewTopic;
      string                                    m_strTopicTitle;


      __pointer(::user::document)               m_pdocMenu;


      pane_view();
      virtual ~pane_view();


      void on_create_impact(::user::impact_data * pimpactdata) override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;


      DECL_GEN_SIGNAL(_001OnCreate);
      bool BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent);
      void on_change_cur_sel() override;

      virtual void update(::update * pupdate) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void on_change_cur_sel() override;

      //virtual string get_hover_font();

   };


} // namespace complex_drawing













