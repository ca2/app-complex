#pragma once

#include <mfcaptureengine.h>
class CaptureManager;

namespace videocapture
{


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE view :
      virtual public impact_base,
      public IMFCaptureEngineOnSampleCallback
   {
   public:

      class bilbo
      {
      public:

         string         m_strPath;
         bool           m_b;
         bool           m_bNew;

         bilbo();
         bilbo(string strPath);
         ~bilbo();

      };

      IMFActivate*            m_pSelectedDevice;

      CaptureManager *        m_pEngine;
      string                  m_strServer;
/*      ::image_pointer        m_pimage;

      string                  m_strImage;
      string_array                 m_stra23;
      bool                    m_b23;
      u32                m_uiCurrent23;
      string                  m_strCurrent23;
      string                  m_strLast23;
      bool                    m_bFirst23;
      ::u32                   m_dw23;



      bool                    m_bOkPending;
      millis m_millisLastOk;
      millis                   m_millisAnime;
      millis m_millisLastFast;
      ::u32                   m_millisFastAnime;
      bool                    m_bFast;
      bool                    m_bFastOnEmpty;


      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;


      render *                m_prender;

      manual_reset_event *    m_pevRenderEnd;

      HWND                    m_hwndPreview;



      array < bilbo >         m_bilboa;


      view(::object * pobject);
      virtual ~view();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }

      virtual void install_message_routing(::channel * pchannel);


      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      ::user::document * get_document();

      virtual bool start_capture();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      virtual void defer_update_bilbo();

      virtual void OnCaptureEvent(wparam wparam, lparam lparam);
      
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnDestroy);

      virtual string get_videocapture();

      virtual string get_processed_videocapture();

      virtual bool in_anime();


      virtual void defer_check_on_draw_layout();
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pgraphics);

      // IUnknown
      STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
      STDMETHODIMP_(ULONG) AddRef();
      STDMETHODIMP_(ULONG) Release();
      virtual HRESULT STDMETHODCALLTYPE OnSample(
      /* [annotation][in] */
      _In_opt_  IMFSample *pSample) override;
   };


} // namespace videocapture





















