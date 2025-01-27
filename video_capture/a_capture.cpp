// THIS CODE AND log_information( IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#include "framework.h"
//#include "capture.h"

IMFDXGIDeviceManager* g_pDXGIMan = nullptr;
ID3D11Device*         g_pDX11Device = nullptr;
unsigned int                  g_ResetToken = 0;

STDMETHODIMP CaptureManager::CaptureEngineCB::QueryInterface(REFIID riid, void** ppv)
{
   static const QITAB qit[] =
   {
      QITABENT(CaptureEngineCB, IMFCaptureEngineOnHappeningCallback),
      { 0 }
   };
   return QISearch(this, qit, riid, ppv);
}

STDMETHODIMP_(ULONG) CaptureManager::CaptureEngineCB::AddRef()
{
   return increment_reference_count();
}

STDMETHODIMP_(ULONG) CaptureManager::CaptureEngineCB::Release()
{
   return release();
}

// Callback method to receive happenings from the capture engine.
STDMETHODIMP CaptureManager::CaptureEngineCB::OnHappening(_In_ IMFMediaEvent* pEvent)
{
   // Post a message to the application window, so the happening is handled 
   // on the application's main thread. 

   if (m_fSleeping && m_pManager != nullptr)
   {
      // We're about to fall asleep, that means we've just asked the CE to stop the thumbnail
      // and record.  We need to handle it here since our message pump may be gone.
      GUID    guidType;
      HRESULT hrStatus;
      HRESULT hr = pEvent->GetStatus(&hrStatus);
      if (FAILED(hr))
      {
         hrStatus = hr;
      }

      hr = pEvent->GetExtendedType(&guidType);
      if (SUCCEEDED(hr))
      {
         if (guidType == MF_CAPTURE_ENGINE_PREVIEW_STOPPED)
         {
            m_pManager->OnThumbnailStopped(hrStatus);
            SetEvent(m_pManager->m_hEvent);
         }
         else if (guidType == MF_CAPTURE_ENGINE_RECORD_STOPPED)
         {
            m_pManager->OnRecordStopped(hrStatus);
            SetEvent(m_pManager->m_hEvent);
         }
         else
         {
            // This is an happening we don't know about, we don't really care and there's
            // no clean way to report the error so just set the happening and fall through.
            SetEvent(m_pManager->m_hEvent);
         }
      }

      return S_OK;
   }
   else
   {
      pEvent->AddRef();  // The application will release the pointer when it handles the message.
      PostMessage(m_hwnd, WM_APP_CAPTURE_EVENT, (WPARAM)pEvent, 0L);
   }

   return S_OK;
}

HRESULT CreateDX11Device(_Out_ ID3D11Device** ppDevice, _Out_ ID3D11DeviceContext** ppDeviceContext, _Out_ D3D_FEATURE_LEVEL* pFeatureLevel)
{
   HRESULT hr = S_OK;
   static const D3D_FEATURE_LEVEL levels[] = {
      D3D_FEATURE_LEVEL_11_1,
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_9_3,
      D3D_FEATURE_LEVEL_9_2,
      D3D_FEATURE_LEVEL_9_1
   };


   hr = D3D11CreateDevice(
      nullptr,
      D3D_DRIVER_TYPE_HARDWARE,
      nullptr,
      D3D11_CREATE_DEVICE_VIDEO_SUPPORT,
      levels,
      ARRAYSIZE(levels),
      D3D11_SDK_VERSION,
      ppDevice,
      pFeatureLevel,
      ppDeviceContext
   );

   if (SUCCEEDED(hr))
   {
      ID3D10Multitask* pMultitask;
      hr = ((*ppDevice)->QueryInterface(IID_PPV_ARGS(&pMultitask)));

      if (SUCCEEDED(hr))
      {
         pMultitask->SetMultitaskProtected(true);
      }

      SafeRelease(&pMultitask);

   }

   return hr;
}

