#pragma once


namespace complex_form
{


   class CLASS_DECL_APP_SIMPLE_FORM complex_form :
      virtual public ::simple_form::form_view
   {
   public:



      simple_form();
      ~simple_form() override;

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

      void install_message_routing(::channel * psender) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace simple_form


