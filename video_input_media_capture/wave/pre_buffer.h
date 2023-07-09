#pragma once


namespace wave
{


   class CLASS_DECL_APP_CORE_AUDIO pre_buffer :
      virtual public ::object
   {
   public:


      class buffer
      {
      public:


         memory         m_memory;
         bool           m_bFilled;


      };


      class buffer_array :
         public array < buffer >
      {
      public:

      };

   public:

      ::pointer<::audio::plugin>  m_pplugin;

   //public:

      out *                                           m_pwaveout;
      ::count                                         m_iChannelCount;
      ::count                                         m_iSampleCount;
      ::count                                         m_iBufferCount;
      i64                                             m_iLostBytes;

      ::pointer<::iaudio::wave_stream_effect>        m_speffect;
      buffer_array                                    m_buffera;

      bool                                            m_bPlayPreBuffer;

      ::pointer<::iaudio::wave_stream_effect>        m_pstreameffectOut;
      memory_file                                     m_memfileBuffer;

      class ::time                                     m_time;
      class ::time                                     m_timeStart;
      i64                                             m_iBytes;
      ::i32_array                                       m_iaFree;
      manual_reset_event                              m_evRead;
      manual_reset_event                              m_evWritten;
      bool                                            m_bPluginEverSet;
      ::task_pointer                             m_pthreadFillBuffer;


      pre_buffer();
      virtual ~pre_buffer();


      virtual bool pre_output(buffer * pbuffer);

      virtual ::count fill_synch(buffer * pbuffer);
      virtual ::count fill_asynch(buffer * pbuffer);


      virtual bool read_buffer(void * pbuffer, memsize s, index iChunkId);
      virtual bool fill_buffer(index iChunkId);
      virtual ::count get_buffer_count();
      virtual ::memsize get_buffer_size();
      virtual ::memsize get_frame_size();
      virtual void * get_buffer_data(index iId);

      virtual void set_plugin(::audio::plugin * pinterface);
      virtual void defer_unset_plugin(::audio::plugin * pinterface);

      virtual bool open(::count iChannelCount, ::count iGroupCount, ::count iGroupSampleCount);

      //virtual void start(const class ::time & position);
      //virtual void stop();

      virtual bool is_eof();

      virtual class ::time get_millis_length();

      virtual void set_finish_composites(::object * pcontextobjectFinish) override;

      inline ::audio::plugin * plugin() { return m_pplugin;}

   };


} // namespace wave




