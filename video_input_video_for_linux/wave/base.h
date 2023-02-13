#pragma once


namespace wave
{


   class buffer;


   class CLASS_DECL_APP_CORE_AUDIO base :
      virtual public ::thread
   {
   public:



      void                     m_estatusWave;

      ::pointer<format>          m_pwaveformat;
      ::pointer<buffer>          m_pwavebuffer;


      base();
      virtual ~base();

      virtual void init_thread() override;

      virtual void allocate_buffer_data(::wave::buffer::item * pbuffer, memsize uiBufferSize, memsize uiAlign);

      virtual void free_buffer_data(::wave::buffer::item * pbuffer);



   };


} // namespace wave



