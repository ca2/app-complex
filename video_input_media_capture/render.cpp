// Created on 2021-07-07 by camilo 14:11 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "render.h"
#include "device.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"
#include "app-complex/video_input/media_format.h"
#include "acme/_operating_system.h"
#include <winrt/windows.graphics.imaging.h>
#include <Memorybuffer.h>

extern "C"
{

#include <libavformat/avformat.h>


} // extern "C"

namespace video_input_media_capture
{


   render::render()
   {
      m_pswscontext = nullptr;
      //m_pSelectedDevice = nullptr;
      //m_pEngine = nullptr;

      m_pevRenderEnd = nullptr;

   }

   
   render::~render()
   {

   }


   void render::initialize_video_input_render(::video_input::device * pdevice)
   {

      m_pdevice = pdevice;

      start_capture();

   }


   void render::on_set_format()
   {


      if (m_pswscontext)
      {

         sws_freeContext(m_pswscontext);

      }

         m_pswscontext = sws_getContext(
       m_pdevice->m_size.cx(),
       m_pdevice->m_size.cy(),
       AV_PIX_FMT_YUYV422,
       m_pdevice->m_size.cx(),
       m_pdevice->m_size.cy(),
       AV_PIX_FMT_BGRA,
       SWS_BICUBIC, NULL, NULL, NULL);

   }


   void render::prepare_image()
   {

      m_pimage->map();

      if (::is_set(m_memory.data()))
      {

         m_pimage->image32()->copy(
            m_pimage->width(),
            m_pimage->height(),
            m_pimage->scan_size(),
            (::image32_t *)m_memory.data(),
            m_pimage->width() * 4);

      }

   }


   //void render::assert_ok() const
   //{
   //   
   //   object::assert_ok();

   //}


   //void render::dump(dump_context& dumpcontext) const
   //{
   //   
   //   object::dump(dumpcontext);

   //}


   void render::on_create()
   {


      //string_array straName;

      //string_array straPath;

      //video_capture_enum_encoders(straName, straPath);


   }


