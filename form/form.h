#pragma once


#include "app-simple/form/form.h"


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM form :
      virtual public ::app_simple_form::form
   {
   public:



      form();
      ~form() override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

#ifdef _DEBUG
      int64_t increment_reference_count() override;
      int64_t decrement_reference_count() override;
#endif

      void install_message_routing(::channel * psender) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace app_complex_form



