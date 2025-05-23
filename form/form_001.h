#pragma once


#include "form.h"
#include "app-simple/form/form_001.h"


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM form_001 :
      virtual public form,
      virtual public app_simple_form::form_001
   {
   public:


      form_001();
      ~form_001() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


#ifdef _DEBUG
      long long increment_reference_count() override;
      long long decrement_reference_count() override;
#endif

      void install_message_routing(::channel * psender) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   };


} // namespace app_complex_form



