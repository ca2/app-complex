#include "framework.h"
#include <math.h>
//#include "capture.h"


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace videocapture
{

   view::bilbo::bilbo()
   {

      m_b         = false;
      m_bNew      = false;

   }

   view::bilbo::bilbo(string strPath) :
      bilbo()
   {

      m_strPath   = strPath;

   }

   view::bilbo::~bilbo()
   {
   }

   view::view(::object * pobject):
      object(pobject),
      impact_base(pobject),

   {

      m_pSelectedDevice = nullptr;
      m_pEngine = nullptr;
      m_flagNonClient.erase(non_client_background);
      m_flagNonClient.erase(non_client_focus_rect);

      m_pevRenderEnd = nullptr;

      m_strNewFont = pnode->font_name(e_font_sans);

      m_bFirst23 = false;
      m_eeffect                  = effect_none;

      m_bOkPending               = false;
      m_millisLastOk                 = 0;
      m_millisAnime                  = 0;
      m_millisLastFast               = 0;
      m_millisFastAnime              = 0;
      m_bFast                    = false;
      m_bFastOnEmpty             = false;
      //m_dFps = 1.0 / 60.0;
      m_dFps = 0.0;


      m_bHelloLayoutOn001Layout  = false;
      m_b001LayoutIgnoreEmpty    = false;


      m_prender                  = nullptr;


      m_prender = new render(this);

      m_prender->m_pview = this;

      m_prender->m_pmutexText = &m_mutexText;

      m_millisAnime = 2000;

      m_millisFastAnime = 584;

      m_bOkPending = true;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

      m_bFastOnEmpty = true;

      m_bFast = true;

      //m_stra23.add("http://ca2.cc/matter/app/_matter/main/_std/_std/nanosvg/23.svg");
      //m_stra23.add("http://ca2.cc/matter/app/_matter/main/_std/_std/main/rock_with_a_mask.png");



      m_ppcreutil = pcre_util::compile(get_application(), "\\:\\-\\)");

   }

   view::~view()
   {
   }

   void view::assert_valid() const
   {
      user::box::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void view::install_message_routing(::channel * pchannel)
   {

      impact_base::install_message_routing(pchannel);

      
      MESSAGE_LINK(e_message_create,pchannel,this,&view::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &view::_001OnDestroy);

   }


   void view::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;



      string strId = get_document()->m_pimpactsystem->m_strMatter;

      if (papplication->m_strAppId == "app-core/flag")
      {

         m_bilboa.add(bilbo("matter://cat.gif"));
         m_bilboa.add(bilbo("matter://nanosvg/23.svg"));
         m_bilboa.add(bilbo("matter://main/rock_with_a_mask.png"));
         m_bilboa.add(bilbo("matter://picachu_by_rondex.png"));
         m_bilboa.add(bilbo("matter://totoro_plus_plus.png"));

      }
      else if (strId == "switcher")
      {

         m_bilboa.add(bilbo("matter://cat.gif"));
         m_bilboa.add(bilbo("matter://picachu_by_rondex.png"));
         m_bilboa.add(bilbo("matter://totoro_plus_plus.png"));

      }
      else
      {

         m_bilboa.add(bilbo("matter://cat.gif"));
         m_bilboa.add(bilbo("matter://nanosvg/23.svg"));
         m_bilboa.add(bilbo("matter://main/rock_with_a_mask.png"));

      }


      string strText;

      data_get("cur_font",m_strNewFont);

      data_get("cur_text",strText);

      if(GetTypedParent<::user::split_view>() != nullptr)
      {

         if(GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != nullptr)
         {

            GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view")->_001SetText(strText,::e_source_initialize);

         }

      }

      int i = 1;

      for (auto & bilbo : m_bilboa)
      {

         data_get("bilbo." + bilbo.m_strPath, bilbo.m_bNew);

         i++;

      }




      defer_update_bilbo();


      if(papplication->m_etype == application::type_normal)
      {

         if(!m_prender->m_bLite)
         {

            papplication->load_ai_font();

         }

         m_prender->begin();

      }


      GetTypedParent<main_frame>()->m_pview = this;


      string_array straName;

      string_array straPath;

      video_capture_enum_encoders(straName, straPath);


   }

   void view::_001OnDestroy(::message::message * pmessage)
   {

      m_pevRenderEnd = new manual_reset_event(this);

      m_prender->set_finish();

      m_pevRenderEnd->wait(seconds(15));

      delete m_pevRenderEnd;

   }

   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      {

         synchronous_lock slText(&m_mutexText);

         if(m_strNewHelloMultiverse.is_empty())
         {

            if(m_bFastOnEmpty)
            {

               m_bFast = true;

            }

            return;

         }

      }

      m_prender->m_bHelloRender = true;

      if(m_bHelloLayoutOn001Layout)
      {

         m_prender->m_bNewLayout = true;

         m_bOkPending = true;

         m_bFast = true;

      }
      else
      {

         on_layout(::draw2d::graphics_pointer & pgraphics);

      }

   }


   void view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      if(eupdate == 0)
      {
         __pointer(::userex::pane_tab_view) ppaneview = GetTypedParent < ::userex::pane_tab_view >();
         //if(ppaneview.is_set())
         //{
         //   ppaneview->m_pflagview = this;
         //}

      }
      UNREFERENCED_PARAMETER(psubject);
   }

   bool view::in_anime()
   {
      if(m_bFast || m_millisLastFast.elapsed() < m_millisFastAnime)
         return true;
      if(m_millisLastOk.elapsed() < m_millisAnime)
         return true;
      return false;
   }










   ::user::document * view::get_document()
   {

      return  (::user::impact::get_document());

   }






   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if(rectangleClient.area() <= 0)
         return;

