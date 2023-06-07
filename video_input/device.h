#pragma once


#include "_struct.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/collection/string_map.h"


namespace video_input
{

	using subtype_map = string_map < int_array >;

	using frame_rate_map = map < ::u64, subtype_map >;

	typedef void(*emergensyStopEventCallback)(int, void *);

	enum enum_device_state
	{

	   e_device_state_initial,
	   e_device_state_start_capturing,
	   e_device_state_already_in_use_by_other_client,
	   e_device_state_capturing,
	   e_device_state_device_removed,

	};


	class CLASS_DECL_VIDEO_INPUT device :
		virtual public ::object
	{

	public:


		enum_lock									m_elock;

		string									   m_strHardwareId;

		string										m_strName;

		camera_parameters							m_cameraparametersPrevious;

		::size_i32									m_size;

		//::u32										m_uCurrentNumber;

		bool										m_bSetup;

		map < u64, frame_rate_map>					m_mapCaptureFormat;

		pointer_array < media_format > 			m_mediaformata;

		emergensyStopEventCallback					m_emergencystopcallback;

		::pointer<::video_input::render>		m_prender;

		::pointer<::video_input::video_input>  	m_pvideoinput;

		enum_device_state							m_edevicestate;


		device(void);
		~device(void) override;

		virtual void close();

		virtual camera_parameters get_camera_parameters();

		virtual void set_camera_parameters(camera_parameters parameters);

		virtual string get_name();

		

		virtual ::u32 get_width();

		virtual ::u32 get_height();

		virtual ::size_i32 get_size();

		virtual ::pointer<media_format>get_media_format(::index i);

		virtual ::count get_media_format_count();

		virtual ::index find_argb_32_format();

		virtual ::index find_format(::u32 w, ::u32 h, ::u32 idealFramerate = 0);

		virtual void set_format(::index iIndex);

		virtual bool is_setup();

		virtual bool is_media_source();

		virtual bool is_raw_data_source();

		virtual void start_capturing();

		virtual void stop_capturing();

		virtual ::memory * get_out_memory();

		virtual render * get_render();

		virtual void create_render();

		virtual void enumerate_capture_formats();

		virtual void buildLibraryofTypes();

		virtual int findType(::u32 size, ::u32 frameRate = 0);

		virtual void initialize_device();

		virtual bool get_pixels(color32_t * dstBuffer, bool flipRedAndBlue = false, bool flipImage = false);

		virtual string get_id2();


	};


} // namespace video_input



