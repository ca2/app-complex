#pragma once


namespace app_complex_impact3d
{


   class CLASS_DECL_APP_COMPLEX_IMPACT3D frame :
      virtual public simple_frame_window
   {
   public:


      frame();
      virtual ~frame();


	   void assert_ok() const override;
	   void dump(dump_context & dumpcontext) const override;


      //virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace app_complex_impact3d












