#pragma once

namespace imediamanager
{

   class playlist_interface;

   class CLASS_DECL_APP_CORE_AUDIO player_interface  
   {
   protected:

      playlist_interface   * m_pplaylist;

   public:

      player_interface();
      virtual ~player_interface();

      void set_playlist(playlist_interface * pplaylist);

   //   virtual void PlayerPlay(playlist_document * pdocument, const wchar_t * lpcwsz, mediaplaylist::ESetCurrentSongHint ehint, bool bMakeVisible);
      virtual void player_on_next_song();

   };

} // namespace imediamanager
