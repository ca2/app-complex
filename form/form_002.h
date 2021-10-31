#pragma once


namespace complex_form
{


   class CLASS_DECL_APP_SIMPLE_FORM complex_form_002 :
      virtual public complex_form,
      virtual public simple_form::simple_form_002,
   {
   public:



      simple_form_002();
      ~simple_form_002() override;

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

      void install_message_routing(::channel * psender) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::subject * psubject, ::context * pcontext) override;


   };


} // namespace simple_form


