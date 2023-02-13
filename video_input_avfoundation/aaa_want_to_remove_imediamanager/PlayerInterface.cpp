#include "framework.h"

#include "PlayerInterface.h"
#include "PlaylistInterface.h"

namespace imediamanager
{

   player_interface::player_interface()
   {
      m_pplaylist = nullptr;
   }

   player_interface::~player_interface()
   {

   }

   //void player_interface::PlayerPlay(playlist_document * pdocument, const wchar_t * lpcwsz, mediaplaylist::ESetCurrentSongHint ehint, bool bMakeVisible);
   void player_interface::player_on_next_song()
   {

      if(m_pplaylist != nullptr)
      {

         m_pplaylist->playlist_on_next_song();

      }

   }


   void player_interface::set_playlist(playlist_interface *pplaylist)
   {

      m_pplaylist = pplaylist;

   }


} // namespace imediamanager

