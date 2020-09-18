#pragma once


namespace simple_form
{


   class CLASS_DECL_APP_SIMPLE_FORM frame :
      virtual public simple_frame_window
   {
   public:


      frame();
      virtual ~frame();


	   virtual void assert_valid() const override;
	   virtual void dump(dump_context & dumpcontext) const override;


      //virtual ::user::e_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace simple_form












