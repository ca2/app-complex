#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE application :
      virtual public ::core::application
   //,virtual public ::html::application
   {
   public:


      enum enum_type
      {

         type_normal,
         type_mili,

      };

      enum_type                                 m_etype;
      string                                 m_strHelloMultiverse;
      string                                 m_strHelloMultiverseDefault;
      string                                 m_strAlternateHelloMultiverse;
      string                                 m_strAlternateHelloMultiverseDefault;

      bool                                   m_bMultiverseChat;

      bool                                   m_bMFStartup;

      ::user::document *                     m_pdocMenu;
      ::user::single_document_template *     m_ptemplateHelloMultiverseMain;
      ::user::single_document_template *     m_ptemplateHelloMultiverseImpact;

      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



      void init_instance() override;
      //virtual void exit_instance() override;

      virtual void on_request(::request * prequest) override;

      virtual i64 increment_reference_count();
      virtual i64 decrement_reference_count();

   };


} // namespace app_complex_video_capture



