#pragma once


namespace simple_form
{


   class CLASS_DECL_APP_SIMPLE_FORM tab_view :
      virtual public ::user::tab_view,
      virtual public ::user::form_callback
   {
   public:


      ::user::split_view *                            m_ptopviewLast;
      impact *                                          m_pviewLast;
      string                                          m_strTopicTitle;


      __pointer(::user::document)                            m_pdocMenu;


      tab_view();
      ~tab_view() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::subject * psubject, ::context * pcontext) override;
      void on_change_cur_sel() override;

      //virtual void handle(::subject * psubject, ::context * pcontext) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace simple_form













