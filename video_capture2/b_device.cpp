#include "Common.h"
//#include "BufferLock.h"

const ::u32 NUM_BACK_BUFFERS = 2;

void TransformImage_RGB24(
   byte*       pDest,
   ::i32        lDestStride,
   const byte* pSrc,
   ::i32        lSrcStride,
   ::u32       dwWidthInPixels,
   ::u32       dwHeightInPixels
);

void TransformImage_RGB32(
   byte*       pDest,
   ::i32        lDestStride,
   const byte* pSrc,
   ::i32        lSrcStride,
   ::u32       dwWidthInPixels,
   ::u32       dwHeightInPixels
);

void TransformImage_YUY2(
   byte*       pDest,
   ::i32        lDestStride,
   const byte* pSrc,
   ::i32        lSrcStride,
   ::u32       dwWidthInPixels,
   ::u32       dwHeightInPixels
);

void TransformImage_NV12(
   byte* pDst,
   ::i32 dstStride,
   const byte* pSrc,
   ::i32 srcStride,
   ::u32 dwWidthInPixels,
   ::u32 dwHeightInPixels
);


RECTANGLE_I32    LetterBoxRect(const ::rectangle_i32 &rcSrc, const ::rectangle_i32 &rcDst);
RECTANGLE_I32    CorrectAspectRatio(const ::rectangle_i32 &src, const MFRatio& srcPAR);
HRESULT GetDefaultStride(IMFMediaType *pType, ::i32 *plStride);


inline ::i32 Width(const ::rectangle_i32 &r)
{
   return rectangle.right - rectangle.left;
}

inline ::i32 Height(const ::rectangle_i32 &r)
{
   return rectangle.bottom - rectangle.top;
}


// Static table of output formats and conversion functions.
struct ConversionFunction
{
   GUID               subtype;
   IMAGE_TRANSFORM_FN xform;
};


ConversionFunction   g_FormatConversions[] =
{
   { MFVideoFormat_RGB32, TransformImage_RGB32 },
   { MFVideoFormat_RGB24, TransformImage_RGB24 },
   { MFVideoFormat_YUY2,  TransformImage_YUY2 },
   { MFVideoFormat_NV12,  TransformImage_NV12 }
};

const ::u32   g_cFormats = ARRAYSIZE(g_FormatConversions);


//-------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------

DrawDevice::DrawDevice() :
   m_hwnd(nullptr),
   m_pD3D(nullptr),
   m_pDevice(nullptr),
   m_pSwapChain(nullptr),
   m_format(D3DFMT_UNKNOWN),
   m_width(0),
   m_height(0),
   m_lDefaultStride(0),
   m_interlace(MFVideoInterlace_Unknown),
   m_convertFn(nullptr)
{
   m_PixelAR.Denominator = m_PixelAR.Numerator = 1;

   ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
}


//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------

DrawDevice::~DrawDevice()
{
   DestroyDevice();
}


//-------------------------------------------------------------------
// GetFormat
//
// Get a supported output format by index.
//-------------------------------------------------------------------

HRESULT DrawDevice::GetFormat(::u32 index, GUID *pSubtype) const
{
   if (index < g_cFormats)
   {
      *pSubtype = g_FormatConversions[index].subtype;
      return S_OK;
   }
   return MF_E_NO_MORE_TYPES;
}


//-------------------------------------------------------------------
//  IsFormatSupported
//
//  Query if a format is supported.
//-------------------------------------------------------------------

BOOL DrawDevice::IsFormatSupported(REFGUID subtype) const
{
   for (::u32 i = 0; i < g_cFormats; i++)
   {
      if (subtype == g_FormatConversions[i].subtype)
      {
         return true;
      }
   }
   return false;
}




//-------------------------------------------------------------------
// CreateDevice
//
// Create the Direct3D device.
//-------------------------------------------------------------------

