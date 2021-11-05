#pragma once


namespace simple_os_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_OS_DRAG_AND_DROP tab_view :
      virtual public ::user::tab_view,
      virtual public ::user::form_callback,
      virtual public __application_consumer
   {
   public:


      ::user::split_view *                            m_ptopviewLast;
      impact *                                          m_pviewTopic;
      string                                          m_strTopicTitle;


      __pointer(::user::document)                     m_pdocMenu;


      tab_view();
      virtual ~tab_view();


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      bool BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent);
      void on_change_cur_sel() override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace simple_os_drag_and_drop













