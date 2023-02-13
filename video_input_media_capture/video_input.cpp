// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "video_input.h"
#include "device.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme_windows_common/cotaskptr.h"
#include "acme_windows_common/hresult_exception.h"
#include "app-complex/video_input/media_format.h"
#include "acme/_operating_system.h"
#include <winrt/windows.foundation.h>
#include <winrt/windows.foundation.collections.h>
#include <winrt/windows.media.capture.h>
#include <winrt/windows.media.capture.frames.h>
//#include <winrt/windows.devices.h>
//#include <winrt/windows.devices.enumeration.h>


//#include <dbt.h>
//#include <ks.h>


// This GUID is for all USB serial host PnP drivers, but you can replace it 
// with any valid device class guid.
GUID WceusbshGUID = { 0x25dbce51, 0x6c8f, 0x4a72,
                 0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35 };


namespace video_input_media_capture
{


   video_input::video_input(void)
   {

      ////m_hdevnotify = nullptr;

      //HRESULT hr = MFStartup(MF_VERSION);

      //if (FAILED(hr))
      //{

      //   throw ::hresult_exception(hr);

      //}

   }


   video_input::~video_input(void)
   {


   }


   void video_input::initialize(::particle * pparticle)
   {

      ::object::initialize(pparticle);

      register_device_listener(::hardware::e_device_video_input);


   }



   void video_input::_update_device_list()
   {

      synchronous_lock synchronouslock(this->synchronization());

      ::winrt::Windows::Foundation::Collections::IVectorView<::winrt::Windows::Media::Capture::Frames::MediaFrameSourceGroup> sourcegroupa(nullptr);

      sourcegroupa = ::winrt::Windows::Media::Capture::Frames::MediaFrameSourceGroup::FindAllAsync().get();
      
      for(::u32 uSourceGroup = 0; uSourceGroup < sourcegroupa.Size(); uSourceGroup++)
      {

         auto sourcegroup = sourcegroupa.GetAt(uSourceGroup);

         for(::u32 uSourceInfo = 0; uSourceInfo < sourcegroup.SourceInfos().Size(); uSourceInfo++)
         {

            auto sourceinfo = sourcegroup.SourceInfos().GetAt(uSourceInfo);

            auto streamtype = sourceinfo.MediaStreamType();

            auto sourcekind = sourceinfo.SourceKind();

            if (streamtype == ::winrt::Windows::Media::Capture::MediaStreamType::VideoRecord
                && sourcekind == ::winrt::Windows::Media::Capture::Frames::MediaFrameSourceKind::Color)
            {

               auto pdevice = __create_new< class device>();

               pdevice->m_strHardwareId = sourcegroup.Id().begin();

               pdevice->m_strName = sourcegroup.DisplayName().begin();

               pdevice->m_mediaframesourcegroup = sourcegroup;

               pdevice->m_mediaframesourceinfo = sourceinfo;

               pdevice->m_pvideoinput = this;

               add_device(pdevice);

               break;

            }

         }

      }
      


//      pdevice->_set_device(pactivate);

         //pdevice->m_pvideoinput = this;

         //add_device(pdevice);

   ////      m_mediacapture = ::winrt::Windows::Media::Capture::MediaCapture();

   //   }


      //if(m_mediacapture.)

      m_estatusAccessToDevices = ::success;

      //comptr<IMFAttributes> pAttributes;

      //::CoInitialize(NULL);

      //hr = MFCreateAttributes(&pAttributes, 1);

      //if (SUCCEEDED(hr))
      //{

      //   hr = pAttributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);

      //}

      //if (SUCCEEDED(hr))
      //{

      //   initDevices(pAttributes);

      //}

   }


   void video_input::close_all_devices()
   {

      for (auto & pdevice : devicea())
      {

         pdevice->close();

      }

   }

   bool video_input::are_devices_accessible()
   {

      return m_estatusAccessToDevices;

   }


   //void video_input::initDevices(IMFAttributes * pAttributes)
   //{

   //   HRESULT hr = S_OK;

   //   comptr_array < IMFActivate > activatea;

   //   //m_devicea.erase_all();

   //   UINT32 cCount = 0;

   //   hr = MFEnumDeviceSources(pAttributes, __comptr_array(activatea));

   //   string_array straHardwareId;

   //   if (FAILED(hr))
   //   {

   //      throw hresult_exception(hr);

   //   }

   //   for (UINT32 u = 0; u < activatea.m_cCount; u++)
   //   {

   //      auto pactivate = activatea.m_pp[u];

   //      cotaskptr < PWCHAR > pwszSymbolicLink;

   //      string strHardwareId;

   //      hr = pactivate->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK, &pwszSymbolicLink, NULL);

   //      if (FAILED(hr))
   //      {

   //         throw ::hresult_exception(hr);

   //      }

   //      strHardwareId = (const wchar_t *)pwszSymbolicLink;

   //      if (strHardwareId.is_empty())
   //      {

   //         throw ::exception(error_invalid_empty_argument);

   //      }

   //      straHardwareId.add(strHardwareId);

   //      if (contains_device_with_hardware_id(strHardwareId))
   //      {

   //         continue;

   //      }

   //      auto pdevice = __create_new< device>();

   //      pdevice->m_strHardwareId = strHardwareId;

   //      pdevice->_set_device(pactivate);

   //      pdevice->m_pvideoinput = this;

   //      add_device(pdevice);

   //   }

   //   m_estatusAccessToDevices = ::success;

   //   for (index i = 0; i < m_devicea.get_count();)
   //   {

   //      auto pdevice = m_devicea[i];

   //      if (straHardwareId.contains(pdevice->m_strHardwareId))
   //      {

   //         i++;

   //      }
   //      else
   //      {

   //         m_devicea.erase_at(i);

   //      }

   //   }

   //}



   void video_input::on_device_plugged(::hardware::enum_device edevice)
   {

      ASSERT(edevice == ::hardware::e_device_video_input);

      _update_device_list();

   }


   void video_input::on_device_unplugged(::hardware::enum_device edevice)
   {

      ASSERT(edevice == ::hardware::e_device_video_input);

      _update_device_list();

   }


} // namespace video_input_media_capture



