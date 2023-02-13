#include "framework.h"

#include "PlaylistInterface.h"

namespace imediamanager
{


   playlist_interface::playlist_interface()
   {
      m_pplayer = nullptr;
   }

   playlist_interface::~playlist_interface()
   {

   }
      
   void playlist_interface::playlist_on_next_song()
   {
   }

   void playlist_interface::SetPlayer(player_interface *pplayer)
   {
      m_pplayer = pplayer;
   }

} // namespace imediamanager


