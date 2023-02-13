#pragma once


#include "apex/parallelization/thread.h"
#include "device.h"

struct IMFMediaSource;


namespace video_input_media_foundation
{


	class callback;


	class CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION thread :
		virtual public ::thread
	{
	public:


		HRESULT m_hresult;

		comptr < callback > m_pcallback;

		::pointer<device>m_pdevice;

		emergensyStopEventCallback igt_func;

		void * m_pUserData;

		bool m_bStop;

		

		thread(device * pdevice);
		~thread() override;


		HRESULT __create_instance();


		callback * get_callback();

		void run() override;

	};


} // namespace video_input_media_foundation



