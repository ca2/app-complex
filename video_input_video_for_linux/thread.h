#pragma once


#include "apex/parallelization/thread.h"


namespace video_input_video_for_linux
{


	class callback;


	class CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION thread :
		virtual public ::thread
	{
	public:


		::pointer<callback> m_pcallback;

		::pointer<device> m_pdevice;

		void * m_pUserData;

		bool m_bStop;

		unsigned int m_uDevice;


      thread(device * pdevice);
		~thread() override;

		void run() override;


	};


} // namespace video_input_video_for_linux