HRESULT DrawDevice::CreateDevice(HWND hwnd)
{
   if (m_pDevice)
   {
      return S_OK;
   }

   // Create the Direct3D object.
   if (m_pD3D == nullptr)
   {
      m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

      if (m_pD3D == nullptr)
      {
         return E_FAIL;
      }
   }


   HRESULT hr = S_OK;
   D3DPRESENT_PARAMETERS pp = { 0 };
   D3DDISPLAYMODE mode = { 0 };

   hr = m_pD3D->GetAdapterDisplayMode(
      D3DADAPTER_DEFAULT,
      &mode
   );

   if (FAILED(hr)) { return hr; }

   hr = m_pD3D->CheckDeviceType(
      D3DADAPTER_DEFAULT,
      D3DDEVTYPE_HAL,
      mode.Format,
      D3DFMT_X8R8G8B8,
      true    // windowed
   );

   if (FAILED(hr)) { return hr; }

   pp.BackBufferFormat = D3DFMT_X8R8G8B8;
   pp.SwapEffect = D3DSWAPEFFECT_COPY;
   pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
   pp.Windowed = true;
   pp.hDeviceWindow = hwnd;

   hr = m_pD3D->CreateDevice(
      D3DADAPTER_DEFAULT,
      D3DDEVTYPE_HAL,
      hwnd,
      D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
      &pp,
      &m_pDevice
   );

   if (FAILED(hr)) { return hr; }

   m_hwnd = hwnd;
   m_d3dpp = pp;


   return hr;
}

//-------------------------------------------------------------------
// SetConversionFunction
//
// Set the conversion function for the specified video format.
//-------------------------------------------------------------------

HRESULT DrawDevice::SetConversionFunction(REFGUID subtype)
{
   m_convertFn = nullptr;

   for (::u32 i = 0; i < g_cFormats; i++)
   {
      if (g_FormatConversions[i].subtype == subtype)
      {
         m_convertFn = g_FormatConversions[i].xform;
         return S_OK;
      }
   }

   return MF_E_INVALIDMEDIATYPE;
}


//-------------------------------------------------------------------
// SetVideoType
//
// Set the video format.  
//-------------------------------------------------------------------

HRESULT DrawDevice::SetVideoType(IMFMediaType *pType)
{
   HRESULT hr = S_OK;
   GUID subtype = { 0 };
   MFRatio PAR = { 0 };

   // Find the video subtype.
   hr = pType->GetGUID(MF_MT_SUBTYPE, &subtype);

   if (FAILED(hr))
   {
      m_format = D3DFMT_UNKNOWN;
      m_convertFn = nullptr;
      return hr;
   }

   // Choose a conversion function.
   // (This also validates the format type.)

   hr = SetConversionFunction(subtype);

   if (FAILED(hr))
   {
      m_format = D3DFMT_UNKNOWN;
      m_convertFn = nullptr;
      return hr;
   }

   //
   // Get some video attributes.
   //

   // Get the frame size.
   hr = MFGetAttributeSize(pType, MF_MT_FRAME_SIZE, &m_width, &m_height);

   if (FAILED(hr))
   {
      m_format = D3DFMT_UNKNOWN;
      m_convertFn = nullptr;
      return hr;
   }


   // Get the interlace mode. Default: assume progressive.
   m_interlace = (MFVideoInterlaceMode)MFGetAttribute::u32(
      pType,
      MF_MT_INTERLACE_MODE,
      MFVideoInterlace_Progressive
   );

   // Get the image stride.
   hr = GetDefaultStride(pType, &m_lDefaultStride);

   if (FAILED(hr))
   {
      m_format = D3DFMT_UNKNOWN;
      m_convertFn = nullptr;
      return hr;
   }

   // Get the pixel aspect ratio. Default: Assume square pixels (1:1)
   hr = MFGetAttributeRatio(
      pType,
      MF_MT_PIXEL_ASPECT_RATIO,
      (::u32*)&PAR.Numerator,
      (::u32*)&PAR.Denominator
   );

   if (SUCCEEDED(hr))
   {
      m_PixelAR = PAR;
   }
   else
   {
      m_PixelAR.Numerator = m_PixelAR.Denominator = 1;
   }

   m_format = (D3DFORMAT)subtype.Data1;

   // Create Direct3D __swap chains.

   hr = CreateSwapChains();

   if (FAILED(hr))
   {
      m_format = D3DFMT_UNKNOWN;
      m_convertFn = nullptr;
      return hr;
   }


   // Update the destination rectangle_i32 for the correct
   // aspect ratio.

   UpdateDestinationRect();



   return hr;
}

