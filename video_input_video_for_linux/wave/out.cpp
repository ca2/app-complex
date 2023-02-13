#include "framework.h"

//#include "aqua/os/_.h"
#include "apex/message.h"


namespace wave
{


   out::out()
   {

      m_bMessageThread = true;

      m_dVolume = 1.0;

      m_bDirectOutput = false;

      m_estate = e_state_initial;
      m_pthreadCallback = nullptr;
      m_iBufferedCount = 0;
      m_estatusWave = ::success;
      m_iLostBytes = 0;

      m_epurpose = purpose_default;

      m_pplayer = nullptr;

      m_timeStart = 0;

   }


   out::~out()
   {

   }


   out::output_thread::output_thread()
   {

      m_bMessageThread = true;

   }


   out::output_thread::~output_thread()
   {

   }


   //void out::output_thread::install_message_routing(::channel * pchannel)
   //{

   //   thread::install_message_routing(pchannel);

   //   MESSAGE_LINK(e_message_player_filled, pchannel, this, &output_thread::on_filled);

   //}


   void out::output_thread::init_thread()
   {

      if (!::thread::init_thread())
      {

         return ::error_failed;

      }

      set_thread_priority(::e_priority_highest);

      return ::success;

   }


   void out::output_thread::on_filled(::index i)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_listFilled.add_head(i);

