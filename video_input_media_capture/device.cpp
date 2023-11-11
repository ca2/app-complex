//https://winplatform.wordpress.com/2015/01/20/winrt-mediacapture-tips/
//https://learn.microsoft.com/en-us/windows/uwp/audio-video-camera/process-media-frames-with-mediaframereader
#include "framework.h"
#include "device.h"
#include "thread.h"
#include "render.h"
#include "media_format.h"
#include "callback.h"
#include "format_reader.h"
#include "apex/platform/system.h"
#include "acme_windows_common/cotaskptr.h"
#include "acme_windows_common/hresult_exception.h"
#include "acme/_operating_system.h"
#include "aura/graphics/image/image.h"
#include <winrt/windows.foundation.h>
#include <winrt/windows.foundation.collections.h>
#include <winrt/windows.media.capture.h>
#include <winrt/windows.media.capture.frames.h>
#include <winrt/windows.media.mediaproperties.h>

#pragma comment(lib, "Strmiids")


namespace video_input_media_capture
{



   device::device() //: 
      //m_bSetup(false),
      //m_elock(::video_input::e_lock_open),
      //m_emergencystopcallback(NULL)
   {

      m_item.m_eelement = ::e_element_item;

   }


   device::~device()
   {

      close();

   }


   void device::set_camera_parameters(::video_input::camera_parameters parameters)
   {

      //if (m_bSetup)
      //{

      //   if (m_pmediasource)
      //   {

      //      ::u32 shift = sizeof(::video_input::parameter);

      //      ::video_input::parameter * pParametr = (::video_input::parameter *)(&parameters);

      //      ::video_input::parameter * pPrevParametr = (::video_input::parameter *)(&m_cameraparametersPrevious);

      //      comptr<IAMVideoProcAmp> pProcAmp;
      //      HRESULT hr = m_pmediasource->QueryInterface(IID_PPV_ARGS(&pProcAmp));

      //      if (SUCCEEDED(hr))
      //      {

      //         for (::u32 i = 0; i < 10; i++)
      //         {

      //            if (pPrevParametr[i].m_lCurrentValue != pParametr[i].m_lCurrentValue || pPrevParametr[i].m_lFlag != pParametr[i].m_lFlag)
      //            {

      //               hr = pProcAmp->Set(VideoProcAmp_Brightness + i, pParametr[i].m_lCurrentValue, pParametr[i].m_lFlag);

      //            }

      //         }

      //      }

      //      comptr<IAMCameraControl> pProcControl;

      //      hr = m_pmediasource->QueryInterface(IID_PPV_ARGS(&pProcControl));

      //      if (SUCCEEDED(hr))
      //      {

      //         for (::u32 i = 0; i < 7; i++)
      //         {

      //            if (pPrevParametr[10 + i].m_lCurrentValue != pParametr[10 + i].m_lCurrentValue || pPrevParametr[10 + i].m_lFlag != pParametr[10 + i].m_lFlag)
      //            {

      //               hr = pProcControl->Set(CameraControl_Pan + i, pParametr[10 + i].m_lCurrentValue, pParametr[10 + i].m_lFlag);

      //            }

      //         }

      //      }

      //      m_cameraparametersPrevious = parameters;

      //   }

      //}

   }


