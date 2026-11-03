#include "platform.h"
#include "render.h"
#include "device.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"
#if defined(_M_X64) || defined(_M_IX86)
#include <emmintrin.h>
#endif
namespace video_input_direct_show
{
   void render::initialize_video_input_render(::video_input::device * pdevice)
   {
      m_pdevice = dynamic_cast<device *>(pdevice);
   }
   void render::prepare_image()
   {
      if (!m_pdevice || !m_pdevice->m_pgrabber) return;
      synchronous_lock lock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      auto receiver = m_pdevice->m_preceiver;
      if (!receiver) return;
      std::unique_lock<std::mutex> frameLock(receiver->m_mutex);
      if (!receiver->m_generation || receiver->m_generation == m_uFramesReceived) return;
      // Exchange reusable buffers, then let capture continue during GPU upload.
      auto generation = receiver->m_generation;
      auto captureTime = receiver->m_time;
      auto & pixels = m_pdevice->m_pixels;
      pixels.swap(receiver->m_frame);
      frameLock.unlock();
      auto bytes = pixels.size();
      // Previous polling path (the graph interface belongs to the application thread):
//       long bytes = 0;
//       if (FAILED(m_pdevice->m_pgrabber->GetCurrentBuffer(&bytes, nullptr)) || bytes <= 0) return;
//       auto & pixels = m_pdevice->m_pixels; pixels.resize(bytes);
//       if (FAILED(m_pdevice->m_pgrabber->GetCurrentBuffer(&bytes, (long *)pixels.data()))) return;
      auto size = m_pdevice->m_size;
      if ((size_t)bytes < (size_t)size.cx * size.cy * 4) return;
      if (!m_pimage || m_pimage->size() != size) { defer_constructø(m_pimage); m_pimage->create_as_descriptor(size, m_pdevice->draw2d_domain()); }
      auto pixmap = m_pimage->map(::image::e_map_discard);
      if (!pixmap) return;
      auto stride = size.cx * 4;
      for (int y = 0; y < size.cy; ++y)
      {
         int sourceY = m_pdevice->m_lConnectedHeight > 0 ? size.cy - 1 - y : y;
         auto dst = (unsigned char *)pixmap->m_pimage32 + y * pixmap->m_iScan;
         auto src = pixels.data() + (size_t)sourceY * stride;
         int x = 0;
#if defined(_M_X64) || defined(_M_IX86)
         const auto alpha = _mm_set1_epi32((int)0xff000000u);
         for (; x + 4 <= size.cx; x += 4)
         {
            auto rgba = _mm_loadu_si128((const __m128i *)(src + x * 4));
            _mm_storeu_si128((__m128i *)(dst + x * 4), _mm_or_si128(rgba, alpha));
         }
#endif
         for (; x < size.cx; ++x)
         {
            memcpy(dst + x * 4, src + x * 4, 4);
            dst[x * 4 + 3] = 255;
         }
      }
      if (m_timeFpsWindow.time_since_epoch().count() == 0)
      {
         m_timeFpsWindow = captureTime;
         m_uFpsWindowFrames = generation;
      }
      auto seconds = std::chrono::duration<double>(captureTime - m_timeFpsWindow).count();
      if (seconds >= 1.0)
      {
         m_dCaptureFps = (generation - m_uFpsWindowFrames) / seconds;
         m_timeFpsWindow = captureTime;
         m_uFpsWindowFrames = generation;
      }
      m_uFramesReceived = generation;
      m_timeLastFrame = captureTime;
   }
   void render::destroy()
   {
      m_pdevice = nullptr; m_pimage.release(); ::object::destroy();
   }
}


