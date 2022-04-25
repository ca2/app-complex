#pragma once


namespace app_complex_impact3d
{


   class CLASS_DECL_APP_COMPLEX_IMPACT3D pane_impact :
      virtual public ::app_consumer < application, ::userex::pane_tab_impact, ::user::form_callback >
   {
   public:


      ::user::split_view *                      m_ptopviewLast;
      __reference(impact)                       m_pviewTopic;
      string                                    m_strTopicTitle;


      __pointer(::user::document)               m_pdocMenu;


      pane_impact();
      ~pane_impact() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      bool BaseOnControlEvent(::user::form_window * pimpact,::user::control_event * pevent);
      void on_change_cur_sel() override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //void on_change_cur_sel() override;


   };


} // namespace app_complex_impact3d













