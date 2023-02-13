#pragma once


namespace user
{
   class multiple_document_template;
}


namespace mediaplaylist
{


   class CLASS_DECL_APP_CORE_AUDIO startup :
      public property_set
   {
   public:

      bool                 m_bFirstLoad; /// not serialized, cache/initialization information
      bool      &          m_bWasPlaying;
      string    &          m_strPlaylist;
      string    &          m_strPlaylistPlaying;
      ::file::path &       m_pathDefault;


      startup();


   };


   class document;
   class central_callback_interface;


   class CLASS_DECL_APP_CORE_AUDIO media_playlist :
      virtual public ::object
   {
   public:


      pointer_array < listener >                         m_listenera;
      ::user::interaction  *                       m_puiOwner;
      bool                                         m_bProcessingQueue;

      bool                                         m_bSimulatePlaybackEnd;
      bool                                         m_bPendingCheckForRestartOnWasPlaying;
      bool                                         m_bRestartFadeIn;



      string_array                                      m_straPlaylistQueue;


      ::pointer<user::single_document_template>          m_pimpactsystem;
      ::mediaplaylist::document *                  m_pplaylistdoc;
      ::type                                     m_typeFrameWnd;
      ::type                                     m_typeImpact;
      string                                       m_strMatter;
      bool                                         m_bOpenPlaylist;
      bool                                         m_bBeforeOpenPlaylist;

      ::pointer<::acme::library>                        m_plibrarySpotify;
      ::pointer<::multimedia_playlist::session>          m_psessionSpotify;
      ::pointer<::multimedia_playlist::web_api>          m_pspotifywebapi;

      ::multimedia_playlist::veriwell::session *   m_psessionVeriwell;

      ::mediaplaylist::playlist_list_impact *        m_pplaylistlistview;
      ::mediaplaylist::list_impact *                 m_plistview;

      ::pointer<startup>                          m_pstartup;



      media_playlist();
      virtual ~media_playlist();


      virtual void initialize(::particle * pparticle) override;


      void load_startup();
      void save_startup();

      bool initialize();


      ::mediaplaylist::document * GetNewPlaylist(bool bMakeVisible = false);

      ::mediaplaylist::document * GetDiscardPlaylist();
      ::mediaplaylist::document * GetDefaultPlaylist();
      ::mediaplaylist::document * GetCurrentPlaylist(bool bEmptyOk, bool bMakeVisible = false, ::user::interaction * puiParent = nullptr, e_window_flag ewindowflag = e_window_flag_none, ::atom atom = nullptr);

      ::mediaplaylist::document * OpenDiscardPlaylist(bool bMakeVisible, ::user::interaction* puiParent = nullptr, e_window_flag ewindowflag = e_window_flag_none, ::atom atom = nullptr);
      ::mediaplaylist::document * OpenDefaultPlaylist(bool bMakeVisible, ::user::interaction* puiParent = nullptr, e_window_flag ewindowflag = e_window_flag_none, ::atom atom = nullptr);
      ::mediaplaylist::document * OpenPlaylist(::payload payloadFile, bool bMakeVisible, ::user::interaction* puiParent = nullptr, e_window_flag ewindowflag = e_window_flag_none, ::atom atom = nullptr);

      ::multimedia_playlist::session *             spotify();
      inline ::pointer<::multimedia_playlist::web_api>   spotifywebapi() { return m_pspotifywebapi; }



      void OnCloseDefaultPlaylist();
      bool GetDiscardPath(::file::path & str);
      bool GetDefaultPath(::file::path & str, bool bLocal = false);
      bool GetPath(::file::listing & listing);
      bool GetFolder(::file::path & path);


      ::file::path get_new_playlist_path();


      virtual string calc_default_object_id();


      virtual ::multimedia_playlist::playlist * open_playlist(::payload payloadFile);


      void defer_initialize();


   };


} // namespace mediaplaylist

