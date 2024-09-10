#pragma once


using property_set_array = pointer_array < property_set >;


namespace multimedia
{

   namespace audio
   {


      class wave_player;


   } // namespace audio


} // namespace multimedia


namespace mediaplay
{

   class record_notify_impact;

   enum EExecute
   {
      ExecuteNone,
      ExecuteNext,
      ExecutePrevious,
      ExecuteStop,
      ExecuteApplicationExit,
      ExecuteProcessBatch,
      ExecuteFirst,
      ExecuteLast,
      ExecuteRoulette,
   };

   class document;
   class data;

   class CLASS_DECL_APP_CORE_AUDIO impact_interface :
      virtual public ::user::impact,
      virtual public ::wave::player::listener,
      virtual public ::audio::wave_recorder_container,
      virtual public ::mediaplaylist::player,
      virtual public double_scalar_source,
      virtual public int_scalar_source,
      virtual public ::user::alpha_source
   {
   public:


      ::pointer<::wave::player>     m_pwaveplayer;


      enum_timer                                   m_etimerFade;
      bool                                      m_bAutoSaveSongPosition;
      ::duration m_durationLastOnSongPositionAlive;
      property_set_array                        m_propertysetaBatch;
      ::draw2d::graphics_pointer                     m_spgraphics;
      ::pointer<::mediaplay::record_notify_impact>      m_precordnotifyview;
      atom                                        m_atomPopup;
      atom                                        m_atomPopupLink;
      ::rectangle_f64                                    m_rectangleKaraokeImpact;
      file_pointer                           m_spfileRecord;
      ::mediaplay::document *                   m_pdocument;
      xfplayer_impact_linea                       m_impactlineaStatus;
      ::draw2d::graphics_pointer                     m_gdi;
      bool                                      m_bWaitingToPlay;
      ::duration                                      m_durationPlayWait;
      bool                                      m_bDestroy;
      ::duration                                      m_tick100Timer;
      string                                    m_strCurrentLink;
      rectangle_i32_array                                m_rectangleaUpdate;
      ::duration                                      m_durationLastUpdate;
      double                                    m_dBlend;
      double                                    m_dAudioBlend;
      ::duration                                      m_durationFadeStart;
      EExecute                                  m_eexecuteAfterFadeOut;
      bool                                      m_bAutoRecord;
      bool                                      m_bSavingPlaylist;
      ::duration                                      m_durationLastPlaylistSaving;
      bool                                      m_bIpiPostNewSong;


      i32                                   m_iDelay;

      bool                                      m_bFadeOut;

      ::file::path                              m_pathLastOrigin;
      string                                    m_strLastTitle;
      string_array                                   m_straLastPerformer;
      string                                    m_strAlbum;


      double_scalar                             m_scalarTime;
      double_scalar                             m_scalarVolume;
      //::task_pointer                              m_pthreadSaveSongPosition;
      string                                    m_strFullShortTitle;



      impact_interface();
      virtual ~impact_interface();


      //void common_construct();


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;


      ::wave::player * get_wave_player();




      ::mediaplay::data * get_data();

      virtual bool is_ok_for_rendering();

      virtual void OnFadeOutEnd();
      virtual void StartVisualFadeOut();
      virtual bool StartFadeOut(EExecute eexecuteNow, EExecute eexecuteAfter);
      virtual bool StartFadeIn(::mediaplaylist::info * pinfo);
      virtual void StartVisualFadeIn(bool bAudio);
      virtual void backimpact_Feedback(::image::image *pimage);
      virtual void _001OnTimer(::timer * ptimer) override;
      virtual void CloseDevice();
      virtual void OnMediaPlaybackStart(::wave::player_command * pcommand);
      virtual void OnMediaPlaybackStart();
      virtual void on_media_playback_end();
      virtual bool OnExecuteBeforePlay();

      virtual bool DBListenMinusOne(bool bSave, const ::string & lpcszPathName, bool &bMinusOne);


      DECLARE_MESSAGE_HANDLER(_001OnMessageX);
      //DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnTopDraw(::image::image *pimage);

      virtual void karaoke_bouncing_ball();
      virtual void KaraokeGradualFilling();
      virtual void CopyLinkLocation();

      virtual void SetKaraokeCodePage(u32 dw);
      virtual u32 IdToCodePage(const ::string & pszCommandId);
      virtual u32 GetKaraokeCodePage(const ::string & lpsz);


      virtual void attach_playlist(::mediaplaylist::document * pdocument);


      virtual ::draw2d::graphics * GetGdi();
      virtual i32 InitGL();
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool backimpact_GetDestroy();
      virtual void StartMusicRendering();
      
      //   virtual void data_on_after_change(i32 iConfigurationId, i32 iLine, i32 iColumn, CVmsDataUpdateHint * pupdate);
      virtual bool UpdateScreen(rectangle_i32_array & recta, u32 uiRedraw);

      virtual void on_delete_contents();

      virtual void _ToggleAutoRecord();
      virtual void _AutoRecord(bool bRecord = true);
      virtual void _StartRecording();
      virtual void _StopRecording();

      virtual bool _Execute(EExecute eexecute);
      virtual void _ExecutePlay(bool bMakeVisible, ::duration time, bool bFadeIn);
      virtual void _ExecuteStop() override;
      virtual void _ExecuteStopAndQuit();
      virtual void _ExecutePause();
      virtual bool _ExecuteGetPlayEnable();
      virtual bool _ExecuteIsWaitingToPlay();
      virtual bool _ExecuteIsPaused();
      virtual bool _ExecuteGetPauseEnable();
      virtual bool _ExecuteGetStopEnable();
      virtual void _ExecuteListenMinusOne(bool bMinusOne);
      virtual void _ExecuteToggleListenMinusOne();
      virtual bool _ExecuteGetListenMinusOneEnable();
      virtual bool _ExecuteIsPlaying();
      virtual bool GetListenMinusOneCheck();

      virtual bool _ExecuteIsEntertaining();


      void install_message_routing(::channel * pchannel) override;

      virtual void on_set_scalar(e_scalar escalar, double d, int iFlags) override;
      virtual void get_scalar_minimum(e_scalar escalar, double & d) override;
      virtual void get_scalar(e_scalar escalar, double & d) override;
      virtual void get_scalar_maximum(e_scalar escalar, double & d) override;
      virtual void on_set_scalar(e_scalar escalar,i64 iValue,int iFlags) override;
      virtual void get_scalar_minimum(e_scalar escalar, i64 & iValue) override;
      virtual void get_scalar(e_scalar escalar, i64 & iValue) override;
      virtual void get_scalar_maximum(e_scalar escalar, i64 & iValue) override;

      virtual ::duration KaraokeGetLyricsDelay();

      virtual ::duration get_millis_for_synch();
      virtual ::duration get_position_for_synch();


      virtual void start_saving_song_position();
      virtual void _thread_save_song_position();
      virtual bool save_song_position();





      using mediaplaylist::player::PlaylistPlay;
      virtual bool PlaylistOnBeforePlay(mediaplaylist::info * pinfo);
      virtual mediaplaylist::e_play PlaylistPlay(mediaplaylist::info * pinfo) override;
      virtual void PlaylistOnBeforeOpen() override;
      virtual void playlist_on_playback_end() override;

      virtual bool is_playing() override;


      virtual bool on_open_document(const ::payload & payloadFile);
      virtual bool PlaylistHasBatch();
      virtual bool PlaylistStepBatch();
      virtual bool PlaylistDeferBatch();


      virtual double get_alpha(::user::interaction * puiTarget) override;
      virtual void on_alpha_target_initial_frame_position() override;


      virtual void ipi_post_new_song();


      virtual bool get_short_title(string & strTitle, string_array & straArtist, string & strPlaylist);
      virtual void defer_update_full_short_title();

   };



} // namespace mediaplay

