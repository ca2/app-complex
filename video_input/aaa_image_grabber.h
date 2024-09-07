#pragma once


namespace video_input
{

	//class ::image::image;

	// Class for grabbing ::image::image from video stream
	class image_grabber : public IMFSampleGrabberSinkCallback
	{
	public:



		virtual ~image_grabber(void);

		// IUnknown methods
		STDMETHODIMP QueryInterface(REFIID iid, void ** ppv);
		STDMETHODIMP_(ULONG) AddRef();
		STDMETHODIMP_(ULONG) Release();


		HRESULT initImageGrabber(IMFMediaSource * pSource, GUID VideoFormat);

		HRESULT startGrabbing(void);

		void stopGrabbing();

		::memory * get_memory();

		// Function of creation of the instance of the class
		static HRESULT CreateInstance(image_grabber ** ppIG, ::u32 deviceID);

	private:

		bool m_bClose;

		long m_cRef;

		::u32 m_uDevice;

		comptr < IMFMediaSource > m_pmediasource;

		comptr < IMFMediaSession>  m_pmediasession;

		comptr < IMFTopology > m_ptopology;

		::memory * m_pmemoryOut;

		::memory m_memorya[2];

		int	m_iMemory;




		image_grabber(::u32 deviceID);

		HRESULT CreateTopology(IMFMediaSource * pSource, IMFActivate * pSinkActivate, IMFTopology ** ppTopo);

		HRESULT AddSourceNode(
			IMFTopology * pTopology,
			IMFMediaSource * pSource,
			IMFPresentationDescriptor * ppresentationdescriptor,
			IMFStreamDescriptor * pstreamdescriptor,
			IMFTopologyNode ** ppNode);

		HRESULT AddOutputNode(
			IMFTopology * pTopology,
			IMFActivate * pActivate,
			DWORD dwId,
			IMFTopologyNode ** ppNode);


		// IMFClockStateSink methods
		STDMETHODIMP OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset);
		STDMETHODIMP OnClockStop(MFTIME hnsSystemTime);
		STDMETHODIMP OnClockPause(MFTIME hnsSystemTime);
		STDMETHODIMP OnClockRestart(MFTIME hnsSystemTime);
		STDMETHODIMP OnClockSetRate(MFTIME hnsSystemTime, float flRate);

		// IMFSampleGrabberSinkCallback methods
		STDMETHODIMP OnSetPresentationClock(IMFPresentationClock * pClock);
		STDMETHODIMP OnProcessSample(REFGUID guidMajorMediaType, DWORD dwSampleFlags,
			LONGLONG llSampleTime, LONGLONG llSampleDuration, const BYTE * pSampleBuffer,
			DWORD dwSampleSize);
		STDMETHODIMP OnShutdown();


	};


} // namespace video_input



