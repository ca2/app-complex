#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO source :
      virtual public ::audio::plugin
   {
   public:

      int            m_iChannelCount;
      int            m_iBitsPerSample;
      float          m_fSamplePerSecond;
      int            m_iIndex;
      bool           m_bMute;


      source();

      virtual memsize audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize) override;

      virtual void audio_seek_begin() override;
      virtual bool audio_eof() override;


      u32 audio_get_samples_per_second() const override;
      u32 audio_get_channel_count() const override;
      u32 audio_get_bits_per_sample() const override;

      //memsize _DecoderFillBuffer(LPVOID lpvoidBuffer,memsize uiBufferSize);

      virtual i64   audio_get_sample_count() override;



      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback) override;

      int waveout_start();
      int waveout_write(const void * pdata, unsigned int s);
      int waveout_stop();
      int waveout_close();



   };


} // namespace audio



