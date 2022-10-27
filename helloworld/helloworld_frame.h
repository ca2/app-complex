#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_SIMPLE_HELLOWORLD frame :
      public simple_frame_window
   {
   public:


      frame(::particle * pparticle);
      virtual ~frame();


	   void assert_ok() const override;
	   void dump(dump_context & dumpcontext) const override;


      virtual bool get_translucency(::user::ETranslucency & etranslucency);
      virtual ::experience::frame * frame_experience();

      virtual bool has_pending_graphical_update() override;


   };


} // namespace helloworld




