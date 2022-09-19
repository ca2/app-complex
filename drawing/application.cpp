#include "framework.h"
#include "application.h"
#include "pane_impact.h"
#include "core/platform/session.h"
#include "core/user/user/user.h"


//IMPLEMENT_APPLICATION(app_complex_drawing);


namespace app_complex_drawing
{


   application::application() 
   {
      
      m_ptemplateSimpleDrawingMain = nullptr;

      m_ptabimpact = nullptr;

      m_strAppId = "app-complex/drawing";

      m_strAppName = "Complex Drawing";

      m_strBaseSupportId = "app-complex/drawing";

      m_bLicense = false;

      m_bMultiverseChat = true;

   }


   application::~application()
   {

   }


   ::type application::get_pane_impact_type() const
   {

      return __type(pane_impact);

   }


   void application::init_instance()
   {


      auto psession = get_session();

      auto puser = psession->user()->m_pcoreuser;

      puser->will_use_impact_hint(FONTSEL_IMPACT);

      ::factory::add_factory_item <::app_complex_drawing::pane_impact >();

      ::app_simple_drawing::application::init_instance();

      //if (!::app_simple_drawing::application::init_instance())
      //{

      //   return false;

      //}

      application_properties().m_strMainTitle = "Simple Drawing";

      add_matter_locator("app-simple/drawing");

      //return true;

   }


} // namespace complex_drawing



