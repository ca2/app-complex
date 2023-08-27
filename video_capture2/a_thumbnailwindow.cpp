// THIS CODE AND log_information( IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#include "framework.h"
//#include "Capture.h"



// Implements the window procedure for the video thumbnail window.

namespace ThumbnailWnd
{
   HBRUSH hBackgroundBrush = 0;

   BOOL OnCreate(HWND /*hwnd*/, LPCREATESTRUCT /*lpCreateStruct*/)
   {
      hBackgroundBrush = CreateSolidBrush(rgb(0, 0, 0));
      return (hBackgroundBrush != nullptr);
   }

   void OnDestroy(HWND hwnd)
   {
      DeleteObject(hBackgroundBrush);
   }

   void OnPaint(HWND hwnd)
   {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);
      CaptureManager * p = (CaptureManager *) ::GetWindowLongPtrW(hwnd, GWLP_USERDATA);
      if (p->IsThumbnailing())
      {
         p->UpdateVideo();
      }
      else
      {
         FillRect(hdc, &ps.rcPaint, hBackgroundBrush);
      }
      EndPaint(hwnd, &ps);
   }

   void OnSize(HWND hwnd, ::u32 state, int /*cx*/, int /*cy*/)
   {
      if (state == SIZE_RESTORED)
      {
         InvalidateRect(hwnd, nullptr, false);
      }
   }

   LRESULT CALLBACK WindowProc(HWND hwnd, ::u32 uMsg, WPARAM wParam, LPARAM lParam)
   {
      switch (uMsg)
      {
         HANDLE_MSG(hwnd, e_message_create, OnCreate);
         HANDLE_MSG(hwnd, e_message_paint, OnPaint);
         HANDLE_MSG(hwnd, e_message_size, OnSize);
         HANDLE_MSG(hwnd, e_message_destroy, OnDestroy);

      case e_message_erase_background:
         return 1;
      }
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
   }
};


HWND CreateThumbnailWindow(HINSTANCE hInstance, HWND hParent, CaptureManager * p)
{
   // Register the window class.
   const wchar_t CLASS_NAME[] = L"Capture Engine Thumbnail Window Class";

   WNDCLASSW wc = {};

   wc.lpfnWndProc = ThumbnailWnd::WindowProc;
   wc.hInstance = hInstance;
   wc.lpszClassName = CLASS_NAME;

   RegisterClassW(&wc);

   ::rectangle_i32 rc;
   this->rectangle(hParent, &rc);

   // Create the window.
   HWND hwnd = CreateWindowExW(0, CLASS_NAME, nullptr,
      WS_VISIBLE, 0, 0, 800, 600,
      nullptr, nullptr, hInstance, nullptr);

   if(hwnd != nullptr)
   {

      ::SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR) p);

      ::set_window_position(hwnd, HWND_TOPMOST, 0, 0, 800, 600, SWP_SHOWWINDOW);

   }

   

   return hwnd;
};
