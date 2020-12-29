#pragma once



namespace simple_app
{


   class CLASS_DECL_APP_SIMPLE_APP application :
      virtual public ::aura::application
   {
   public:


      __reference(window)                             m_pwindow;


      application();
      virtual ~application();

      virtual ::e_status init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif

   };


} // namespace simple_app