HRESULT CreateD3DManager()
{
   HRESULT hr = S_OK;
   D3D_FEATURE_LEVEL FeatureLevel;
   ID3D11DeviceContext* pDX11DeviceContext;

   hr = CreateDX11Device(&g_pDX11Device, &pDX11DeviceContext, &FeatureLevel);

   if (SUCCEEDED(hr))
   {
      hr = MFCreateDXGIDeviceManager(&g_ResetToken, &g_pDXGIMan);
   }

   if (SUCCEEDED(hr))
   {
      hr = g_pDXGIMan->ResetDevice(g_pDX11Device, g_ResetToken);
   }

   SafeRelease(&pDX11DeviceContext);

   return hr;
}

HRESULT
CaptureManager::InitializeCaptureManager(HWND hwndThumbnail, IMFCaptureEngineOnSampleCallback * pcallback, IUnknown* pUnk)
{
   HRESULT                         hr = S_OK;
   IMFAttributes*                  pAttributes = nullptr;
   IMFCaptureEngineClassFactory*   pFactory = nullptr;

   DestroyCaptureEngine();

   m_hEvent = CreateEvent(nullptr, false, false, nullptr);
   if (nullptr == m_hEvent)
   {
      hr = HRESULT_FROM_WIN32(GetLastError());
      goto Exit;
   }

   m_pCallback = __allocate< CaptureEngineCB(get_app >(), m_hwndEvent);
   if (m_pCallback == nullptr)
   {
      hr = E_OUTOFMEMORY;
      goto Exit;
   }

   m_pCallback->m_pManager = this;
   m_hwndThumbnail = hwndThumbnail;
   m_pcallback = pcallback;

   //Create a D3D Manager
   hr = CreateD3DManager();
   if (FAILED(hr))
   {
      goto Exit;
   }
   hr = MFCreateAttributes(&pAttributes, 1);
   if (FAILED(hr))
   {
      goto Exit;
   }
   hr = pAttributes->SetUnknown(MF_CAPTURE_ENGINE_D3D_MANAGER, g_pDXGIMan);
   if (FAILED(hr))
   {
      goto Exit;
   }

   // Create the factory_item object for the capture engine.
   hr = CoCreateInstance(CLSID_MFCaptureEngineClassFactory, nullptr,
      CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory));
   if (FAILED(hr))
   {
      goto Exit;
   }

   // Create and initialize the capture engine.
   hr = pFactory->CreateInstance(CLSID_MFCaptureEngine, IID_PPV_ARGS(&m_pEngine));
   if (FAILED(hr))
   {
      goto Exit;
   }
   hr = m_pEngine->Initialize(m_pCallback, pAttributes, nullptr, pUnk);
   if (FAILED(hr))
   {
      goto Exit;
   }

Exit:
   if (nullptr != pAttributes)
   {
      pAttributes->Release();
      pAttributes = nullptr;
   }
   if (nullptr != pFactory)
   {
      pFactory->Release();
      pFactory = nullptr;
   }
   return hr;
}

// Handle an happening from the capture engine. 
// NOTE: This method is called from the application's UI thread. 
HRESULT CaptureManager::OnCaptureEvent(WPARAM wParam, LPARAM lParam)
{
   GUID guidType;
   HRESULT hrStatus;

   IMFMediaEvent *pEvent = reinterpret_cast<IMFMediaEvent*>(wParam);

   HRESULT hr = pEvent->GetStatus(&hrStatus);
   if (FAILED(hr))
   {
      hrStatus = hr;
   }

   hr = pEvent->GetExtendedType(&guidType);
   if (SUCCEEDED(hr))
   {

#ifdef _DEBUG
      LPOLESTR str;
      if (SUCCEEDED(StringFromCLSID(guidType, &str)))
      {
         informationf("MF_CAPTURE_ENGINE_EVENT: %S (hr = 0x%X)\n", str, hrStatus);
         CoTaskMemFree(str);
      }
#endif

      if (guidType == MF_CAPTURE_ENGINE_INITIALIZED)
      {
         OnCaptureEngineInitialized(hrStatus);
         SetErrorID(hrStatus, IDS_ERR_INITIALIZE);
      }
      else if (guidType == MF_CAPTURE_ENGINE_PREVIEW_STARTED)
      {
         OnThumbnailStarted(hrStatus);
         SetErrorID(hrStatus, IDS_ERR_PREVIEW);
      }
      else if (guidType == MF_CAPTURE_ENGINE_PREVIEW_STOPPED)
      {
         OnThumbnailStopped(hrStatus);
         SetErrorID(hrStatus, IDS_ERR_PREVIEW);
      }
      else if (guidType == MF_CAPTURE_ENGINE_RECORD_STARTED)
      {
         OnRecordStarted(hrStatus);
         SetErrorID(hrStatus, IDS_ERR_RECORD);
      }
      else if (guidType == MF_CAPTURE_ENGINE_RECORD_STOPPED)
      {
         OnRecordStopped(hrStatus);
         SetErrorID(hrStatus, IDS_ERR_RECORD);
      }
      else if (guidType == MF_CAPTURE_ENGINE_PHOTO_TAKEN)
      {
         m_bPhotoPending = false;
         SetErrorID(hrStatus, IDS_ERR_PHOTO);
      }
      else if (guidType == MF_CAPTURE_ENGINE_ERROR)
      {
         DestroyCaptureEngine();
         SetErrorID(hrStatus, IDS_ERR_CAPTURE);
      }
      else if (FAILED(hrStatus))
      {
         SetErrorID(hrStatus, IDS_ERR_CAPTURE);
      }
   }

   pEvent->Release();
   SetEvent(m_hEvent);
   return hrStatus;
}


