#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO sampler:
      virtual public ::audio::plugin
   {
   public:


      ::pointer<plugin>   m_pplugin;
      ::u32                m_dwSample;
      int                  m_iChannelCount;
      int                  m_iBitsPerSample;
      float                m_fSamplePerSecond;
      index                m_iIndex;
      bool                 m_bMute;


      sampler();
      virtual ~sampler();


      virtual void initialize_sampler(plugin * pplugin);

      virtual bool sample(short * sh) = 0;

      virtual void reset(float fSamplesPerSecond);

      virtual memsize audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize) override;

      virtual void audio_seek_begin() override;
      virtual bool audio_eof() override;


      u32 audio_get_samples_per_second() const override;
      u32 audio_get_channel_count() const override;
      u32 audio_get_bits_per_sample() const override;

      //memsize _DecoderFillBuffer(LPVOID lpvoidBuffer,memsize uiBufferSize);

      virtual i64   audio_get_sample_count() override;

   };


} // namespace audio