/*      m_pimage = create_image(rectangleClient->size());

      start_capture();

      if(m_prender->m_cx == rectangleClient.width()
            && m_prender->m_cy == rectangleClient.height()
            && m_strNewFont == m_strFont)
         return;


      if(m_strNewFont != m_strFont)
      {
         m_strFont = m_strNewFont;

         data_set("cur_font",m_strFont);

      }

      m_prender->m_cx = rectangleClient.width();

      m_prender->m_cy = rectangleClient.height();

      m_prender->m_rectangleClient = rectangleClient;

      m_prender->m_bNewLayout = true;

      m_bOkPending = true;

      m_bFast = true;

   }


   string view::get_processed_videocapture()
   {

      synchronous_lock slText(&m_mutexText);

      string str = get_videocapture();

      int c = m_ppcreutil->matches(str);

//      int c = pcre2_get_ovector_count(m_pmd);

      if(c > 0)
      {
         str += "Smile for you too (pcremade |-) !!";
      }


      if(::str::begins_eat_ci(str,"image:"))
      {

         string strImage = str;

         strsize iFind = strImage.find(",");

         if(iFind >= 0)
         {

            strImage = strImage.Mid(0,iFind);

         }

         if(m_strImage != strImage)
         {

            m_strImage = strImage;


            ::fork(get_application(),[=]()
            {


               if(::str::ends_ci(strImage,".png"))
               {
               }
               else if(::str::ends_ci(strImage,".jpg"))
               {
               }
               else
               {
                  sleep(900_ms);
               }

               if(m_strImage != strImage)
                  return;


               get_document()->on_open_document(m_strImage);
               //   ::payload varFile;
               //
               //   varFile["url"] = strImage;
               //
               //   varFile["http_set"]["raw_http"] = purl->get_server(m_strImage).find_wci("ca2") < 0;
               //
               //   ::image_pointer pimage;
               //
               //   if(pimage->load_from_file(varFile))
               //   {
               //
               //      if(strImage == m_strImage)
               //      {

               //         *m_prender->m_pimageImage = * pimage;
               //      }

               //   }

            });

         }


         if(m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
         {

            if(::str::begins_eat_ci(str,m_strImage))
            {
               ::str::begins_eat_ci(str,",");
            }

         }

      }

      if(::str::begins_eat_ci(str, "crt:"))
      {

         m_eeffect = effect_crt;

      }
      else
      {

         m_eeffect = effect_none;

      }

      return str;

   }


   string view::get_videocapture()
   {

      synchronous_lock synchronouslock(&m_mutexText);

      if(m_strHelloMultiverse != m_strNewHelloMultiverse)
      {

         m_strHelloMultiverse = m_strNewHelloMultiverse;

      }

      if(m_strHelloMultiverse.is_empty())
      {

         if(m_prender->m_bAlternate)
         {

            if(m_dFps != 0.0)
            {
               return "Rolling " + papplication->m_strAlternateHelloMultiverse;
            }
            else
            {
               return papplication->m_strAlternateHelloMultiverse;
            }


         }
         else
         {

            if(m_dFps != 0.0)
            {
               return "Rolling " + papplication->m_strHelloMultiverse;
            }
            else
            {
               return papplication->m_strHelloMultiverse;
            }


         }

      }
      else
      {

         return m_strHelloMultiverse;

      }

   }


   void view::defer_check_on_draw_layout()
   {

      if (m_prender != nullptr)
      {

         synchronous_lock synchronouslock(&m_mutexText);

         if (get_processed_videocapture() != m_prender->m_strHelloMultiverse)
         {

            m_prender->m_strHelloMultiverse = get_processed_videocapture().c_str(); // rationale : string allocation fork *for parallelization*

            synchronouslock.unlock();

            set_need_layout();

         }

      }

   }


   void view::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_prender->m_bImageEnable && m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
         //if(m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
      {

         //m_bFirstDone = true;

         ::rectangle_i32 rectWork(0, 0, m_prender->m_pimageWork->get_size()->cx, m_prender->m_pimageWork->get_size()->cy);
         ::rectangle_i32 rectImage(0, 0, m_prender->m_pimageImage->get_size()->cx, m_prender->m_pimageImage->get_size()->cy);

         rectImage.FitOnCenterOf(rectWork);

         m_pimagePost->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         m_pimagePost->get_graphics()->StretchBlt(rectImage.left, rectImage->top, rectImage->width(), rectImage->height(),
/*                                                m_prender->m_pimagepimage->g(), 0, 0,
                                                m_prender->m_pimageImage->get_size()->cx,
                                                m_prender->m_pimageImage->get_size()->cy);


      }

   }

   void view::defer_update_bilbo()
   {

      synchronous_lock synchronouslock(mutex());

      for (auto & bilbo : m_bilboa)
      {

         if (bilbo.m_bNew && !bilbo.m_b)
         {

            m_stra23.add_unique(bilbo.m_strPath);

            bilbo.m_b = true;

            data_set("bilbo." + bilbo.m_strPath, bilbo.m_b);

         }
         else if (!bilbo.m_bNew && bilbo.m_b)
         {

            m_stra23.erase(bilbo.m_strPath);

            bilbo.m_b = false;

            data_set("bilbo." + bilbo.m_strPath, bilbo.m_b);

         }

      }

   }

   HRESULT view::OnSample(
   /* [annotation][in] */
   _In_opt_  IMFSample *pSample)
   {

      if (pSample == nullptr)
      {

         return S_OK;

      }


      IMFMediaBuffer * pBuffer = nullptr;

      HRESULT hr = pSample->GetBufferByIndex(0,&pBuffer);

      if (FAILED(hr) || pBuffer == nullptr)
      {

         return S_OK;

      }

      ::u32 dwLen = 0;

      hr = pBuffer->GetCurrentLength(&dwLen);

      if (FAILED(hr) || dwLen <= 0)
      {

         pBuffer->Release();

      }
      byte * p = nullptr;
      hr = pBuffer->Lock(&p, nullptr, nullptr);
      if (FAILED(hr))
      {

         pBuffer->Release();

      }

      {
         synchronous_lock synchronouslock(mutex());

/*         if (m_pimage->is_null() || m_pimage->m_pcolorref == nullptr)
         {

            pBuffer->Unlock();

            pBuffer->Release();

            return S_OK;

         }


/*         ::memcpy_dup(m_pimage->m_pcolorref, p, minimum(m_pimage->area() * 4, dwLen));

      }

      pBuffer->Unlock();

      pBuffer->Release();



      return S_OK;

   }

   STDMETHODIMP view::QueryInterface(REFIID riid, void** ppv)
   {
      //static const QITAB qit[] =
      //{
      //   QITABENT(view, IMFCaptureEngineOnSampleCallback),
      //   { 0 }
      //};
      //return QISearch(this, qit, riid, ppv);
      return E_FAIL;
   }

   STDMETHODIMP_(ULONG) view::AddRef()
   {
      return add_ref(OBJ_REF_DBG_ARGS);
   }

   STDMETHODIMP_(ULONG) view::Release()
   {
      return release();
   }

   void view::OnCaptureEvent(wparam wparam, lparam lparam)
   {

      if (m_pEngine != nullptr)
      {

//         m_pEngine->OnCaptureEvent(wparam, lparam);

      }

   }

   bool view::start_capture()
   {

      if (m_pEngine != nullptr)
      {

         return true;

      }

      ::aura::application * papp = get_application();

      HWND hwnd = get_handle();

      //HRESULT hr = CaptureManager::CreateInstance(papp, hwnd, &m_pEngine);

      //if (FAILED(hr) || m_pEngine == nullptr)
      //{
      //   return false;
      //}

      //manual_reset_event      evReady(this);

      //evReady.ResetEvent();

      //::fork(get_application(), [&]()
      //{

      //   m_hwndPreview = CreatePreviewWindow(GetModuleHandle("app_core_videocapture.dll"), hwnd, m_pEngine);

      //   evReady.SetEvent();

      //   MSG msg;

      //   while (task_get_run() && GetMessage(&msg, nullptr, 0, 0xffffffffu))
      //   {

      //      TranslateMessage(&msg);

      //      DispatchMessage(&msg);

      //   }

      //});

      //evReady.wait();

      //hr = m_pEngine->InitializeCaptureManager(m_hwndPreview, this, m_pSelectedDevice);
      //if (FAILED(hr))
      //{
      //   //ShowError(hwnd, IDS_ERR_SET_DEVICE, hr);
      //   return false;
      //}

      //m_pEngine->StartPreview();

      return true;

   }

} // namespace videocapture


















int c_video_capture_enum_encoders(wchar_t *** pppszName, wchar_t *** pppszPath);


int video_capture_enum_encoders(string_array & straName, string_array & straPath)
{

   wchar_t ** ppszName;
   wchar_t ** ppszPath;

   int iCount = c_video_capture_enum_encoders(&ppszName, &ppszPath);

   straName.c_add(ppszName, iCount);

   straPath.c_add(ppszPath, iCount);

   return straName.get_count();

}