void CaptureManager::OnCaptureEngineInitialized(HRESULT& hrStatus)
{
   if (hrStatus == MF_E_NO_CAPTURE_DEVICES_AVAILABLE)
   {
      hrStatus = S_OK;  // No capture device. Not an application error.
   }
}

void CaptureManager::OnThumbnailStarted(HRESULT& hrStatus)
{
   m_bThumbnailing = SUCCEEDED(hrStatus);
}

void CaptureManager::OnThumbnailStopped(HRESULT& hrStatus)
{
   m_bThumbnailing = false;
}

void CaptureManager::OnRecordStarted(HRESULT& hrStatus)
{
   m_bRecording = SUCCEEDED(hrStatus);
}

void CaptureManager::OnRecordStopped(HRESULT& hrStatus)
{
   m_bRecording = false;
}


HRESULT CaptureManager::StartThumbnail()
{
   if (m_pEngine == nullptr)
   {
      return MF_E_NOT_INITIALIZED;
   }

   if (m_bThumbnailing == true)
   {
      return S_OK;
   }

   IMFCaptureSink *pSink = nullptr;
   IMFMediaType *pMediaType = nullptr;
   IMFMediaType *pMediaType2 = nullptr;
   IMFCaptureSource *pSource = nullptr;

   HRESULT hr = S_OK;

   // Get a pointer to the thumbnail sink.
   if (m_pThumbnail == nullptr)
   {
      hr = m_pEngine->GetSink(MF_CAPTURE_ENGINE_SINK_TYPE_PREVIEW, &pSink);
      if (FAILED(hr))
      {
         goto done;
      }



      hr = pSink->QueryInterface(IID_PPV_ARGS(&m_pThumbnail));
      if (FAILED(hr))
      {
         goto done;
      }


      hr = m_pThumbnail->SetRenderHandle(m_hwndThumbnail);
      if (FAILED(hr))
      {
         goto done;
      }


      hr = m_pEngine->GetSource(&pSource);
      if (FAILED(hr))
      {
         goto done;
      }

      //// Configure the video format for the thumbnail sink.
      hr = pSource->GetCurrentDeviceMediaType((unsigned int)MF_CAPTURE_ENGINE_PREFERRED_SOURCE_STREAM_FOR_VIDEO_PREVIEW, &pMediaType);
      if (FAILED(hr))
      {
         goto done;
      }

      hr = CloneVideoMediaType(pMediaType, MFVideoFormat_RGB32, &pMediaType2);
      if (FAILED(hr))
      {
         goto done;
      }

      hr = pMediaType2->Setunsigned int(MF_MT_ALL_SAMPLES_INDEPENDENT, true);
      if (FAILED(hr))
      {
         goto done;
      }

      // Connect the video stream to the thumbnail sink.
      unsigned int dwSinkStreamIndex;
      hr = m_pThumbnail->AddStream((unsigned int)MF_CAPTURE_ENGINE_PREFERRED_SOURCE_STREAM_FOR_VIDEO_PREVIEW, pMediaType2, nullptr, &dwSinkStreamIndex);
      if (FAILED(hr))
      {
         goto done;
      }

      //hr = m_pThumbnail->SetSampleCallback(dwSinkStreamIndex, m_pcallback);
      //if (FAILED(hr))
      //{
        // goto done;
      //}


   }


   hr = m_pEngine->StartThumbnail();
   if (!m_fPowerRequestSet && m_hpwrRequest != INVALID_HANDLE_VALUE)
   {
      // NOTE:  By calling this, on SOC systems (AOAC enabled), we're asking the system to not go
      // into sleep/connected standby while we're streaming.  However, since we don't want to block
      // the device from ever entering connected standby/sleep, we're going to latch ourselves to
      // the monitor on/off notification (RegisterPowerSettingNotification(GUID_MONITOR_POWER_ON)).
      // On SOC systems, this notification will fire when the user decides to put the device in
      // connected standby mode--we can trap this, turn off our media streams and clear this
      // power set request to allow the device to go into the lower power state.
      m_fPowerRequestSet = (true == PowerSetRequest(m_hpwrRequest, PowerRequestExecutionRequired));
   }
done:
   SafeRelease(&pSink);
   SafeRelease(&pMediaType);
   SafeRelease(&pMediaType2);
   SafeRelease(&pSource);

   return hr;
}