   ::video_input::camera_parameters device::get_camera_parameters()
   {

      return {};
      //::video_input::camera_parameters out;

      //if (m_bSetup)
      //{

      //   if (m_pmediasource)
      //   {

      //      ::u32 shift = sizeof(::video_input::parameter);

      //      ::video_input::parameter * pParametr = (::video_input::parameter *)(&out);

      //      comptr<IAMVideoProcAmp> pProcAmp;

      //      HRESULT hr = m_pmediasource->QueryInterface(IID_PPV_ARGS(&pProcAmp));

      //      if (SUCCEEDED(hr))
      //      {

      //         for (::u32 i = 0; i < 10; i++)
      //         {

      //            ::video_input::parameter temp;

      //            hr = pProcAmp->GetRange(VideoProcAmp_Brightness + i, &temp.m_lMin, &temp.m_lMax, &temp.m_lStep, &temp.m_lDefault, &temp.m_lFlag);

      //            if (SUCCEEDED(hr))
      //            {

      //               long currentValue = temp.m_lDefault;

      //               hr = pProcAmp->Get(VideoProcAmp_Brightness + i, &currentValue, &temp.m_lFlag);

      //               temp.m_lCurrentValue = currentValue;

      //               pParametr[i] = temp;

      //            }

      //         }

      //      }

      //      comptr<IAMCameraControl> pProcControl;

      //      hr = m_pmediasource->QueryInterface(IID_PPV_ARGS(&pProcControl));

      //      if (SUCCEEDED(hr))
      //      {

      //         for (::u32 i = 0; i < 7; i++)
      //         {

      //            ::video_input::parameter temp;

      //            hr = pProcControl->GetRange(CameraControl_Pan + i, &temp.m_lMin, &temp.m_lMax, &temp.m_lStep, &temp.m_lDefault, &temp.m_lFlag);

      //            if (SUCCEEDED(hr))
      //            {

      //               long currentValue = temp.m_lDefault;

      //               hr = pProcAmp->Get(CameraControl_Pan + i, &currentValue, &temp.m_lFlag);

      //               temp.m_lCurrentValue = currentValue;

      //               pParametr[10 + i] = temp;

      //            }

      //         }

      //      }

      //   }

      //}

      //return out;

   }


   //void device::_set_device(IMFActivate * pactivate)
   //{

   //   if (::is_null(pactivate))
   //   {

   //      throw ::exception(error_null_pointer);

   //   }

   //   //m_pactivate = pactivate;

   //   //HRESULT hr = E_FAIL;

   //   //m_mediaformata.clear();

   //   //hr = m_pactivate->ActivateObject(__uuidof(IMFMediaSource), (void **)&m_pmediasource);

   //   //if (FAILED(hr))
   //   //{

   //   //   throw ::hresult_exception(hr);

   //   //}

   //   //cotaskptr < PWCHAR > pFriendlyName;

   //   //hr = m_pactivate->GetAllocatedString(
   //   //   MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
   //   //   &pFriendlyName,
   //   //   NULL
   //   //);

   //   //m_strName = (const WCHAR *)pFriendlyName;

   //   //enumerate_capture_formats();

   //   //buildLibraryofTypes();

   //}


   //long device::readInfoOfDevice(IMFActivate * pActivate)
   //{

   //   HRESULT hr = -1;

   //   hr = resetDevice(pActivate);

   //   return hr;

   //}


   //long device::checkDevice(IMFAttributes * pAttributes, IMFActivate ** pDevice)
   //{

   //	HRESULT hr = S_OK;

   //	IMFActivate ** ppDevices = NULL;

   //	UINT32 m_cCount;

   //	wchar_t * newFriendlyName = NULL;

   //	hr = MFEnumDeviceSources(pAttributes, &ppDevices, &m_cCount);

   //	if (SUCCEEDED(hr))
   //	{

   //		if (m_cCount > 0)
   //		{

   //			if (m_cCount > m_uCurrentNumber)
   //			{

   //				hr = ppDevices[m_uCurrentNumber]->GetAllocatedString(
   //					MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
   //					&newFriendlyName,
   //					NULL
   //				);

   //				string strNewFriendlyName = newFriendlyName;

   //				CoTaskMemFree(newFriendlyName);

   //				if (SUCCEEDED(hr))
   //				{

   //					if (m_strName != strNewFriendlyName)
   //					{

   //						hr = -1;

   //						pDevice = NULL;

   //					}
   //					else
   //					{

   //						*pDevice = ppDevices[m_uCurrentNumber];

   //						(*pDevice)->AddRef();

   //					}

   //				}
   //				else
   //				{

   //					//pdebugprintout->print_out(L"VIDEODEVICE %i: Name of device cannot be gotten \n", m_uCurrentNumber);

   //				}

   //			}
   //			else
   //			{

