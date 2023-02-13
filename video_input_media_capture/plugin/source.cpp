#include "framework.h"


// if buffer "has" more than this time of samples,
// consider out of synch, and should trim.
#define TIME_DELAY_MS   1200


namespace audio
{


   source::source()
   {

      m_bEof = false;
      m_iChannelCount = 2;
      m_iBitsPerSample = 16;
      m_bStop = false;
      m_bMute = false;

   }


   void source::audio_seek_begin()
   {

      plugin::audio_seek_begin();

   }


   bool source::audio_eof()
   {

      return m_bEof;

   }


   memsize source::audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize)
   {
      return 0;

//      memsize iRead = 0;
//
//      int iLim = (int) (m_fSamplePerSecond * TIME_DELAY_MS * m_iBitsPerSample * m_iChannelCount / 8000);
//
//      iLim -= iLim % (m_iBitsPerSample * m_iChannelCount / 8);
//
//      iRead = (memsize) minimum(audio_file()).get_size(), uiBufferSize);
//
//      if (m_memfileDecoder.get_size() > iLim)
//      {
//
//         m_memfileDecoder.erase_begin(nullptr, iLim);
//
//      }
//
//      iRead = (memsize)audio_file().erase_begin(lpvoidBuffer, iRead);
//
//      m_dwDecodePosition += iRead;
//
//      return iRead;

   }


   i64   source::audio_get_sample_count()
   {

      return 0;

   }


   u32 source::audio_get_samples_per_second() const
   {

      return (u32)m_fSamplePerSecond;

   }

   u32 source::audio_get_channel_count() const
   {
      return m_iChannelCount;
   }
   u32 source::audio_get_bits_per_sample() const
   {
      return m_iBitsPerSample;
   }

   int waveout_start(void * waveoutcontext)
   {

      ::audio::source * psource = (::audio::source *)waveoutcontext;

      return psource->waveout_start();

   }

   int waveout_write(void * waveoutcontext, const void * pdata, unsigned int s)
   {

      ::audio::source * psource = (::audio::source *)waveoutcontext;

      return psource->waveout_write(pdata, s);

   }

   int waveout_stop(void * waveoutcontext)
   {

      ::audio::source * psource = (::audio::source *)waveoutcontext;

      return psource->waveout_stop();

   }

   int waveout_close(void * waveoutcontext)
   {

      ::audio::source * psource = (::audio::source *)waveoutcontext;

      int i = psource->waveout_close();

      ::release(psource);

      return i;

   }


   int source::waveout_start()
   {

      paudio->play_plugin(this, false);

      return true;

   }


   int source::waveout_write(const void * pdata, unsigned int s)
   {

      synchronous_lock synchronouslock(audio_mutex());

      audio_file().write(pdata, s);

      return true;

   }

   int source::waveout_stop()
   {

      m_bEof = true;

      return true;

   }

   int source::waveout_close()
   {

      return true;

   }

   LPWAVEOUT source::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   {

      LPWAVEOUT lpwaveout = memory_new WAVEOUT();


      m_iChannelCount = pformat->m_iChannels;
      m_fSamplePerSecond = (float) pformat->m_iSamplePerSec;
      m_iBitsPerSample = pformat->m_iBitsPerSample;



      lpwaveout->waveoutcontext = (::audio::source *) this;

      lpwaveout->waveout_start = &::audio::waveout_start;
      lpwaveout->waveout_write = &::audio::waveout_write;
      lpwaveout->waveout_stop = &::audio::waveout_stop;
      lpwaveout->waveout_close = &::audio::waveout_close;


      return lpwaveout;

   }


} // namespace audio