HRESULT CaptureManager::StopThumbnail()
{
   HRESULT hr = S_OK;

   if (m_pEngine == nullptr)
   {
      return MF_E_NOT_INITIALIZED;
   }

   if (!m_bThumbnailing)
   {
      return S_OK;
   }
   hr = m_pEngine->StopThumbnail();
   if (FAILED(hr))
   {
      goto done;
   }
   WaitForResult();

   if (m_fPowerRequestSet && m_hpwrRequest != INVALID_HANDLE_VALUE)
   {
      PowerClearRequest(m_hpwrRequest, PowerRequestExecutionRequired);
      m_fPowerRequestSet = false;
   }
done:
   return hr;
}

// Helper function to get the frame int_size from a video media type.
inline HRESULT GetFrameSize(IMFMediaType *pType, unsigned int *pWidth, unsigned int *pHeight)
{
   return MFGetAttributeSize(pType, MF_MT_FRAME_SIZE, pWidth, pHeight);
}

// Helper function to get the frame rate from a video media type.
inline HRESULT GetFrameRate(
   IMFMediaType *pType,
   unsigned int *pNumerator,
   unsigned int *pDenominator
)
{
   return MFGetAttributeRatio(
      pType,
      MF_MT_FRAME_RATE,
      pNumerator,
      pDenominator
   );
}


HRESULT GetEncodingBitrate(IMFMediaType *pMediaType, unsigned int *uiEncodingBitrate)
{
   unsigned int uiWidth;
   unsigned int uiHeight;
   float uiBitrate;
   unsigned int uiFrameRateNum;
   unsigned int uiFrameRateDenom;

   HRESULT hr = GetFrameSize(pMediaType, &uiWidth, &uiHeight);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = GetFrameRate(pMediaType, &uiFrameRateNum, &uiFrameRateDenom);
   if (FAILED(hr))
   {
      goto done;
   }

   uiBitrate = uiWidth / 3.0f * uiHeight * uiFrameRateNum / uiFrameRateDenom;

   *uiEncodingBitrate = (unsigned int)uiBitrate;

done:

   return hr;
}

