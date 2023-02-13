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



namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO mixer :
      virtual public ::audio::plugin
   {
   public:

      //i32                                 m_iSamMul;
      //i32                                 m_iSamDiv;

      //i32                                 m_iReadPointer;
      memory                              m_memory;
      //memory                              m_memOut;
      //char                                m_buf[1024 * 8];
      //int                                 m_iPos;
      //int                                 m_iMaxPos;
      //i64                                 m_iAccL;
      //i64                                 m_iAccR;
      //::pointer<::file::circular_file>   m_pfileL;
      //::pointer<::file::circular_file>   m_pfileR;
      i64                                 m_nSampleCount;
      bool                                m_bNonStopOnEof;

      bool                                m_bExtraOn;

      //bool                                m_bRemoveDC;
      //byte                                m_chCountDown;

      int                                 m_iDecoder;
      pointer_array < plugin >                  m_plugina;

      bool                                m_bExtra;


      mixer();
      virtual ~mixer();


      virtual void            add_plugin(plugin * pplugin);
      //virtual void            on_init_child() override;

      virtual void            replace_with_track(plugin* plugin);

      virtual bool            audio_initialize() override;
      virtual bool            audio_finalize() override;
      virtual bool            audio_eof() override;

      virtual void            audio_seek_end() override;


      virtual void            audio_stop() override;
      virtual memsize         audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize) override;

      virtual void            audio_move_next() override;
      virtual i64             audio_get_sample_count() override;
      virtual u32             audio_get_samples_per_second() const override;
      virtual u32             audio_get_channel_count() const override;
      virtual u32             audio_get_bits_per_sample() const override;
      virtual void            audio_seek_begin() override;
      virtual bool            audio_set_non_stop_on_eof(bool bSet) override;


   };


} // namespace audio



