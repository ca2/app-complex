#pragma once


namespace simple_application
{


   class CLASS_DECL_APP_SIMPLE_APPLICATION main_frame :
      virtual public simple_main_frame
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame();
      virtual ~main_frame();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      //::user::enum_translucency get_translucency(::user::style * pstyle) override;
      ::experience::frame * frame_experience() override;

      bool has_pending_graphical_update() override;

   };


} // namespace simple_application