   //				//pdebugprintout->print_out(L"VIDEODEVICE %i: Number of devices more than corrent number of the device \n", m_uCurrentNumber);

   //				hr = -1;

   //			}

   //			for (UINT32 i = 0; i < m_cCount; i++)
   //			{

   //				if (ppDevices[i])
   //				{

   //					ppDevices[i]->Release();

   //				}

   //			}

   //		}
   //		else
   //		{

   //			hr = -1;

   //		}

   //	}
   //	else
   //	{
   //		
   //		// pdebugprintout->print_out(L"VIDEODEVICE %i: List of DeviceSources cannot be enumerated \n", m_uCurrentNumber);

   //	}

   //	return hr;

   //}


   void device::initialize_device()
   {

      if (!m_mediacapture)
      {

         m_mediacapture = ::winrt::Windows::Media::Capture::MediaCapture();

         ::winrt::Windows::Media::Capture::MediaCaptureInitializationSettings settings;

         settings.SourceGroup(m_mediaframesourcegroup);
         settings.SharingMode(::winrt::Windows::Media::Capture::MediaCaptureSharingMode::ExclusiveControl);
         settings.MemoryPreference(::winrt::Windows::Media::Capture::MediaCaptureMemoryPreference::Cpu);
         settings.StreamingCaptureMode(::winrt::Windows::Media::Capture::StreamingCaptureMode::Video);


         m_mediacapture.InitializeAsync(settings).get();

         enumerate_capture_formats();

      }
      //}
      
      //settings.VideoDeviceId(::__hstring(m_strHardwareId.c_str()));

      //m_mediacapture.InitializeAsync(settings);

   }


   //::video_input::media_format device::get_format(::index iIndex)
   //{

   //	if (::comparison::lt(atom, m_mediaformata.size()))
   //	{

   //		return m_mediaformata[atom];

   //	}
   //	else
   //	{

   //		return {};

   //	}

   //}


   //int device::get_format_count()
   //{

   //	return (int) m_mediaformata.size();

   //}


   void device::set_emergency_stop_event(void(*func)(int, void *))
   {

      m_emergencystopcallback = func;

   }


   void device::close()
   {

      //if (m_bSetup)
      //{

      //   m_bSetup = false;

      //   m_pmediasource->Stop();

      //   if (m_elock == ::video_input::e_lock_raw_data)
      //   {

      //      m_pthread->set_finish();

      //      m_pthread.release();

      //   }

      //   m_elock = ::video_input::e_lock_open;

      //   //debug_print_out * pdebugprintout = &debug_print_out::get_instance();

      //   //pdebugprintout->print_out(L"VIDEODEVICE %i: Device is stopped \n", m_uCurrentNumber);

      //}

   }


   ::u32 device::get_width()
   {

      if (m_bSetup)
      {

         return m_size.cx();
      }
      else
      {

         return 0;

      }

   }


   ::u32 device::get_height()
   {

      if (m_bSetup)
      {

         return m_size.cy();

      }
      else
      {

         return 0;

      }

   }


   ::size_i32 device::get_size()
   {

      if (m_bSetup)
      {

         return m_size;

      }
      else
      {

         return {};

      }

   }


   //IMFMediaSource * device::get_media_source()
   //{

   //   IMFMediaSource * out = NULL;

   //   if (m_elock == ::video_input::e_lock_open)
   //   {

   //      m_elock = ::video_input::e_lock_media_source;

   //      out = m_pmediasource;

   //   }

   //   return out;

   //}


