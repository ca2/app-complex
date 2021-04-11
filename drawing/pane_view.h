#pragma once


namespace complex_drawing
{


   class CLASS_DECL_APP_COMPLEX_DRAWING pane_view :
      virtual public ::application_consumer < application, ::userex::pane_tab_view >
      
   {
   public:


      ::user::split_view *                      m_ptopviewLast;
      __reference(::simple_drawing::view)       m_pviewTopic;
      string                                    m_strTopicTitle;


      __pointer(::user::document)               m_pdocMenu;


      pane_view();
      virtual ~pane_view();



      //virtual ::e_status on_initialize_object() override;


      //inline ::complex_drawing::application* get_application() const { return ::application_consumer < ::complex_drawing::application>::application(); }


      void on_create_impact(::user::impact_data * pimpactdata) override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      bool BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent);
      void on_change_cur_sel() override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void on_change_cur_sel() override;

      //virtual string get_hover_font();

   };


} // namespace complex_drawing













