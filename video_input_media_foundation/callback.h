#pragma once


#include "acme/primitive/primitive/memory.h"
#include "acme_windows_common/comptr.h"
#include <mfidl.h>


struct IMFMediaSource;


namespace video_input_media_foundation
{


	class CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION callback :
		public IMFSampleGrabberSinkCallback2
	{
	public:

		bool m_bStopCapturing;
		bool m_bLoop;
		bool m_bClose;

		long m_cRef;

		comptr < IMFMediaSession>  m_pmediasession;

		comptr < IMFTopology > m_ptopology;

		::pointer<device>m_pdevice;

		::memory * m_pmemoryOut;

		::memory m_memorya[2];

		int	m_iMemory;

		callback(device * pdevice);
		virtual ~callback(void);


		::memory * get_memory();


		void _initialize_callback(GUID VideoFormat);

		void _capture_loop();

		void _start_capturing();

		void _stop_capturing();

		void _create_topology();

		void _add_source_node(
			IMFPresentationDescriptor * ppresentationdescriptor,
			IMFStreamDescriptor * pstreamdescriptor,
			comptr < IMFTopologyNode > & pnode);

		void _add_output_node(
			DWORD dwId,
			comptr < IMFTopologyNode > & pnode);

		// BEGIN IMFSampleGrabberSinkCallback2 methods
		STDMETHODIMP OnProcessSampleEx(
			/* [in] */ REFGUID guidMajorMediaType,
			/* [in] */ DWORD dwSampleFlags,
			/* [in] */ LONGLONG llSampleTime,
			/* [in] */ LONGLONG llSampleDuration,
			/* [annotation][in] */
			_In_reads_bytes_(dwSampleSize)  const BYTE * pSampleBuffer,
			/* [in] */ DWORD dwSampleSize,
			/* [annotation][in] */
			_In_  IMFAttributes * pAttributes);
		// END IMFSampleGrabberSinkCallback2

		// BEGIN IMFSampleGrabberSinkCallback methods
		STDMETHODIMP OnSetPresentationClock(IMFPresentationClock * pClock);
		STDMETHODIMP OnProcessSample(REFGUID guidMajorMediaType, DWORD dwSampleFlags,
			LONGLONG llSampleTime, LONGLONG llSampleDuration, const BYTE * pSampleBuffer,
			DWORD dwSampleSize);
		STDMETHODIMP OnShutdown();
		// END IMFSampleGrabberSinkCallback methods


		// BEGIN IMFClockStateSink methods
		STDMETHODIMP OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset);
		STDMETHODIMP OnClockStop(MFTIME hnsSystemTime);
		STDMETHODIMP OnClockPause(MFTIME hnsSystemTime);
		STDMETHODIMP OnClockRestart(MFTIME hnsSystemTime);
		STDMETHODIMP OnClockSetRate(MFTIME hnsSystemTime, float flRate);
		// END IMFClockStateSink methods


		// BEGIN IUnknown methods
		STDMETHODIMP QueryInterface(REFIID iid, void ** ppv);
		STDMETHODIMP_(ULONG) AddRef();
		STDMETHODIMP_(ULONG) Release();
		// END IUnknown methods

	};


} // namespace video_input_media_foundation



