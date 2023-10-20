#pragma once


#include "core/platform/application.h"


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE application :
      virtual public ::core::application
   //,virtual public ::html::application
   {
   public:

      
      ::pointer<video_input::video_input>   m_pvideoinput;
      ::pointer<video_input::device>        m_pvideoinputdevice;



      document *                             m_pdocument;
      ::user::single_document_template *     m_ptemplateVideoCaptureMain;
      ::user::single_document_template *     m_ptemplateVideoCaptureImpact;


      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



      void init_instance() override;
      //virtual void exit_instance() override;

      void on_request(::request * prequest) override;

      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


      string prepare_impact_options_main_body() override;


      virtual string get_current_video_input_device();
      virtual void set_current_video_input_device(const ::string & strDevice);
      virtual void set_current(::video_input::device * pdevice);


   };


} // namespace app_complex_video_capture



