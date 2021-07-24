#pragma once


namespace video_capture
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
      ::user::single_document_template *     m_ptemplateHelloMultiverseView;

      application();
      virtual ~application();


      virtual ::e_status init_instance() override;
      //virtual void exit_instance() override;

      virtual void on_request(::create * pcreate);

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

   };


} // namespace video_capture



