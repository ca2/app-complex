#pragma once


#include "app-complex/video_input/device.h"


struct IMFActivate;

struct IMFMediaSource;

struct IMFMediaType;

namespace video_input_media_foundation
{

	class thread;

	//class ::image::image;

	using subtype_map = string_map < ::int_array >;

	using frame_rate_map = map < unsigned long long, subtype_map >;

	typedef void(*emergensyStopEventCallback)(int, void *);


	class CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION device :
		virtual public ::video_input::device
	{
	public:


		//::video_input::enum_lock					m_elock;
		//string											m_strName;

		///::pointer<image_grabber_thread>		m_pthreadImageGrabber;

		//::video_input::camera_parameters			m_cameraparametersPrevious;

		//::int_size										m_size;

		//unsigned int												m_uCurrentNumber;

		//bool												m_bSetup;

		//map < unsigned long long, frame_rate_map>					m_mapCaptureFormat;

		////::array <::video_input::media_format >	m_mediaformata;

		comptr < IMFMediaSource  >					m_pmediasource;
		comptr < IMFActivate  >						m_pactivate;

		//emergensyStopEventCallback					m_emergencystopcallback;

		//void * m_pUserData;
		::pointer<thread>							m_pthread;


		device(void);
		~device(void) override;

		void close() override;

		::video_input::camera_parameters get_camera_parameters() override;

		void set_camera_parameters(::video_input::camera_parameters parameters) override;

		void set_emergency_stop_event(void(*func)(int, void *));

		//virtual long readInfoOfDevice(IMFActivate * pActivate);

		string get_name() override;

		//int get_format_count() override;

		unsigned int get_width() override;

		unsigned int get_height() override;

		::int_size get_size() override;

		//::video_input::media_format get_format(::collection::index iIndex) override;

		//::collection::index find_format(unsigned int w, unsigned int h, unsigned int idealFramerate = 0) override;

		void set_format(::collection::index iIndex) override;

		bool is_setup() override;

		bool is_media_source() override;

		bool is_raw_data_source() override;

		void start_capturing() override;

		void stop_capturing() override;

		virtual IMFMediaSource * get_media_source();

		::memory * get_out_memory() override;

		void enumerate_capture_formats() override;

		virtual void _set_device_format(unsigned long dwFormatIndex);

		void buildLibraryofTypes() override;

		int findType(unsigned int size, unsigned int frameRate = 0) override;

		virtual void _set_device(IMFActivate * pActivate);

		void initialize_device() override;

		//virtual long checkDevice(IMFAttributes * pAttributes, IMFActivate ** pDevice);

		virtual bool get_pixels(color32_t * dstBuffer, bool flipRedAndBlue = false, bool flipImage = false) override;

		virtual string get_id2() override;

	};


} // namespace video_input_media_foundation



