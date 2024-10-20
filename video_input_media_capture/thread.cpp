// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "thread.h"
#include "callback.h"
#include "app-complex/video_input/media_format.h"


namespace video_input_media_capture
{


	thread::thread(device * pdevice)
	{

		///m_pdevice = pdevice;

	}


	thread::~thread(void)
	{

	}


	void thread::run()
	{

		//::CoInitialize(NULL);

		//m_pcallback = ___new callback(m_pdevice);

		////m_pcallback->_initialize_callback(MFVideoFormat_RGB32);
		//m_pcallback->_initialize_callback(MFVideoFormat_RGB32);

		//m_pcallback->_capture_loop();

	}

	
} // namespace video_input_media_capture



