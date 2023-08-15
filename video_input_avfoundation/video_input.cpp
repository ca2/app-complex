// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "acme/parallelization/synchronous_lock.h"

int avfoundation_enumerate_webcams(CFTypeRef ** pptyperef);

namespace video_input_video_avfoundation
{


	video_input::video_input(void)
	{

      defer_create_synchronization();
		
	}


	video_input::~video_input(void)
	{


	}


	void video_input::initialize(::particle * pparticle)
	{

		::object::initialize(pparticle);

	}


	void video_input::_update_device_list()
	{

		synchronous_lock synchronouslock(this->synchronization());

      CFTypeRef * ptyperef = nullptr;
      
      auto count =  avfoundation_enumerate_webcams(&ptyperef);
      
      for(int iDevice = 0; iDevice < count;iDevice++)
      {
         
         auto typerefAVCaptureDevice = ptyperef[iDevice];
         
         string strName =::string_from_strdup(avcapture_device_localized_name(typerefAVCaptureDevice));
         
         string strHardwareId = ::string_from_strdup(avcapture_device_unique_id(typerefAVCaptureDevice));
         
         auto pdevice = memory_new device(iDevice, strName,"", strHardwareId);
         
                                                     
         pdevice->m_ptyperefAVCaptureDevice = typerefAVCaptureDevice;
                                                     
                                                     pdevice->initialize(this);
         m_pitemaDevice->add(pdevice);
         
      }
      
      m_estatusAccessToDevices = ::success;
      
	}

	
	void video_input::close_all_devices()
	{
		
		for (auto & pitem : *m_pitemaDevice)
		{
         
         ::pointer < ::video_input::device > pdevice = pitem;

			pdevice->close();

		}

	}


	bool video_input::are_devices_accessible()
	{
		
		return m_estatusAccessToDevices.ok();

	}


	void video_input::set_verbose(bool state)
	{

	}


   void video_input::handle(::topic * ptopic, ::context * pcontext)
   {

      ::video_input::video_input::handle(ptopic, pcontext);

   }

	
} // namespace video_input_video_avfoundation