   int device::findType(::u32 size, ::u32 frameRate)
   {

      if (m_mapCaptureFormat.size() == 0)
      {

         return 0;

      }

      auto & FRM = m_mapCaptureFormat[size];

      if (FRM.size() == 0)
      {

         return 0;

      }

      ::u32 frameRateMax = 0;

      subtype_map * psubtypemap = nullptr;

      if (frameRate == 0)
      {

         for (auto & pair : FRM)
         {

            if (pair.element1() >= frameRateMax)
            {

               frameRateMax = (::u32)pair.element1();

               psubtypemap = &pair.element2();

            }

         }

      }
      else
      {

         for (auto & pair : FRM)
         {

            if (pair.element1() >= frameRateMax)
            {

               if (frameRate > pair.element1())
               {

                  frameRateMax = (::u32)pair.element1();

                  psubtypemap = &pair.element2();

               }

            }

         }

      }

      if (!psubtypemap || psubtypemap->is_empty())
      {

         return 0;

      }

      auto it = psubtypemap->begin();

      auto n = it->element2();

      if (n.size() == 0)
      {

         return 0;

      }

      return n[0];

   }


   void device::buildLibraryofTypes()
   {

      ::u32 size;

      ::u32 framerate;

      int m_cCount = 0;

      for (auto & pmediaformat1 : m_mediaformata)
      {

         auto pmediaformat = pmediaformat1.cast < media_format >();

         size = pmediaformat->m_uFrameSize;

         framerate = pmediaformat->m_uFrameRate;

         auto & FRM = m_mapCaptureFormat[size];

         auto & STM = FRM[framerate];

         string subType(pmediaformat->m_strSubtypeName);

         auto & VN = STM[subType];

         VN.add(m_cCount);

         //STM[subType] = VN;

         //FRM[framerate] = STM;

         //m_mapCaptureFormat[size_i32] = FRM;

         m_cCount++;

      }

   }


   void device::_set_device_format(unsigned long  dwFormatIndex)
   {


      ::pointer < media_format >  pmediaformat = m_mediaformata[dwFormatIndex];

      m_mediaframesource.SetFormatAsync(pmediaformat->m_mediaframeformat).get();

      //comptr<IMFPresentationDescriptor> ppresentationdescriptor;
      //comptr < IMFStreamDescriptor> pstreamdescriptor;
      //comptr <IMFMediaTypeHandler > pmediatypehandler;
      //comptr < IMFMediaType> pmediatype;

      //HRESULT hr = m_pmediasource->CreatePresentationDescriptor(&ppresentationdescriptor);

      //if (FAILED(hr))
      //{

      //   throw ::hresult_exception(hr);

      //}

      //BOOL fSelected;
      //
      //hr = ppresentationdescriptor->GetStreamDescriptorByIndex(0, &fSelected, &pstreamdescriptor);
      //
      //if (FAILED(hr))
      //{

      //   throw ::hresult_exception(hr);

      //}

      //hr = pstreamdescriptor->GetMediaTypeHandler(&pmediatypehandler);

      //if (FAILED(hr))
      //{

      //   throw ::hresult_exception(hr);

      //}

      //hr = pmediatypehandler->GetMediaTypeByIndex((DWORD)dwFormatIndex, &pmediatype);

      //if (FAILED(hr))
      //{

      //   throw ::hresult_exception(hr);

      //}

      //hr = pmediatypehandler->SetCurrentMediaType(pmediatype);

      //if (FAILED(hr))
      //{

      //   throw ::hresult_exception(hr);

      //}

   }


   bool device::is_setup()
   {

      return m_bSetup;

   }


   ::memory * device::get_out_memory()
   {

      //if (!m_bSetup) return NULL;

      //if (m_pthread.get())
      //{

      //   return m_pthread->m_pcallback->get_memory();

      //}
      //else
      //{

      //   //debug_print_out * pdebugprintout = &debug_print_out::get_instance();

      //   //pdebugprintout->print_out(L"VIDEODEVICE %i: The instance of image_grabber_thread class does not exist  \n", m_uCurrentNumber);

      //}

      return nullptr;

   }


