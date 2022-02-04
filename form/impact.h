#pragma once


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM impact :
      virtual public ::app_simple_form::impact
   {
   public:


      impact();
      ~impact() override;

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


      void install_message_routing(::channel * psender) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * psubject, ::context * pcontext) override;

      ::user::document * get_document();

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);


   };


} // namespace app_complex_form