         m_evFilled.SetEvent();

      }

   }


   void out::output_thread::run()
   {

      while (this->task_get_run())
      {

         {

            synchronous_lock synchronouslock(this->synchronization());

            while (m_listFilled.has_elements())
            {

               auto iFilled = m_listFilled.pop_tail();

               synchronouslock.unlock();

               m_pwaveout->out_filled(iFilled);

               synchronouslock.lock();

            }

            m_evFilled.ResetEvent();

         }

         m_evFilled.wait(1_s);

      }

      return ::success;

   }


   out::synth_thread::synth_thread()
   {

      m_bMessageThread = false;

   }


   out::synth_thread::~synth_thread()
   {

   }


   //void out::synth_thread::install_message_routing(::channel * pchannel)
   //{

   //   thread::install_message_routing(pchannel);
   //MESSAGE_LINK(e_message_player_free, pchannel, this, &synth_thread::on_free);

   //}


   void out::synth_thread::init_thread()
   {

      if (!::thread::init_thread())
      {

         return false;

      }

      set_thread_priority(::e_priority_highest);

      return true;

   }


   void out::synth_thread::on_free(::index i)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());
         
         if(m_listFree.has_elements())
         {

            m_listFree.add_head(i);
            
         }
         else
         {
            
            m_listFree.add_head(i);

            m_evFree.SetEvent();
            
         }

      }

   }


   void out::synth_thread::run()
   {

      while (this->task_get_run())
      {

         {

            synchronous_lock synchronouslock(this->synchronization());

            while(m_listFree.has_elements())
            {

               auto iFree = m_listFree.pop_tail();

               synchronouslock.unlock();

               m_pwaveout->out_free(iFree);

               synchronouslock.lock();

            }

            m_evFree.ResetEvent();

         }

         m_evFree.wait(1_s);

      }

      return ::success;

   }



   void out::on_free(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      out_free(pusermessage->m_wparam);

   }


   void out::install_message_routing(::channel * pchannel)
   {

      base::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_player_open, pchannel, this, &out::on_open);
      MESSAGE_LINK(e_message_player_start, pchannel, this, &out::on_start);
      MESSAGE_LINK(e_message_player_stop, pchannel, this, &out::on_stop);
      MESSAGE_LINK(e_message_player_close, pchannel, this, &out::on_close);

   }


   void out::init_thread()
   {

      if (!base::init_thread())
      {

         return false;

      }

      auto estatus = __construct_new(m_pprebuffer);

      if (!estatus)
      {

         throw ::exception(error_resource);

      }

      m_pprebuffer->m_pwaveout = this;

      estatus = __construct_new(m_pwavebuffer);

      if (!estatus)
      {

         throw ::exception(error_resource);

      }

      estatus = __construct_new(m_pwaveformat);

      if (!estatus)
      {

         throw ::exception(error_resource);

      }

      estatus = __construct_new(m_poutputthread);

      if (!estatus)
      {

         return estatus;

      }

      m_poutputthread->m_pwaveout = this;

      estatus = __construct_new(m_psynthtask);

      if (!estatus)
      {

         return estatus;

      }


      m_psynthtask->m_pwaveout = this;

      if(!m_poutputthread->begin_synch())
      {

         return false;

      }

      if(!m_psynthtask->begin_synch())
      {

         return false;

      }

      return true;

   }


   void out::term_thread()
   {

      if (m_estate == e_state_playing)
      {

         out_stop();

      }

      if (get_itask() != null_itask)
      {

         out_close();

      }



      thread::term_thread();

   }


   void     out::out_open_ex(thread * pthreadCallback, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, ::wave::enum_purpose epurpose)
   {

      return error_failed;

   }


   void     out::out_close()
   {

      //m_pprebuffer->stop();

      m_pwavebuffer->Close(this);

      m_estate = e_state_initial;

      return ::success;

   }


   void out::on_filled(::message::message * pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      out_filled(pusermessage->m_wparam);

   }



   void out::out_filled(index iBuffer)
   {

   }


   void out::out_prebuffer_eof()
   {

      synchronous_lock synchronouslock(this->synchronization());

      ::count cBufferedCount = out_get_buffered_buffer_count();

      bool bEffectOutNull = m_pprebuffer->m_pstreameffectOut.is_null();

      bool bEffectOutEnd = false;

      if(!bEffectOutNull)
      {

         bEffectOutEnd = m_pprebuffer->m_pstreameffectOut->m_bEnd;

      }

      if(m_estate == ::wave::out::e_state_playing)
      {

         if (cBufferedCount <= 0 || bEffectOutEnd)
         {

            synchronouslock.unlock();

            out_on_playback_end();

         }

      }


   }


   void     out::out_start(const ::time & position)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         if (m_estate == e_state_playing)
         {

            return ::success;

         }

         if (m_estate != e_state_opened && m_estate != state_stopped)
         {

            return error_failed;

         }

         m_bEOS = false;

         m_estate = e_state_playing;

         m_iLostBytes = 0;

         ::time positionStart = 0;

         if(m_pprebuffer->plugin() != nullptr)
         {

            positionStart = minimum(position, m_pprebuffer->plugin()->audio_get_sample_count() - 1);

         }

         positionStart = maximum(0, positionStart);

         m_timeStart = positionStart;

         synchronouslock.unlock();

         // after prebuffer start, buffers are synchronously full
         //m_pprebuffer->start(m_positionStart);

      }

      {

         KEEP(m_bDirectOutput);
         // after prebuffer start (operation immediatelly above), buffers are synchronously full
         out_launch_buffers();

      }

      return ::success;

   }


   void out::out_launch_buffers()
   {

      for (i32 dw = 0; dw < out_get_buffer()->GetBufferCount(); dw++)
      {

         m_iBufferedCount++;

         out_free(dw);

      }

   }


   void     out::out_stop()
   {


      return error_failed;

   }


   void     out::out_pause()
   {

      return error_failed;

   }


   void     out::out_restart()
   {

      return error_failed;

   }


   //::time out::out_get_time_for_synch()
   //{

   //   if (m_pwaveformat->nSamplesPerSec <= 0)
   //   {

   //      return 0;

   //   }

   //   return out_get_time_for_synch() * 1000 / m_pwaveformat->nSamplesPerSec;

   //}


   ::time out::out_get_time()
   {

      return 0;

   }


   ::time out::out_get_time_for_synch()
   {

      ::time position = out_get_time();

      memsize iFrameSize = m_pprebuffer->get_frame_size();

      if (iFrameSize <= 0)
      {

         return position;

      }

      double dTimeLost = (double) (m_iLostBytes / iFrameSize) / (double)(m_pwaveformat->m_waveformat.nSamplesPerSec);

      return position - dTimeLost;

   }


   //::time out::out_get_time()
   //{

   //   return 0;

   //}


   ::count out::out_get_buffered_buffer_count()
   {

      return m_iBufferedCount;

   }


   void out::on_open(::message::message * pmessage)
   {

      defer_open();

      pmessage->m_bRet = true;

   }


   void out::defer_open()
   {

      ::pointer<audio::plugin>pplugin = out_plugin();

      if(pplugin.is_null())
      {

         m_estatusWave = error_failed;

         return;

      }

      m_estatusWave = out_open_ex(
                        m_pplayer->cast < ::thread>(),
                        pplugin->audio_get_samples_per_second(),
                        pplugin->audio_get_channel_count(),
                        pplugin->audio_get_bits_per_sample(),
                        m_pplayer->m_epurpose);

   }


   void out::on_start(::message::message * pmessage)
   {

      ::pointer<player_command>pcommand(pmessage->m_lparam);

      if (m_estate == e_state_initial)
      {

         defer_open();

         if (m_estatusWave != ::success)
         {

            TRACE("out::on_start open FAILED");

            m_pplayer->post_event(player::e_player_event_open_device_failed, pcommand);

            return;

         }

         TRACE("out::on_start open SUCCESS");

         m_pplayer->post_event(player::e_player_event_open_device);

      }

      if (m_estate != e_state_opened)
      {

         m_estatusWave = error_wrong_state;

         TRACE("out::on_start wrong state (1)");

         return;

      }

      if (pcommand->m_bFadeIn)
      {

         TRACE("OMG FADE IN is this source of BUG?!?");

         effect_crescendo * pfadein = memory_new effect_crescendo;

         pfadein->m_bDeleteOnEnd = true;
         pfadein->m_bSustain = true;
         pfadein->m_bTriggerEnd = true;
         pfadein->m_bWaitFirstNonZeroToStart = true;
         pfadein->SetLengthMillis(5000, out_get_buffer()->m_waveformatOut.m_waveformat.nSamplesPerSec);
         pfadein->Initialize();
         out_set_stream_out_effect(pfadein);

      }

      auto pos = pcommand->m_time *   m_pwaveformat->m_waveformat.nSamplesPerSec / 1000;

      m_timeStart = maximum(pcommand->m_time, pos);

      defer_start();

      if (m_estatusWave != ::success)
      {

         TRACE("audio_player start FAILED");

         m_pplayer->post_event(player::e_player_event_start_device_failed, pcommand);

         return;

      }

      TRACE("audio_player start SUCCESS");

      m_pplayer->post_event(player::e_player_event_play, pcommand);

   }


   void out::on_stop(::message::message * pmessage)
   {

      //::pointer<::user::message>pusermessage(pmessage);

      //         ::pointer<player_command>pcommand(pmessage->m_lparam);

      out_stop();

      m_pplayer->post_event(player::e_player_event_stop);

      if (out_plugin() != nullptr)
      {

         out_plugin()->audio_seek_begin();

      }

   }



   void out::defer_start()
   {

      m_estatusWave = out_start(m_timeStart);

   }



   void out::on_close(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      out_close();

   }


   void out::out_post_close()
   {

      post_message(e_message_player_close);

   }


   void * out::out_get_buffer_data(index iBuffer)
   {

      return m_pwavebuffer->PCMOutGetBuffer(iBuffer);

   }


   memsize out::out_get_buffer_size()
   {

      return m_pwavebuffer->PCMOutGetInBufferSize();

   }

   ::count out::out_get_buffer_sample_count()
   {

      return (out_get_buffer_size() * 8) / (m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels);

   }

   void     out::out_errno()
   {

      return m_estatusWave;

   }


   void out::out_set_stream_out_effect(::iaudio::wave_stream_effect * peffect)
   {

      m_pprebuffer->m_pstreameffectOut = peffect;

   }


   bool out::out_set_plugin(::audio::plugin * pplugin)
   {

      if(pplugin != nullptr)
      {

         pplugin->__refer(pplugin->m_pwaveout, this);

         ::pointer<::audio::decoder>pdecoder = pplugin;

         if (pdecoder.is_set())
         {

            if (pdecoder->m_pthreadDecode)
            {

               add_composite(pdecoder->m_pthreadDecode);

            }

         }

      }

      m_pprebuffer->set_plugin(pplugin);

      return pplugin;

   }


   ::audio::plugin * out::out_plugin()
   {

      return m_pprebuffer->plugin();

   }


   void out::out_on_pre_buffer(index iBuffer)
   {

      __UNREFERENCED_PARAMETER(iBuffer);

   }


   bool out::raw_pump_message()
   {

      try
      {

         if (!get_message())
         {

            TRACE(trace_category_appmsg, e_trace_level_information, "OUT thread::raw_pump_message - Received e_message_quit.\n");

            ::output_debug_string("OUT thread::raw_pump_message - Received e_message_quit.\n");

            m_nDisablePumpCount++; // application must die
            // Note: prevents calling message loop things in 'exit_thread'
            // will never be decremented
            return false;

         }

         if (m_message.message == e_message_player_free)
         {

            out_free(m_message.wParam);

         }
         else
         {

            raw_process_message();


         }

         return true;

      }
      catch (::exception_pointer e)
      {

         if (handle_exception(e))
         {

            return true;

         }

      }
      catch (...)
      {

      }

      return false;

   }


   void out::out_free(index iBuffer)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_iBufferedCount--;

         if(m_pwavebuffer.is_null())
         {

            return;

         }

         iBuffer = int(minimum(maximum(0, iBuffer), m_pwavebuffer->m_buffera.get_upper_bound()));

         if (iBuffer < 0)
         {

            return;

         }

         auto pbuffer = m_pwavebuffer->PCMOutGetBuffer(iBuffer);

         auto bufferSize = m_pwavebuffer->PCMOutGetInBufferSize();

         bool bFilled = m_pprebuffer->read_buffer(pbuffer, bufferSize, iBuffer);

         if (!bFilled || out_get_state() != e_state_playing)
         {

            if (m_pprebuffer->is_eof() || out_get_state() != e_state_playing)
            {

               if (!m_bEOS)
               {

                  m_bEOS = true;

                  if (m_pwavebuffer != nullptr)
                  {

                     synchronous_lock synchronouslock(m_estate == e_state_stopping || m_estate == state_closing ? nullptr : mutex());

                     short * pshTarget = (short *)m_pwavebuffer->PCMOutGetBuffer(iBuffer);

                     short * pshSource = (short *)m_pprebuffer->get_buffer_data(iBuffer);

                     auto iByteCount = m_pprebuffer->get_buffer_count();

                     ::memcpy_dup(pshTarget, pshSource, iByteCount);

                  }

               }
               else
               {

                  synchronouslock.unlock();

                  out_prebuffer_eof();

                  return;

               }

            }
            else
            {


            }

         }

      }

      try
      {

         if (m_bDirectOutput)
         {

            out_filled(iBuffer);

         }
         else
         {

            m_poutputthread->on_filled(iBuffer);

         }

      }
      catch (...)
      {

      }

   }


   void out::out_on_playback_end()
   {

      out_stop();

      if (m_pprebuffer->m_pstreameffectOut && m_pprebuffer->m_pstreameffectOut->m_bDeleteOnEnd)
      {

         m_pprebuffer->m_pstreameffectOut.release();

      }

      m_pplayer->OnEvent(player::e_player_event_playback_end);

   }


   bool out::defer_pump_message()
   {

      return ::thread::defer_pump_message();

   }


   void * out::out_get_os_data()
   {

      return nullptr;

   }


   ::pointer<buffer>out::out_get_buffer()
   {

      return m_pwavebuffer;

   }


   out::enum_state out::out_get_state()
   {

      return m_estate;

   }


} // namespace wave