   void device::start_capturing()
   {

      if (!m_bSetup)
      {

         throw ::exception(error_wrong_state);

      }


      //var colorFrameSource = mediaCapture.FrameSources[colorSourceInfo.Id];
      //var preferredFormat = colorFrameSource.SupportedFormats.Where(format = >
      //{
      //   return format.VideoFormat.Width >= 1080
      //      && format.Subtype == MediaEncodingSubtypes.Argb32;

      //}).FirstOrDefault();

      ::pointer <render > prender = get_render();

      prender->m_mediaframereader = m_mediacapture.CreateFrameReaderAsync(m_mediaframesource).get();

      auto framearrived = ::winrt::Windows::Foundation::TypedEventHandler<
         ::winrt::Windows::Media::Capture::Frames::MediaFrameReader,
         ::winrt::Windows::Media::Capture::Frames::MediaFrameArrivedEventArgs >(
            prender.m_p, &render::OnFrameArrived);

      prender->m_mediaframereader.FrameArrived(framearrived);

      prender->m_mediaframereader.StartAsync().get();

      //m_mediacapture.StartRecordToStreamAsync()

      /*if (m_pthread
         && m_pthread->m_pcallback
         && m_pthread->m_pcallback->m_bLoop)
      {

         m_pthread->m_pcallback->_start_capturing();

         return;

      }

      m_pthread = __new(::video_input_media_capture::thread(this));

      m_pthread->initialize(this);

      m_pthread->branch();*/

   }



   void device::stop_capturing()
   {

      if (!m_bSetup)
      {

         return;

      }

      if (!m_pthread)
      {

         return;

      }

      /*if (m_edevicestate == ::video_input::e_device_state_capturing)
      {

         m_pthread->m_pcallback->_stop_capturing();

      }*/

      m_edevicestate = ::video_input::e_device_state_initial;

      ::video_input::device::stop_capturing();

   }


   string device::get_id2()
   {

      auto psystem = system()->m_papexsystem;

      return psystem->crypto_md5_text(m_strName);

   }


   bool device::get_pixels(color32_t * dstBuffer, bool flipRedAndBlue, bool flipImage)
   {
      bool success = false;

      ::u32 bytes = 4;

      //debug_print_out * pdebugprintout = &debug_print_out::get_instance();

      if (!is_raw_data_source())
      {


         //pdebugprintout->print_out(L"error: GetPixels() - Unable to grab frame for device %s\n", m_strName.c_str());

         return false;

      }

      auto pmemory = get_out_memory();

      if (pmemory)
      {

         ::u32 height = get_height();

         ::u32 width = get_width();

         ::u32 size = bytes * width * height;

         if (size == pmemory->size())
         {

            ::video_input::processPixels((color32_t *)pmemory->data(), dstBuffer, width, height, bytes, flipRedAndBlue, flipImage);

            pmemory->clear_flag(e_flag_changed);

            success = true;

         }
         else
         {

            // pdebugprintout->print_out(L"ERROR: GetPixels() - bufferSizes do not match!\n");

         }

      }

      return true;

   }


   bool device::is_media_source()
   {

      if (m_elock == ::video_input::e_lock_media_source)
      {

         return true;

      }

      return false;

   }


   bool device::is_raw_data_source()
   {

      if (m_elock == ::video_input::e_lock_raw_data)
      {

         return true;

      }

      return false;

   }


   void device::set_format(::index iIndex)
   {

      ////debug_print_out * pdebugprintout = &debug_print_out::get_instance();

      //if (!m_bSetup)
      {

         initialize_device();

         m_size = m_mediaformata[iIndex]->m_size;

         _set_device_format((DWORD)iIndex);

         m_bSetup = true;

         //if (m_bSetup)
            //pdebugprintout->print_out(L"\n\nVIDEODEVICE %i: Device is setuped \n", m_uCurrentNumber);

         m_cameraparametersPrevious = get_camera_parameters();

         ::pointer < render > prender = get_render();

         __defer_construct(prender->m_pimage);

         prender->m_pimage->create(m_size);

         prender->on_set_format();

         //return m_bSetup;

         //}
         //else
         //{
         //	pdebugprintout->print_out(L"VIDEODEVICE %i: Interface IMFMediaSource cannot be got \n", m_uCurrentNumber);

         //	return false;
         //}

      }
      //else
      //{

      //	//pdebugprintout->print_out(L"VIDEODEVICE %i: Device is setuped already \n", m_uCurrentNumber);

      //	return false;

      //}

   }


