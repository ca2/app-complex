#pragma once


namespace complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM form_001 :
      virtual public form,
      virtual public simple_form::form_001
   {
   public:


      form_001();
      ~form_001() override;


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


#ifdef _DEBUG
      int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

      void install_message_routing(::channel * psender) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::subject * psubject, ::context * pcontext) override;


   };


} // namespace complex_form



