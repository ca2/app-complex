#include "framework.h"
#include "callback.h"
#include "device.h"
#include "render.h"
#include "_functionh_ffmpeg.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"
#include "app-complex/video_input/frame.h"


bool ffmpeg_init_frame(AVFrame **framep, int width, int height);
void ffmpeg_free_frame(AVFrame **framep);


namespace video_input_video_for_linux
{


   callback::callback(device * pdevice, ::u32 deviceID) :
      m_cRef(1), m_uDevice(deviceID), m_iMemory(0), m_bClose(false),
      m_pframe(nullptr)
   {

      m_pframePicture = nullptr;
      m_pframe = nullptr;
      m_psws = nullptr;
      m_sizeSwsDest.cx = -1;
      m_sizeSwsDest.cy = -1;
      m_pdevice = pdevice;
      m_bStopCapture = false;
      m_bCapturing = false;

   }


   callback::~callback(void)
   {

      if(m_pframe != nullptr)
      {

         delete m_pframe;

      }

   }


   
   void callback::stop_capturing()
   {

      if(m_bCapturing)
      {

         m_bStopCapture = true;

         m_eventStop.wait(5_s);

      }

   }


   void callback::start_capturing()
   {

      m_bStopCapture = false;

      m_eventStop.ResetEvent();

/*
 * Worker thread to get video data
 */
//      static void *v4l2_thread(void *vptr)
//      {
         //V4L2_DATA(vptr);
         int r;
         fd_set fds;
         uint8_t *start;
         uint64_t frames;
         uint64_t first_ts;
         struct timeval tv;
         struct v4l2_buffer buf;
         //struct obs_source_frame out;
         size_t plane_offsets[MAX_AV_PLANES]={};
         size_t linesize[MAX_AV_PLANES]={};
         float ffps;
         uint64_t timeout_usec;

         //FORMATTED_INFORMATION("%s: memory_new capture thread", m_pdevice->m_iDeviceice_id);
         //os_set_thread_name("v4l2: capture");

         /* Get framerate and calculate appropriate select timeout value. */
         ffps = (float)m_pdevice->m_iFrameRateDenominator / (float) m_pdevice->m_iFrameRateNumerator;
         FORMATTED_INFORMATION("%s: framerate: %.2f fps", m_pdevice->m_strDevice.c_str(), ffps);
         /* Timeout set to 5 frame periods. */
         timeout_usec = (1000000 * m_pdevice->m_iTimeoutFrames) / ffps;
      FORMATTED_INFORMATION(
              "%s: select timeout set to %" PRIu64 " (%Δx frame periods)",
              m_pdevice->m_strDevice.c_str(), timeout_usec, m_pdevice->m_iTimeoutFrames);

         //if (v4l2_start_capture(m_pdevice->m_iDevice, &data->buffers) < 0)
           // goto exit;

      m_sizeSwsDest.cx = -1;
      m_sizeSwsDest.cy = -1;
      m_pframePicture = nullptr;

      m_pdevice->_start_capture();

      m_bCapturing = true;

      FORMATTED_INFORMATION("%s: memory_new capture started", m_pdevice->m_strDevice.c_str());

      m_pframe = memory_new ::video::frame(v4l2_pix_fmt_to_video_format(m_pdevice->m_iPixFmt),
                                    m_pdevice->m_size.cx, m_pdevice->m_size.cy);

//      m_pframe->video_frame_init(x);


      switch(m_pdevice->m_iPixFmt) {
         case V4L2_PIX_FMT_NV12:
            linesize[0] = m_pframe->m_linesize[0];
            linesize[1] = m_pframe->m_linesize[0] / 2;
            plane_offsets[1] = m_pframe->m_linesize[0] * m_pdevice->m_size.cy;
            break;
         case V4L2_PIX_FMT_YVU420:
            linesize[0] = m_pframe->m_linesize[0];
            linesize[1] = m_pframe->m_linesize[0] / 2;
            linesize[2] = m_pframe->m_linesize[0] / 2;
            plane_offsets[1] = m_pframe->m_linesize[0] * m_pdevice->m_size.cy * 5 / 4;
            plane_offsets[2] = m_pframe->m_linesize[0] * m_pdevice->m_size.cy;
            break;
         case V4L2_PIX_FMT_YUV420:
            linesize[0] = m_pframe->m_linesize[0];
            linesize[1] = m_pframe->m_linesize[0] / 2;
            linesize[2] = m_pframe->m_linesize[0] / 2;
            plane_offsets[1] = m_pframe->m_linesize[0] * m_pdevice->m_size.cy;
            plane_offsets[2] = m_pframe->m_linesize[0] * m_pdevice->m_size.cy* 5 / 4;
            break;
         default:
            linesize[0] = m_pframe->m_linesize[0];
            break;
      }

      frames = 0;
      first_ts = 0;
//         v4l2_prep_obs_frame(data, &out, plane_offsets);
//
//         FORMATTED_INFORMATION("%s: obs frame prepared", m_pdevice->m_strDevice.c_str());

      while (::task_get_run() && !m_bStopCapture)
      {

         FD_ZERO(&fds);

         FD_SET(m_pdevice->m_iDevice, &fds);

         tv.tv_sec = 2;

         tv.tv_usec= 0;
         //tv.tv_usec = timeout_usec;

         r = select(m_pdevice->m_iDevice + 1, &fds, NULL, NULL, &tv);

         if(m_bStopCapture)
         {

            break;

         }

         if (r < 0)
         {

            if (errno == EINTR)
            {

               continue;

            }

            FORMATTED_ERROR("%s: select failed", m_pdevice->m_strDevice.c_str());

            break;

         }
         else if (r == 0)
         {

            FORMATTED_ERROR("%s: select timed out", m_pdevice->m_strDevice.c_str());

#ifdef _DEBUG

            m_pdevice->_query_all_buffers();

#endif

            if (v4l2_ioctl(m_pdevice->m_iDevice, VIDIOC_LOG_STATUS) < 0)
            {

               FORMATTED_ERROR("%s: failed to log status", m_pdevice->m_strDevice.c_str());

            }

            if (m_pdevice->m_bAutoReset)
            {

               m_pdevice->_reset_capture();

               FORMATTED_INFORMATION("%s: stream reset successful", m_pdevice->m_strDevice.c_str());
//                  else
//                     FORMATTED_ERROR("%s: failed to reset",
//                          m_pdevice->m_strDevice.c_str());
            }

            continue;

         }

         buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
         buf.memory = V4L2_MEMORY_MMAP;

         if (v4l2_ioctl(m_pdevice->m_iDevice, VIDIOC_DQBUF, &buf) < 0)
         {

            if (errno == EAGAIN)
            {

               FORMATTED_INFORMATION("%s: ioctl dqbuf eagain", m_pdevice->m_strDevice.c_str());

               continue;

            }

            FORMATTED_ERROR("%s: failed to dequeue buffer", m_pdevice->m_strDevice.c_str());

            break;

         }

         m_pdevice->m_iBufferedCount--;

         FORMATTED_INFORMATION(
              "%s: ts: %06ld buf id #%d, flags 0x%08X, seq #%d, len %d, used %d",
              m_pdevice->m_strDevice.c_str(), buf.timestamp.tv_usec, buf.index,
              buf.flags, buf.sequence, buf.length, buf.bytesused);

         m_iTimestamp = timeval2ns(buf.timestamp);

         if (!frames)
         {

            first_ts = m_iTimestamp;

         }

         m_iTimestamp -= first_ts;

         start = (uint8_t *)m_pdevice->m_pmemorymap->m_itema[buf.index].start;

         if (m_pdevice->m_iPixFmt == V4L2_PIX_FMT_MJPEG)
         {

            m_pdevice->m_pmjpegdecoder->decode(m_pframe, start, buf.bytesused);

//                                                      < 0) {
//                  FORMATTED_ERROR("failed to unpack jpeg");
//                  break;
//               }
         }
         else
         {

            auto eformat = v4l2_pix_fmt_to_video_format(m_pdevice->m_iPixFmt);

            int cy = m_pdevice->m_size.cy;

            switch (eformat) {
               case e_video_format_none:
                  return;

               case e_video_format_i420:
                  memcpy(m_pframe->m_data[0], start + plane_offsets[0], linesize[0] * cy);
                  memcpy(m_pframe->m_data[1], start + plane_offsets[1], linesize[1] * cy / 2);
                  memcpy(m_pframe->m_data[2], start + plane_offsets[2], linesize[2] * cy / 2);
                  break;

               case e_video_format_nv12:
                  memcpy(m_pframe->m_data[0], start + plane_offsets[0], linesize[0] * cy);
                  memcpy(m_pframe->m_data[1], start + plane_offsets[1], linesize[1] * cy / 2);
                  break;

               case e_video_format_y800:
               case e_video_format_yvyu:
               case e_video_format_yuy2:
               case e_video_format_uyvy:
               case e_video_format_rgba:
               case e_video_format_bgra:
               case e_video_format_bgrx:
               case e_video_format_bgr3:
               case e_video_format_ayuv:
                  memcpy(m_pframe->m_data[0], start + plane_offsets[0], linesize[0] * cy);
                  break;

               case e_video_format_i444:
               case e_video_format_i422:
                  memcpy(m_pframe->m_data[0], start + plane_offsets[0], linesize[0] * cy);
                  memcpy(m_pframe->m_data[1], start + plane_offsets[1], linesize[1] * cy);
                  memcpy(m_pframe->m_data[2], start + plane_offsets[2], linesize[2] * cy);
                  break;

               case e_video_format_i40a:
                  memcpy(m_pframe->m_data[0], start + plane_offsets[0], linesize[0] * cy);
                  memcpy(m_pframe->m_data[1], start + plane_offsets[1], linesize[1] * cy / 2);
                  memcpy(m_pframe->m_data[2], start + plane_offsets[2], linesize[2] * cy / 2);
                  memcpy(m_pframe->m_data[3], start + plane_offsets[3], linesize[3] * cy);
                  break;

               case e_video_format_i42a:
               case e_video_format_yuva:
                  memcpy(m_pframe->m_data[0], start + plane_offsets[0], linesize[0] * cy);
                  memcpy(m_pframe->m_data[1], start + plane_offsets[1], linesize[1] * cy);
                  memcpy(m_pframe->m_data[2], start + plane_offsets[2], linesize[2] * cy);
                  memcpy(m_pframe->m_data[3], start + plane_offsets[3], linesize[3] * cy);
                  break;
            }

         }

         //obs_source_output_video(m_pdevice->m_iSource, &out);

         ::size_i32 s;

         s.cx = m_pdevice->m_size.cx;
         s.cy = m_pdevice->m_size.cy;

         if (m_sizeSwsDest.area() <= 0 || m_sizeSwsDest != s || m_psws == nullptr)
         {

            m_sizeSwsDest = s;

            int iFlags = SWS_FAST_BILINEAR;

            //#if !defined(ANDROID) && !defined(_UWP)

            //iFlags |= SWS_C | SWS_CPU_CAPS_MMX2;

            //#endif

            if (m_psws != nullptr)
            {

               sws_freeContext(m_psws);

            }

            //if (m_ppic != nullptr)
            //{

            //   av_freep(m_ppic->data);

            //}

            auto evideoformat = v4l2_pix_fmt_to_video_format(m_pdevice->m_iPixFmt);

            auto avpixelformat = video_format_to_avpixelformat(evideoformat);

            m_psws = sws_getContext(m_pdevice->m_size.cx,
                                    m_pdevice->m_size.cy,
                                    avpixelformat,
                                    m_sizeSwsDest.cx,
                                    m_sizeSwsDest.cy, FFMPEG_DST_PIXEL_FORMAT, iFlags,
                                    nullptr, nullptr, nullptr);

            ffmpeg_init_frame(&m_pframePicture, m_sizeSwsDest.cx, m_sizeSwsDest.cy);

         }

         sws_scale(m_psws, m_pframe->m_data, (const int *) m_pframe->m_linesize, 0,
                   m_pframe->m_height-1, m_pframePicture->data, m_pframePicture->linesize);

         auto prender = m_pdevice->get_render();

         synchronous_lock synchronouslock(prender->synchronization());

         auto & pimage = prender->m_pimage;

         if(pimage.nok())
         {

            __construct(pimage);

         }

         pimage->create(m_sizeSwsDest);

         if (pimage.ok())
         {

            pimage->map();

            color32_t * pref = pimage->get_data();

#if defined(MACOS)

            ::vertical_swap_copy_colorref(pref,m_pdecoder->m_sizeSwsDest.cx, m_pdecoder->m_sizeSwsDest.cy,
                                                   pimage->scan_size(), (color32_t *)m_ppic->data[0], m_ppic->linesize[0]);

#elif defined(APPLE_IOS)

            ::draw2d::vertical_swap_copy_colorref_swap_red_blue(m_pdecoder->m_sizeSwsDest.cx, m_pdecoder.m_sizeSwsDest.cy,
                  pref, pimage->m_iScan, (color32_t *)m_ppic->data[0], m_ppic->linesize[0]);

#else

            ::copy_colorref(pref, m_sizeSwsDest.cx, m_sizeSwsDest.cy,
                            pimage->scan_size(), (color32_t *) m_pframePicture->data[0],
                            m_pframePicture->linesize[0]);

#endif


         }

         if(!m_bStopCapture)
         {

            if (v4l2_ioctl(m_pdevice->m_iDevice, VIDIOC_QBUF, &buf) < 0)
            {
               FORMATTED_ERROR("%s: failed to enqueue buffer",
                               m_pdevice->m_strDevice.c_str());
               break;
            }

            frames++;

            m_pdevice->m_iBufferedCount++;

         }

      }

      FORMATTED_INFORMATION("%s: Stopped capture after %" PRIu64 " frames",
           m_pdevice->m_strDevice.c_str(), frames);

      exit:

      m_bCapturing = false;

      m_pdevice->_stop_capture();

      if (m_psws != nullptr)
      {

         sws_freeContext(m_psws);

         m_psws = nullptr;

      }

      delete m_pframe;

      m_pframe = nullptr;

      if(m_pframePicture)
      {

         ffmpeg_free_frame(&m_pframePicture);

         m_pframePicture = nullptr;

      }

      m_pdevice->close();

      m_eventStop.set_event();

   }


} // namespace video_input_video_for_linux