   //bool device::setup_device(::u32 w, ::u32 h, ::u32 idealFramerate)
   //{
   //	
   //	::u32 atom = findType(w * h, idealFramerate);

   //	return setup_device(atom);

   //}


   string device::get_name()
   {

      return m_strName;

   }


   void device::enumerate_capture_formats()
   {

      m_mediaformata.clear();

      m_mediaframesource = m_mediacapture.FrameSources().Lookup(m_mediaframesourceinfo.Id());

      auto formata = m_mediaframesource.SupportedFormats();

      for (::u32 uFormat = 0; uFormat < formata.Size(); uFormat++)
      {

         auto pmediaformat = __new(media_format);

         pmediaformat->m_mediaframeformat = formata.GetAt(uFormat);

         pmediaformat->m_size.cx() = pmediaformat->m_mediaframeformat.VideoFormat().Width();

         pmediaformat->m_size.cy() = pmediaformat->m_mediaframeformat.VideoFormat().Height();

         ::winrt::Windows::Media::MediaProperties::MediaRatio mediaratio = nullptr;
         
         mediaratio = pmediaformat->m_mediaframeformat.FrameRate();

         pmediaformat->m_uFrameRate = mediaratio.Numerator() / mediaratio.Denominator();

         auto subtype = ::string(pmediaformat->m_mediaframeformat.Subtype().c_str());

         auto argb32Subtype = ::string(::winrt::Windows::Media::MediaProperties::MediaEncodingSubtypes::Argb32().c_str());

         pmediaformat->m_uSampleSize = subtype == argb32Subtype ? 32 : 0;

         m_mediaformata.add(pmediaformat);

      }
      //var preferredFormat = colorFrameSource.SupportedFormats.Where(format = >
      //{
      //   return format.VideoFormat.Width >= 1080
      //      && format.Subtype == MediaEncodingSubtypes.Argb32;

      //}).FirstOrDefault();

      //if (preferredFormat == null)
      //{
      //   // Our desired format is not supported
      //   return;
      //}

      //await colorFrameSource.SetFormatAsync(preferredFormat);

      //comptr<IMFPresentationDescriptor> ppresentationdescriptor;
      //comptr<IMFStreamDescriptor> pstreamdescriptor;
      //comptr<IMFMediaTypeHandler> pmediatypehandler;
      //comptr<IMFMediaType> pmediatype;

      //HRESULT hr = m_pmediasource->CreatePresentationDescriptor(&ppresentationdescriptor);

      //if (FAILED(hr))
      //{

      //   auto estatus = ::windows::hresult_status(hr);

      //   throw ::exception(estatus);

      //}

      //BOOL fSelected;

      //hr = ppresentationdescriptor->GetStreamDescriptorByIndex(0, &fSelected, &pstreamdescriptor);

      //if (FAILED(hr))
      //{

      //   auto estatus = ::windows::hresult_status(hr);

      //   throw ::exception(estatus);

      //}

      //hr = pstreamdescriptor->GetMediaTypeHandler(&pmediatypehandler);

      //if (FAILED(hr))
      //{

      //   auto estatus = ::windows::hresult_status(hr);

      //   throw ::exception(estatus);

      //}

      //DWORD cTypes = 0;

      //hr = pmediatypehandler->GetMediaTypeCount(&cTypes);

      //if (FAILED(hr))
      //{

      //   auto estatus = ::windows::hresult_status(hr);

      //   throw ::exception(estatus);

      //}

      //for (DWORD i = 0; i < cTypes; i++)
      //{

      //   hr = pmediatypehandler->GetMediaTypeByIndex(i, &pmediatype);

      //   if (FAILED(hr))
      //   {

      //      auto estatus = ::windows::hresult_status(hr);

      //      throw ::exception(estatus);

      //   }

      //   auto pformatreader = __create_new < format_reader >();

      //   auto pmediaformat = pformatreader->Read(pmediatype);

      //   m_mediaformata.add(pmediaformat);

      //}

   }


} // namespace video_input_media_capture



