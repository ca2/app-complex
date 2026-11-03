#pragma once


namespace mediaplaylist
{


   class document;
   class info;


   class CLASS_DECL_APP_CORE_AUDIO player : 
      virtual public ::mediaplaylist::listener
   {
   public:


      ::pointer<::mediaplaylist::document>                   m_pplaylistdoc;



      player();
      virtual ~player();

      virtual void OnClosePlayer();

      virtual bool DoesImplementSongNumber();
      virtual int GetSongNumber(const wchar_t * lpcwsz);

      virtual void PlaylistOnBeforeOpen();

      virtual void playlist_on_playback_end();

      void PlaylistPlay(int iOffset);
      virtual e_play PlaylistPlay(info * pinfo);

      virtual bool is_playing();
   };


} // namespace mediaplaylist



