#include "framework.h"



namespace mediaplaylist
{


   frame::frame(::particle * pparticle) :
      ::object(pparticle),
      simple_frame_window(pparticle),
      m_toolbar(pparticle)
   {
      

   }

   frame::~frame()
   {
   }

   void frame::install_message_routing(::channel * pchannel)
   {
      simple_frame_window::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &frame::on_message_create); 
   }

 
   void frame::on_message_create(::message::message * pmessage) 
   {

      __UNREFERENCED_PARAMETER(pmessage);


      LoadToolBar(0,"playlist_toolbar.xml");


   }

   ::pointer<::user::impact>frame::GetParentLyricWindow()
   {
      ::pointer<::user::interaction>pParentWnd = get_parent();
      if(pParentWnd != nullptr && base_class <::user::impact >::bases(pParentWnd))
         return  (pParentWnd);
      return nullptr;
   }


} // namespace mediaplaylist



