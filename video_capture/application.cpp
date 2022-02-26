#include "framework.h"


namespace app_complex_video_capture
{


   application::application() 
   {

      m_ptemplateVideoCaptureMain = nullptr;

      m_ptemplateVideoCaptureImpact = nullptr;

      m_strAppId = "app-complex/video_capture";

      m_strBaseSupportId = "app-complex/video_capture";

      m_strAppName = "Video Capture";

      m_bLicense = false;

   }


   application::~application()
   {

   }


   void application::init_instance()
   {
      
      ::factory::add_factory_item <::app_complex_video_capture::document >();
      ::factory::add_factory_item <::app_complex_video_capture::frame >();
      ::factory::add_factory_item <::app_complex_video_capture::main_frame >();
      ::factory::add_factory_item <::app_complex_video_capture::edit_view >();
      ::factory::add_factory_item <::user::button_view >();
      ::factory::add_factory_item <::app_complex_video_capture::impact >();
      ::factory::add_factory_item <::app_complex_video_capture::main_impact >();
      ::factory::add_factory_item <::app_complex_video_capture::pane_view >();
      ::factory::add_factory_item <::app_complex_video_capture::top_view >();
      ::factory::add_factory_item <::app_complex_video_capture::toggle_view >();
      ::factory::add_factory_item <::app_complex_video_capture::device_selector >();

      ::aura::application::init_instance();
        
      auto pDocTemplate = __new(::user::single_document_template(
                          "main",
                          __type(::user::document),
                          __type(main_frame),
                          __type(pane_view)));

      add_document_template(pDocTemplate);

      m_ptemplateVideoCaptureMain = pDocTemplate;

      pDocTemplate = __new(::user::single_document_template(
                          "main",
                          __type(document),
                          __type(frame),
                          __type(main_impact)));

      add_document_template(pDocTemplate);
      
      m_ptemplateVideoCaptureImpact = pDocTemplate;

#ifdef LINUX

      auto pfactory = m_psystem->factory("video_input", "video_for_linux");

#else

      auto pfactory = m_psystem->factory("video_input", "media_foundation");

#endif

      pfactory->merge_to_global_factory();

      __construct(m_pvideoinput);

      m_pvideoinput->update_device_list();

      string strDevice = data_get("device").get_string();

      set_current_video_input_device(strDevice);

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(false);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      if(m_ptemplateVideoCaptureMain->get_document_count() == 0)
      {

         m_ptemplateVideoCaptureMain->do_request(pcreate);

      }

      if(pcreate->m_pcommandline->m_payloadFile.has_char())
      {

         m_ptemplateVideoCaptureImpact->do_request(pcreate);

      }

      //rectangle_i32 r(20, 20, 20, 20);

      //ClipCursor(rectangle);


   }




   i64 application::increment_reference_count()
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   i64 application::decrement_reference_count()
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   string application::prepare_impact_options_main_body()
   {

      string strMainBody;

      string strBilbo;

      for (auto & pdevice : m_pvideoinput->devicea())
      {

         string strName = pdevice->get_name();

         string strId = "video_input_" + pdevice->get_id2();

         strBilbo += "<input type=\"checkbox\" id=\"" + strId + "\" />" + strName + "<br/>";


      }

      return strBilbo;

   }


   string application::get_current_video_input_device()
   {

      return m_pvideoinputdevice ? m_pvideoinputdevice->get_id2() : string();
      
   }
   
   
   void application::set_current_video_input_device(const ::string & strDevice)
   {

      auto pvideoinputdevice = m_pvideoinput->get_device_by_id2(strDevice);

      set_current(pvideoinputdevice);

   }

   
   void application::set_current(::video_input::device * pdevice)
   {

      if (::is_set(pdevice) && !m_pvideoinput->contains_device(pdevice))
      {

         throw ::exception(::error_invalid_parameter, "Device should make part of video input");

      }

      if (m_pvideoinputdevice)
      {

         m_pvideoinputdevice->stop_capturing();

         if (m_pvideoinputdevice == pdevice)
         {

            pdevice = nullptr;

         }

      }

      if (::is_set(pdevice))
      {

         pdevice->initialize_device();

         auto iFormat = pdevice->find_argb_32_format();

         pdevice->set_format(iFormat);

         pdevice->start_capturing();

      }

      m_pvideoinputdevice = pdevice;

      if (::is_set(pdevice))
      {

         data_set("device", pdevice->get_id2());

      }
      else
      {

         data_set("device", "");

      }

   }


} // namespace app_complex_video_capture







