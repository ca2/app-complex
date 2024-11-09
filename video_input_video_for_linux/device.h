#pragma once


#include "acme/parallelization/manual_reset_happening.h"
#include "app-complex/video_input/device.h"


namespace video_input_video_for_linux
{

	class thread;

	//class ::image::image;

	using subtype_map = string_map < ::int_array >;

	using frame_rate_map = map < huge_natural, subtype_map >;

	typedef void(*emergensyStopEventCallback)(int, void *);

   class device;

   class pixel_format;

   class frame_rate :
      virtual public ::particle
   {
   public:


      int                     m_iNumerator;
      int                     m_iDenominator;
      float                   m_fFps;

      string                  m_strDescription;


   };



   class resolution:
      virtual public ::particle
   {
   public:


      ::int_size              m_size;
      string                  m_strDescription;

      pointer_array < frame_rate >    m_frameratea;


      void _list_frame_rate(pixel_format * ppixelformat, device * pdevice);

   };


   class pixel_format :
      virtual public ::particle
   {
   public:


      int         m_iPixFmt;
      string      m_strDescription;

      pointer_array < resolution > m_resolutiona;


      void _list_resolution(device * pdevice);


   };

   class input :
      virtual public ::particle
   {
   public:


      int         m_iInput;
      string      m_strDescription;

   };

   class standard :
      virtual public ::particle
   {
   public:


      int         m_iStandard;
      string      m_strDescription;

   };

   class CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION device :
		virtual public ::video_input::device
	{

	public:



      pointer_array < input >           m_inputa;

      pointer_array < standard >        m_standarda;

      pointer_array < pixel_format >    m_pixelformata;

      int      m_iBufferedCount;


      //::collection::index m_iIndex;
      string m_strDevice;
      //string m_strId;
      int_fast32_t m_iDevice;

      int m_iInput;
      int m_iStandard;
      int m_iDvTiming;
      int m_iFrameRateNumerator;
      int m_iFrameRateDenominator;

      int m_iLineSize;
      int m_iPixelFormat;

      int m_iTimeoutFrames;

      bool m_bAutoReset;

      ::pointer<memory_map>     m_pmemorymap;

      ::pointer<mjpeg_decoder>  m_pmjpegdecoder;

      manual_reset_happening         m_happening;

		//::video_input::enum_lock					m_elock;
		//string											m_strName;

		///::pointer<image_grabber_thread>		m_pthreadImageGrabber;

		//::video_input::camera_parameters			m_cameraparametersPrevious;

		//::int_size										m_size;

		//unsigned int												m_uCurrentNumber;

		//bool												m_bSetup;

		//map < huge_natural, frame_rate_map>					m_mapCaptureFormat;

		////::array <::video_input::media_format >	m_mediaformata;

		//comptr < IMFMediaSource  >					m_pmediasource;

		//emergensyStopEventCallback					m_emergencystopcallback;

		//void * m_pUserData;
		::pointer<thread>							m_pthread;


		device(::collection::index iDevice, const ::string & strName, const ::string & strDevice, const ::string & strHardwareId);
		~device(void) override;


      void _001_list_input();
      void _002_list_standard();
      void _003_list_pixel_format();
      void _004_list_resolution();
      void _005_list_frame_rate();

      void _006_erase_resolution_with_empty_frame_rate_list();
      void _007_erase_pixel_format_with_empty_resolution_list();


		void close() override;


      int ioctl(int request, void * arg);

		//::video_input::camera_parameters get_camera_parameters() override;

		//void set_camera_parameters(::video_input::camera_parameters parameters) override;

		void set_emergency_stop_event(void(*func)(int, void *));

		//virtual long readInfoOfDevice(IMFActivate * pActivate, unsigned int Num);

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

		//virtual IMFMediaSource * get_media_source();

		::memory * get_out_memory() override;

		void enumerate_capture_formats() override;

		//virtual long setDeviceFormat(IMFMediaSource * pSource, unsigned long dwFormatIndex);

		void buildLibraryofTypes() override;

		int findType(unsigned int size, unsigned int frameRate = 0) override;

		//virtual long resetDevice(IMFActivate * pActivate);

		void initialize_device() override;

		//virtual long checkDevice(IMFAttributes * pAttributes, IMFActivate ** pDevice);

		virtual bool get_pixels(color32_t * dstBuffer, bool flipRedAndBlue = false, bool flipImage = false) override;

		virtual string get_id2() override;



      void _start_capture();

      void _stop_capture();


      void _reset_capture();

#ifdef _DEBUG
      void _query_all_buffers();

#endif


   };


} // namespace video_input_video_for_linux



