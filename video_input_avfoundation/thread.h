#pragma once


namespace video_input_video_avfoundation
{


	class callback;


	class CLASS_DECL_VIDEO_INPUT_AVFOUNDATION thread :
		virtual public ::thread
	{
	public:


		//::pointer<callback>m_pcallback;
      CFTypeRef m_ptyperefCapture;
		::pointer<device>m_pdevice;

		void * m_pUserData;

		bool m_bStop;

		::u32 m_uDevice;


      thread(device * pdevice);
		~thread() override;

		void run() override;


	};


} // namespace video_input_video_avfoundation



