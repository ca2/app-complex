#include "framework.h"
#include "aura/application.h"
#include "aura/update.h"



namespace simple_app
{


   application::application()
   {

      m_strAppId = "app-simple/app";

      m_strAppName = "app-simple/app";

      m_strBaseSupportId = "app_simple_app";

      m_bLicense = false;

   }


   application::~application()
   {

   }


   void application::init_instance()
   {

      if (!::aura::application::init_instance())
      {

         return false;

      }

      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

      __refer(m_pwindow, __create_new < window >());

      ::rectangle_i32 rectangleWindow;

      m_pwindow->_001InitialFramePosition(rectangleWindow, {0.05, 0.05, 0.4, 0.4});

      ::user::system cs(0, nullptr, "simple_app", WS_VISIBLE, rectangleWindow);

      m_pwindow->create_window_ex(cs);

      m_pwindow->display(e_display_restored);

      m_pwindow->place(rectangleWindow);

      m_pwindow->set_need_layout();

      m_pwindow->set_need_redraw();

      m_pwindow->post_redraw();

   }


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   __namespace_application_factory("app-simple/app");


} // namespace simple_app







//
//extern "C"
//::acme::library * app_simple_drawing_get_new_library()
//{
//
//   return new ::apex::single_application_library < ::simple_app::application >("app-simple/drawing");
//
//}
//
//
//aura_app aura_app_simple_drawing("app-simple/drawing", &app_simple_drawing_get_new_library);
//
//
//simple_app::application application;


