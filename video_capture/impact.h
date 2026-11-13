#pragma once
#include <atomic>
#include <chrono>


#include "apex/platform/app_consumer.h"
#include "berg/user/user/impact.h"
#include "aura/user/menu/track_popup.h"


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE impact :
      virtual public app_consumer < application, ::user::impact >
   {
   public:


      ::pointer<::video_input::render>   m_prender;


      ::string m_strPreviewGeometry;
      ::pointer<::menu::track_popup> m_ptrackpopupContextMenu;
      bool m_bShowStats = false;
      bool m_bStatsWereVisible = false;
      bool m_bEnableNativeSizeToggle = false;
      std::atomic<bool> m_bNativeSize{false};
      std::chrono::steady_clock::time_point m_timePreviewWindow = std::chrono::steady_clock::now();
      std::chrono::steady_clock::time_point m_timePreviewError{};
      ::u64 m_uPreviewFrames = 0;
      ::u64 m_uPreviewPaints = 0;
      ::u64 m_uLastPreviewFrame = 0;
      double m_dPreviewFps = 0.0;
      double m_dDrawMilliseconds = 0.0;
      double m_dDrawTotalMilliseconds = 0.0;
      ::string m_strGeometryTrace;
      void trace_view_geometry();
      bool on_click(::item * pitem, ::user::mouse * pmouse) override;

      impact();
      ~impact() override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      ::i64 increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }
      
      
      ::i64 decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }

      void install_message_routing(::channel * pchannel) override;


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      ::user::document * get_document();

      void on_layout(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      void _001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;
      
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      DECLARE_MESSAGE_HANDLER(on_toggle_show_stats);
      DECLARE_MESSAGE_HANDLER(on_update_show_stats);

      virtual void defer_check_on_draw_layout();
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pdraw2dgraphics);

      // IUnknown
      //STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
      //STDMETHODIMP_(ULONG) AddRef();
      //STDMETHODIMP_(ULONG) Release();
      //virtual HRESULT STDMETHODCALLTYPE OnSample(
      ///* [annotation][in] */
      //_In_opt_  IMFSample *pSample) override;
   };


} // namespace app_complex_video_capture




