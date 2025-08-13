#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO audio :
      virtual public ::aqua::audio,
      virtual public sound_track_player_container
   {
   public:


      ::pointer<::multimedia::file_application>          m_pmultimediafile;
      ::pointer<::wave::wave>                            m_pwave;


      ::pointer<tts::speaker>                              m_pspeaker;
      ::pointer<tts::speaker>                              m_ptransspeaker;
      int                                                   m_iGTranslatorFile;
      string_map_base < LPFN_NEW_MULTIMEDIA_DECODER >            m_mapMultimediaDecoderFactory;

      bool                                                  m_bFadeOutAndStopOnExit;


      audio();
      virtual ~audio();


      virtual void init3() override;
      virtual void init_instance() override;


      virtual LPFN_NEW_MULTIMEDIA_DECODER get_multimedia_decoder_factory(const ::scoped_string & scopedstrTitle) override;

      inline ::multimedia::file_application * multimedia_file() { return m_pmultimediafile; }
      inline ::wave::wave * audiowave() { return m_pwave; }

      void term_instance() override;

#ifdef LINUX
      inline unsigned int multimedia_get_time() { return ::get_tick(); }
#endif

      virtual void play_audio(::file::file* pfile, bool bSynch = false);

      virtual ::file_pointer get_rtp_file(const ::payload & payloadFile) override;

      //virtual void on_song_added(const ::scoped_string & scopedstrId);

      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback) override;

      virtual ::pointer<::tts::speaker>create_tts_speaker() override;
      virtual ::pointer<::tts::speaker>create_trans_speaker();

      virtual ::pointer<::tts::speaker>tts_speaker(); // default tts speaker
      virtual ::pointer<::tts::speaker>trans_speaker(); // default trans speaker

      virtual void speak(const ::scoped_string & scopedstrText) override;
      virtual void speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSynch) override;
      virtual void trans_speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSynch) override;
      virtual void google_speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSynch) override;


      virtual void init_multimedia();
      virtual void term_multimedia();

      virtual void OnWavePlayerEvent(::wave::player * pplayer, ::wave::player::enum_player_happening happening, ::wave::player_command * pcommand) override;

      virtual ::pointer<::audio::plugin>prepare_audio(::file::file * pfile);
      virtual ::pointer<::audio::plugin>prepare_plugin(::audio::plugin * pplugin);

      virtual ::pointer<::audio::plugin>play_plugin(::audio::plugin * pplugin, bool bSynch = false);

      virtual ::pointer<::audio::plugin>play_prepared_plugin(::audio::plugin* pplugin, bool bSynch = false);

      virtual ::pointer<::audio::plugin>get_and_play_audio(::file::file * pfile, bool bSynch = false);



   };


} // namespace multimedia



