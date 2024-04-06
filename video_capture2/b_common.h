#include <d3d9.h>
#include <Windows.h>
#undef i32_x
#undef i32_y
#include <WindowsX.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>
#include <assert.h>
#include <d3d11.h>
#include <ks.h>
#include <ksmedia.h>
#include <Dbt.h>
#include <tchar.h>
#include <strsafe.h>
#include <AclAPI.h>


template <class T> void SafeRelease(T **ppT)
{
   if (*ppT)
   {
      (*ppT)->Release();
      *ppT = nullptr;
   }
}

#define BREAK_ON_FAIL(value)            if(FAILED(value)) break;
#define BREAK_ON_NULL(value, newHr)     if(value == nullptr) { hr = newHr; break; }

#include "b_Device.h"
#include "b_Thumbnail.h"




