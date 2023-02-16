// Created on 2021-07-07 by camilo 14:11 BRT <3ThomasBorregaardSørensen!!

#include "framework.h"

#include <math.h>
//#include "aura/graphics/draw2d/_component.h"
//#include "capture.h"


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace video_input_video_avfoundation
{


   render::render()
   {

      //m_pSelectedDevice = nullptr;
      //m_pEngine = nullptr;

      m_pevRenderEnd = nullptr;

   }

   
   render::~render()
   {

   }

/**
 * Prepare the output frame structure for obs and compute plane offsets
 * For encoded formats (mjpeg) this clears the frame and plane offsets,
 * which will be filled in after decoding.
 *
 * Basically all data apart from memory pointers and the timestamp is known
 * before the capture starts. This function prepares the obs_source_frame
 * struct with all the data that is already known.
 *
 * v4l2 uses a continuous memory segment for all planes so we simply compute
 * offsets to add to the start address in order to give obs the correct data
 * pointers for the individual planes.
 *
 */
//   static void device::_v4l2_prep_obs_frame(struct v4l2_data *data,
//                                   struct obs_source_frame *frame,
//                                   size_t *plane_offsets)
//   {
//   }

   void render::initialize_video_input_render(::video_input::device * pdevice)
   {

      m_pdevice = pdevice;

      //start_capture();

//      memset(frame, 0, sizeof(struct obs_source_frame));
//      memset(plane_offsets, 0, sizeof(size_t) * MAX_AV_PLANES);
//
//      frame->width = data->width;
//      frame->height = data->height;
//      frame->format = v4l2_to_obs_video_format(data->pixfmt);
//      video_format_get_parameters(VIDEO_CS_DEFAULT, data->color_range,
//                                  frame->color_matrix, frame->color_range_min,
//                                  frame->color_range_max);
//
//      switch (data->pixfmt) {
//         case V4L2_PIX_FMT_NV12:
//            frame->linesize[0] = data->linesize;
//            frame->linesize[1] = data->linesize;
//            plane_offsets[1] = data->linesize * data->height;
//            break;
//         case V4L2_PIX_FMT_YVU420:
//            frame->linesize[0] = data->linesize;
//            frame->linesize[1] = data->linesize / 2;
//            frame->linesize[2] = data->linesize / 2;
//            plane_offsets[1] = data->linesize * data->height * 5 / 4;
//            plane_offsets[2] = data->linesize * data->height;
//            break;
//         case V4L2_PIX_FMT_YUV420:
//            frame->linesize[0] = data->linesize;
//            frame->linesize[1] = data->linesize / 2;
//            frame->linesize[2] = data->linesize / 2;
//            plane_offsets[1] = data->linesize * data->height;
//            plane_offsets[2] = data->linesize * data->height * 5 / 4;
//            break;
//         case V4L2_PIX_FMT_MJPEG:
//            frame->linesize[0] = 0;
//            frame->linesize[1] = 0;
//            frame->linesize[2] = 0;
//            plane_offsets[1] = 0;
//            plane_offsets[2] = 0;
//            break;
//         default:
//            frame->linesize[0] = data->linesize;
//            break;
//      }
//

   }


//   void render::assert_ok() const
//   {
//      
//      object::assert_ok();
//
//   }
//
//
//   void render::dump(dump_context& dumpcontext) const
//   {
//      
//      object::dump(dumpcontext);
//
//   }


   void render::on_create()
   {


      //string_array straName;

      //string_array straPath;

      //video_capture_enum_encoders(straName, straPath);


   }


   void render::destroy()
   {

      ::video_input::render::on_destroy();

      //m_pevRenderEnd = memory_new manual_reset_event(this);

      //m_prender->set_finish();

      //m_pevRenderEnd->wait(seconds(15));

      //delete m_pevRenderEnd;

      //return ::success;

   }


   //void render::on_layout(::draw2d::graphics_pointer& pgraphics)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   {

   //      synchronous_lock slText(m_pmutexText);

   //      if (m_strNewVideoCapture.is_empty())
   //      {

   //         if (m_bFastOnEmpty)
   //         {

   //            m_bFast = true;

   //         }

   //         return;

   //      }

   //   }

   //   m_prender->m_bHelloRender = true;

   //   if (m_bHelloLayoutOn001Layout)
   //   {

   //      m_prender->m_bNewLayout = true;

   //      m_bOkPending = true;

   //      m_bFast = true;

   //   }
   //   else
   //   {

   //      on_layout(pgraphics);

   //   }

   //}


   void render::handle(::topic * ptopic, ::context * pcontext)
   {

      //if (eupdate == 0)
      //{
      //   ::pointer<::userex::pane_tab_impact>ppaneimpact = get_typed_parent < ::userex::pane_tab_impact >();
      //   //if(ppaneimpact.is_set())
      //   //{
      //   //   ppaneimpact->m_pflagview = this;
      //   //}

      //}
      //__UNREFERENCED_PARAMETER(ptopic);
   }

   //bool render::in_anime()
   //{
   //   if (m_bFast || m_timeLastFast.elapsed() < m_timeFastAnime)
   //      return true;
   //   if (m_timeLastOk.elapsed() < m_timeAnime)
   //      return true;
   //   return false;
   //}



   //::user::document* render::get_document()
   //{

   //   return  (::user::impact::get_document());

   //}


   //void render::on_layout(::draw2d::graphics_pointer& pgraphics)
   //{

   //   ::rectangle_i32 rectangleClient;

   //   client_rectangle(rectangleClient);

   //   if (rectangleClient.area() <= 0)
   //      return;

   //         m_pimage = create_image(rectangleClient->size());

   //         start_capture();

   //         if(m_prender->m_cx == rectangleClient.width()
   //               && m_prender->m_cy == rectangleClient.height()
   //               && m_strNewFont == m_strFont)
   //            return;


   //         if(m_strNewFont != m_strFont)
   //         {
   //            m_strFont = m_strNewFont;

   //            datastream()->set("cur_font",m_strFont);

   //         }

   //         m_prender->m_cx = rectangleClient.width();

   //         m_prender->m_cy = rectangleClient.height();

   //         m_prender->m_rectangleClient = rectangleClient;

   //         m_prender->m_bNewLayout = true;

   //         m_bOkPending = true;

   //         m_bFast = true;

   //      }


      //   string render::get_processed_videocapture()
      //   {

      //      synchronous_lock slText(m_pmutexText);

      //      string str = get_videocapture();

      //      int c = m_ppcreutil->matches(str);

      ////      int c = pcre2_get_ovector_count(m_pmd);

      //      if(c > 0)
      //      {
      //         str += "Smile for you too (pcremade |-) !!";
      //      }


      //      if(str.case_insensitive_begins_eat("image:"))
      //      {

      //         string strImage = str;

      //         strsize iFind = strImage.find(",");

      //         if(iFind >= 0)
      //         {

      //            strImage = strImage.substr(0,iFind);

      //         }

      //         if(m_strImage != strImage)
      //         {

      //            m_strImage = strImage;


      //            ::fork(get_app(),[=]()
      //            {


      //               if(string_ends_ci(strImage,".png"))
      //               {
      //               }
      //               else if(string_ends_ci(strImage,".jpg"))
      //               {
      //               }
      //               else
      //               {
      //                  sleep(900_ms);
      //               }

      //               if(m_strImage != strImage)
      //                  return;


      //               get_document()->on_open_document(m_strImage);
      //               //   ::payload payloadFile;
      //               //
      //               //   payloadFile["url"] = strImage;
      //               //
      //               //   payloadFile["http_set"]["raw_http"] = purl->get_server(m_strImage).unicode_case_insensitive_find("ca2") < 0;
      //               //
      //               //   ::image_pointer pimage;
      //               //
      //               //   if(pimage->load_from_file(payloadFile))
      //               //   {
      //               //
      //               //      if(strImage == m_strImage)
      //               //      {

      //               //         *m_prender->m_pimageImage = * pimage;
      //               //      }

      //               //   }

      //            });

      //         }


      //         if(m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
      //         {

      //            if(str.case_insensitive_begins_eat(m_strImage))
      //            {
      //               str.case_insensitive_begins_eat(",");
      //            }

      //         }

      //      }

      //      if(str.case_insensitive_begins_eat("crt:"))
      //      {

      //         m_eeffect = effect_crt;

      //      }
      //      else
      //      {

      //         m_eeffect = effect_none;

      //      }

      //      return str;

      //   }


         //string render::get_videocapture()
         //{

         //   synchronous_lock synchronouslock(m_pmutexText);

         //   if(m_strVideoCapture != m_strNewVideoCapture)
         //   {

         //      m_strVideoCapture = m_strNewVideoCapture;

         //   }

         //   if(m_strVideoCapture.is_empty())
         //   {

         //      if(m_prender->m_bAlternate)
         //      {

         //         if(m_frequencyFramesPerSecond != 0.0)
         //         {
         //            return "Rolling " + papp->m_strAlternateVideoCapture;
         //         }
         //         else
         //         {
         //            return papp->m_strAlternateVideoCapture;
         //         }


         //      }
         //      else
         //      {

         //         if(m_frequencyFramesPerSecond != 0.0)
         //         {
         //            return "Rolling " + papp->m_strVideoCapture;
         //         }
         //         else
         //         {
         //            return papp->m_strVideoCapture;
         //         }


         //      }

         //   }
         //   else
         //   {

         //      return m_strVideoCapture;

         //   }

         //}


         //void render::defer_check_on_draw_layout()
         //{

         //   if (m_prender != nullptr)
         //   {

         //      synchronous_lock synchronouslock(m_pmutexText);

         //      if (get_processed_videocapture() != m_prender->m_strVideoCapture)
         //      {

         //         m_prender->m_strVideoCapture = get_processed_videocapture().c_str(); // rationale : string allocation fork *for parallelization*

         //         synchronouslock.unlock();

         //         set_need_layout();

         //      }

         //   }

         //}


         //void render::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
         //{

         //   if (m_prender->m_bImageEnable && m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
         //      //if(m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
         //   {

         //      //m_bFirstDone = true;

         //      ::rectangle_i32 rectangleWork(0, 0, m_prender->m_pimageWork->get_size()->cx, m_prender->m_pimageWork->get_size()->cy);
         //      ::rectangle_i32 rectangleImage(0, 0, m_prender->m_pimageImage->get_size()->cx, m_prender->m_pimageImage->get_size()->cy);

         //      rectangleImage.FitOnCenterOf(rectangleWork);

         //      m_pimagePost->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

         //      m_pimagePost->get_graphics()->StretchBlt(rectangleImage.left, rectangleImage->top, rectangleImage->width(), rectangleImage->height(),
         //                                             m_prender->m_pimagepimage->g(), 0, 0,
         //                                             m_prender->m_pimageImage->get_size()->cx,
         //                                             m_prender->m_pimageImage->get_size()->cy);


         //   }

         //}

         //void render::defer_update_bilbo()
         //{

         //   synchronous_lock synchronouslock(this->synchronization());

         //   for (auto & bilbo : m_bilboa)
         //   {

         //      if (bilbo.m_bNew && !bilbo.m_b)
         //      {

         //         m_stra23.add_unique(bilbo.m_strPath);

         //         bilbo.m_b = true;

         //         datastream()->set("bilbo." + bilbo.m_strPath, bilbo.m_b);

         //      }
         //      else if (!bilbo.m_bNew && bilbo.m_b)
         //      {

         //         m_stra23.erase(bilbo.m_strPath);

         //         bilbo.m_b = false;

         //         datastream()->set("bilbo." + bilbo.m_strPath, bilbo.m_b);

         //      }

         //   }

         //}

//   HRESULT render::OnSample(_In_opt_  IMFSample* pSample)
//   {
//
//      if (pSample == nullptr)
//      {
//
//         return S_OK;
//
//      }
//
//
//      IMFMediaBuffer* pBuffer = nullptr;
//
//      HRESULT hr = pSample->GetBufferByIndex(0, &pBuffer);
//
//      if (FAILED(hr) || pBuffer == nullptr)
//      {
//
//         return S_OK;
//
//      }
//
//      DWORD dwLen = 0;
//
//      hr = pBuffer->GetCurrentLength(&dwLen);
//
//      if (FAILED(hr) || dwLen <= 0)
//      {
//
//         pBuffer->Release();
//
//      }
//
//      byte * p = nullptr;
//
//      hr = pBuffer->Lock(&p, nullptr, nullptr);
//
//      if (FAILED(hr))
//      {
//
//         pBuffer->Release();
//
//      }
//
//      {
//
//         synchronous_lock synchronouslock(this->synchronization());
//
//         if (m_pimage->is_null() || m_pimage->get_data() == nullptr)
//         {
//
//            pBuffer->Unlock();
//
//            pBuffer->Release();
//
//            return S_OK;
//
//         }
//
//         ::memcpy_dup(m_pimage->m_pcolorref1, p, minimum(m_pimage->area() * 4, dwLen));
//
//      }
//
//      pBuffer->Unlock();
//
//      pBuffer->Release();
//
//      return S_OK;
//
//   }


//   STDMETHODIMP render::QueryInterface(REFIID riid, void** ppv)
//   {
//
//      //static const QITAB qit[] =
//      //{
//      //   QITABENT(render, IMFCaptureEngineOnSampleCallback),
//      //   { 0 }
//      //};
//      //return QISearch(this, qit, riid, ppv);
//
//      return E_FAIL;
//
//   }
//
//
//   STDMETHODIMP_(ULONG) render::AddRef()
//   {
//
//      return (ULONG) increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//   }
//
//
//   STDMETHODIMP_(ULONG) render::Release()
//   {
//
//      return (ULONG) release();
//
//   }


//   void render::OnCaptureEvent(wparam wparam, lparam lparam)
//   {
//
////      if (m_pEngine != nullptr)
////      {
////
////      }
//
//
//
//   }

//
//   bool render::start_capture()
//   {
//
//      m_pdevice->initialize_device();
//
//      return true;
//
//   }


} // namespace video_input_video_avfoundation



