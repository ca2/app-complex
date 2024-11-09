#include "framework.h"



namespace mediaplaylist
{


   listener::listener()
   {

   }

   listener::~listener()
   {

   }

   void listener::on_event(e_happening ehappening)
   {
      __UNREFERENCED_PARAMETER(ehappening);
   }


   ::pointer<::mediaplaylist::document> listener::_001OnBeforeOpenPlaylist()
   {
      return nullptr;
   }


} // namespace mediaplaylist


