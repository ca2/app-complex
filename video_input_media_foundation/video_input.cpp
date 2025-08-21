// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "video_input.h"
#include "device.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/operating_system/windows_common/com/cotaskptr.h"
#include "acme/operating_system/windows_common/com/hresult_exception.h"
#include "app-complex/video_input/media_format.h"
#include "acme/_operating_system.h"
#include <dbt.h>
#include <ks.h>
CLASS_DECL_ACME_WINDOWS_COMMON void throw_if_failed(HRESULT hr);
//#include <mfapi.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfobjects.h>
#include <mferror.h>
#include <mfreadwrite.h>
#include <Mfvirtualcamera.h>


// This GUID is for all USB serial host PnP drivers, but you can replace it 
// with any valid device class guid.
GUID WceusbshGUID = { 0x25dbce51, 0x6c8f, 0x4a72,
                 0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35 };


namespace video_input_media_foundation
{


   video_input::video_input()
   {

      ::CoInitialize(NULL);

      HRESULT hr = MFStartup(MF_VERSION);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

   }


   video_input::~video_input(void)
   {


   }


   void video_input::initialize(::particle * pparticle)
   {

      ::video_input::video_input::initialize(pparticle);

      register_device_listener(::hardware::e_device_video_input);

   }


   void video_input::_update_device_list()
   {

      synchronous_lock synchronouslock(this->synchronization());

      {

         HRESULT hr = S_OK;

         HRESULT hrCamera = E_FAIL;

         comptr<IMFAttributes> pAttributes;

         hr = MFCreateAttributes(&pAttributes, 1);

         if (SUCCEEDED(hr))
         {

            hrCamera = pAttributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);

         }

         if (SUCCEEDED(hrCamera))
         {

            initDevices(pAttributes);

         }

      }

      auto ptopic = create_topic(id_update);

      ptopic->m_pparticle = this;

      route(ptopic);

   }


   void video_input::close_all_devices()
   {

      for (auto & pitem : itema())
      {

         ::pointer < ::video_input::device > pdevice = pitem;

         pdevice->close();

      }

   }


   bool video_input::are_devices_accessible()
   {

      return m_estatusAccessToDevices.ok();

   }


   void video_input::initDevices(IMFAttributes * pAttributes)
   {

      HRESULT hr = S_OK;

      comptr_array < IMFActivate > activatea;

      //m_devicea.erase_all();

      UINT32 cCount = 0;

      hr = MFEnumDeviceSources(pAttributes, __comptr_array(activatea));

      string_array_base straHardwareId;

      if (FAILED(hr))
      {

         throw hresult_exception(hr);

      }

      for (UINT32 u = 0; u < activatea.m_cCount; u++)
      {

         auto pactivate = activatea.m_pp[u];

         cotaskptr < PWCHAR > pwszSymbolicLink;

         string strHardwareId;

         hr = pactivate->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK, &pwszSymbolicLink, NULL);

         if (FAILED(hr))
         {

            throw ::hresult_exception(hr);

         }

         strHardwareId = (const wchar_t *)pwszSymbolicLink;

         if (strHardwareId.is_empty())
         {

            throw ::exception(error_invalid_empty_argument);

         }

         straHardwareId.add(strHardwareId);

         if (contains_device_with_hardware_id(strHardwareId))
         {

            continue;

         }

         auto pdevice = øcreate_new< device>();

         pdevice->m_strHardwareId = strHardwareId;

         pdevice->_set_device(pactivate);

         pdevice->m_pvideoinput = this;

         itema().add(pdevice);

      }

      m_estatusAccessToDevices = ::success;

      for (::collection::index i = 0; i < m_pitemaDevice->get_count();)
      {

         auto pitem = m_pitemaDevice->element_at(i);

         ::pointer < ::video_input::device > pdevice = pitem;

         if (straHardwareId.contains(pdevice->m_strHardwareId))
         {

            i++;

         }
         else
         {

            m_pitemaDevice->erase_at(i);

         }

      }

      for (::collection::index i = 0; i < m_pitemaDevice->get_count(); i++)
      {

         m_pitemaDevice->element_at(i)->m_item.m_iItem = i;

      }

   }


   void video_input::on_device_nodes_changed()
   {

      _update_device_list();

   }


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


} // namespace video_input_media_foundation



