#pragma once



namespace video_input
{


	class image_grabber;


	typedef void(*emergensyStopEventCallback)(int, void *);


	/// Class for controlling of thread of the grabbing raw data from video device
	class image_grabber_thread :
		virtual public ::thread
	{
		//friend DWORD WINAPI MainThreadFunction(LPVOID lpParam);

	public:

		HRESULT m_hresult;

		comptr < image_grabber > m_pimagegrabber;

		comptr < IMFMediaSource > m_psource;

		emergensyStopEventCallback igt_func;

		void * m_pUserData;

		bool m_bStop;

		::u32 m_uDevice;
		image_grabber_thread(IMFMediaSource * pSource, ::u32 deviceID, void(*func)(int, void *));

		virtual ~image_grabber_thread();

		static HRESULT CreateInstance(image_grabber_thread ** ppIGT, IMFMediaSource * pSource, ::u32 deviceID, void(*func)(int, void *));

		HRESULT __create_instance();

		void start();

		void stop();

		void set_emergency_stop_event(void(*func)(int, void *));

		image_grabber * get_image_grabber();

		//HANDLE getMutexHandle();

	//protected:

		virtual void init_thread() override;
		virtual void run() override;

	//private:


		//HANDLE m_handle;

		//HANDLE m_hMutex;

		///DWORD   m_dwThreadIdArray;


	};


} // namespace video_input



