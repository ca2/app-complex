#include "framework.h"
#include "aura/update.h"


namespace complex_drawing
{


   application::application() 
   {
      
      m_ptemplateSimpleDrawingMain = nullptr;

      m_ptabview = nullptr;

      m_strAppId = "app-complex/drawing";

      m_strAppName = "app-complex/drawing";

      m_strBaseSupportId = "app-complex/drawing";

      m_bLicense = false;

      m_bMultiverseChat = true;

   }


   application::~application()
   {

   }


   ::type application::get_pane_view_type() const
   {

      return __type(pane_view);

   }


   ::e_status application::init_instance()
   {


      auto psession = get_session();

      auto puser = psession->user()->m_pcoreuser;

      puser->will_use_view_hint(FONTSEL_IMPACT);

      create_factory <::complex_drawing::pane_view >();

      if (!::simple_drawing::application::init_instance())
      {

         return false;

      }

      properties().m_strMainTitle = "Simple Drawing";

      add_matter_locator("app-simple/drawing");

      return true;

   }


} // namespace complex_drawing



