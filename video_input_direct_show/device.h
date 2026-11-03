#pragma once
#include "app-complex/video_input/device.h"
#include <dshow.h>
#include <dvdmedia.h>
#include <vector>
namespace video_input_direct_show
{
   MIDL_INTERFACE("6B652FFF-11FE-4FCE-92AD-0266B5D7C78F") sample_grabber : public IUnknown
   {
      virtual HRESULT STDMETHODCALLTYPE SetOneShot(BOOL) = 0;
      virtual HRESULT STDMETHODCALLTYPE SetMediaType(const AM_MEDIA_TYPE *) = 0;
      virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType(AM_MEDIA_TYPE *) = 0;
      virtual HRESULT STDMETHODCALLTYPE SetBufferSamples(BOOL) = 0;
      virtual HRESULT STDMETHODCALLTYPE GetCurrentBuffer(long *, long *) = 0;
      virtual HRESULT STDMETHODCALLTYPE GetCurrentSample(IMediaSample **) = 0;
      virtual HRESULT STDMETHODCALLTYPE SetCallback(IUnknown *, long) = 0;
   };
   class CLASS_DECL_VIDEO_INPUT_DIRECT_SHOW device : virtual public ::video_input::device
   {
   public:
      comptr<IMoniker> m_pmoniker;
      comptr<IGraphBuilder> m_pgraph;
      comptr<ICaptureGraphBuilder2> m_pbuilder;
      comptr<IBaseFilter> m_psource;
      comptr<IBaseFilter> m_pgrabberfilter;
      comptr<IBaseFilter> m_pnullrenderer;
      comptr<sample_grabber> m_pgrabber;
      comptr<IAMStreamConfig> m_pconfig;
      comptr<IMediaControl> m_pcontrol;
      std::vector<int> m_formatindices;
      std::vector<unsigned char> m_pixels;
      long m_lConnectedHeight = 0;
      device();
      ~device() override;
      void _set_device(IMoniker * pmoniker);
      void initialize_device() override;
      void enumerate_capture_formats() override;
      ::collection::index find_argb_32_format() override;
      void set_format(::collection::index i) override;
      void start_capturing() override;
      void stop_capturing() override;
      void close() override;
      string get_name() override { return m_strName; }
      string get_id2() override { return m_strHardwareId; }
      ::u32 get_width() override { return m_size.cx; }
      ::u32 get_height() override { return m_size.cy; }
      ::i32_size get_size() override { return m_size; }
      bool is_setup() override { return m_bSetup; }
      bool is_media_source() override { return false; }
      bool is_raw_data_source() override { return true; }
   };
}


// Previous Media Foundation implementation retained for migration reference.
// #pragma once
// 
// 
// #include "app-complex/video_input/device.h"
// 
// 
// struct IMFActivate;
// 
// struct IMFMediaSource;
// 
// struct IMFMediaType;
// 
// namespace video_input_direct_show
// {
// 
// 	class thread;
// 
// 	//class ::image::image;
// 
// 	using subtype_map = string_map_base < ::i32_array_base >;
// 
// 	using frame_rate_map = map_base < ::u64, subtype_map >;
// 
// 	typedef void(*emergensyStopEventCallback)(int, void *);
// 
// 
// 	class CLASS_DECL_VIDEO_INPUT_DIRECT_SHOW device :
// 		virtual public ::video_input::device
// 	{
// 	public:
// 
// 
// 		//::video_input::enum_lock					m_elock;
// 		//string											m_strName;
// 
// 		///::pointer<image_grabber_thread>		m_pthreadImageGrabber;
// 
// 		//::video_input::camera_parameters			m_cameraparametersPrevious;
// 
// 		//::i32_size										m_size;
// 
// 		//::u32												m_uCurrentNumber;
// 
// 		//bool												m_bSetup;
// 
// 		//map_base < ::u64, frame_rate_map>					m_mapCaptureFormat;
// 
// 		////::array <::video_input::media_format >	m_mediaformata;
// 
// 		comptr < IMFMediaSource  >					m_pmediasource;
// 		comptr < IMFActivate  >						m_pactivate;
// 
// 		//emergensyStopEventCallback					m_emergencystopcallback;
// 
// 		//void * m_pUserData;
// 		::pointer<thread>							m_pthread;
// 
// 
// 		device(void);
// 		~device(void) override;
// 
// 		void close() override;
// 
// 		::video_input::camera_parameters get_camera_parameters() override;
// 
// 		void set_camera_parameters(::video_input::camera_parameters parameters) override;
// 
// 		void set_emergency_stop_event(void(*func)(int, void *));
// 
// 		//virtual long readInfoOfDevice(IMFActivate * pActivate);
// 
// 		string get_name() override;
// 
// 		//int get_format_count() override;
// 
// 		::u32 get_width() override;
// 
// 		::u32 get_height() override;
// 
// 		::i32_size get_size() override;
// 
// 		//::video_input::media_format get_format(::collection::index iIndex) override;
// 
// 		//::collection::index find_format(::u32 w, ::u32 h, ::u32 idealFramerate = 0) override;
// 
// 		::collection::index find_argb_32_format() override;
// 
//       void set_format(::collection::index iIndex) override;
// 
// 		bool is_setup() override;
// 
// 		bool is_media_source() override;
// 
// 		bool is_raw_data_source() override;
// 
// 		void start_capturing() override;
// 
// 		void stop_capturing() override;
// 
// 		virtual IMFMediaSource * get_media_source();
// 
// 		::memory * get_out_memory() override;
// 
// 		void enumerate_capture_formats() override;
// 
// 		virtual void _set_device_format(unsigned long dwFormatIndex);
// 
// 		void buildLibraryofTypes() override;
// 
// 		int findType(::u32 size, ::u32 frameRate = 0) override;
// 
// 		virtual void _set_device(IMFActivate * pActivate);
// 
// 		void initialize_device() override;
// 
// 		//virtual long checkDevice(IMFAttributes * pAttributes, IMFActivate ** pDevice);
// 
// 		virtual bool get_pixels(color32_t * dstBuffer, bool flipRedAndBlue = false, bool flipImage = false) override;
// 
// 		virtual string get_id2() override;
// 
// 	};
// 
// 
// } // namespace video_input_direct_show
// 
// 
// 
