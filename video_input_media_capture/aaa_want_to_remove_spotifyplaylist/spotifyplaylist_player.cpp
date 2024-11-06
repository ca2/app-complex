#include "framework.h"



namespace mediaplaylist
{


   player::player()
   {

   }

   player::~player()
   {

   }

   e_play player::PlaylistPlay(info * pinfo)
   {
      __UNREFERENCED_PARAMETER(pinfo);
      return play_error_cancel;
   }

   bool player::DoesImplementSongNumber()
   {
      return false;
   }

   int player::GetSongNumber(const wchar_t * lpcwsz)
   {
      __UNREFERENCED_PARAMETER(lpcwsz);
      return -1;
   }

   void player::PlaylistPlay(int iOffset)
   {
      if(m_pplaylistdoc != nullptr)
      {
         info info;
         info.m_iCurrentSong     = m_pplaylistdoc->m_play.m_iCurrentSong + iOffset;
         info.m_ehint            = id_do_play;
         info.m_bMakeVisible     = true;
         m_pplaylistdoc->play(&info);
      }
   }

   void player::OnClosePlayer()
   {

      ///if(m_pplaylistdoc != nullptr)
         //m_pplaylistdoc->set_callback(nullptr);

   }


   void player::PlaylistOnBeforeOpen()
   {
   }


   void player::playlist_on_playback_end()
   {
      PlaylistPlay(1);
   }


   bool player::is_playing()
   {
      return false;
   }


} // namespace mediaplaylist

