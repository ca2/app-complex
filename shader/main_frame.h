#pragma once


namespace simple_shader
{


   class CLASS_DECL_APP_SIMPLE_SHADER main_frame :
      virtual public simple_main_frame
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame();
      virtual ~main_frame();


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      //virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;
      virtual ::experience::frame * frame_experience() override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace simple_shader












