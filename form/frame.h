#pragma once


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM frame :
      virtual public simple_frame_window
   {
   public:


      frame();
      ~frame() override;


	   void assert_ok() const override;
	   void dump(dump_context & dumpcontext) const override;


      //virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace simple_form












