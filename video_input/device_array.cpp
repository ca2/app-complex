// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "device_array.h"
#include "device.h"
#include "media_format.h"
#include "acme/parallelization/synchronous_lock.h"


namespace video_input
{


	device_array::device_array() 
	{
	}

	//void device_array::clearDevices()
	//{
	//	//array<device *>::iterator i = m_deviceptra.begin();

	//	//for (; i != m_deviceptra.end(); ++i)
	//		//delete (*i);

	//	erase_all();
	//}

	device_array::~device_array(void)
	{
		//clearDevices();
	}

	//device * device_array::get_device(unsigned int i)
	//{
	//	if (i >= m_deviceptra.size())
	//	{
	//		return NULL;
	//	}

	//	if (i < 0)
	//	{
	//		return NULL;
	//	}

	//	return m_deviceptra[i];
	//}

	//
	//long device_array::initDevices(IMFAttributes * pAttributes)
	//{

	//	HRESULT hr = S_OK;

	//	IMFActivate ** ppDevices = NULL;

	//	m_devicea.erase_all();

	//	UINT32 cCount  = 0;

	//	hr = MFEnumDeviceSources(pAttributes, &ppDevices, &cCount);

	//	if (SUCCEEDED(hr))
	//	{

	//		if (cCount > 0)
	//		{

	//			for (UINT32 i = 0; i < cCount; i++)
	//			{

	//				auto pdevice = øallocate device();

	//				pdevice->readInfoOfDevice(ppDevices[i], i);

	//				add_device(pdevice);

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
	//		debug_print_out * pdebugprintout = &debug_print_out::get_instance();

	//		pdebugprintout->print_out(L"VIDEODEVICES: The instances of the device class cannot be created\n");

	//	}

	//	for (DWORD i = 0; i < cCount; i++)
	//	{
	//		
	//		SafeRelease(&ppDevices[i]);

	//	}

	//	CoTaskMemFree(ppDevices);

	//	return hr;

	//}


	device * device_array::get_device_by_id2(const ::scoped_string & scopedstrMd5)
	{

		synchronous_lock synchronouslock(this->synchronization());

		for (auto & pitem : itema())
		{

         ::pointer < ::video_input::device > pdevice = pitem;

			if (pdevice->get_id2().case_insensitive_order(scopedstrMd5) == 0)
			{

				return pdevice;

			}

		}

		return nullptr;

	}
	
	
	device * device_array::get_device_by_name(const ::scoped_string & scopedstrName)
	{

		synchronous_lock synchronouslock(this->synchronization());


		for (auto & pitem : itema())
		{

         ::pointer < ::video_input::device > pdevice = pitem;

			if (pdevice->get_name().case_insensitive_order(scopedstrName) == 0)
			{

				return pdevice;

			}

		}

		return nullptr;

	}



	//int device_array::getCount()
	//{

	//	return m_deviceptra.size();

	//}


	//device_array & device_array::get_instance()
	//{

	//	static device_array instance;

	//	return instance;

	//}


   ::item_array & device_array::itema()
   {

      return *m_pitemaDevice;

   }


   const ::item_array & device_array::itema() const
   {

      return *m_pitemaDevice;

   }

   
   bool device_array::contains_item(::item * pitem) const
   {
   
      if(!m_pitemaDevice)
      {
         
         return false;
         
      }
      
      return m_pitemaDevice->contains(pitem);
   
   }


   bool device_array::has_item() const
   {
   
      if(!m_pitemaDevice)
      {
       
         return 0;
         
      }
   
      return m_pitemaDevice->has_element();
   
   }


} // namespace video_input


