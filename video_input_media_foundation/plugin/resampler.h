/////////////////////////////////////////////////////////////////////////////////////////
// file name: plugin.h
// module: audio_wave::plugin
// module Long name: notSAD Audio plugin MPEG Library plugin
// Purpose: Provide not sad interface for mpglib plugin.
//
/////////////////////////////////////////////////////////////////////////////////////////
// 2006-02-22  Adaptation from the original veriwell Musical Player sources   |   1|cst
//             to audio library project                                      |    |
/////////////////////////////////////////////////////////////////////////////////////////
#pragma once

typedef struct
{
   float * pointer;
   float state[1000];
   float output;
} filter1Type;


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO resampler:
      virtual public ::audio::plugin
   {
   public:

      i64                                    m_iSourcePointer;
      bool                                   m_bUnsignedSource;
      filter1Type *                          m_pfilter1;
      i32                                    m_iSamMul;
      i32                                    m_iSamDiv;

      i32                                    m_iReadPointer;
      i64                                    m_nSampleCount;
      memory                                 m_memSource;
      bool                                   m_bNonStopOnEof;

      bool                                   m_bExtraOn;

      u32                                    m_den;
      u32                                    m_num;
      i64                                    m_posSrc;
      i64                                    m_posDst;
      float                                 m_fNextSample;

      i64_array                              m_iaLowerPos;
      i64_array                              m_iaUpperPos;

      ::u8                                   m_chCountDown;

      ::u32                                  m_dwTargetSamplesPerSecond;
      int                                    m_iTargetChannelCount;
      int                                    m_iTargetBitsPerSample;

      ::pointer<plugin>                     m_pplugin; // Source plugin
      int                                    m_acc[16];
      ::memory_file                          m_src;
      f32_array                            m_daLastSample;
      array<f32_array>                     m_da;
      array<f32_array>                     m_xa1;
      array<f32_array>                     m_ya1;
      array<f32_array>                     m_xa2;
      array<f32_array>                     m_ya2;
      bool                                   m_bExtra;



      resampler();
      virtual ~resampler();


      void                    audio_seek_end() override;


      void                    audio_stop() override;
      virtual memsize         audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize) override;
      virtual bool            read_source();

      virtual bool            audio_is_loop() override;
      virtual bool            audio_eof() override;

      virtual bool            audio_initialize() override;
      virtual bool            audio_finalize() override;

      virtual void            audio_move_next() override;
      virtual i64             audio_get_sample_count() override;
      virtual u32             audio_get_samples_per_second() const override;
      virtual u32             audio_get_channel_count() const override;
      virtual u32             audio_get_bits_per_sample() const override;
      virtual void            audio_seek_begin() override;
      virtual bool            audio_set_non_stop_on_eof(bool bSet) override;
      virtual void            audio_on_event(e_event eevent) override;

   };


} // namespace audio