// Previous Media Foundation implementation retained for migration reference.
// // Created on 2021-07-07 by camilo 14:11 BRT <3ThomasBorregaardSorensen!!
// #include "platform.h"
// #include "render.h"
// #include "device.h"
// #include "acme/parallelization/synchronous_lock.h"
// #include "aura/graphics/image/image.h"
// #include "app-complex/video_input/media_format.h"
// 
// 
// namespace video_input_direct_show
// {
// 
// 
//    render::render()
//    {
// 
//       m_pSelectedDevice = nullptr;
//       m_pEngine = nullptr;
// 
//       m_pevRenderEnd = nullptr;
// 
//    }
// 
//    
//    render::~render()
//    {
// 
//    }
// 
// 
//    void render::initialize_video_input_render(::video_input::device * pdevice)
//    {
// 
//       m_pdevice = pdevice;
// 
//       start_capture();
// 
//    }
// 
// 
//    //void render::assert_ok() const
//    //{
//    //   
//    //   object::assert_ok();
// 
//    //}
// 
// 
//    //void render::dump(dump_context& dumpcontext) const
//    //{
//    //   
//    //   object::dump(dumpcontext);
// 
//    //}
// 
// 
//    void render::on_create()
//    {
// 
// 
//       //string_array_base straName;
// 
//       //string_array_base straPath;
// 
//       //video_capture_enum_encoders(straName, straPath);
// 
// 
//    }
// 
// 
//    void render::destroy()
//    {
// 
//       ::video_input::render::on_destroy();
// 
//       //m_pevRenderEnd = ___new manual_reset_happening(this);
// 
//       //m_prender->set_finish();
// 
//       //m_pevRenderEnd->wait(seconds(15));
// 
//       //delete m_pevRenderEnd;
// 
//       //return ::success;
// 
//    }
// 
// 
//    //void render::on_layout(::draw2d::graphics_pointer& pdraw2dgraphics)
//    //{
// 
//    //   synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
// 
//    //   {
// 
//    //      synchronous_lock slText(m_pmutexText, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
// 
//    //      if (m_strNewVideoCapture.is_empty())
//    //      {
// 
//    //         if (m_bFastOnEmpty)
//    //         {
// 
//    //            m_bFast = true;
// 
//    //         }
// 
//    //         return;
// 
//    //      }
// 
//    //   }
// 
//    //   m_prender->m_bHelloRender = true;
// 
//    //   if (m_bHelloLayoutOn001Layout)
//    //   {
// 
//    //      m_prender->m_bNewLayout = true;
// 
//    //      m_bOkPending = true;
// 
//    //      m_bFast = true;
// 
//    //   }
//    //   else
//    //   {
// 
//    //      on_layout(pdraw2dgraphics);
// 
//    //   }
// 
//    //}
// 
// 
//    void render::handle(::topic * ptopic, ::handler_context * phandlercontext)
//    {
// 
//       //if (eupdate == 0)
//       //{
//       //   ::pointer<::userex::pane_tab_impact>ppaneimpact = get_typed_parent < ::userex::pane_tab_impact >();
//       //   //if(ppaneimpact.is_set())
//       //   //{
//       //   //   ppaneimpact->m_pflagview = this;
//       //   //}
// 
//       //}
//       //__UNREFERENCED_PARAMETER(ptopic);
//    }
// 
//    //bool render::in_anime()
//    //{
//    //   if (m_bFast || m_timeLastFast.elapsed() < m_timeFastAnime)
//    //      return true;
//    //   if (m_timeLastOk.elapsed() < m_timeAnime)
//    //      return true;
//    //   return false;
//    //}
// 
// 
// 
//    //::user::document* render::get_document()
//    //{
// 
//    //   return  (::user::impact::get_document());
// 
//    //}
// 
// 
//    //void render::on_layout(::draw2d::graphics_pointer& pdraw2dgraphics)
//    //{
// 
//    //   ::i32_rectangle rectangleX;
// 
//    //   this->rectangle(rectangleX);
// 
//    //   if (rectangleX.area() <= 0)
//    //      return;
// 
//    //         m_pimage = create_image(rectangleX->size());
// 
//    //         start_capture();
// 
//    //         if(m_prender->m_cx == rectangleX.width()
//    //               && m_prender->m_cy == rectangleX.height()
//    //               && m_strNewFont == m_strFont)
//    //            return;
// 
// 
//    //         if(m_strNewFont != m_strFont)
//    //         {
//    //            m_strFont = m_strNewFont;
// 
//    //            datastream()->set("cur_font",m_strFont);
// 
//    //         }
// 
//    //         m_prender->m_cx = rectangleX.width();
// 
//    //         m_prender->m_cy = rectangleX.height();
// 
//    //         m_prender->m_rectangleX = rectangleX;
// 
//    //         m_prender->m_bNewLayout = true;
// 
//    //         m_bOkPending = true;
// 
//    //         m_bFast = true;
// 
//    //      }
// 
// 
//       //   string render::get_processed_videocapture()
//       //   {
// 
//       //      synchronous_lock slText(m_pmutexText, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
// 
//       //      string str = get_videocapture();
// 
//       //      int c = m_ppcreutil->matches(str);
// 
//       ////      int c = pcre2_get_ovector_count(m_pmd);
// 
//       //      if(c > 0)
//       //      {
//       //         str += "Smile for you too (pcremade |-) !!";
//       //      }
// 
// 
//       //      if(str.case_insensitive_begins_eat("image:"))
//       //      {
// 
//       //         string strImage = str;
// 
//       //         character_count iFind = strImage.find(",");
// 
//       //         if(iFind >= 0)
//       //         {
// 
//       //            strImage = strImage.substr(0,iFind);
// 
//       //         }
// 
//       //         if(m_strImage != strImage)
//       //         {
// 
//       //            m_strImage = strImage;
// 
// 
//       //            ::fork(get_app(),[=]()
//       //            {
// 
// 
//       //               if(string_ends_ci(strImage,".png"))
//       //               {
//       //               }
//       //               else if(string_ends_ci(strImage,".jpg"))
//       //               {
//       //               }
//       //               else
//       //               {
//       //                  sleep(900_ms);
//       //               }
// 
//       //               if(m_strImage != strImage)
//       //                  return;
// 
// 
//       //               get_document()->on_open_document(m_strImage);
//       //               //   ::payload payloadFile;
//       //               //
//       //               //   payloadFile["url"] = strImage;
//       //               //
//       //               //   payloadFile["http_set"]["raw_http"] = purl->get_server(m_strImage).unicode_case_insensitive_find("ca2") < 0;
//       //               //
//       //               //   ::image::image_pointer pimage;
//       //               //
//       //               //   if(pimage->load_from_file(payloadFile))
//       //               //   {
//       //               //
//       //               //      if(strImage == m_strImage)
//       //               //      {
// 
//       //               //         *m_prender->m_pimageImage = * pimage;
//       //               //      }
// 
//       //               //   }
// 
//       //            });
// 
//       //         }
// 
// 
//       //         if(m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
//       //         {
// 
//       //            if(str.case_insensitive_begins_eat(m_strImage))
//       //            {
//       //               str.case_insensitive_begins_eat(",");
//       //            }
// 
//       //         }
// 
//       //      }
// 
//       //      if(str.case_insensitive_begins_eat("crt:"))
//       //      {
// 
//       //         m_eeffect = effect_crt;
// 
//       //      }
//       //      else
//       //      {
// 
//       //         m_eeffect = effect_none;
// 
//       //      }
// 
//       //      return str;
// 
//       //   }
// 
// 
//          //string render::get_videocapture()
//          //{
// 
//          //   synchronous_lock synchronouslock(m_pmutexText, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
// 
//          //   if(m_strVideoCapture != m_strNewVideoCapture)
//          //   {
// 
//          //      m_strVideoCapture = m_strNewVideoCapture;
// 
//          //   }
// 
//          //   if(m_strVideoCapture.is_empty())
//          //   {
// 
//          //      if(m_prender->m_bAlternate)
//          //      {
// 
//          //         if(m_frequencyFramesPerSecond != 0.0)
//          //         {
//          //            return "Rolling " + papp->m_strAlternateVideoCapture;
//          //         }
//          //         else
//          //         {
//          //            return papp->m_strAlternateVideoCapture;
//          //         }
// 
// 
//          //      }
//          //      else
//          //      {
// 
//          //         if(m_frequencyFramesPerSecond != 0.0)
//          //         {
//          //            return "Rolling " + papp->m_strVideoCapture;
//          //         }
//          //         else
//          //         {
//          //            return papp->m_strVideoCapture;
//          //         }
// 
// 
//          //      }
// 
//          //   }
//          //   else
//          //   {
// 
//          //      return m_strVideoCapture;
// 
//          //   }
// 
//          //}
// 
// 
//          //void render::defer_check_on_draw_layout()
//          //{
// 
//          //   if (m_prender != nullptr)
//          //   {
// 
//          //      synchronous_lock synchronouslock(m_pmutexText, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
// 
//          //      if (get_processed_videocapture() != m_prender->m_strVideoCapture)
//          //      {
// 
//          //         m_prender->m_strVideoCapture = get_processed_videocapture().c_str(); // rationale : string allocation fork *for parallelization*
// 
//          //         synchronouslock.unlock();
// 
//          //         set_need_layout();
// 
//          //      }
// 
//          //   }
// 
//          //}
// 
// 
//          //void render::on_draw_image_layer(::draw2d::graphics_pointer & pdraw2dgraphics)
//          //{
// 
//          //   if (m_prender->m_bImageEnable && m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
//          //      //if(m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
//          //   {
// 
//          //      //m_bFirstDone = true;
// 
//          //      ::i32_rectangle rectangleWork(0, 0, m_prender->m_pimageWork->get_size()->cx, m_prender->m_pimageWork->get_size()->cy);
//          //      ::i32_rectangle rectangleImage(0, 0, m_prender->m_pimageImage->get_size()->cx, m_prender->m_pimageImage->get_size()->cy);
// 
//          //      rectangleImage.FitOnCenterOf(rectangleWork);
// 
//          //      m_pimagePost->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);
// 
//          //      m_pimagePost->get_graphics()->StretchBlt(rectangleImage.left, rectangleImage->top, rectangleImage->width(), rectangleImage->height(),
//          //                                             m_prender->m_pgraphicsImagepimage->, 0, 0,
//          //                                             m_prender->m_pimageImage->get_size()->cx,
//          //                                             m_prender->m_pimageImage->get_size()->cy);
// 
// 
//          //   }
// 
//          //}
// 
//          //void render::defer_update_bilbo()
//          //{
// 
//          //   synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
// 
//          //   for (auto & bilbo : m_bilboa)
//          //   {
// 
//          //      if (bilbo.m_bNew && !bilbo.m_b)
//          //      {
// 
//          //         m_stra23.add_unique(bilbo.m_strPath);
// 
//          //         bilbo.m_b = true;
// 
//          //         datastream()->set("bilbo." + bilbo.m_strPath, bilbo.m_b);
// 
//          //      }
//          //      else if (!bilbo.m_bNew && bilbo.m_b)
//          //      {
// 
//          //         m_stra23.erase(bilbo.m_strPath);
// 
//          //         bilbo.m_b = false;
// 
//          //         datastream()->set("bilbo." + bilbo.m_strPath, bilbo.m_b);
// 
//          //      }
// 
//          //   }
// 
//          //}
// 
//    HRESULT render::OnSample(_In_opt_  IMFSample* pSample)
//    {
// 
//       if (pSample == nullptr)
//       {
// 
//          return S_OK;
// 
//       }
// 
// 
//       IMFMediaBuffer* pBuffer = nullptr;
// 
//       HRESULT hr = pSample->GetBufferByIndex(0, &pBuffer);
// 
//       if (FAILED(hr) || pBuffer == nullptr)
//       {
// 
//          return S_OK;
// 
//       }
// 
//       DWORD dwLen = 0;
// 
//       hr = pBuffer->GetCurrentLength(&dwLen);
// 
//       if (FAILED(hr) || dwLen <= 0)
//       {
// 
//          pBuffer->Release();
// 
//       }
//    
//       ::u8 * p = nullptr;
//    
//       hr = pBuffer->Lock(&p, nullptr, nullptr);
//    
//       if (FAILED(hr))
//       {
// 
//          pBuffer->Release();
// 
//       }
// 
//       {
//    
//          synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
// 
//          auto ppixmap = m_pimage->map();
// 
//          if (!ppixmap)
//          {
// 
//             pBuffer->Unlock();
// 
//             pBuffer->Release();
// 
//             return S_OK;
// 
//          }
// 
//          ppixmap->copy(ppixmap->size(), (::image32_t *) p, minimum(m_pimage->area() * 4, dwLen));
// 
//       }
// 
//       pBuffer->Unlock();
// 
//       pBuffer->Release();
// 
//       return S_OK;
// 
//    }
// 
// 
//    STDMETHODIMP render::QueryInterface(REFIID riid, void** ppv)
//    {
//    
//       //static const QITAB qit[] =
//       //{
//       //   QITABENT(render, IMFCaptureEngineOnSampleCallback),
//       //   { 0 }
//       //};
//       //return QISearch(this, qit, riid, ppv);
//       
//       return E_FAIL;
//       
//    }
// 
// 
//    STDMETHODIMP_(ULONG) render::AddRef()
//    {
// 
//       return (ULONG) increment_reference_count();
// 
//    }
// 
// 
//    STDMETHODIMP_(ULONG) render::Release()
//    {
//             
//       return (ULONG) release();
// 
//    }
// 
// 
//    void render::OnCaptureEvent(wparam wparam, lparam lparam)
//    {
// 
//       if (m_pEngine != nullptr)
//       {
// 
//       }
// 
//    }
// 
// 
//    bool render::start_capture()
//    {
// 
//       m_pdevice->initialize_device();
// 
//       return true;
// 
//    }
// 
// 
// } // namespace video_input_direct_show
// 
// 
// 