//-------------------------------------------------------------------
//  UpdateDestinationRect
//
//  Update the destination rectangle_i32 for the current window size.
//  The destination rectangle_i32 is letterboxed to preserve the 
//  aspect ratio of the video pimage->
//-------------------------------------------------------------------

void DrawDevice::UpdateDestinationRect()
{
   RECTANGLE_I32 rcClient;
   RECTANGLE_I32 rcSrc = { 0, 0, m_width, m_height };

   client_rectangle(m_hwnd, &rcClient);

   rcSrc = CorrectAspectRatio(rcSrc, m_PixelAR);

   m_rcDest = LetterBoxRect(rcSrc, rcClient);

   width = Width(m_rcDest) - 60;

   height = Height(m_rcDest);
}


//-------------------------------------------------------------------
// CreateSwapChains
//
// Create Direct3D __swap chains.
//-------------------------------------------------------------------

HRESULT DrawDevice::CreateSwapChains()
{
   HRESULT hr = S_OK;

   D3DPRESENT_PARAMETERS pp = { 0 };

   SafeRelease(&m_pSwapChain);

   pp.BackBufferWidth = m_width;
   pp.BackBufferHeight = m_height;
   pp.Windowed = true;
   pp.SwapEffect = D3DSWAPEFFECT_FLIP;
   pp.hDeviceWindow = m_hwnd;
   pp.BackBufferFormat = D3DFMT_X8R8G8B8;
   pp.Flags =
      D3DPRESENTFLAG_VIDEO | D3DPRESENTFLAG_DEVICECLIP |
      D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
   pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
   pp.BackBufferCount = NUM_BACK_BUFFERS;

   hr = m_pDevice->CreateAdditionalSwapChain(&pp, &m_pSwapChain);

   return hr;
}


//-------------------------------------------------------------------
// DrawFrame
//
// Draw the video frame.
//-------------------------------------------------------------------

