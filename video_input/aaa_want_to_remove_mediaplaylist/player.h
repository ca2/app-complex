#pragma once


namespace mediaplaylist
{


   class document;
   class info;


   class CLASS_DECL_APP_CORE_AUDIO player :
      virtual public ::mediaplaylist::listener
   {
   public:


      ::mediaplaylist::document *               m_pplaylistdoc;
      ::multimedia_playlist::playlist *         m_pplPlaying;
      bool                                      m_bAlbumArt;
      pointer_array < ::image >                       m_imageaAlbum;
      pointer_array < ::image >                       m_imageaAlbum128;


      player();
      virtual ~player();


      virtual void initialize(::particle * pparticle) override;


      virtual void OnClosePlayer();

      virtual bool DoesImplementSongNumber();
      virtual i32 GetSongNumber(const wchar_t * lpcwsz);

      virtual void PlaylistOnBeforeOpen();

      virtual void playlist_on_playback_end();

      virtual void PlaylistPlayByIndex(::raw::index iIndex);
      virtual bool PlaylistPlay(::raw::index iOffset);
      virtual bool PlaylistPlayRandomItem();
      virtual e_play PlaylistPlay(info * pinfo);

      virtual bool is_playing();

      virtual void _ExecuteStop();

      virtual void set_album_art(pointer_array < ::image > & imagea);

   };


} // namespace mediaplaylist



