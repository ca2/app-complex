#include "framework.h"



namespace mediaplaylist
{


   listener::listener()
   {

   }

   listener::~listener()
   {

   }

   void listener::on_event(e_event eevent)
   {
      __UNREFERENCED_PARAMETER(eevent);
   }


   ::mediaplaylist::document * listener::_001OnBeforeOpenPlaylist()
   {

      return nullptr;

   }


} // namespace mediaplaylist


