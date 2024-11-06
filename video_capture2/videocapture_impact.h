#pragma once

//#include <mfcaptureengine.h>
//class CaptureManager;

namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE impact :
      virtual public impact_base
   {
   public:



      ::pointer<::video_input::render>   m_prender;



      impact();
      virtual ~impact();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual huge_integer increment_reference_count()
      {
         return ::object::increment_reference_count();
      }
      virtual huge_integer decrement_reference_count()
      {
         return ::object::decrement_reference_count();
      }

      void install_message_routing(::channel * pchannel) override;


      void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      virtual bool start_capture();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      //virtual void defer_update_bilbo();

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





















