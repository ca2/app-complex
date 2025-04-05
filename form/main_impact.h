#pragma once


#include "app-simple/form/main_impact.h"


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM main_impact:
      virtual public ::app_consumer < application, ::app_simple_form::main_impact >
   {
   public:


      main_impact();
      ~main_impact() override;


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact() override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace app_complex_form




