#include "framework.h"
#include "aura/application.h"
#include "aura/update.h"


namespace complex_drawing
{


   application::application() 
   {
      
      m_ptemplateSimpleDrawingMain = nullptr;

      m_ptabview = nullptr;

      m_strAppId = "app-complex/drawing";

      m_strAppName = "app-complex/drawing";

      m_strBaseSupportId = "ca2_flag";

      m_bLicense = false;

      m_bMultiverseChat = true;

      m_strMainTitle = "Simple Drawing";

   }


   application::~application()
   {

   }


   ::type application::get_pane_view_type() const
   {

      return __type(pane_view);

   }


   ::estatus application::init_instance()
   {

      auto puser = User;

      puser->will_use_view_hint(FONTSEL_IMPACT);

      create_factory <::complex_drawing::pane_view >();

      if (!::simple_drawing::application::init_instance())
      {

         return false;

      }

      add_matter_locator("app-simple/drawing");

      return true;

   }


   __namespace_application_factory("app-complex/drawing");


} // namespace complex_drawing



