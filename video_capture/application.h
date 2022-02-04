#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE application :
      virtual public ::core::application
   //,virtual public ::html::application
   {
   public:

      
      __pointer(video_input::video_input)    m_pvideoinput;
      __pointer(video_input::device)         m_pvideoinputdevice;



      document *                             m_pdocument;
      ::user::single_document_template *     m_ptemplateVideoCaptureMain;
      ::user::single_document_template *     m_ptemplateVideoCaptureImpact;


      application();
      ~application() override;


      void init_instance() override;
      //virtual void exit_instance() override;

      virtual void on_request(::create * pcreate);

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


      string prepare_impact_options_main_body() override;


      virtual string get_current_video_input_device();
      virtual void set_current_video_input_device(const ::string & strDevice);


   };


} // namespace app_complex_video_capture



