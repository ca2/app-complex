#pragma once


// typedef ::multimedia::decoder * CDECL NEW_MULTIMEDIA_DECODER(::particle * pparticle);


// typedef NEW_MULTIMEDIA_DECODER * LPFN_NEW_MULTIMEDIA_DECODER;


// namespace multimedia
// {


//    class CLASS_DECL_APP_CORE_AUDIO multimedia :
//       virtual public ::aura::multimedia,
//       virtual public ::wave::player::listener
//    {
//    public:


//       ::pointer<::audio::sound_track_player>             m_psoundtrackplayer;

//       ::pointer<::audio::file_application>               m_pmultimediafile;
//       ::pointer<::wave::wave>                            m_pwave;


//       ::pointer<tts::speaker>                              m_pspeaker;
//       ::pointer<tts::speaker>                              m_ptransspeaker;
//       int                                                   m_iGTranslatorFile;
//       string_map < LPFN_NEW_MULTIMEDIA_DECODER >            m_mapMultimediaDecoderFactory;

//       bool                                                  m_bFadeOutAndStopOnExit;


//       multimedia();
//       virtual ~multimedia();


//       virtual void init3() override;
//       virtual void init_instance() override;


//       virtual LPFN_NEW_MULTIMEDIA_DECODER get_multimedia_decoder_factory(const ::string & pszTitle);

//       inline ::multimedia::file_application * multimedia_file() { return m_pmultimediafile; }
//       inline ::audio::wave * audiowave() { return m_paudiowave; }

//       virtual void term_instance() override;

// #ifdef LINUX
//       inline unsigned int multimedia_get_time() { return ::get_tick(); }
// #endif

//       virtual void play_audio(::payload payloadFile, bool bSynch = false) override;

//       virtual void on_song_added(string strId);

//       virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);

//       virtual ::pointer<::tts::speaker>create_tts_speaker();
//       virtual ::pointer<::tts::speaker>create_trans_speaker();

//       virtual ::pointer<::tts::speaker>tts_speaker(); // default tts speaker
//       virtual ::pointer<::tts::speaker>trans_speaker(); // default trans speaker

//       virtual void speak(string strText) override;
//       virtual void speak(string strLang, string strText, bool bSynch) override;
//       virtual void trans_speak(string strLang, string strText, bool bSynch) override;
//       virtual void google_speak(string strLang, string strText, bool bSynch) override;


//       virtual void init_multimedia();
//       virtual void term_multimedia();

//       sound_track_player * sound_track();

//       virtual void OnWavePlayerEvent(wave::player * pplayer, wave::player::e_event event, wave::player_command * pcommand) override;

//       virtual void defer_initialize_audio_playback(::audio::e_purpose epurpose= ::wave::purpose_playground);

//       string get_media_call_title(string str);

//       virtual ::pointer<::audio_plugin::plugin>prepare_audio(::file::file * pfile);
//       virtual ::pointer<::audio_plugin::plugin>prepare_plugin(::audio_plugin::plugin * pplugin);

//       virtual ::pointer<::audio_plugin::plugin>play_plugin(::audio_plugin::plugin * pplugin, bool bSynch = false);

//       virtual ::pointer<::audio_plugin::plugin>play_prepared_plugin(::audio_plugin::plugin* pplugin, bool bSynch = false);

//       virtual ::pointer<::audio_plugin::plugin>get_and_play_audio(::file::file * pfile, bool bSynch = false);

//       virtual void on_decoder_fill_title_info(::multimedia::decoder * pdecoder, string_array & straTitle, string_array_array & straaTitle);


//    };


// } // namespace multimedia



