#include "framework.h"



namespace mediaplaylist
{


   frame::frame()
   {



   }


   frame::~frame()
   {

   }


   void frame::install_message_routing(::channel * pchannel)
   {
      simple_frame_window::install_message_routing(pchannel);
      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &frame::on_message_create);
   }


   void frame::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);


      LoadToolBar(0, "mediaplaylist/playlist_toolbar.xml");


   }


   ::pointer<::user::impact>frame::GetParentLyricWindow()
   {

      ::pointer<::user::interaction>pParentWnd = get_parent();

      if (pParentWnd != nullptr && base_class <::user::impact >::bases(pParentWnd))
      {

         return pParentWnd;

      }

      return nullptr;

   }


} // namespace mediaplaylist



