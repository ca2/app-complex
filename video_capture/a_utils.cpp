// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.


// Miscellaneous helper functions.
#include "framework.h"
//#include "Capture.h"
#include <wincodec.h>


HRESULT CopyAttribute(IMFAttributes *pSrc, IMFAttributes *pDest, const GUID& key)
{
   
   PROPVARIANT ::payload;
   
   PropVariantInit(&payload);
   
   HRESULT hr = pSrc->GetItem(key, &payload);

   if (SUCCEEDED(hr))
   {

      hr = pDest->SetItem(key, payload);

   }
   
   PropVariantClear(&payload);
   
   return hr;

}


// Creates a compatible video format with a different subtype.


HRESULT CloneVideoMediaType(IMFMediaType *pSrcMediaType, REFGUID guidSubType, IMFMediaType **ppNewMediaType)
{
   IMFMediaType *pNewMediaType = nullptr;

   HRESULT hr = MFCreateMediaType(&pNewMediaType);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = pNewMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = pNewMediaType->SetGUID(MF_MT_SUBTYPE, guidSubType);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = CopyAttribute(pSrcMediaType, pNewMediaType, MF_MT_FRAME_SIZE);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = CopyAttribute(pSrcMediaType, pNewMediaType, MF_MT_FRAME_RATE);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = CopyAttribute(pSrcMediaType, pNewMediaType, MF_MT_PIXEL_ASPECT_RATIO);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = CopyAttribute(pSrcMediaType, pNewMediaType, MF_MT_INTERLACE_MODE);
   if (FAILED(hr))
   {
      goto done;
   }

   *ppNewMediaType = pNewMediaType;
   (*ppNewMediaType)->AddRef();

done:
   SafeRelease(&pNewMediaType);
   return hr;
}

// Creates a JPEG image type that is compatible with a specified video media type.

HRESULT CreatePhotoMediaType(IMFMediaType *pSrcMediaType, IMFMediaType **ppPhotoMediaType)
{
   *ppPhotoMediaType = nullptr;

   const ::u32 uiFrameRateNumerator = 30;
   const ::u32 uiFrameRateDenominator = 1;

   IMFMediaType *pPhotoMediaType = nullptr;

   HRESULT hr = MFCreateMediaType(&pPhotoMediaType);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = pPhotoMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Image);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = pPhotoMediaType->SetGUID(MF_MT_SUBTYPE, GUID_ContainerFormatJpeg);
   if (FAILED(hr))
   {
      goto done;
   }

   hr = CopyAttribute(pSrcMediaType, pPhotoMediaType, MF_MT_FRAME_SIZE);
   if (FAILED(hr))
   {
      goto done;
   }

   *ppPhotoMediaType = pPhotoMediaType;
   (*ppPhotoMediaType)->AddRef();

done:
   SafeRelease(&pPhotoMediaType);
   return hr;
}

void ShowError(HWND hwnd, PCWSTR szMessage, HRESULT hr)
{

   wchar_t msg[256];

   if (SUCCEEDED(StringCchPrintfW(msg, ARRAYSIZE(msg), L"%s (hr = 0x%X)", szMessage, hr)))
   {

      os_message_box(hwnd, msg, nullptr, e_message_box_ok | MB_ICONERROR);

   }

}


void ShowError(HWND hwnd, ::u32 identification, HRESULT hr)
{
   wchar_t msg[256];

   if (0 != LoadStringW(GetModuleHandle(nullptr), identification, msg, ARRAYSIZE(msg)))
   {
      ShowError(hwnd, msg, hr);
   }
}



void SetMenuItemText(HMENU hMenu, ::u32 utem, _In_ PWSTR pszText)
{
   MENUITEMINFOW mii = {};
   mii.cbSize = sizeof(mii);
   mii.fMask = MIIM_STRING;
   mii.dwTypeData = pszText;

   SetMenuItemInfoW(hMenu, uItem, false, &mii);
}


VOID DbgPrint(PCTSTR format, ...)
{
   va_list args;
   va_start(args, format);

   TCHAR string[MAX_PATH];

   if (SUCCEEDED(StringCbVPrintf(string, sizeof(string), format, args)))
   {
      output_debug_string(string);
   }
   else
   {
      DebugBreak();
   }
}