HRESULT ConfigureVideoEncoding(IMFCaptureSource *pSource, IMFCaptureRecordSink *pRecord, REFGUID guidEncodingType)
{
   IMFMediaType *pMediaType = nullptr;
   IMFMediaType *pMediaType2 = nullptr;
   GUID guidSubType = GUID_NULL;

   // Configure the video format for the recording sink.
   HRESULT hr = pSource->GetCurrentDeviceMediaType((unsigned int)MF_CAPTURE_ENGINE_PREFERRED_SOURCE_STREAM_FOR_VIDEO_RECORD, &pMediaType);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = CloneVideoMediaType(pMediaType, guidEncodingType, &pMediaType2);
   if (FAILED(hr))
   {
      goto done;
   }


   hr = pMediaType->GetGUID(MF_MT_SUBTYPE, &guidSubType);
   if (FAILED(hr))
   {
      goto done;
   }

   if (guidSubType == MFVideoFormat_H264_ES || guidSubType == MFVideoFormat_H264)
   {
      //When the webcam supports H264_ES or H264, we just bypass the stream. The output from Capture engine shall be the same as the native type supported by the webcam
      hr = pMediaType2->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264);
   }
   else
   {
      unsigned int uiEncodingBitrate;
      hr = GetEncodingBitrate(pMediaType2, &uiEncodingBitrate);
      if (FAILED(hr))
      {
         goto done;
      }

      hr = pMediaType2->Setunsigned int(MF_MT_AVG_BITRATE, uiEncodingBitrate);
   }

   if (FAILED(hr))
   {
      goto done;
   }

   // Connect the video stream to the recording sink.
   unsigned int dwSinkStreamIndex;
   hr = pRecord->AddStream((unsigned int)MF_CAPTURE_ENGINE_PREFERRED_SOURCE_STREAM_FOR_VIDEO_RECORD, pMediaType2, nullptr, &dwSinkStreamIndex);

done:
   SafeRelease(&pMediaType);
   SafeRelease(&pMediaType2);
   return hr;
}

HRESULT ConfigureAudioEncoding(IMFCaptureSource *pSource, IMFCaptureRecordSink *pRecord, REFGUID guidEncodingType)
{
   IMFCollection *pAvailableTypes = nullptr;
   IMFMediaType *pMediaType = nullptr;
   IMFAttributes *pAttributes = nullptr;

   // Configure the audio format for the recording sink.

   HRESULT hr = MFCreateAttributes(&pAttributes, 1);
   if (FAILED(hr))
   {
      goto done;
   }

   // Enumerate low latency media types
   hr = pAttributes->Setunsigned int(MF_LOW_LATENCY, true);
   if (FAILED(hr))
   {
      goto done;
   }


   // Get a list of encoded output formats that are supported by the encoder.
   hr = MFTranscodeGetAudioOutputAvailableTypes(guidEncodingType, MFT_ENUM_FLAG_ALL | MFT_ENUM_FLAG_SORTANDFILTER,
      pAttributes, &pAvailableTypes);
   if (FAILED(hr))
   {
      goto done;
   }

   // Pick the first format from the list.
   hr = GetCollectionObject(pAvailableTypes, 0, &pMediaType);
   if (FAILED(hr))
   {
      goto done;
   }

   // Connect the audio stream to the recording sink.
   unsigned int dwSinkStreamIndex;
   hr = pRecord->AddStream((unsigned int)MF_CAPTURE_ENGINE_PREFERRED_SOURCE_STREAM_FOR_AUDIO, pMediaType, nullptr, &dwSinkStreamIndex);
   if (hr == MF_E_INVALIDSTREAMNUMBER)
   {
      //If an audio device is not present, allow video only recording
      hr = S_OK;
   }
done:
   SafeRelease(&pAvailableTypes);
   SafeRelease(&pMediaType);
   SafeRelease(&pAttributes);
   return hr;
}

