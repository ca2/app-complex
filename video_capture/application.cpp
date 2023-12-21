#include "framework.h"
#include "application.h"
#include "frame.h"
#include "main_frame.h"
#include "pane_impact.h"
#include "device_selector.h"
#include "document.h"
#include "impact.h"
#include "edit_impact.h"
#include "main_impact.h"
#include "top_impact.h"
#include "toggle_impact.h"
#include "acme/platform/system.h"
#include "acme/handler/request.h"
#include "apex/database/_binary_stream.h"
#include "base/user/user/single_document_template.h"
#include "app-complex/video_input/video_input.h"
#include "app-complex/video_input/device.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(app_complex_video_capture);


namespace app_complex_video_capture
{


   // __IMPLEMENT_APPLICATION_RELEASE_TIME1(app_complex_video_capture));


   application::application() 
   {

      //m_ptemplateVideoCaptureMain = nullptr;

      //m_ptemplateVideoCaptureImpact = nullptr;

      m_strAppId = "app-complex/video_capture";

      m_strBaseSupportId = "app-complex/video_capture";

      m_strAppName = "Video Capture";

      m_bLicense = false;

      m_bNetworking = false;

   }


   application::~application()
   {

   }


   void application::init_instance()
   {
      
      factory()->add_factory_item <::app_complex_video_capture::document >();
      factory()->add_factory_item <::app_complex_video_capture::frame >();
      factory()->add_factory_item <::app_complex_video_capture::main_frame >();
      factory()->add_factory_item <::app_complex_video_capture::edit_impact >();
      factory()->add_factory_item <::user::button_impact >();
      factory()->add_factory_item <::app_complex_video_capture::impact >();
      factory()->add_factory_item <::app_complex_video_capture::main_impact >();
      factory()->add_factory_item <::app_complex_video_capture::pane_impact >();
      factory()->add_factory_item <::app_complex_video_capture::top_impact >();
      factory()->add_factory_item <::app_complex_video_capture::toggle_impact >();
      factory()->add_factory_item <::app_complex_video_capture::device_selector >();

      ::aura::application::init_instance();
        
      add_impact_system("main",
      __allocate < ::user::single_document_template >(
                          "main",
                          ::type < ::user::document >(),
                          ::type < main_frame >(),
                          ::type < pane_impact >()));

      //add_document_template(pDocTemplate);

      //m_ptemplateVideoCaptureMain = pDocTemplate;

      add_impact_system(
         "impact",
      __allocate < ::user::single_document_template >(
                          "main",
                          ::type < document >(),
                          ::type < frame >(),
                          ::type < main_impact >()));

      //add_document_template(pDocTemplate);
      //
      //m_ptemplateVideoCaptureImpact = pDocTemplate;

#if defined(MACOS)

      auto pfactory = system()->factory("video_input", "avfoundation");

#elif defined(LINUX) || defined(FREEBSD)

      auto pfactory = system()->factory("video_input", "video_for_linux");

#elif defined(UNIVERSAL_WINDOWS)

      auto pfactory = system()->factory("video_input", "media_capture");

#else

      auto pfactory = system()->factory("video_input", "media_foundation");

#endif

      pfactory->merge_to_global_factory();

      __construct(m_pvideoinput);

      m_pvideoinput->update_device_list();


   }


   void application::on_request(::request * prequest)
   {

#if 0

#ifdef _DEBUG

      informationf("_DEBUG build? (basis)");

      ASSERT(false);

#else

      informationf("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      if(impact_system("main")->get_document_count() == 0)
      {

         impact_system("main")->request(prequest);

      }

      if(prequest->m_payloadFile.has_char())
      {

         impact_system("impact")->request(prequest);

      }


      //string strDevice;

      //datastream()->get("device", strDevice);

      //set_current_video_input_device(strDevice);


      //rectangle_i32 r(20, 20, 20, 20);

      //ClipCursor(rectangle);


   }




   i64 application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }

   i64 application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


   string application::prepare_impact_options_main_body()
   {

      string strMainBody;

      string strBilbo;

      for (auto & pitem : m_pvideoinput->itema())
      {

         ::pointer < ::video_input::device > pdevice = pitem;

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

      if (::is_set(pdevice) && !m_pvideoinput->itema().contains(pdevice))
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

         datastream()->set("device", pdevice->get_id2());

      }
      else
      {

         datastream()->set("device", "");

      }

   }


} // namespace app_complex_video_capture