HRESULT DrawDevice::DrawFrame(IMFMediaBuffer *pBuffer)
{
   if (m_convertFn == nullptr)
   {
      return MF_E_INVALIDREQUEST;
   }

   HRESULT hr = S_OK;
   byte *pbScanline0 = nullptr;
   ::i32 lStride = 0;
   D3DLOCKED_RECT lr;

   IDirect3DSurface9 *pSurf = nullptr;
   IDirect3DSurface9 *pBB = nullptr;

   if (m_pDevice == nullptr || m_pSwapChain == nullptr)
   {
      return S_OK;
   }

   VideoBufferLock buffer(pBuffer);    // Helper object to lock the video buffer.

   hr = TestCooperativeLevel();

   if (FAILED(hr))
   {
      SafeRelease(&pBB);
      SafeRelease(&pSurf);
      return hr;
   }

   // Lock the video buffer. This method returns a pointer to the first scan
   // line in the image, and the stride in bytes.

   hr = buffer.LockBuffer(m_lDefaultStride, m_height, &pbScanline0, &lStride);

   if (FAILED(hr))
   {
      SafeRelease(&pBB);
      SafeRelease(&pSurf);
      return hr;
   }

   // Get the __swap-chain surface.
   hr = m_pSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pSurf);

   if (FAILED(hr))
   {
      SafeRelease(&pBB);
      SafeRelease(&pSurf);
      return hr;
   }

   // Lock the __swap-chain surface.
   hr = pSurf->LockRect(&lr, nullptr, D3DLOCK_NOSYSLOCK);

   if (FAILED(hr))
   {
      SafeRelease(&pBB);
      SafeRelease(&pSurf);
      return hr;
   }


   // Convert the frame. This also copies it to the Direct3D surface.

   m_convertFn(
      (byte*)lr.pBits,
      lr.Pitch,
      pbScanline0,
      lStride,
      m_width,
      m_height
   );

   hr = pSurf->UnlockRect();

   if (FAILED(hr))
   {
      SafeRelease(&pBB);
      SafeRelease(&pSurf);
      return hr;
   }


   // Color fill the back buffer.
   hr = m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBB);

   if (FAILED(hr))
   {
      SafeRelease(&pBB);
      SafeRelease(&pSurf);
      return hr;
   }

   hr = m_pDevice->ColorFill(pBB, nullptr, D3DCOLOR_XRGB(0, 0, 0x80));

   if (FAILED(hr))
   {
      SafeRelease(&pBB);
      SafeRelease(&pSurf);
      return hr;
   }



   IDirect3DSurface9* pRenderTarget;
   LPDIRECT3DTEXTURE9 imagetex; //texture our image will be loaded into

   D3DXVECTOR3 imagepos; //vector for the position of the sprite

   m_pDevice->CreateOffscreenPlainSurface(1040, 690, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &pRenderTarget, 0);


   RECTANGLE_I32 rectangle_i32;
   rectangle.bottom = 1040;
   rectangle.left = 0;
   rectangle.right = 690;
   rectangle.top = 0;

   m_pDevice->BeginScene();
   D3DXCreateSprite(m_pDevice, &textSprite);
   D3DXCreateTexture(m_pDevice, 1040, 690, 0, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &imagetex);
   D3DXCreateTextureFromResource(m_pDevice, GetModuleHandle(nullptr), MAKEINTRESOURCE(IMAGE), &imagetex);

   // Use the DrawText method of the D3D render target interface to draw.
   textSprite->Begin(D3DXSPRITE_ALPHABLEND);


   imagepos.x = 0.0f; //coord x of our sprite
   imagepos.y = 18.0f; //coord y of out sprite
   imagepos.z = 0.0f; //coord z of out sprite	
   textSprite->Draw(imagetex, nullptr, nullptr, &imagepos, 0xFFFFFFFF);
   textSprite->End();

   m_pDevice->SetRenderTarget(0, pSurf);
   POINT_I32 p;
   p.x = 0;
   p.y = 0;
   // then use UpdateSurface to copy the drawn text surface to the texture's surface


   m_pDevice->EndScene();

   m_pDevice->UpdateSurface(pRenderTarget, &rectangle, pSurf, &p);
   // release the render surface because you don't need it anymore
   if (pRenderTarget)
   {
      pRenderTarget->Release();
      pRenderTarget = 0;
   }


   // save the frame
   if (saveframe == true)
   {
      D3DXSaveSurfaceToFile(L"Capture.jpg", D3DXIFF_JPG, pSurf, nullptr, nullptr);
      saveframe = false;
   }
   // Blit the frame.

   hr = m_pDevice->StretchRect(pSurf, nullptr, pBB, &m_rcDest, D3DTEXF_LINEAR);

   if (FAILED(hr))
   {
      SafeRelease(&pBB);
      SafeRelease(&pSurf);
      return hr;
   }


   // Present the frame.

   hr = m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);



   SafeRelease(&pBB);
   SafeRelease(&pSurf);
   return hr;
}

//-------------------------------------------------------------------
// TestCooperativeLevel
//
// Test the cooperative-level status of the Direct3D device.
//-------------------------------------------------------------------

HRESULT DrawDevice::TestCooperativeLevel()
{
   if (m_pDevice == nullptr)
   {
      return E_FAIL;
   }

   HRESULT hr = S_OK;

   // Check the current status of D3D9 device.
   hr = m_pDevice->TestCooperativeLevel();

   switch (hr)
   {
   case D3D_OK:
      break;

   case D3DERR_DEVICELOST:
      hr = S_OK;

   case D3DERR_DEVICENOTRESET:
      hr = ResetDevice();
      break;

   default:
      // Some other failure.
      break;
   }

   return hr;
}


//-------------------------------------------------------------------
// ResetDevice
//
// Resets the Direct3D device.
//-------------------------------------------------------------------

