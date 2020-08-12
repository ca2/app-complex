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


      //virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pinteraction) override;


   };


} // namespace simple_form












