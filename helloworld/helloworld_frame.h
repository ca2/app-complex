#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_SIMPLE_HELLOWORLD frame :
      public simple_frame_window
   {
   public:


      frame(::object * pobject);
      virtual ~frame();


	   void assert_valid() const override;
	   void dump(dump_context & dumpcontext) const override;


      virtual bool get_translucency(::user::ETranslucency & etranslucency);
      virtual ::experience::frame * experience_get_frame();

      virtual bool has_pending_graphical_update() override;


   };


} // namespace helloworld