HRESULT DrawDevice::ResetDevice()
{
   HRESULT hr = S_OK;

   if (m_pDevice)
   {
      D3DPRESENT_PARAMETERS d3dpp = m_d3dpp;

      hr = m_pDevice->Reset(&d3dpp);

      if (FAILED(hr))
      {
         DestroyDevice();
      }
   }

   if (m_pDevice == nullptr)
   {
      hr = CreateDevice(m_hwnd);

      if (FAILED(hr)) { goto done; }
   }

   if ((m_pSwapChain == nullptr) && (m_format != D3DFMT_UNKNOWN))
   {
      hr = CreateSwapChains();

      if (FAILED(hr)) { goto done; }

      UpdateDestinationRect();
   }

done:

   return hr;
}


//-------------------------------------------------------------------
// DestroyDevice 
//
// Release all Direct3D resources.
//-------------------------------------------------------------------

void DrawDevice::DestroyDevice()
{
   SafeRelease(&m_pSwapChain);
   SafeRelease(&m_pDevice);
   SafeRelease(&m_pD3D);
}



//-------------------------------------------------------------------
//
// Conversion functions
//
//-------------------------------------------------------------------

__forceinline byte Clip(int clr)
{
   return (byte)(clr < 0 ? 0 : (clr > 255 ? 255 : clr));
}

__forceinline RGBQUAD ConvertYCrCbToRGB(
   int y,
   int color32,
   int cb
)
{
   RGBQUAD rgbq;

   int c = y - 16;
   int d = cb - 128;
   int e = color32 - 128;

   rgbq.rgbRed = Clip((298 * c + 409 * e + 128) >> 8);
   rgbq.rgbGreen = Clip((298 * c - 100 * d - 208 * e + 128) >> 8);
   rgbq.rgbBlue = Clip((298 * c + 516 * d + 128) >> 8);

   return rgbq;
}


//-------------------------------------------------------------------
// TransformImage_RGB24 
//
// rgb-24 to rgb-32
//-------------------------------------------------------------------

void TransformImage_RGB24(
   byte*       pDest,
   ::i32        lDestStride,
   const byte* pSrc,
   ::i32        lSrcStride,
   ::u32       dwWidthInPixels,
   ::u32       dwHeightInPixels
)
{
   for (::u32 y = 0; y < dwHeightInPixels; y++)
   {
      RGBTRIPLE *pSrcPel = (RGBTRIPLE*)pSrc;
      ::u32 *pDestPel = (::u32*)pDest;

      for (::u32 x = 0; x < dwWidthInPixels; x++)
      {
         pDestPel[x] = D3DCOLOR_XRGB(
            pSrcPel[x].rgbtRed,
            pSrcPel[x].rgbtGreen,
            pSrcPel[x].rgbtBlue
         );
      }

      pSrc += lSrcStride;
      pDest += lDestStride;
   }
}

//-------------------------------------------------------------------
// TransformImage_RGB32
//
// rgb-32 to rgb-32 
//
// Note: This function is needed to copy the image from system
// memory to the Direct3D surface.
//-------------------------------------------------------------------

void TransformImage_RGB32(
   byte*       pDest,
   ::i32        lDestStride,
   const byte* pSrc,
   ::i32        lSrcStride,
   ::u32       dwWidthInPixels,
   ::u32       dwHeightInPixels
)
{
   MFCopyImage(pDest, lDestStride, pSrc, lSrcStride, dwWidthInPixels * 4, dwHeightInPixels);
}

//-------------------------------------------------------------------
// TransformImage_YUY2 
//
// YUY2 to rgb-32
//-------------------------------------------------------------------

