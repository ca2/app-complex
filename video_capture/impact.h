#pragma once

//#include <mfcaptureengine.h>
//class CaptureManager;

namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE impact :
      virtual public application_consumer < application, ::user::impact >
   {
   public:



      __pointer(::video_input::render)    m_prender;



      impact();
      ~impact() override;

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }

      void install_message_routing(::channel * pchannel) override;


      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      virtual bool start_capture();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      //virtual void OnCaptureEvent(wparam wparam, lparam lparam);
      
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

            virtual void defer_check_on_draw_layout();
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pgraphics);

      // IUnknown
      //STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
      //STDMETHODIMP_(ULONG) AddRef();
      //STDMETHODIMP_(ULONG) Release();
      //virtual HRESULT STDMETHODCALLTYPE OnSample(
      ///* [annotation][in] */
      //_In_opt_  IMFSample *pSample) override;
   };


} // namespace app_complex_video_capture





















