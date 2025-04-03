#pragma once


#include "form.h"
#include "app-simple/form/form_002.h"


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM form_002 :
      virtual public form,
      virtual public app_simple_form::form_002
   {
   public:



      form_002();
      ~form_002() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


#ifdef _DEBUG
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
#endif


      void install_message_routing(::channel * psender) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::handler_context * pcontext) override;


   };


} // namespace app_complex_form



