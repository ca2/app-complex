// THIS CODE AND log_information( IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#pragma once

#undef i32_x
#undef i32_y

//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by CaptureEngine.rc
//
#define IDR_MENU1                       101
#define IDD_CHOOSE_DEVICE               102
#define IDS_ERR_SET_DEVICE              103
#define IDS_ERR_INITIALIZE              104
#define IDS_ERR_PREVIEW                 105
#define IDS_ERR_RECORD                  106
#define IDS_ERR_CAPTURE                 107
#define IDS_ERR_PHOTO                   108
#define IDC_DEVICE_LIST                 1001
#define IDC_STATUS_BAR                  1002
#define ID_CAPTURE_CHOOSEDEVICE         40001
#define ID_CAPTURE_STARTRECORDING       40002
#define ID_CAPTURE_RECORD               40003
#define ID_CAPTURE_TAKEPHOTO            40004
#define ID_CAPTURE_PREVIEW              40005



#include <windowsx.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mferror.h>
#include <mfcaptureengine.h>
#include <shlwapi.h>
#include <strsafe.h>
#include <commctrl.h>
#include <d3d11.h>

const ::u32 WM_APP_CAPTURE_EVENT = WM_APP + 975;

class CaptureManager;

HWND    CreateThumbnailWindow(HINSTANCE hInstance, HWND hParent, CaptureManager * p);
HWND    CreateMainWindow(HINSTANCE hInstance);
void    SetMenuItemText(HMENU hMenu, ::u32 utem, _In_ PWSTR pszText);
void    ShowError(HWND hwnd, PCWSTR szMessage, HRESULT hr);
void    ShowError(HWND hwnd, ::u32 identification, HRESULT hr);
HRESULT CloneVideoMediaType(IMFMediaType *pSrcMediaType, REFGUID guidSubType, IMFMediaType **ppNewMediaType);
HRESULT CreatePhotoMediaType(IMFMediaType *pSrcMediaType, IMFMediaType **ppPhotoMediaType);

// DXGI DevManager support
extern IMFDXGIDeviceManager* g_pDXGIMan;
extern ID3D11Device*         g_pDX11Device;
extern ::u32                  g_ResetToken;

#ifdef _DEBUG
#define DBGMSG(x)  { DbgPrint x;}
#else
#define DBGMSG(x)
#endif

VOID DbgPrint(PCTSTR format, ...);


template <class T> void SafeRelease(T **ppT)
{
   if (*ppT)
   {
      (*ppT)->Release();
      *ppT = nullptr;
   }
}

// Gets an interface pointer from a Media Foundation collection.
template <class IFACE>
HRESULT GetCollectionObject(IMFCollection *pCollection, ::u32 index, IFACE **ppObject)
{
   IUnknown *pUnk;
   HRESULT hr = pCollection->GetElement(index, &pUnk);
   if (SUCCEEDED(hr))
   {
      hr = pUnk->QueryInterface(IID_PPV_ARGS(ppObject));
      pUnk->Release();
   }
   return hr;
}


struct ChooseDeviceParam
{
   ChooseDeviceParam() : ppDevices(nullptr), count(0)
   {
   }
   ~ChooseDeviceParam()
   {
      for (::u32 i = 0; i < count; i++)
      {
         SafeRelease(&ppDevices[i]);
      }
      CoTaskMemFree(ppDevices);
   }

   IMFActivate **ppDevices;
   ::u32      count;
   ::u32      selection;
};



// CaptureManager class
// Wraps the capture engine and implements the event callback.

