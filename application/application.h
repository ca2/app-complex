#pragma once



namespace simple_application
{


   class CLASS_DECL_APP_SIMPLE_APPLICATION application :
      virtual public ::aura::application
   {
   public:



      ::user::document *                              m_pdocMenu;
      ::pointer<::user::single_document_template>  m_ptemplateSimpleDrawingMain;
      pane_impact *                                     m_ppaneimpact;

      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


      virtual string preferred_experience() override;
      void init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::request * prequest) override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

   };


} // namespace simple_application



