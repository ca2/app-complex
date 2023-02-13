#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO decoder :
      virtual public ::multimedia::decoder,
      virtual public ::audio::plugin
   {
   public:


      filesize                            m_dwAsynchDecodeLength;
      ::pointer<::thread>              m_pthreadDecode;
      memory                              m_memory;


      decoder();
      virtual ~decoder();


      virtual bool      audio_initialize() override;
      virtual bool      audio_finalize() override;

      virtual void multimedia_open(::file::file * pfile) override;
      virtual void impl_multimedia_open(::file::file * pfile) override;

      virtual bool      multimedia_close() override;
      virtual bool      impl_multimedia_close() override;

      virtual string    multimedia_get_origin_path() override;
      virtual void      multimedia_set_origin_path(const ::string & strOriginPath) override;

      virtual bool      begin_decode_thread();

      virtual memsize   read_frame(void * lpvoidBuffer, memsize uiBufferSize);
      virtual memsize   audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize) override;


      /// This function buffers decoder data ahead.
      virtual i32       run_decode_thread();



      virtual void      audio_stop() override;
      virtual void      audio_close() override;

      virtual bool      audio_is_loop() override;

      virtual void      audio_move_next() override;
      virtual bool      audio_eof() override;
      virtual bool      audio_decode_eof() override;
      virtual void      audio_seek_begin() override;
      virtual void      audio_decode_seek_begin();

      virtual bool      audio_set_expected_parameters(u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitCount, u32 uiEncodedAvgBitRate) override;
      virtual u32       audio_get_raw_bit_rate() override;
      virtual u32       audio_get_average_bit_rate() override;
      virtual u32       audio_get_raw_size(u32 uiEncodeSize) override;

      virtual void      audio_seek_end() override;
      virtual bool      audio_set_non_stop_on_eof(bool bSet = true) override;


      virtual class ::time       audio_get_lost_time(class ::time dwExpandedMillis) override;
      //virtual class ::time   audio_get_lost_time(class ::time position) override;

      // low level adjustments that may be not supported by the decoder in
      // which case the decoder client may not be able to use the decoder
      // if such adjustments cannot take effect;
      virtual bool      audio_set_seekable(bool bSet = true) override;
      virtual bool      audio_is_seekable() override;
      virtual i32       audio_set_read_block_size(i32 iSize) override;

      // return number of bytes written

      /// This function should only return 0 if end of file or end of stream is reached.
      /// If it is not known, it should wait for data.
      /// Callers should be prepared for this behaviour.
      /// This function calls _DecoderFillBuffer
      //virtual memsize       audio_read(LPVOID lpvoidBuffer, memsize uiBufferSize);


      virtual i64   audio_get_millis_length() override;


      virtual bool      audio_is_real_time() override;
      virtual bool      audio_set_real_time(bool bRealTime = true) override;

      virtual void audio_on_event(e_event eevent) override;





   };


} // namespace audio




