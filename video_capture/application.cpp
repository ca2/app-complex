#include "framework.h"

//void throw_a_::exception::exception_through_one_single_function_boundary(string str)
//{
//
//   throw ::exception(::exception(str + " this is also a very artificial simple exception to test if exception can be safely thrown and caught at this environment (in this specific case: Android)... but across a single function boundary (thrown in function, should be caught in caller...) ..."));
//
//}

namespace app_complex_video_capture
{


   application::application() 
   {


      //m_ptopviewLast                          = nullptr;
      //m_pviewLast                            = nullptr;

      //m_ptopviewMain                          = nullptr;
      //m_pviewMain                          = nullptr;
      //m_ptoggleviewMain= nullptr;
      //m_peditMain= nullptr;

      //m_ptopviewSwitcher                          = nullptr;
      //m_pviewSwitcher                          = nullptr;
      //m_ptoggleviewSwitcher= nullptr;
      //m_peditSwitcher= nullptr;

      //m_ptopviewFont                          = nullptr;
      //m_pfontlistview                          = nullptr;
      //m_ptoggleviewFontSel= nullptr;
      //m_peditFontSel = nullptr;

      m_ptemplateVideoCaptureMain = nullptr;
      m_ptemplateVideoCaptureImpact = nullptr;


      m_strAppId = "app-complex/video_capture";

      m_strAppName = "app-complex/video_capture";

      m_strBaseSupportId = "app-complex/video_capture";


      m_bLicense              = false;


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

   //i32 application::exit_application()
   //{

   //   return ::aura::application::exit_application();
   //}

   void application::on_request(::create * pcreate)
   {
      //debug_filling_holding();

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

      if(pcreate->m_pcommandline->m_varFile.has_char())
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

      data_set("device", strDevice);

      m_pvideoinputdevice = m_pvideoinput->get_device_by_id2(strDevice);

   }


} // namespace app_complex_video_capture







