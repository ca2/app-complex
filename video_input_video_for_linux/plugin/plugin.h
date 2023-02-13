#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO plugin :
      virtual public ::object
   {
   public:


      ::pointer<::audio::plugin>                      m_ppluginParent;
      ::pointer<class ::pointer < ::mutex >>                           m_pmutexAudio;
      ::pointer<::wave::pre_buffer>                   m_pprebuffer;
      bool                                               m_bStop;
      bool                                               m_bEof;
      bool                                               m_bDecodeEof;
      ::pointer<::wave::out>                          m_pwaveout;
      bool                                               m_bPersistent;
      bool                                               m_bWait;
      bool                                               m_bLoop;
      bool                                               m_bKick;
      string                                             m_str;
      filesize                                           m_iDecodeLength;
      i64_array                                          m_iaLostPosition;
      i64_array                                          m_iaLostCount;
      i64                                                m_iReadExpanded;
      i64                                                m_iRead;
      bool                                               m_bInitialized;
      bool                                               m_bRunning;
      i32                                                m_iBufferSize;
      i32                                                m_iReadBlockSize;
      i64                                                m_iRestartPosition;
      i64                                                m_iAudioRead;
      i64                                                m_iNoBlockSilence;
      i64                                                m_iFrameRead;
      i64                                                m_iStartOffset;
      bool                                               m_bRealTime;
      bool                                               m_bSynch;
      ::pointer<plugin>                                 m_ppluginNext;
      ::pointer<memory_file>                            m_pfileFrame;
      ::pointer<memory_file>                            m_pfileAudio;
      // Release decoded/cached data that was playback right after playback
      bool                                               m_bReleasePlaybackMemory;
      pointer< pointer_array < plugin > >                 m_ppluginaFree;





      plugin();
      virtual ~plugin();


      inline class ::pointer< ::mutex > audio_mutex() { return m_pmutexAudio; }
      inline ::memory_file & audio_file() { return *m_pfileAudio; }
      inline ::memory_file & frame_file() { return *m_pfileFrame; }

      virtual void               init_child(plugin * pplugin);
      //virtual void               on_init_child();

      virtual memsize            default_frame_size();
      virtual memory_base &      default_frame();

      virtual bool               audio_initialize();
      inline  bool               audio_is_initialized() const { return m_bInitialized; }
      virtual bool               audio_finalize();

      virtual void               audio_stop();
      virtual void               audio_close();

      virtual bool               audio_is_loop();

      //virtual void               multimedia_read_frame();

      //virtual memsize            call_multimedia_read_frame();

      virtual u32                audio_get_samples_per_second() const;
      virtual u32                audio_get_channel_count() const;
      virtual u32                audio_get_bits_per_sample() const;

      virtual bool               audio_set_expected_parameters(u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitCount, u32 uiEncodedAvgBitRate);
      virtual u32                audio_get_raw_bit_rate();
      virtual u32                audio_get_average_bit_rate();
      virtual u32                audio_get_raw_size(u32 uiEncodeSize);

      //virtual bool             multimedia_get_attribute(e_attribute attribute, ::payload & str);

      virtual class ::time        audio_get_lost_time(class ::time dwExpandedMillis);
      ///virtual class ::time    audio_get_lost_time(class ::time position);

      // low level adjustments that may be not supported by the plugin in
      // which case the plugin client may not be able to use the plugin
      // if such adjustments cannot take effect;
      virtual bool               audio_set_seekable(bool bSet = true);
      virtual bool               audio_is_seekable();
      virtual i32                audio_set_read_block_size(i32 iSize);

      // return number of bytes written

      /// This function should only return 0 if end of file or end of stream is reached.
      /// If it is not known, it should wait for data.
      /// Callers should be prepared for this behaviour.
      /// This function calls _DecoderFillBuffer
      //virtual memsize          audio_read(LPVOID lpvoidBuffer, memsize uiBufferSize);

      /// This function optionally may return 0, if nothing was written.
      /// Delay should be avoided and if no data is immediately, or almost immediately available, it is preferrable to return immediately.
      /// This function is called by audio_read and run_decode_thread.
      //virtual memsize          audio_read(LPVOID lpvoidBuffer, memsize uiBufferSize);
      //virtual memsize          audio_read_non_block(LPVOID lpvoidBuffer, memsize uiBufferSize);


      /// This function optionally may return 0, if nothing was written.
      /// Delay should be avoided and if no data is immediately, or almost immediately available, it is preferrable to return immediately.
      /// This function is called by audio_read and run_decode_thread.
      //virtual memsize            audio_read(LPVOID lpvoidBuffer, memsize uiBufferSize);
      //virtual memsize            audio_read_blocking(LPVOID lpvoidBuffer, memsize uiBufferSize);
      //virtual memsize            audio_read_no_block(LPVOID lpvoidBuffer, memsize uiBufferSize);
      virtual memsize            audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize);
      virtual memsize            audio_read(void * lpvoidBuffer, memsize uiBufferSize);
      //virtual memsize            audio_fill(LPVOID lpvoidBuffer, memsize uiBufferSize);


      virtual i64                audio_get_millis_length();
      virtual i64                audio_get_millis_read();
      virtual i64                audio_get_position_read();

      virtual bool               audio_is_real_time();
      virtual bool               audio_set_real_time(bool bRealTime = true);

      virtual void               audio_on_event(::audio::e_event eevent);

      virtual i64                audio_get_sample_count();

      virtual void               audio_move_next();
      virtual void               audio_seek_begin();
      virtual void               audio_seek_end();
      virtual void               audio_restart();
      virtual bool               audio_set_non_stop_on_eof(bool bSet = true);

      virtual bool               audio_eof();
      virtual bool               audio_decode_eof();

      virtual string             multimedia_get_origin_path();
      virtual void               multimedia_set_origin_path(const ::string & strOriginPath);

      virtual bool               audio_matches(const ::audio::plugin * ppluginOther) const;

      virtual LPWAVEOUT          waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);


   };


} // namespace audio



