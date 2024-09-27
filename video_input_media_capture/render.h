// Created on 2021-07-07 by camilo 14:11 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "app-complex/video_input/render.h"
#include "acme/prototype/prototype/memory.h"
#include <winrt/windows.media.capture.frames.h>
extern "C"
{

#include <libswscale/swscale.h>
#include <libavutil/frame.h>

} // extern "C"


//class CaptureManager;


namespace video_input_media_capture
{


   class CLASS_DECL_VIDEO_INPUT_MEDIA_CAPTURE render :
      virtual public ::video_input::render
      //,      public IMFCaptureEngineOnSampleCallback
   {
   public:

      ::pointer<device>      m_pdevice;

      ::memory             m_memory;

      ::winrt::Windows::Media::Capture::Frames::MediaFrameReader              m_mediaframereader = nullptr;

      SwsContext * m_pswscontext;
      //IMFActivate*            m_pSelectedDevice;

      //CaptureManager *        m_pEngine;
      uint8_t * m_data[AV_NUM_DATA_POINTERS];
      int  m_linesize[AV_NUM_DATA_POINTERS];

      render();
      ~render() override;


      void initialize_video_input_render(::video_input::device * pdevice) override;

      void prepare_image() override;
      // void assert_ok() const override;
      //void dump(dump_context& dumpcontext) const;

#ifdef _DEBUG

      virtual i64 increment_reference_count()
      {
         return ::object::increment_reference_count();
      }
      virtual i64 decrement_reference_count()
      {
         return ::object::decrement_reference_count();
      }

#endif


      void OnFrameArrived(::winrt::Windows::Media::Capture::Frames::MediaFrameReader framereader, ::winrt::Windows::Media::Capture::Frames::MediaFrameArrivedEventArgs args);



      //virtual void install_message_routing(::channel* pchannel);


      void handle(::topic * ptopic, ::context * pcontext) override;

      //::user::document* get_document();

      bool start_capture() override;
      void on_set_format();
      //virtual void on_layout(::draw2d::graphics_pointer& pgraphics);

      //virtual void defer_update_bilbo();

      virtual void OnCaptureEvent(wparam wparam, lparam lparam);

      void on_create()override;
      void destroy() override;

      //virtual string get_videocapture();

      //virtual string get_processed_videocapture();

      //virtual bool in_anime();


      //virtual void defer_check_on_draw_layout();
      //virtual void on_draw_image_layer(::draw2d::graphics_pointer& pgraphics);

      // IUnknown
      //STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
      //STDMETHODIMP_(ULONG) AddRef();
      //STDMETHODIMP_(ULONG) Release();
      //virtual HRESULT STDMETHODCALLTYPE OnSample(
      ///* [annotation][in] */
      //_In_opt_  IMFSample *pSample) override;
   };


} // namespace video_capture





















