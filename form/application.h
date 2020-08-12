#pragma once



namespace simple_form
{


   class CLASS_DECL_APP_SIMPLE_FORM application :
      virtual public ::aura::application
   {
   public:


      bool                                   m_bMultiverseChat;

      ::user::document *                     m_pdocMenu;
      ::user::plain_edit_view *              m_prollfps;
      ::user::single_document_template *     m_ptemplateBeatMapperMain;
      ::user::single_document_template *     m_ptemplateBeatMapperView;


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


} // namespace simple_form



