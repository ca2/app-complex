#pragma once


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM main_impact:
      virtual public ::application_consumer < application, ::app_simple_form::main_impact >
   {
   public:


      main_impact();
      ~main_impact() override;


      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact() override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace app_complex_form




