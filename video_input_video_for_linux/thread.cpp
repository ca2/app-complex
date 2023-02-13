// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "thread.h"
#include "callback.h"
#include "device.h"


namespace video_input_video_for_linux
{


   thread::thread(device * pdevice)
	{

		m_pdevice = pdevice;

	}


	thread::~thread(void)
	{

	}


	void thread::run()
	{

		m_pcallback = __new(callback(m_pdevice, m_uDevice));

      m_pcallback->initialize(this);

		m_pcallback->start_capturing();

	}

	
} // namespace video_input_video_for_linux