class CaptureManager :
   virtual public ::object
{
   // The event callback object.
   class CaptureEngineCB : public IMFCaptureEngineOnEventCallback,
      virtual public ::object
   {
      HWND m_hwnd;

   public:
      CaptureEngineCB(::particle * pparticle, HWND hwnd) : ::object(pparticle), m_hwnd(hwnd), m_fSleeping(false), m_pManager(nullptr) {}

      // IUnknown
      STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
      STDMETHODIMP_(ULONG) AddRef();
      STDMETHODIMP_(ULONG) Release();

      // IMFCaptureEngineOnEventCallback
      STDMETHODIMP OnEvent(_In_ IMFMediaEvent* pEvent);

      bool m_fSleeping;
      CaptureManager* m_pManager;
   };

   HWND                    m_hwndEvent;
   HWND                    m_hwndThumbnail;
   IMFCaptureEngineOnSampleCallback * m_pcallback;

   IMFCaptureEngine        *m_pEngine;
   IMFCaptureThumbnailSink   *m_pThumbnail;

   CaptureEngineCB         *m_pCallback;

   bool                    m_bThumbnailing;
   bool                    m_bRecording;
   bool                    m_bPhotoPending;

   ::u32                    m_errorID;
   HANDLE                  m_hEvent;
   HANDLE                  m_hpwrRequest;
   bool                    m_fPowerRequestSet;

   CaptureManager(::particle * pparticle, HWND hwnd) :
      ::object(pparticle),
      m_hwndEvent(hwnd), m_hwndThumbnail(nullptr),m_pcallback(nullptr), m_pEngine(nullptr), m_pThumbnail(nullptr),
      m_pCallback(nullptr), m_bRecording(false), m_bThumbnailing(false), m_bPhotoPending(false), m_errorID(0), m_hEvent(nullptr)
      , m_hpwrRequest(INVALID_HANDLE_VALUE)
      , m_fPowerRequestSet(false)
   {
      REASON_CONTEXT  pwrCtxt;

      pwrCtxt.Version = POWER_REQUEST_CONTEXT_VERSION;
      pwrCtxt.Flags = POWER_REQUEST_CONTEXT_SIMPLE_STRING;
      pwrCtxt.Reason.SimpleReasonString = L"CaptureEngine is recording!";

      m_hpwrRequest = PowerCreateRequest(&pwrCtxt);
   }

   void SetErrorID(HRESULT hr, ::u32 identification)
   {
      m_errorID = SUCCEEDED(hr) ? 0 : identification;
   }

   // Capture Engine Event Handlers
   void OnCaptureEngineInitialized(HRESULT& hrStatus);
   void OnThumbnailStarted(HRESULT& hrStatus);
   void OnThumbnailStopped(HRESULT& hrStatus);
   void OnRecordStarted(HRESULT& hrStatus);
   void OnRecordStopped(HRESULT& hrStatus);
   void WaitForResult()
   {
      WaitForSingleObject(m_hEvent, U32_INFINITE_TIMEOUT);
   }
public:
   ~CaptureManager()
   {
      DestroyCaptureEngine();
   }

   static HRESULT CreateInstance(::particle * pparticle, HWND hwndEvent, CaptureManager **ppEngine)
   {
      HRESULT hr = S_OK;
      *ppEngine = nullptr;

      CaptureManager *pEngine = memory_new CaptureManager(papp, hwndEvent);
      if (pEngine == nullptr)
      {
         hr = E_OUTOFMEMORY;
         goto Exit;
      }
      *ppEngine = pEngine;
      pEngine = nullptr;

   Exit:
      if (nullptr != pEngine)
      {
         delete pEngine;
      }
      return hr;
   }

   HRESULT InitializeCaptureManager(HWND hwndThumbnail, IMFCaptureEngineOnSampleCallback * pcallback, IUnknown* pUnk);
   void DestroyCaptureEngine()
   {
      if (nullptr != m_hEvent)
      {
         CloseHandle(m_hEvent);
         m_hEvent = nullptr;
      }
      SafeRelease(&m_pThumbnail);
      SafeRelease(&m_pEngine);
      SafeRelease(&m_pCallback);

      if (g_pDXGIMan)
      {
         g_pDXGIMan->ResetDevice(g_pDX11Device, g_ResetToken);
      }
      SafeRelease(&g_pDX11Device);
      SafeRelease(&g_pDXGIMan);

      m_bThumbnailing = false;
      m_bRecording = false;
      m_bPhotoPending = false;
      m_errorID = 0;
   }



   bool    IsThumbnailing() const { return m_bThumbnailing; }
   bool    IsRecording() const { return m_bRecording; }
   bool    IsPhotoPending() const { return m_bPhotoPending; }
   ::u32    ErrorID() const { return m_errorID; }

   HRESULT OnCaptureEvent(WPARAM wParam, LPARAM lParam);
   HRESULT SetVideoDevice(IUnknown *pUnk);
   HRESULT StartThumbnail();
   HRESULT StopThumbnail();
   HRESULT StartRecord(PCWSTR pszDestinationFile);
   HRESULT StopRecord();
   HRESULT TakePhoto(PCWSTR pszFileName);

   void    SleepState(bool fSleeping)
   {
      if (nullptr != m_pCallback)
      {
         m_pCallback->m_fSleeping = fSleeping;
      }
   }

   HRESULT UpdateVideo()
   {
      if (m_pThumbnail)
      {
         return m_pThumbnail->UpdateVideo(nullptr, nullptr, nullptr);
      }
      else
      {
         return S_OK;
      }
   }
};

