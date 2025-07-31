#pragma once


namespace multimedia_playlist
{


   class CLASS_DECL_APP_CORE_AUDIO playlist :
      virtual public ::object
   {
   public:

      session *                        m_psession;
      string                           m_path;
      ::property_set                   m_setFile;
      ::collection::index                            m_iCurrentSong;
      bool                             m_bDiscard;
      bool                             m_bSearch;
      string                           m_strUrl;
      int                              m_iCurrentVScroll;

      string                           m_strName;
      string                           m_strTitle;
      pointer_array < track >                m_tracka;
      bool                             m_bNew;
      bool                             m_bNewTracks;
      ::collection::index                            m_iIndex;
      ::collection::count                          m_c;
      string_array                          m_stra;

      property_set                     m_setPlaylist;



      playlist();
      virtual ~playlist();

      
      virtual void initialize_multimedia_playlist_playlist(session * psession);


      virtual string get_name();

      virtual string_array get_stra();

      virtual void on_update();

      virtual void on_update_tracks();

      virtual bool update();

      virtual bool update_tracks();

      virtual void on_tracks_erased(const int * tracks, int num_tracks);

      virtual bool is_recursive();
      virtual bool is_loop();
      virtual bool is_shuffle();

      virtual bool save();
      virtual bool load(string strFile);

      virtual string add_song(::payload payloadFile, bool bAddDuplicate);
      virtual bool erase_song(::collection::index iSong, bool bUpdate= true);
      virtual void ensure_playlist();

      virtual ::collection::count get_count();


      virtual void set_int(const ::scoped_string & scopedstr, long long iValue);
      virtual long long get_int(const ::scoped_string & scopedstr, long long iDefault);
      virtual void set_string(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrValue);
      virtual string get_string(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrValue);



      virtual string get_title();

   };


} // namespace multimedia_playlist





