#pragma once

//#include <mfidl.h>


//struct IMFMediaSource;


//namespace video_input_video_avfoundation
//{


	class avcapture_device_callback
	{
	public:

		

		virtual void avcapture_device_on_frame(const void * pdata, int width, int height, int scan) = 0;

		


	};

//
//} // namespace video_input_video_avfoundation



