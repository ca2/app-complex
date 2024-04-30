#pragma once


#include "app-complex/video_input/device.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/primitive/collection/string_map.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "avcapture_device_callback.h"

//struct IMFActivate;
//
//struct IMFMediaSource;
//
//struct IMFMediaType;

namespace video_input_video_avfoundation
{

	class thread;

	//class ::image;

	using subtype_map = string_map < ::i32_array >;

	using frame_rate_map = map < ::u64, subtype_map >;

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


      ::size_i32              m_size;
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

   class CLASS_DECL_VIDEO_INPUT_AVFOUNDATION device :
		virtual public ::video_input::device,
      virtual public ::avcapture_device_callback
	{

	public:


      CFTypeRef         m_ptyperefAVCaptureDevice;

      pointer_array < input >           m_inputa;

      pointer_array < standard >        m_standarda;

      pointer_array < pixel_format >    m_pixelformata;

      int      m_iBufferedCount;


      ::raw::index m_iIndex;
      string m_strDevice;
      //string m_strId;
      int_fast32_t m_iDevice;

      int m_iInput;
      int m_iStandard;
      int m_iDvTiming;
      int m_iFrameRateNumerator;
      int m_iFrameRateDenominator;

      int m_iLineSize;
      int m_iPixFmt;

      int m_iTimeoutFrames;

      bool m_bAutoReset;

      manual_reset_event         m_event;

		::pointer<thread>							m_pthread;


		device(::raw::index iDevice, const ::string & strName, const ::string & strDevice, const ::string & strHardwareId);
		~device(void) override;


      void _001_list_input();
      void _002_list_standard();
      void _003_list_pixel_format();
      void _004_list_resolution();
      void _005_list_frame_rate();

      void _006_erase_resolution_with_empty_frame_rate_list();
      void _007_erase_pixel_format_with_empty_resolution_list();


		void close() override;


      //int ioctl(int request, void * arg);

		//::video_input::camera_parameters get_camera_parameters() override;

		//void set_camera_parameters(::video_input::camera_parameters parameters) override;

		void set_emergency_stop_event(void(*func)(int, void *));

		//virtual long readInfoOfDevice(IMFActivate * pActivate, ::u32 Num);

		string get_name() override;

		//int get_format_count() override;

		::u32 get_width() override;

		::u32 get_height() override;

		::size_i32 get_size() override;

		//::video_input::media_format get_format(::raw::index iIndex) override;

		//::raw::index find_format(::u32 w, ::u32 h, ::u32 idealFramerate = 0) override;

		void set_format(::raw::index iIndex) override;

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

		int findType(::u32 size, ::u32 frameRate = 0) override;

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

       void avcapture_device_on_frame(const void * pdata, int width, int height, int scan) override;

   };


} // namespace video_input_video_avfoundation



