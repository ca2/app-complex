#pragma once


#include "app-core/multimedia/imedia/imedia.h"


namespace mediaplaylist
{


   class impact;
   class document;


   class CLASS_DECL_APP_CORE_AUDIO info
   {
   public:


      info();
      virtual ~info();


      ::pointer<::user::document>                  m_pdocument;
      string                                 m_strFilePath;
      index                                  m_iCurrentSong;
      e_hint                                 m_ehint;
      bool                                   m_bMakeVisible;
      ::duration                       m_position;
      ::action_context                      m_context;
      bool                                   m_bFadeIn;

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


      class data:
         virtual public object
      {
      public:

         data(::particle * pparticle);
         virtual ~data();

         ::file::path                     m_path;
         xml::document                    m_xmldoc;
         ::property_set                   m_setFile;
         ::pointer<::xml::node>                 m_pnodePlaylist;
         ::pointer<::xml::node>                 m_pnodeCurrent;
         ::pointer<::xml::edit>                 m_pxmledit;

         index                            m_iCurrentSong;

         data & operator = (const data & data);

         void delete_contents();

         virtual void set_flag(const ::string & psz,bool bFlag);
         virtual bool get_flag(const ::string & psz,bool bDefault);
         virtual void set_int(const ::string & psz,i64 iValue);
         virtual i64 get_int(const ::string & psz,i64 iDefault);
         virtual void set_string(const ::string & psz, const ::string & pszValue);
         virtual string get_string(const ::string & psz, const ::string & pszValue);
         virtual bool is_recursive();
         virtual bool is_loop();
         virtual bool is_shuffle();

         void ensure_playlist();
      };

      data                             m_impact;
      data                             m_play;

      ::file::path                     m_pathFile;


      index_array                      m_iaQueue;
      //::pointer<player>                      m_pplayer;

      // pre calculated values
      ::count                          m_iCurrentPlaylistSongCount;
      string_array                          m_straQueue;


      pointer_array < listener >                    m_listenerspa;
      ::pointer<player>                      m_spplayer;


      static const                     LPARAM LHINT_FRAMEDOWN;
      static const                     LPARAM LHINT_FRAMEUP;


      document(::particle * pparticle);
      virtual ~document();


      virtual void delete_contents();


      void write(stream & outputstream);
      void read(stream & inputstream);

      virtual bool on_save_document(::payload payloadFile);

      void add_listener(::pointer<::mediaplaylist::listener>plistener);
      void erase_listener(::pointer<::mediaplaylist::listener>plistener);

      void set_player(::pointer<::mediaplaylist::player>spplayer);
      ::pointer<::mediaplaylist::player>get_player();


      virtual void set_current_playlist(const ::string & pszPath);
      virtual string get_current_playlist_path();
      virtual string get_default_playlist_path();


      //virtual void ensure_playlist();



      virtual void Popimpacts();


      virtual void restartconst ::action_context & action_context, bool bFadeIn);

      virtual void populate_queue(::index iSong);

      virtual void on_final_release();
      virtual bool on_open_document(const ::payload & payloadFile) override;
      virtual void on_close_document();
      virtual bool on_new_document();
      virtual bool on_new_playlist();
      virtual bool save_modified();

//      virtual ::pointer<::mediaplaylist::player>get_player();
      virtual ::pointer<::user::impact>GetFirstAttachableImpact();
      virtual bool IsDefaultPath();
      virtual bool IsDefaultPath(const ::file::path & lpcsz);

      virtual void OnRemoveSong(::pointer<::user::impact>pimpact = nullptr);
      virtual bool IsDefaultPlaylist();
      virtual void DoDefaultPlaylistSave();
      virtual void DoPlaylistSave();
      virtual void OnChangeSongs(::pointer<::user::impact>pimpact = nullptr);
      virtual void OnAddSong();
      virtual ::count get_song_count(bool bEditingPlaylist);
      virtual index get_current_song(bool bEditingPlaylist);

      virtual bool get_song_at(::file::path & str, index iSong, bool bEditingPlaylist);
      virtual bool pick_a_song(index & iSong, string & str);

      virtual bool play(info * pinfo);

      virtual bool RemoveSong(index iSong, ::pointer<::user::impact>pimpact = nullptr);
      virtual bool get_songs(string_array & stra, bool bEditingPlaylist);
      virtual bool get_song_current_queue(string_array & stra, bool bEditingPlaylist);
      virtual void update_title();


      virtual bool AddSong(string_array & stra, bool bDoPlay, bool bMakeVisible);
      virtual bool AddSong(LPINT lpiaSongs, ::count iSongCount, bool bDoPlay, bool bMakeVisible);

      virtual bool AddSong(::payload payloadFile, EAddSong eaddsong, bool bMakeVisible, bool bUpdateAllImpacts);
      virtual bool AddSong(index iSongCode, bool bDoPlay, bool bMakeVisible, bool bUpdateAllImpacts);


      

#ifdef _DEBUG
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
#endif

      virtual void OnPlay();



      virtual ::count get_current_playlist_song_count();
      virtual ::count get_current_queue_song_count();



      virtual bool has_next_song();




      bool do_save(const ::string & pszPathName, bool bReplace);

      void defer_restart_on_was_playing();

   };


} // namespace mediaplaylist

