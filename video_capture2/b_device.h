#pragma once

// Function pointer for the function that transforms the pimage->

typedef void(*IMAGE_TRANSFORM_FN)(
   ::u8*       pDest,
   int        lDestStride,
   const ::u8* pSrc,
   int        lSrcStride,
   ::u32       dwWidthInPixels,
   ::u32       dwHeightInPixels
   );


// DrawDevice class

class DrawDevice
{
private:

   HWND                    m_hwnd;
   HDC                     *phdc;
   IDirect3D9              *m_pD3D;
   IDirect3DDevice9        *m_pDevice;
   IDirect3DSwapChain9     *m_pSwapChain;

   D3DPRESENT_PARAMETERS   m_d3dpp;
//   ID3DXSprite             *textSprite;
   // Format information
   D3DFORMAT               m_format;
   int                    m_lDefaultStride;
   MFRatio                 m_PixelAR;
   MFVideoInterlaceMode    m_interlace;
   ::i32_rectangle                    m_rcDest;       // Destination i32_rectangle

                                           // Drawing
   IMAGE_TRANSFORM_FN      m_convertFn;    // Function to convert the video to RGB32

private:

   HRESULT TestCooperativeLevel();
   HRESULT SetConversionFunction(REFGUID subtype);
   HRESULT CreateSwapChains();
   void    UpdateDestinationRect();

public:
   bool saveframe;
   ::u32                    m_width;
   ::u32                    m_height;
   ::u32                    width;
   ::u32                    height;
   DrawDevice();
   virtual ~DrawDevice();

   HRESULT CreateDevice(HWND hwnd);
   HRESULT ResetDevice();
   void    DestroyDevice();

   HRESULT SetVideoType(IMFMediaType *pType);
   HRESULT DrawFrame(IMFMediaBuffer *pBuffer);

   // What video formats we accept
   BOOL     IsFormatSupported(REFGUID subtype) const;
   HRESULT  GetFormat(::u32 index, GUID *pSubtype)  const;
};



