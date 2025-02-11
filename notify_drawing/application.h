#pragma once



namespace notify_drawing
{


   class CLASS_DECL_APP_SIMPLE_NOTIFY_DRAWING application :
      virtual public ::simple_drawing::application
   {
   public:


      ::user::document *                     m_pdocMenu;
      ::user::plain_edit_impact *              m_prollfps;
      ::user::single_document_template *     m_ptemplateNotifyDrawingMain;


      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


      virtual string preferred_experience() override;
      void init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::request * prequest) override;

#ifdef _DEBUG
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
#endif

      virtual ::pointer<simple_drawing::impact>create_simple_drawing_impact(::user::impact* pimpactParent, ::user::impact_data* pimpactdata) override;

   };


} // namespace notify_drawing



