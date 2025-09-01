#include "framework.h"
//#include "Common.h"
#include <shlwapi.h>

//-------------------------------------------------------------------
//  CreateInstance
//
//  Static class method to create the CThumbnail object.
//-------------------------------------------------------------------

HRESULT CThumbnail::CreateInstance(
   HWND hVideo,        // Handle to the video window.
   HWND hEvent,        // Handle to the window to receive notifications.
   CThumbnail **ppPlayer // Receives a pointer to the CThumbnail object.
)
{
   assert(hVideo != nullptr);
   assert(hEvent != nullptr);

   if (ppPlayer == nullptr)
   {
      return E_POINTER;
   }

   CThumbnail *pPlayer = ___new CThumbnail(hVideo, hEvent);

   // The CPlayer constructor sets the ref count to 1.

   if (pPlayer == nullptr)
   {
      return E_OUTOFMEMORY;
   }

   HRESULT hr = pPlayer->Initialize();

   if (SUCCEEDED(hr))
   {
      *ppPlayer = pPlayer;
      (*ppPlayer)->AddRef();
   }

   SafeRelease(&pPlayer);
   return hr;
}


//-------------------------------------------------------------------
//  constructor
//-------------------------------------------------------------------

CThumbnail::CThumbnail(HWND hVideo, HWND hEvent) :
   m_pReader(nullptr),
   m_hwndVideo(hVideo),
   m_hwndEvent(hEvent),
   m_nRefCount(1),
   m_pwszSymbolicLink(nullptr),
   m_cchSymbolicLink(0)
{
   InitializeCriticalSection(&m_critsec);
}

//-------------------------------------------------------------------
//  destructor
//-------------------------------------------------------------------

CThumbnail::~CThumbnail()
{
   CloseDevice();

   m_draw.DestroyDevice();

   DeleteCriticalSection(&m_critsec);
}


//-------------------------------------------------------------------
//  Initialize
//
//  Initializes the object.
//-------------------------------------------------------------------

HRESULT CThumbnail::Initialize()
{
   HRESULT hr = S_OK;

   hr = m_draw.CreateDevice(m_hwndVideo);

   return hr;
}


//-------------------------------------------------------------------
//  CloseDevice
//
//  Releases all resources held by this object.
//-------------------------------------------------------------------

HRESULT CThumbnail::CloseDevice()
{
   EnterCriticalSection(&m_critsec);

   SafeRelease(&m_pReader);

   CoTaskMemFree(m_pwszSymbolicLink);
   m_pwszSymbolicLink = nullptr;
   m_cchSymbolicLink = 0;

   LeaveCriticalSection(&m_critsec);
   return S_OK;
}


/////////////// IUnknown methods ///////////////

//-------------------------------------------------------------------
//  AddRef
//-------------------------------------------------------------------

ULONG CThumbnail::AddRef()
{
   return InterlockedIncrement(&m_nRefCount);
}


//-------------------------------------------------------------------
//  Release
//-------------------------------------------------------------------

ULONG CThumbnail::Release()
{
   ULONG uCount = InterlockedDecrement(&m_nRefCount);
   if (uCount == 0)
   {
      delete this;
   }
   // For thread safety, return a temporary variable.
   return uCount;
}



//-------------------------------------------------------------------
//  QueryInterface
//-------------------------------------------------------------------

HRESULT CThumbnail::QueryInterface(REFIID riid, void** ppv)
{
   static const QITAB qit[] =
   {
      QITABENT(CThumbnail, IMFSourceReaderCallback),
      { 0 },
   };
   return QISearch(this, qit, riid, ppv);
}


/////////////// IMFSourceReaderCallback methods ///////////////

//-------------------------------------------------------------------
// OnReadSample
//
// Called when the IMFMediaSource::ReadSample method completes.
//-------------------------------------------------------------------

HRESULT CThumbnail::OnReadSample(
   HRESULT hrStatus,
   unsigned int /* dwStreamIndex */,
   unsigned int /* dwStreamFlags */,
   long long /* llTimestamp */,
   IMFSample *pSample      // Can be nullptr
)
{
   HRESULT hr = S_OK;
   IMFMediaBuffer *pBuffer = nullptr;

   EnterCriticalSection(&m_critsec);

   if (FAILED(hrStatus))
   {
      hr = hrStatus;
   }

   if (SUCCEEDED(hr))
   {
      if (pSample)
      {
         // Get the video frame buffer from the sample.

         hr = pSample->GetBufferByIndex(0, &pBuffer);

         // Draw the frame.

         if (SUCCEEDED(hr))
         {
            hr = m_draw.DrawFrame(pBuffer);
         }
      }
   }

   // Request the next frame.
   if (SUCCEEDED(hr))
   {
      hr = m_pReader->ReadSample(
         (unsigned int)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
         0,
         nullptr,   // actual
         nullptr,   // flags
         nullptr,   // timestamp
         nullptr    // sample
      );
   }

   if (FAILED(hr))
   {
      NotifyError(hr);
   }
   SafeRelease(&pBuffer);

   LeaveCriticalSection(&m_critsec);
   return hr;
}


//-------------------------------------------------------------------
// TryMediaType
//
// Test a proposed video format.
//-------------------------------------------------------------------