HRESULT CaptureManager::StartRecord(PCWSTR pszDestinationFile)
{
   if (m_pEngine == nullptr)
   {
      return MF_E_NOT_INITIALIZED;
   }

   if (m_bRecording == true)
   {
      return MF_E_INVALIDREQUEST;
   }

   PWSTR pszExt = PathFindExtensionW(pszDestinationFile);

   GUID guidVideoEncoding;
   GUID guidAudioEncoding;

   if (wcscmp(pszExt, L".mp4") == 0)
   {
      guidVideoEncoding = MFVideoFormat_H264;
      guidAudioEncoding = MFAudioFormat_AAC;
   }
   else if (wcscmp(pszExt, L".wmv") == 0)
   {
      guidVideoEncoding = MFVideoFormat_WMV3;
      guidAudioEncoding = MFAudioFormat_WMAudioV9;
   }
   else if (wcscmp(pszExt, L".wma") == 0)
   {
      guidVideoEncoding = GUID_NULL;
      guidAudioEncoding = MFAudioFormat_WMAudioV9;
   }
   else
   {
      return MF_E_INVALIDMEDIATYPE;
   }

   IMFCaptureSink *pSink = nullptr;
   IMFCaptureRecordSink *pRecord = nullptr;
   IMFCaptureSource *pSource = nullptr;

   HRESULT hr = m_pEngine->GetSink(MF_CAPTURE_ENGINE_SINK_TYPE_RECORD, &pSink);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = pSink->QueryInterface(IID_PPV_ARGS(&pRecord));
   if (FAILED(hr))
   {
      goto done;
   }

   hr = m_pEngine->GetSource(&pSource);
   if (FAILED(hr))
   {
      goto done;
   }

   // Clear any existing streams from previous recordings.
   hr = pRecord->RemoveAllStreams();
   if (FAILED(hr))
   {
      goto done;
   }

   hr = pRecord->SetOutputFileName(pszDestinationFile);
   if (FAILED(hr))
   {
      goto done;
   }

   // Configure the video and audio streams.
   if (guidVideoEncoding != GUID_NULL)
   {
      hr = ConfigureVideoEncoding(pSource, pRecord, guidVideoEncoding);
      if (FAILED(hr))
      {
         goto done;
      }
   }

   if (guidAudioEncoding != GUID_NULL)
   {
      hr = ConfigureAudioEncoding(pSource, pRecord, guidAudioEncoding);
      if (FAILED(hr))
      {
         goto done;
      }
   }

   hr = m_pEngine->StartRecord();
   if (FAILED(hr))
   {
      goto done;
   }

   m_bRecording = true;

done:
   SafeRelease(&pSink);
   SafeRelease(&pSource);
   SafeRelease(&pRecord);

   return hr;
}

HRESULT CaptureManager::StopRecord()
{
   HRESULT hr = S_OK;

   if (m_bRecording)
   {
      hr = m_pEngine->StopRecord(true, false);
      WaitForResult();
   }

   return hr;
}


HRESULT CaptureManager::TakePhoto(PCWSTR pszFileName)
{
   IMFCaptureSink *pSink = nullptr;
   IMFCapturePhotoSink *pPhoto = nullptr;
   IMFCaptureSource *pSource;
   IMFMediaType *pMediaType = 0;
   IMFMediaType *pMediaType2 = 0;
   bool bHasPhotoStream = true;

   // Get a pointer to the photo sink.
   HRESULT hr = m_pEngine->GetSink(MF_CAPTURE_ENGINE_SINK_TYPE_PHOTO, &pSink);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = pSink->QueryInterface(IID_PPV_ARGS(&pPhoto));
   if (FAILED(hr))
   {
      goto done;
   }

   hr = m_pEngine->GetSource(&pSource);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = pSource->GetCurrentDeviceMediaType((unsigned int)MF_CAPTURE_ENGINE_PREFERRED_SOURCE_STREAM_FOR_PHOTO, &pMediaType);
   if (FAILED(hr))
   {
      goto done;
   }

   //Configure the photo format
   hr = CreatePhotoMediaType(pMediaType, &pMediaType2);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = pPhoto->RemoveAllStreams();
   if (FAILED(hr))
   {
      goto done;
   }

   unsigned int dwSinkStreamIndex;
   // Try to connect the first still image stream to the photo sink
   if (bHasPhotoStream)
   {
      hr = pPhoto->AddStream((unsigned int)MF_CAPTURE_ENGINE_PREFERRED_SOURCE_STREAM_FOR_PHOTO, pMediaType2, nullptr, &dwSinkStreamIndex);
   }

   if (FAILED(hr))
   {
      goto done;
   }

   hr = pPhoto->SetOutputFileName(pszFileName);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = m_pEngine->TakePhoto();
   if (FAILED(hr))
   {
      goto done;
   }

   m_bPhotoPending = true;

done:
   SafeRelease(&pSink);
   SafeRelease(&pPhoto);
   SafeRelease(&pSource);
   SafeRelease(&pMediaType);
   SafeRelease(&pMediaType2);
   return hr;
}




bool mf_startup()
{

   HRESULT hr = MFStartup(MF_VERSION);

   if (FAILED(hr))
   {
      return false;
   }

   return true;

}
