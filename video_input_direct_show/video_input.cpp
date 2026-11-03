#include "platform.h"
#include "video_input.h"
#include "device.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/operating_system/windows_common/com/hresult_exception.h"
namespace video_input_direct_show
{
   void video_input::initialize(::particle * pparticle)
   {
      ::video_input::video_input::initialize(pparticle);
      register_device_listener(::hardware::e_device_video_input);
   }
   void video_input::_update_device_list()
   {
      HRESULT apartment = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
      if (FAILED(apartment) && apartment != RPC_E_CHANGED_MODE) throw ::hresult_exception(apartment);
      struct apartment_scope { bool owned; ~apartment_scope() { if (owned) CoUninitialize(); } } scope{SUCCEEDED(apartment)};
      synchronous_lock lock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      comptr<ICreateDevEnum> devices;
      HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&devices));
      if (FAILED(hr)) throw ::hresult_exception(hr);
      comptr<IEnumMoniker> enumerator;
      hr = devices->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &enumerator, 0);
      if (FAILED(hr)) throw ::hresult_exception(hr);
      string_array_base ids;
      if (hr == S_OK)
      {
         comptr<IMoniker> moniker;
         while (enumerator->Next(1, &moniker, nullptr) == S_OK)
         {
            LPOLESTR display = nullptr;
            hr = moniker->GetDisplayName(nullptr, nullptr, &display);
            if (SUCCEEDED(hr))
            {
               string id = display; CoTaskMemFree(display); ids.add(id);
               if (!contains_device_with_hardware_id(id))
               {
                  auto camera = create_newø<device>(); camera->m_strHardwareId = id;
                  camera->_set_device(moniker); camera->m_pvideoinput = this; itema().add(camera);
                  information() << "[video_input.direct_show] camera=" << camera->m_strName << " id=" << id;
               }
            }
            moniker.release();
         }
      }
      for (::collection::index i = itema().get_count(); i > 0; --i)
      {
         ::pointer<::video_input::device> camera = itema()[i - 1];
         if (!ids.contains(camera->m_strHardwareId)) { camera->close(); itema().erase_at(i - 1); }
      }
      for (::collection::index i = 0; i < itema().get_count(); ++i) itema()[i]->m_item.m_iItem = i;
      m_estatusAccessToDevices = ::success;
      lock.unlock();
      auto topic = create_topic(id_update); topic->m_pparticle = this; route(topic);
   }
}


