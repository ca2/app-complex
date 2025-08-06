#pragma once


#include "berg/user/simple/frame_window.h"


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM frame :
      virtual public simple_frame_window
   {
   public:


      frame();
      ~frame() override;


	   // void assert_ok() const override;
	   // void dump(dump_context & dumpcontext) const override;


      //::user::enum_translucency get_translucency(::user::style * pstyle) override;


   };


} // namespace simple_form