   void render::destroy()
   {

      ::video_input::render::on_destroy();

      //m_pevRenderEnd = ___new manual_reset_happening(this);

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


   void render::handle(::topic * ptopic, ::handler_context * phandlercontext)
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

   //   ::int_rectangle rectangleX;

   //   this->rectangle(rectangleX);

   //   if (rectangleX.area() <= 0)
   //      return;

   //         m_pimage = create_image(rectangleX->size());

   //         start_capture();

   //         if(m_prender->m_cx == rectangleX.width()
   //               && m_prender->m_cy == rectangleX.height()
   //               && m_strNewFont == m_strFont)
   //            return;


   //         if(m_strNewFont != m_strFont)
   //         {
   //            m_strFont = m_strNewFont;

   //            datastream()->set("cur_font",m_strFont);

   //         }

   //         m_prender->m_cx = rectangleX.width();

   //         m_prender->m_cy = rectangleX.height();

   //         m_prender->m_rectangleX = rectangleX;

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

      //         character_count iFind = strImage.find(",");

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
      //               //   ::image::image_pointer pimage;
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

         //      ::int_rectangle rectangleWork(0, 0, m_prender->m_pimageWork->get_size()->cx(), m_prender->m_pimageWork->get_size()->cy());
         //      ::int_rectangle rectangleImage(0, 0, m_prender->m_pimageImage->get_size()->cx(), m_prender->m_pimageImage->get_size()->cy());

         //      rectangleImage.FitOnCenterOf(rectangleWork);

         //      m_pimagePost->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

         //      m_pimagePost->get_graphics()->StretchBlt(rectangleImage.left(), rectangleImage->top(), rectangleImage->width(), rectangleImage->height(),
         //                                             m_prender->m_pimagepimage->g(), 0, 0,
         //                                             m_prender->m_pimageImage->get_size()->cx(),
         //                                             m_prender->m_pimageImage->get_size()->cy());


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

   //HRESULT render::OnSample(_In_opt_  IMFSample* pSample)
   //{

   //   if (pSample == nullptr)
   //   {

   //      return S_OK;

   //   }


   //   IMFMediaBuffer* pBuffer = nullptr;

   //   HRESULT hr = pSample->GetBufferByIndex(0, &pBuffer);

   //   if (FAILED(hr) || pBuffer == nullptr)
   //   {

   //      return S_OK;

   //   }

   //   DWORD dwLen = 0;

   //   hr = pBuffer->GetCurrentLength(&dwLen);

   //   if (FAILED(hr) || dwLen <= 0)
   //   {

   //      pBuffer->Release();

   //   }
   //
   //   unsigned char * p = nullptr;
   //
   //   hr = pBuffer->Lock(&p, nullptr, nullptr);
   //
   //   if (FAILED(hr))
   //   {

   //      pBuffer->Release();

   //   }

   //   {
   //
   //      synchronous_lock synchronouslock(this->synchronization());

   //      if (m_pimage->is_null() || m_pimage->get_data() == nullptr)
   //      {

   //         pBuffer->Unlock();

   //         pBuffer->Release();

   //         return S_OK;

   //      }

   //      ::memory_copy(m_pimage->m_pimage32, p, minimum(m_pimage->area() * 4, dwLen));

   //   }

   //   pBuffer->Unlock();

   //   pBuffer->Release();

   //   return S_OK;

   //}


   //STDMETHODIMP render::QueryInterface(REFIID riid, void** ppv)
   //{
   //
   //   //static const QITAB qit[] =
   //   //{
   //   //   QITABENT(render, IMFCaptureEngineOnSampleCallback),
   //   //   { 0 }
   //   //};
   //   //return QISearch(this, qit, riid, ppv);
   //   
   //   return E_FAIL;
   //   
   //}


   //STDMETHODIMP_(ULONG) render::AddRef()
   //{

   //   return (ULONG) increment_reference_count();

   //}


   //STDMETHODIMP_(ULONG) render::Release()
   //{
   //         
   //   return (ULONG) release();

   //}


   void render::OnCaptureEvent(wparam wparam, lparam lparam)
   {

      //if (m_pEngine != nullptr)
      //{

      //}

   }


   bool render::start_capture()
   {

      m_pdevice->initialize_device();

      return true;

   }


   void render::OnFrameArrived(::winrt::Windows::Media::Capture::Frames::MediaFrameReader framereader, ::winrt::Windows::Media::Capture::Frames::MediaFrameArrivedEventArgs args)
   {
      
      synchronous_lock synchronouslock(this->synchronization());

      if (m_pimage.nok())
      {

         return;

      }

      auto ref = m_mediaframereader.TryAcquireLatestFrame();

      if (ref)
      {

         auto videoframe = ref.VideoMediaFrame();

         if (videoframe)
         {

            auto bitmap = videoframe.SoftwareBitmap();
            int h = 0;
            int w = 0;
            ::array < ::comptr < Windows::Foundation::IMemoryBufferByteAccess > > adata;


            if (bitmap)
            {

               ::winrt::Windows::Graphics::Imaging::BitmapBuffer buffer = nullptr;

               buffer = bitmap.LockBuffer(::winrt::Windows::Graphics::Imaging::BitmapBufferAccessMode::Read);
               m_data[0] = nullptr;
               m_data[1] = nullptr;
               m_data[2] = nullptr;
               m_data[3] = nullptr;
               m_data[4] = nullptr;
               m_data[5] = nullptr;
               m_data[6] = nullptr;
               m_data[7] = nullptr;
               m_linesize[0] = 0;
               m_linesize[1] = 0;
               m_linesize[2] = 0;
               m_linesize[3] = 0;
               m_linesize[4] = 0;
               m_linesize[5] = 0;
               m_linesize[6] = 0;
               m_linesize[7] = 0;

               int iPlaneCount = buffer.GetPlaneCount();

               for (int iPlane = 0; iPlane < iPlaneCount; iPlane++)
               {


                  auto description = buffer.GetPlaneDescription(iPlane);

                  //if (description)
                  {

                     w = minimum(description.Width, m_pimage->width());

                     h = minimum(description.Height, m_pimage->height());

                     if (w > 0 && h > 0)
                     {

                        //linesize = i + 1;

                        /// m_pimage->map();

                        ::winrt::Windows::Foundation::IMemoryBufferReference reference = nullptr;

                        reference = buffer.CreateReference();

                        //comptr < Windows::Foundation::IMemoryBufferByteAccess  > paccess;
                        auto paccess = reference.try_as< Windows::Foundation::IMemoryBufferByteAccess>();
                        //access = nullptr;

                        adata.add(paccess.get());
                        //reference.as(access);

                        BYTE * pdata = nullptr;

                        UINT32 uSize = 0;

                        auto hresult = paccess->GetBuffer(&pdata, &uSize);


                        m_data[iPlane] = pdata;
                        m_linesize[iPlane] = description.Stride;

                        auto sizeBytes = (h * description.Stride);



                        //if (SUCCEEDED(hresult) && uSize >= sizeBytes)
                        //{

                        //   //::copy_image32((::color32_t *)m_memory.data(), w, h, w * 4,
                        //     // (::color32_t *) pdata, description.Stride);

                        //}

                     }

                  }


               }


               m_memory.set_size(h * w * 4);

               uint8_t * data[AV_NUM_DATA_POINTERS];
               int  linesize[AV_NUM_DATA_POINTERS];

               data[0] = m_memory.data();
               data[1] = nullptr;
               data[2] = nullptr;
               data[3] = nullptr;
               data[4] = nullptr;
               data[5] = nullptr;
               data[6] = nullptr;
               data[7] = nullptr;
               linesize[0] = w * 4;
               linesize[1] = 0;
               linesize[2] = 0;
               linesize[3] = 0;
               linesize[4] = 0;
               linesize[5] = 0;
               linesize[6] = 0;
               linesize[7] = 0;

               sws_scale(
   m_pswscontext,
   m_data,
   m_linesize,
   0,
   h,
   data,
   linesize);


            }


         }

      }

      

//   }




   }



} // namespace video_input_media_capture



