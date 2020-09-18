#pragma once


namespace simple_form
{


   class CLASS_DECL_APP_SIMPLE_FORM main_frame :
      virtual public simple_main_frame
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame();
      virtual ~main_frame();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      //virtual ::user::e_translucency get_translucency(::user::style * pstyle) const override;
      virtual ::experience::frame * experience_get_frame() override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace simple_form












