#pragma once


#include "app-core/multimedia/imedia/_.h"


namespace mediaplaylist
{


   class impact;
   class document;


   class CLASS_DECL_APP_CORE_AUDIO info
   {
   public:


      info();
      virtual ~info();

      
      huge_natural                                  m_uHint;


      ::user::document *                     m_pdocument;
      string                                 m_strFilePath;
      ::collection::index                                  m_iCurrentSong;
      bool                                   m_bRandom;
      bool                                   m_bMakeVisible;
      ::duration                            m_time;
      ::action_context                              m_context;
      bool                                   m_bFadeIn;
      bool                                   m_bPendingRestart;

   };


   class CLASS_DECL_APP_CORE_AUDIO document :
      public ::user::document,
      public imediamanager::playlist_interface,
      public ::mediaplaylist::listener
   {
   public:


      


      enum EAddSong
      {

         AddSongOnly,
         AddSongAndPlay,
         AddSongAndPlayIfNotPlaying,

      };


      ::pointer < ::mutex >                                  m_pmutexData;
      ::pointer<::multimedia_playlist::playlist>   m_pplaylistImpact;
      ::pointer<::multimedia_playlist::playlist>   m_pplaylistPlay;
      ::pointer<::multimedia_playlist::playlist>   m_pplaylistPlayback;

      ::file::path                           m_pathFile;
      ::file::path                           m_filepathPreviousRegular;

      bool                                   m_bPendingRestart;


      index_array                            m_iaQueue;
      //::pointer<player>                       m_pplayer;

      // pre calculated values
      ::collection::count                             m_iCurrentPlaylistSongCount;
      string_array                             m_straQueue;

      string_array                             m_straImpact;
      string_array                             m_straPlay;
      string_array                             m_straOnAddPlay;
      string_array                             m_straOnAddQueue;




      address_array < listener * >     m_listenera;
      player *                         m_pplayer;


      static const                     LPARAM LHINT_FRAMEDOWN;
      static const                     LPARAM LHINT_FRAMEUP;


      document();
      virtual ~document();

      virtual huge_integer increment_reference_count()
      {

         return ::object::increment_reference_count();

      }

      virtual huge_integer decrement_reference_count()
      {

         return ::object::decrement_reference_count();

      }


      virtual void delete_contents();


      virtual stream & write(stream & outputstream) const override;
      virtual stream & read(stream & inputstream) override;

      virtual bool on_save_document(::payload payloadFile);

      void add_listener(::mediaplaylist::listener * plistener);
      void erase_listener(::mediaplaylist::listener * plistener);

      void set_player(::mediaplaylist::player * spplayer);
      ::mediaplaylist::player * get_player();


      virtual void set_current_playlist(const ::string & pszPath);
      virtual string get_current_playlist_path();
      virtual string get_default_playlist_path();



      ::multimedia_playlist::playlist * impact_playlist();
      ::multimedia_playlist::playlist * play_playlist();
      ::multimedia_playlist::playlist * playback_playlist();

      void set_impact_playlist(::multimedia_playlist::playlist * pplaylist);
      void set_play_playlist(::multimedia_playlist::playlist * pplaylist);
      void set_playback_playlist(::multimedia_playlist::playlist * pplaylist);


      //virtual void on_change_impact_playlist();

      //virtual void on_change_play_playlist();

      //virtual void on_change_playlist();

      //virtual void ensure_playlist();

      virtual void defer_update_songs(const string_array * pstraNew = nullptr, const string_array * pstraDel = nullptr);
      virtual bool update_songs(string_array & stra, bool bEditingPlaylist);


      virtual void on_update_playlist();


      virtual void Popimpacts();


      virtual bool restart(const ::action_context & action_context, bool bFadeIn);

      virtual void populate_queue(::collection::index iSong);

      virtual void on_final_release();
      virtual bool on_open_document(const ::payload & payloadFile) override;
      virtual bool defer_open_discard_erase_first();
      virtual void on_close_document();
      virtual bool on_new_document();
      virtual bool on_new_playlist();
      virtual bool save_modified();

//      virtual ::pointer<::mediaplaylist::player>get_player();
      virtual ::pointer<::user::impact>GetFirstAttachableImpact();
      virtual bool IsDefaultPath();
      virtual bool IsDefaultPath(const ::file::path & path);

      virtual void OnRemoveSong(::pointer<::user::impact>pimpact = nullptr);
      virtual bool IsDefaultPlaylist();
      virtual void DoDefaultPlaylistSave();
      virtual void DoPlaylistSave();
      virtual void OnChangeSongs(::pointer<::user::impact>pimpact = nullptr);
      virtual void OnAddSong();
      virtual ::collection::count get_song_count(bool bEditingPlaylist);
      virtual ::collection::index get_current_song(bool bEditingPlaylist);

      virtual bool get_song_at(::file::path & str, ::collection::index iSong, bool bEditingPlaylist);
      virtual bool pick_song(::collection::index & iSong, string & str, bool bRandom, int & iLoop);

      virtual bool play(info * pinfo);

      virtual bool RemoveSong(::collection::index iSong, ::pointer<::user::impact>pimpact = nullptr, bool bUpdate = true);
      virtual string_array get_songs(bool bEditingPlaylist);
      virtual bool get_song_current_queue(string_array & stra, bool bEditingPlaylist);
      virtual void update_title();


      virtual bool AddSong(string_array & stra, bool bDoPlay, bool bMakeVisible);
      virtual bool AddSong(LPINT lpiaSongs, ::collection::count iSongCount, bool bDoPlay, bool bMakeVisible);

      virtual string AddSong(::payload payloadFile, EAddSong eaddsong, bool bMakeVisible, bool bUpdateAllImpacts, bool bAddDuplicate = true);
      virtual bool AddSong(::collection::index iSongCode, bool bDoPlay, bool bMakeVisible, bool bUpdateAllImpacts);




#ifdef _DEBUG
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
#endif

      virtual void OnPlay();



      virtual ::collection::count get_current_playlist_song_count();
      virtual ::collection::count get_current_queue_song_count();



      virtual bool has_next_song();




      bool do_save(const ::string & pszPathName, bool bReplace);

      void defer_restart_on_was_playing();
      void defer_check_restart();

      virtual void defer_update_spl();

   };


} // namespace mediaplaylist