// Previous Media Foundation implementation retained for migration reference.
// // https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
// #include "platform.h"
// #include "video_input.h"
// #include "device.h"
// #include "acme/constant/id.h"
// #include "acme/handler/topic.h"
// #include "acme/parallelization/synchronous_lock.h"
// #include "acme/operating_system/windows_common/com/cotaskptr.h"
// #include "acme/operating_system/windows_common/com/hresult_exception.h"
// #include "app-complex/video_input/media_format.h"
// #include "acme/_operating_system.h"
// #include <dbt.h>
// #include <ks.h>
// CLASS_DECL_ACME_WINDOWS_COMMON void throw_if_failed(HRESULT hr);
// //#include <mfapi.h>
// #include <mfapi.h>
// #include <mfidl.h>
// #include <mfobjects.h>
// #include <mferror.h>
// #include <mfreadwrite.h>
// #include <Mfvirtualcamera.h>
// 
// 
// // This GUID is for all USB serial host PnP drivers, but you can replace it 
// // with any valid device class guid.
// GUID WceusbshGUID = { 0x25dbce51, 0x6c8f, 0x4a72,
//                  0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35 };
// 
// 
// namespace video_input_direct_show
// {
// 
// 
//    video_input::video_input()
//    {
// 
//       ::CoInitialize(NULL);
// 
//       HRESULT hr = MFStartup(MF_VERSION);
// 
//       if (FAILED(hr))
//       {
// 
//          throw ::hresult_exception(hr);
// 
//       }
// 
//    }
// 
// 
//    video_input::~video_input(void)
//    {
// 
// 
//    }
// 
// 
//    void video_input::initialize(::particle * pparticle)
//    {
// 
//       ::video_input::video_input::initialize(pparticle);
// 
//       register_device_listener(::hardware::e_device_video_input);
// 
//    }
// 
// 
//    void video_input::_update_device_list()
//    {
// 
//       synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
// 
//       {
// 
//          HRESULT hr = S_OK;
// 
//          HRESULT hrCamera = E_FAIL;
// 
//          comptr<IMFAttributes> pAttributes;
// 
//          hr = MFCreateAttributes(&pAttributes, 1);
// 
//          if (SUCCEEDED(hr))
//          {
// 
//             hrCamera = pAttributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
// 
//          }
// 
//          if (SUCCEEDED(hrCamera))
//          {
// 
//             initDevices(pAttributes);
// 
//          }
// 
//       }
// 
//       auto ptopic = create_topic(id_update);
// 
//       ptopic->m_pparticle = this;
// 
//       route(ptopic);
// 
//    }
// 
// 
//    void video_input::close_all_devices()
//    {
// 
//       for (auto & pitem : itema())
//       {
// 
//          ::pointer < ::video_input::device > pdevice = pitem;
// 
//          pdevice->close();
// 
//       }
// 
//    }
// 
// 
//    bool video_input::are_devices_accessible()
//    {
// 
//       return m_estatusAccessToDevices.ok();
// 
//    }
// 
// 
//    void video_input::initDevices(IMFAttributes * pAttributes)
//    {
// 
//       HRESULT hr = S_OK;
// 
//       comptr_array < IMFActivate > activatea;
// 
//       //m_devicea.erase_all();
// 
//       UINT32 cCount = 0;
// 
//       hr = MFEnumDeviceSources(pAttributes, __comptr_array(activatea));
// 
//       string_array_base straHardwareId;
// 
//       if (FAILED(hr))
//       {
// 
//          throw hresult_exception(hr);
// 
//       }
// 
//       for (UINT32 u = 0; u < activatea.m_cCount; u++)
//       {
// 
//          auto pactivate = activatea.m_pp[u];
// 
//          cotaskptr < PWCHAR > pwszSymbolicLink;
// 
//          string strHardwareId;
// 
//          hr = pactivate->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK, &pwszSymbolicLink, NULL);
// 
//          if (FAILED(hr))
//          {
// 
//             throw ::hresult_exception(hr);
// 
//          }
// 
//          strHardwareId = (const wchar_t *)pwszSymbolicLink;
// 
//          if (strHardwareId.is_empty())
//          {
// 
//             throw ::exception(error_invalid_empty_argument);
// 
//          }
// 
//          straHardwareId.add(strHardwareId);
// 
//          if (contains_device_with_hardware_id(strHardwareId))
//          {
// 
//             continue;
// 
//          }
// 
//          auto pdevice = create_newø< device>();
// 
//          pdevice->m_strHardwareId = strHardwareId;
// 
//          pdevice->_set_device(pactivate);
// 
//          pdevice->m_pvideoinput = this;
// 
//          itema().add(pdevice);
// 
//       }
// 
//       m_estatusAccessToDevices = ::success;
// 
//       for (::collection::index i = 0; i < m_pitemaDevice->get_count();)
//       {
// 
//          auto pitem = m_pitemaDevice->element_at(i);
// 
//          ::pointer < ::video_input::device > pdevice = pitem;
// 
//          if (straHardwareId.contains(pdevice->m_strHardwareId))
//          {
// 
//             i++;
// 
//          }
//          else
//          {
// 
//             m_pitemaDevice->erase_at(i);
// 
//          }
// 
//       }
// 
//       for (::collection::index i = 0; i < m_pitemaDevice->get_count(); i++)
//       {
// 
//          m_pitemaDevice->element_at(i)->m_item.m_iItem = i;
// 
//       }
// 
//    }
// 
// 
//    void video_input::on_device_nodes_changed()
//    {
// 
//       _update_device_list();
// 
//    }
// 
// 
//    void video_input::on_device_plugged(::hardware::enum_device edevice)
//    {
// 
//       ASSERT(edevice == ::hardware::e_device_video_input);
// 
//       _update_device_list();
// 
//    }
// 
// 
//    void video_input::on_device_unplugged(::hardware::enum_device edevice)
//    {
// 
//       ASSERT(edevice == ::hardware::e_device_video_input);
// 
//       _update_device_list();
// 
//    }
// 
// 
// } // namespace video_input_direct_show
// 
// 
// 
