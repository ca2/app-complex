#pragma once


namespace multimedia_playlist
{


   class CLASS_DECL_APP_CORE_AUDIO track:
      virtual public ::object
   {
   public:


      //sp_track *              m_tr;

      session *               m_psession;
      playlist *              m_pl;
      ::collection::index                   m_iIndex;
      string                  m_strName;
      //::duration m_durationLastUpdate;
      bool                    m_bNew;
      string_array                 m_straArtist;
      string                  m_strArtist;
      string                  m_strAlbum;
      string                  m_strUri;
      string                  m_strUrl;
      bool                    m_bLoading;
      ::duration                  m_durationLoading;


      track();
      virtual ~track();


      virtual void initialize_multimedia_playlist_playlist(session * psession);


      virtual bool load(::payload payloadFile);

      virtual string   get_name();
      virtual string   get_artist();
      virtual string_array  get_artista();
      virtual string   get_id();
      virtual string   get_album();

      virtual string   get_uri();

      virtual string   get_path();

      virtual void on_update();
      virtual bool update();

   };


} // namespace multimedia_playlist


