#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_SIMPLE_HELLOWORLD frame :
      public simple_frame_window
   {
   public:


      frame(::context_object * pcontextobject);
      virtual ~frame();


	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;


      virtual bool get_translucency(::user::ETranslucency & etranslucency);
      virtual ::experience::frame * experience_get_frame();

      virtual bool has_pending_graphical_update() override;


   };


} // namespace helloworld




