#pragma once

const ::u32 WM_APP_PREVIEW_ERROR = WM_APP + 1;    // wparam = HRESULT

class CThumbnail : public IMFSourceReaderCallback
{
public:
   DrawDevice              m_draw;             // Manages the Direct3D device.

   static HRESULT CreateInstance(
      HWND hVideo,
      HWND hEvent,
      CThumbnail **ppPlayer
   );

   // IUnknown methods
   STDMETHODIMP QueryInterface(REFIID iid, void** ppv);
   STDMETHODIMP_(ULONG) AddRef();
   STDMETHODIMP_(ULONG) Release();

   // IMFSourceReaderCallback methods
   STDMETHODIMP OnReadSample(
      HRESULT hrStatus,
      ::u32 dwStreamIndex,
      ::u32 dwStreamFlags,
      ::i64 llTimestamp,
      IMFSample *pSample
   );

   STDMETHODIMP OnEvent(::u32, IMFMediaEvent *)
   {
      return S_OK;
   }

   STDMETHODIMP OnFlush(::u32)
   {
      return S_OK;
   }

   HRESULT       SetDevice(IMFActivate *pActivate);
   HRESULT       CloseDevice();
   HRESULT       ResizeVideo(::u16 width, ::u16 height);
   HRESULT       CheckDeviceLost(DEV_BROADCAST_HDR *pHdr, BOOL *pbDeviceLost);

protected:

   // Constructor is private. Use static CreateInstance method to create.
   CThumbnail(HWND hVideo, HWND hEvent);

   // Destructor is private. Caller should call Release.
   virtual ~CThumbnail();

   HRESULT Initialize();
   void    NotifyError(HRESULT hr) { PostMessage(m_hwndEvent, WM_APP_PREVIEW_ERROR, (WPARAM)hr, 0L); }
   HRESULT TryMediaType(IMFMediaType *pType);

   long                    m_nRefCount;        // Reference count.
   CRITICAL_SECTION        m_critsec;

   HWND                    m_hwndVideo;        // Video window.
   HWND                    m_hwndEvent;        // papp window to receive events.

   IMFSourceReader         *m_pReader;



   WCHAR                   *m_pwszSymbolicLink;
   ::u32                  m_cchSymbolicLink;
};



