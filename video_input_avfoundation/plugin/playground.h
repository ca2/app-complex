/////////////////////////////////////////////////////////////////////////////////////////
// file name: plugin.h
// module: audio_wave::plugin
// module Long name: notSAD Audio plugin MPEG Library plugin
// Purpose: Provide not sad interface for mpglib plugin.
//
/////////////////////////////////////////////////////////////////////////////////////////
// 2006-02-22  Adaptation from the original veriwell Musical Player sources   |   1|cst
//             to audio library project                                      |    |
// 2016-01-25 from ::audio::track, track will be used for
//            planned sound scripts while playground depends much more on the actions
//            taken randomly (like from user)
/////////////////////////////////////////////////////////////////////////////////////////
#pragma once



namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO playground:
      public ::audio::plugin
   {
   public:


      i32                           m_iSamMul;
      i32                           m_iSamDiv;

      i32                           m_iReadPointer;
      char                          m_buf[1024 * 8];
      i64                           m_nSampleCount;
      bool                          m_bNonStopOnEof;

      bool                          m_bExtraOn;

      byte                          m_chCountDown;

      pointer_array < plugin >       m_plugina;

      bool                          m_bExtra;


      playground();
      virtual ~playground();


      virtual void            audio_seek_end() override;

      virtual void            audio_stop() override;
      virtual memsize         audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize) override;
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


   };


} // namespace audio



