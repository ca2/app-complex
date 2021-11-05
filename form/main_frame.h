#pragma once


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM main_frame :
      virtual public app_simple_form::main_frame
   {
   public:




      main_frame();
      ~main_frame() override;


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      ::experience::frame * experience_get_frame() override;

      bool has_pending_graphical_update() override;

   };


} // namespace simple_form




