#pragma once


namespace simple_form
{


   class CLASS_DECL_APP_SIMPLE_FORM simple_form :
      virtual public ::user::form_view
   {
   public:


      tab_view *                          m_ptabview;
      string                              m_strFont;
      int                                 m_iId;


      simple_form();
      virtual ~simple_form();

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif

      virtual void install_message_routing(::channel * psender) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace simple_form