void TransformImage_YUY2(
   byte*       pDest,
   ::i32        lDestStride,
   const byte* pSrc,
   ::i32        lSrcStride,
   ::u32       dwWidthInPixels,
   ::u32       dwHeightInPixels
)
{
   for (::u32 y = 0; y < dwHeightInPixels; y++)
   {
      RGBQUAD *pDestPel = (RGBQUAD*)pDest;
      ::u16    *pSrcPel = (::u16*)pSrc;

      for (::u32 x = 0; x < dwWidthInPixels; x += 2)
      {
         // Byte order is U0 Y0 V0 Y1

         int y0 = (int)__LOBYTE(pSrcPel[x]);
         int u0 = (int)HIBYTE(pSrcPel[x]);
         int y1 = (int)__LOBYTE(pSrcPel[x + 1]);
         int v0 = (int)HIBYTE(pSrcPel[x + 1]);

         pDestPel[x] = ConvertYCrCbToRGB(y0, v0, u0);
         pDestPel[x + 1] = ConvertYCrCbToRGB(y1, v0, u0);
      }

      pSrc += lSrcStride;
      pDest += lDestStride;
   }

}


//-------------------------------------------------------------------
// TransformImage_NV12
//
// NV12 to rgb-32
//-------------------------------------------------------------------

void TransformImage_NV12(
   byte* pDst,
   ::i32 dstStride,
   const byte* pSrc,
   ::i32 srcStride,
   ::u32 dwWidthInPixels,
   ::u32 dwHeightInPixels
)
{
   const byte* lpBitsY = pSrc;
   const byte* lpBitsCb = lpBitsY + (dwHeightInPixels * srcStride);;
   const byte* lpBitsCr = lpBitsCb + 1;

   for (::u32 y = 0; y < dwHeightInPixels; y += 2)
   {
      const byte* lpLineY1 = lpBitsY;
      const byte* lpLineY2 = lpBitsY + srcStride;
      const byte* lpLineCr = lpBitsCr;
      const byte* lpLineCb = lpBitsCb;

      LPBYTE lpDibLine1 = pDst;
      LPBYTE lpDibLine2 = pDst + dstStride;

      for (::u32 x = 0; x < dwWidthInPixels; x += 2)
      {
         int  y0 = (int)lpLineY1[0];
         int  y1 = (int)lpLineY1[1];
         int  y2 = (int)lpLineY2[0];
         int  y3 = (int)lpLineY2[1];
         int  cb = (int)lpLineCb[0];
         int  color32 = (int)lpLineCr[0];

         RGBQUAD r = ConvertYCrCbToRGB(y0, color32, cb);
         lpDibLine1[0] = rectangle.rgbBlue;
         lpDibLine1[1] = rectangle.rgbGreen;
         lpDibLine1[2] = rectangle.rgbRed;
         lpDibLine1[3] = 0; // Alpha

         r = ConvertYCrCbToRGB(y1, color32, cb);
         lpDibLine1[4] = rectangle.rgbBlue;
         lpDibLine1[5] = rectangle.rgbGreen;
         lpDibLine1[6] = rectangle.rgbRed;
         lpDibLine1[7] = 0; // Alpha

         r = ConvertYCrCbToRGB(y2, color32, cb);
         lpDibLine2[0] = rectangle.rgbBlue;
         lpDibLine2[1] = rectangle.rgbGreen;
         lpDibLine2[2] = rectangle.rgbRed;
         lpDibLine2[3] = 0; // Alpha

         r = ConvertYCrCbToRGB(y3, color32, cb);
         lpDibLine2[4] = rectangle.rgbBlue;
         lpDibLine2[5] = rectangle.rgbGreen;
         lpDibLine2[6] = rectangle.rgbRed;
         lpDibLine2[7] = 0; // Alpha

         lpLineY1 += 2;
         lpLineY2 += 2;
         lpLineCr += 2;
         lpLineCb += 2;

         lpDibLine1 += 8;
         lpDibLine2 += 8;
      }

      pDst += (2 * dstStride);
      lpBitsY += (2 * srcStride);
      lpBitsCr += srcStride;
      lpBitsCb += srcStride;
   }
}


//-------------------------------------------------------------------
// LetterBoxDstRect
//
// Takes a src rectangle_i32 and constructs the largest possible 
// destination rectangle_i32 within the specifed destination rectangle_i32 
// such thatthe video maintains its current shape.
//
// This function assumes that pels are the same shape within both the 
// source and destination rectangles.
//
//-------------------------------------------------------------------