HRESULT CThumbnail::TryMediaType(IMFMediaType *pType)
{
   HRESULT hr = S_OK;

   BOOL bFound = false;
   GUID subtype = { 0 };

   hr = pType->GetGUID(MF_MT_SUBTYPE, &subtype);

   if (FAILED(hr))
   {
      return hr;
   }

   // Do we support this type directly?
   if (m_draw.IsFormatSupported(subtype))
   {
      bFound = true;
   }
   else
   {
      // Can we decode this media type to one of our supported
      // output formats?

      for (unsigned int i = 0; ; i++)
      {
         // Get the i'th format.
         m_draw.GetFormat(i, &subtype);

         hr = pType->SetGUID(MF_MT_SUBTYPE, subtype);

         if (FAILED(hr)) { break; }

         // Try to set this type on the source reader.
         hr = m_pReader->SetCurrentMediaType(
            (unsigned int)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
            nullptr,
            pType
         );

         if (SUCCEEDED(hr))
         {
            bFound = true;
            break;
         }
      }
   }

   if (bFound)
   {
      hr = m_draw.SetVideoType(pType);
   }

   return hr;
}



//-------------------------------------------------------------------
// SetDevice
//
// Set up thumbnail for a specified video capture device. 
//-------------------------------------------------------------------

HRESULT CThumbnail::SetDevice(IMFActivate *pActivate)
{
   HRESULT hr = S_OK;

   IMFMediaSource  *pSource = nullptr;
   IMFAttributes   *pAttributes = nullptr;
   IMFMediaType    *pType = nullptr;

   EnterCriticalSection(&m_critsec);

   // Release the current device, if any.

   hr = CloseDevice();

   // Create the media source for the device.
   if (SUCCEEDED(hr))
   {
      hr = pActivate->ActivateObject(
         __uuidof(IMFMediaSource),
         (void**)&pSource
      );
   }

   // Get the symbolic link.
   if (SUCCEEDED(hr))
   {
      hr = pActivate->GetAllocatedString(
         MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK,
         &m_pwszSymbolicLink,
         &m_cchSymbolicLink
      );
   }


   //
   // Create the source reader.
   //

   // Create an attribute store to hold initialization settings.

   if (SUCCEEDED(hr))
   {
      hr = MFCreateAttributes(&pAttributes, 2);
   }
   if (SUCCEEDED(hr))
   {
      hr = pAttributes->Setunsigned int(MF_READWRITE_DISABLE_CONVERTERS, true);
   }

   // Set the callback pointer.
   if (SUCCEEDED(hr))
   {
      hr = pAttributes->SetUnknown(
         MF_SOURCE_READER_ASYNC_CALLBACK,
         this
      );
   }

   if (SUCCEEDED(hr))
   {
      hr = MFCreateSourceReaderFromMediaSource(
         pSource,
         pAttributes,
         &m_pReader
      );
   }

   // Try to find a suitable output type.
   if (SUCCEEDED(hr))
   {
      for (unsigned int i = 0; ; i++)
      {
         hr = m_pReader->GetNativeMediaType(
            (unsigned int)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
            i,
            &pType
         );

         if (FAILED(hr)) { break; }

         hr = TryMediaType(pType);

         SafeRelease(&pType);

         if (SUCCEEDED(hr))
         {
            // Found an output type.
            break;
         }
      }
   }

   if (SUCCEEDED(hr))
   {
      // Ask for the first sample.
      hr = m_pReader->ReadSample(
         (unsigned int)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
         0,
         nullptr,
         nullptr,
         nullptr,
         nullptr
      );
   }

   if (FAILED(hr))
   {
      if (pSource)
      {
         pSource->Shutdown();

         // NOTE: The source reader shuts down the media source
         // by default, but we might not have gotten that far.
      }
      CloseDevice();
   }

   SafeRelease(&pSource);
   SafeRelease(&pAttributes);
   SafeRelease(&pType);

   LeaveCriticalSection(&m_critsec);
   return hr;
}



//-------------------------------------------------------------------
//  ResizeVideo
//  Resizes the video rectangle.
//
//  The application should call this method if the int_size of the video
//  window changes; e.g., when the application receives ::user::e_message_size.
//-------------------------------------------------------------------

HRESULT CThumbnail::ResizeVideo(unsigned short /*width*/, unsigned short /*height*/)
{
   HRESULT hr = S_OK;

   EnterCriticalSection(&m_critsec);

   hr = m_draw.ResetDevice();

   if (FAILED(hr))
   {
      MessageBox(nullptr, L"ResetDevice failed!", nullptr, ::user::e_message_box_ok);
   }

   LeaveCriticalSection(&m_critsec);

   return hr;
}


//-------------------------------------------------------------------
//  CheckDeviceLost
//  Checks whether the current device has been lost.
//
//  The application should call this method in response to a
//  WM_DEVICECHANGE message. (The application must register for 
//  device notification to receive this message.)
//-------------------------------------------------------------------

HRESULT CThumbnail::CheckDeviceLost(DEV_BROADCAST_HDR *pHdr, BOOL *pbDeviceLost)
{
   DEV_BROADCAST_DEVICEINTERFACE *pDi = nullptr;

   if (pbDeviceLost == nullptr)
   {
      return E_POINTER;
   }

   *pbDeviceLost = false;

   if (pHdr == nullptr)
   {
      return S_OK;
   }

   if (pHdr->dbch_devicetype != DBT_DEVTYP_DEVICEINTERFACE)
   {
      return S_OK;
   }

   pDi = (DEV_BROADCAST_DEVICEINTERFACE*)pHdr;


   EnterCriticalSection(&m_critsec);

   if (m_pwszSymbolicLink)
   {
      if (_wcsicmp(m_pwszSymbolicLink, pDi->dbcc_name) == 0)
      {
         *pbDeviceLost = true;
      }
   }

   LeaveCriticalSection(&m_critsec);

   return S_OK;
}




