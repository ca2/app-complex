#include "framework.h"
#include "aura/callback.h"
#include "aura/application.h"


namespace simple_message_box
{


   __IMPLEMENT_APPLICATION_RELEASE_TIME();
IMPLEMENT_APPLICATION_FACTORY();


   application::application()
   {

      m_strAppId = "app-simple/box";

      m_strAppName = "app-simple/box";

      m_strBaseSupportId = "app_simple_box";

   }


   application::~application()
   {


   }


   void application::on_request(::request * prequest)
   {

      m_strAppName = "Simple Message Box!!";

      add(e_callback_finish, [=](const ::payload & payload)
         {

            auto pcallbacks = callbacks(e_callback_finish);

            if (payload == "no")
            {

               message_box(
                  "Simple Message Box!! (message_box).<br><br>Finish?", 
                  nullptr,
                  ::user::e_message_box_yes_no | ::user::e_message_box_icon_information,
                  pcallbacks->first());

            }
            else
            {

               set_finish();

            }

         });

      receive(e_callback_finish, "no");

   }


   __namespace_application_factory("app-simple/box");


} // namespace simple_message_box





