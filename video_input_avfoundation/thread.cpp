// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"


CFTypeRef avdevice_capture_create(CFTypeRef typerefAVCaptureDevice, int w, int h, avcapture_device_callback * pcallback);

void avdevice_capture_run(CFTypeRef typerefCapture);

void avdevice_capture_stop(CFTypeRef typerefCapture);

namespace video_input_video_avfoundation
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

      m_ptyperefCapture = avdevice_capture_create(m_pdevice->m_ptyperefAVCaptureDevice,
                            m_pdevice->m_size.cx, m_pdevice->m_size.cy, m_pdevice);
      

      avdevice_capture_run(m_ptyperefCapture);
      
      
	}

	
} // namespace video_input_video_avfoundation



