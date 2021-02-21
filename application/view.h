#pragma once


namespace simple_application
{


   class CLASS_DECL_APP_SIMPLE_APPLICATION view :
      virtual public ::user::impact,
      virtual public __application_consumer
   {
   public:

      ::write_text::font_pointer     m_pfontThomasBS_;
      string         m_strFont1;

      view();
      virtual ~view();

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif

      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnDestroy);

   };


} // namespace simple_application


