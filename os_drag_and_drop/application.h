#pragma once



namespace simple_os_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_OS_DRAG_AND_DROP application :
      virtual public ::aura::application
   {
   public:


      ::user::document *                     m_pdocMenu;
      ::user::plain_edit_view *              m_prollfps;
      ::user::single_document_template *     m_ptemplateSimpleDrawingMain;
      ::user::single_document_template *     m_ptemplateSimpleDrawingView;


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

      virtual __pointer(view) create_simple_os_drag_and_drop_view(::user::impact * pimpactParent, ::user::impact_data * pimpactdata);

   };


} // namespace simple_os_drag_and_drop



