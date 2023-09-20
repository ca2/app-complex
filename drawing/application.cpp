#include "framework.h"
#include "application.h"
#include "pane_impact.h"
#include "apex/database/stream.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/still.h"
#include "axis/user/user/line_layout.h"
#include "core/platform/session.h"
#include "core/user/user/user.h"


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

      return ::type < pane_impact >();

   }


   void application::init_instance()
   {


      auto psession = get_session();

      auto puser = psession->user()->m_pcoreuser;

      puser->will_use_impact_hint(FONTSEL_IMPACT);

      factory()->add_factory_item <::app_complex_drawing::pane_impact >();

      ::app_simple_drawing::application::init_instance();

      //if (!::app_simple_drawing::application::init_instance())
      //{

      //   return false;

      //}

      application_properties().m_strMainTitle = "Simple Drawing";

      add_matter_locator("app-simple/drawing");

      //return true;

   }


   void application::create_options_body(::user::interaction * puserinteractionParent)
   {

      auto pstillTitle = create_label<::user::still>(puserinteractionParent, "Complex Drawing Options");

      __defer_construct(pstillTitle->m_pfont);

      pstillTitle->m_pfont->create_font(e_font_sans_ui, 24_pt);

      {

         auto playoutLine = create_line_layout(puserinteractionParent, e_orientation_horizontal);

         auto pcheckbox = create_check_box<::user::check_box>(playoutLine, "simple_checkbox");

         //bool bCheck = false;

         //if (acmeapplication()->m_papexapplication->datastream()->get("simple_checkbox", bCheck))
         //{

         //   pcheckbox->_001SetCheck(bCheck, ::e_source_initialize);

         //}

         //pcheckbox->m_callbackOnCheck = [this](auto pcheck)
         //   {

         //      bool bCheck = pcheck->bcheck();

         //      acmeapplication()->m_papexapplication->datastream()->set("simple_checkbox", bCheck);

         //      //::pointer <application> papplication = acmeapplication();

         //      //papplication->on_change_synchronize_with_weather();

         //   };

         create_label<::user::still>(playoutLine, "Simple");

      }

      {

         auto playoutLine = create_line_layout(puserinteractionParent, e_orientation_horizontal);

         auto pcheckbox = create_check_box<::user::check_box>(playoutLine, "no_client_frame");

         //bool bCheck = false;

         ////if (acmeapplication()->m_papexapplication->datastream()->get("no_client_frame", bCheck))
         ////{

         ////   pcheckbox->_001SetCheck(bCheck, ::e_source_initialize);

         ////}

         //pcheckbox->m_callbackOnCheck = [this](auto pcheck)
         //   {

         //      bool bCheck = pcheck->bcheck();

         //      acmeapplication()->m_papexapplication->datastream()->set("no_client_frame", bCheck);

         //      //::pointer <application> papplication = acmeapplication();

         //      //papplication->on_change_synchronize_with_weather();

         //   };

         create_label<::user::still>(playoutLine, "No Client Frame");

      }

      //auto pstill = __new(::user::still);

      //__construct_new(m_pedit);

      //__construct_new(m_pbuttonClear);

      //__construct_new(m_pbuttonSend);

      //__construct_new(m_pstillReceiver);

      //m_pstill->create_control(this, "still");

      //m_pedit->create_control(this, "edit");

      //m_pedit->add_handler(this);

      //m_pbuttonClear->create_control(this, "clear_button");

      //m_pbuttonClear->add_handler(this);

      //m_pbuttonSend->create_control(this, "send_button");

      //m_pbuttonSend->add_handler(this);

      //m_pstill->set_window_text("Enter memory_new text:");

      //m_pstillReceiver->create_control(this, "still");

      //m_pstillReceiver->set_window_text("(Waiting to receive...)");

      //m_pedit->m_strEmtpyText = "Enter New Text Here";

      //string strInitialText;

      //auto papp = get_app();

      //papp->datastream()->get("last_text", strInitialText);

      //m_pedit->_001SetText(strInitialText, ::e_source_initialize);

      //m_pbuttonClear->set_window_text("Clear");

      //m_pbuttonSend->set_window_text("Send");

   }


} // namespace complex_drawing



