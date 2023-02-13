#pragma once


namespace wave
{


   struct WAVE_FORMAT
   {

      ::u16        wFormatTag;         /* format type */
      ::u16        nChannels;          /* number of channels (i.e. mono, stereo...) */
      ::u32       nSamplesPerSec;     /* sample rate */
      ::u32       nAvgBytesPerSec;    /* for buffer estimation */
      ::u16        nBlockAlign;        /* block size_i32 of data */
      ::u16        wBitsPerSample;     /* number of bits per sample of mono data */


   };

   class CLASS_DECL_APP_CORE_AUDIO format :
      virtual public ::matter
   {
   public:

      
      WAVE_FORMAT  m_waveformat;


      format();
      format(const format& format);
      virtual ~format();


      format& operator = (const format& format);


      //WAVE_FORMAT& waver ()()
      //{
      //   return m_waveformat;

      //}

      //const WAVE_FORMAT& operator ()() const
      //{
      //   return m_waveformat;

      //}

   };


} // namespace wave








