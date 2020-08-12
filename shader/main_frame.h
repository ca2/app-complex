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


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      //virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pinteraction) override;
      virtual ::experience::frame * experience_get_frame() override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace simple_shader












