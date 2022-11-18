#pragma once


#include "apex/platform/app_consumer.h"
#include "base/user/user/impact.h"


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE impact :
      virtual public app_consumer < application, ::user::impact >
   {
   public:


      ::pointer<::video_input::render>   m_prender;


      impact();
      ~impact() override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      
      
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }

      void install_message_routing(::channel * pchannel) override;


      void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      
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




