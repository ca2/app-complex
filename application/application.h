#pragma once



namespace simple_application
{


   class CLASS_DECL_APP_SIMPLE_APPLICATION application :
      virtual public ::aura::application
   {
   public:



      ::user::document *                              m_pdocMenu;
      __composite(::user::single_document_template)   m_ptemplateSimpleDrawingMain;
      pane_view *                                     m_ppaneview;

      application();
      virtual ~application();

      virtual string preferred_experience() override;
      virtual ::estatus init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif

   };


} // namespace simple_application



