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


__IMPLEMENT_APPLICATION_RELEASE_TIME(app_complex_drawing);
IMPLEMENT_APPLICATION_FACTORY(app_complex_drawing);


namespace app_complex_drawing
{


   // __IMPLEMENT_APPLICATION_RELEASE_TIME1(app_complex_drawing));


   application::application()
   {

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

      return typeid(pane_impact );

   }


   void application::init_instance()
   {


      

      auto puser = user();

      puser->will_use_impact_hint(FONTSEL_IMPACT);

      factory()->add_factory_item <::app_complex_drawing::pane_impact >();

      ::app_simple_drawing::application::init_instance();

      //if (!::app_simple_drawing::application::init_instance())
      //{

      //   return false;

      //}

      m_textMainTitle = { "Simple Drawing", ::e_source_initialize };

      add_matter_locator("app-simple/drawing");

      //return true;

   }


   void application::create_options_body(::user::interaction * puserinteractionParent)
   {

      auto pstillTitle = create_label<::user::still>(puserinteractionParent, "Complex Drawing Options");

      ødefer_construct(pstillTitle->m_pfont);

      pstillTitle->m_pfont->create_font(e_font_sans_ui, 24_pt);

      {

         auto playoutLine = create_line_layout(puserinteractionParent, e_orientation_horizontal);

         auto pcheckbox = create_check_box<::user::check_box>(playoutLine, m_checkSimple);

         //bool bCheck = false;

         //if (application()->datastream()->get("simple_checkbox", bCheck))
         //{

         //   pcheckbox->set_check(bCheck, ::e_source_initialize);

         //}

         //pcheckbox->m_callbackOnCheck = [this](auto pcheck)
         //   {

         //      bool bCheck = pcheck->bcheck();

         //      application()->datastream()->set("simple_checkbox", bCheck);

         //      //::pointer <application> papplication = application();

         //      //papplication->on_change_synchronize_with_weather();

         //   };

         create_label<::user::still>(playoutLine, "Simple");

      }

      {

         auto playoutLine = create_line_layout(puserinteractionParent, e_orientation_horizontal);

         auto pcheckbox = create_check_box<::user::check_box>(playoutLine, m_checkNoClientFrame);

         //bool bCheck = false;

         ////if (application()->datastream()->get("no_client_frame", bCheck))
         ////{

         ////   pcheckbox->set_check(bCheck, ::e_source_initialize);

         ////}

         //pcheckbox->m_callbackOnCheck = [this](auto pcheck)
         //   {

         //      bool bCheck = pcheck->bcheck();

         //      application()->datastream()->set("no_client_frame", bCheck);

         //      //::pointer <application> papplication = application();

         //      //papplication->on_change_synchronize_with_weather();

         //   };

         create_label<::user::still>(playoutLine, "No Client Frame");

      }

      //auto pstill = øallocate ::user::still();

      //øconstruct_new(m_pedit);

      //øconstruct_new(m_pbuttonClear);

      //øconstruct_new(m_pbuttonSend);

      //øconstruct_new(m_pstillReceiver);

      //m_pstill->create_control(this, "still");

      //m_pedit->create_control(this, "edit");

      //m_pedit->add_handler(this);

      //m_pbuttonClear->create_control(this, "clear_button");

      //m_pbuttonClear->add_handler(this);

      //m_pbuttonSend->create_control(this, "send_button");

      //m_pbuttonSend->add_handler(this);

      //m_pstill->set_window_text("Enter  text:");

      //m_pstillReceiver->create_control(this, "still");

      //m_pstillReceiver->set_window_text("(Waiting to receive...)");

      //m_pedit->m_strEmtpyText = "Enter New Text Here";

      //string strInitialText;

      //auto papp = get_app();

      //papp->datastream()->get("last_text", strInitialText);

      //m_pedit->set_text(strInitialText, ::e_source_initialize);

      //m_pbuttonClear->set_window_text("Clear");

      //m_pbuttonSend->set_window_text("Send");

   }


   ::string application::draw2d_get_default_implementation_name()
   {

      return ::app_simple_drawing::application::draw2d_get_default_implementation_name();

   }


} // namespace complex_drawing