RECTANGLE_I32    LetterBoxRect(const ::rectangle_i32 &rcSrc, const ::rectangle_i32 &rcDst)
{
   // figure out src/dest scale ratios
   int iSrcWidth = Width(rcSrc);
   int iSrcHeight = Height(rcSrc);

   int iDstWidth = Width(rcDst);
   int iDstHeight = Height(rcDst);

   int iDstLBWidth;
   int iDstLBHeight;

   if (MulDiv(iSrcWidth, iDstHeight, iSrcHeight) <= iDstWidth) {

      // Column letter boxing ("pillar box")

      iDstLBWidth = MulDiv(iDstHeight, iSrcWidth, iSrcHeight);
      iDstLBHeight = iDstHeight;
   }
   else {

      // Row letter boxing.

      iDstLBWidth = iDstWidth;
      iDstLBHeight = MulDiv(iDstWidth, iSrcHeight, iSrcWidth);
   }


   // Create a centered rectangle_i32 within the current destination rectangle_i32

   RECTANGLE_I32 rc;

   ::i32 left = rcDst.left + ((iDstWidth - iDstLBWidth) / 2);
   ::i32 top = rcDst.top + ((iDstHeight - iDstLBHeight) / 2);

   SetRect(&rc, left, top, left + iDstLBWidth, top + iDstLBHeight);

   return rc;
}


//-----------------------------------------------------------------------------
// CorrectAspectRatio
//
// Converts a rectangle_i32 from the source's pixel aspect ratio (PAR) to 1:1 PAR.
// Returns the corrected rectangle.
//
// For example, a 720 x 486 rectangle_i32 with a PAR of 9:10, when converted to 1x1 PAR,  
// is stretched to 720 x 540. 
//-----------------------------------------------------------------------------

RECTANGLE_I32 CorrectAspectRatio(const ::rectangle_i32 &src, const MFRatio& srcPAR)
{
   // Start with a rectangle_i32 the same size_i32 as src, but offset to the origin (0,0).
   RECTANGLE_I32 rc = { 0, 0, src.right - src.left, src.bottom - src.top };

   if ((srcPAR.Numerator != 1) || (srcPAR.Denominator != 1))
   {
      // Correct for the source's PAR.

      if (srcPAR.Numerator > srcPAR.Denominator)
      {
         // The source has "wide" pixels, so stretch the width.
         rc.right = MulDiv(rc.right, srcPAR.Numerator, srcPAR.Denominator);
      }
      else if (srcPAR.Numerator < srcPAR.Denominator)
      {
         // The source has "tall" pixels, so stretch the height.
         rc.bottom = MulDiv(rc.bottom, srcPAR.Denominator, srcPAR.Numerator);
      }
      // else: PAR is 1:1, which is a no-op.
   }
   return rc;
}


//-----------------------------------------------------------------------------
// GetDefaultStride
//
// Gets the default stride for a video frame, assuming no extra padding bytes.
//
//-----------------------------------------------------------------------------

HRESULT GetDefaultStride(IMFMediaType *pType, ::i32 *plStride)
{
   ::i32 lStride = 0;

   // Try to get the default stride from the media type.
   HRESULT hr = pType->Get::u32(MF_MT_DEFAULT_STRIDE, (::u32*)&lStride);
   if (FAILED(hr))
   {
      // Attribute not set. Try to calculate the default stride.
      GUID subtype = GUID_NULL;

      ::u32 width = 0;
      ::u32 height = 0;

      // Get the subtype and the image size.
      hr = pType->GetGUID(MF_MT_SUBTYPE, &subtype);
      if (SUCCEEDED(hr))
      {
         hr = MFGetAttributeSize(pType, MF_MT_FRAME_SIZE, &width, &height);
      }
      if (SUCCEEDED(hr))
      {
         hr = MFGetStrideForBitmapInfoHeader(subtype.Data1, width, &lStride);
      }

      // Set the attribute for later object.
      if (SUCCEEDED(hr))
      {
         (void)pType->Set::u32(MF_MT_DEFAULT_STRIDE, ::u32(lStride));
      }
   }

   if (SUCCEEDED(hr))
   {
      *plStride = lStride;
   }
   return hr;
}


