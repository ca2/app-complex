#pragma once


//typedef ::multimedia::decoder * CDECL NEW_MULTIMEDIA_DECODER(::particle * pparticle);
//
//typedef NEW_MULTIMEDIA_DECODER * LPFN_NEW_MULTIMEDIA_DECODER;


//namespace multimedia
//{
//
//
//   class CLASS_DECL_APP_CORE_AUDIO application :
//      virtual public ::aura::application,
//      virtual public ::mediaplay::document_container
//   {
//   public:
//
//
//      ::mediaplay::impact *                                   m_pmediaplayview;
//
//      ::pointer<::multimedia::department>                         m_pmultimedia;
//      ::pointer<::audio_mixer::department>            m_paudiomixer;
//      ::pointer<::audio_mixer_user_base::department>   m_paudiomixeruserbase;
//      ::pointer<::multimedia::file_application>                   m_pmultimediafile;
//      ::pointer<::audio::wave>                        m_paudiowave;
//      ::pointer<::mediaplaylist::media_playlist>                  m_pmediaplaylist;
//      ::pointer<::mediamanager::media_manager>                    m_pmediamanager;
//      ::pointer<::mediaplay::mediaplay>                           m_pmediaplay;
//
//
//      string_to_string                                      m_mapMediaCallTitle;
//      string_to_string                                      m_mapMediaCallAlbumArt;
//
//      ::pointer<tts::speaker>                                     m_pspeaker;
//      ::pointer<tts::speaker>                                     m_ptransspeaker;
//      int                                                   m_iGTranslatorFile;
//      string_map < LPFN_NEW_MULTIMEDIA_DECODER, LPFN_NEW_MULTIMEDIA_DECODER>
//      m_mapMultimediaDecoderFactory;
//
//      bool  m_bFadeOutAndStopOnExit;
//
//
//      application();
//      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();

//
//      virtual void init3() override;
//      virtual void init_instance() override;
//
//
//
//      virtual LPFN_NEW_MULTIMEDIA_DECODER get_multimedia_decoder_factory(const ::string & pszTitle);
//
//      inline ::audio_mixer::department *               audiomixer              ()
//      {
//         return m_paudiomixer           ;
//      }
//      inline ::audio_mixer_user_base::department *      audiomixeruserbase      ()
//      {
//         return m_paudiomixeruserbase   ;
//      }
//      inline ::multimedia::file_application *                     multimedia_file         ()
//      {
//         return m_pmultimediafile       ;
//      }
//      inline ::audio::wave *                         audiowave               ()
//      {
//         return m_paudiowave            ;
//      }
//      inline ::mediaplaylist::media_playlist *                    mediaplaylist           ()
//      {
//         return m_pmediaplaylist        ;
//      }
//      inline ::mediamanager::media_manager *                       mediamanager            ()
//      {
//         return m_pmediamanager         ;
//      }
//      inline ::mediaplay::mediaplay *                              mediaplay               ()
//      {
//         return m_pmediaplay            ;
//      }
//
//      inline ::multimedia::department &                             multimedia()
//      {
//         return *m_pmultimedia;
//      }
//
//      virtual void term_instance() override;
//
//#ifdef LINUX
//      inline unsigned int multimedia_get_time()
//      {
//         return ::get_tick();
//      }
//#endif
//
//
//      virtual void play_audio(::payload payloadFile, bool bSynch = false) override;
//
//      virtual void on_song_added(string strId);
//
//      virtual void france_exit() override;
//
//      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback) override;
//
//
//      virtual ::pointer<::tts::speaker>create_tts_speaker();
//      virtual ::pointer<::tts::speaker>create_trans_speaker();
//
//      virtual ::pointer<::tts::speaker>tts_speaker(); // default tts speaker
//      virtual ::pointer<::tts::speaker>trans_speaker(); // default trans speaker
//
//      virtual void speak(string strText);
//      virtual void speak(string strLang, string strText, bool bSynch);
//      virtual void trans_speak(string strLang, string strText, bool bSynch);
//      virtual void google_speak(string strLang, string strText, bool bSynch);
//
//
//      virtual ::pointer<::user::document>defer_create_impact(string strImpact, ::user::interaction * puiParent, e_window_flag ewindowflag = e_window_flag_none, const ::atom & atom = nullptr) override;
//
//
//   };
//
//
//} // namespace multimedia
//


