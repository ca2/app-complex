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
      uninstall_avcapture_video_input_callback(this);

	}


	void video_input::initialize(::particle * pparticle)
	{

		::object::initialize(pparticle);
      
      install_avcapture_video_input_callback(this);

	}

   void video_input::on_device_connected()
   {
   
      fork([this]()
           {
         
         update_device_list();
         
      });
      
   }

   void video_input::on_device_disconnected()
   {
      
      fork([this]()
           {
         
         update_device_list();
      });
      
      
   }


	void video_input::_update_device_list()
	{

		synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      CFTypeRef * ptyperef = nullptr;
      
      auto pitemaDevice = øallocate ::item_array();
      
      auto count =  avfoundation_enumerate_webcams(&ptyperef);
      
      for(int iDevice = 0; iDevice < count;iDevice++)
      {
         
         auto typerefAVCaptureDevice = ptyperef[iDevice];
         
         string strName =::string_from_strdup(avcapture_device_localized_name(typerefAVCaptureDevice));
         
         string strHardwareId = ::string_from_strdup(avcapture_device_unique_id(typerefAVCaptureDevice));
         
         auto pdevice = øallocate device(iDevice, strName,"", strHardwareId);
  
         pdevice->m_ptyperefAVCaptureDevice = typerefAVCaptureDevice;
         
         pdevice->initialize(this);
         
         pitemaDevice->add(pdevice);
         
      }
      
      m_pitemaDevice = pitemaDevice;
      
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


   void video_input::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::video_input::video_input::handle(ptopic, phandlercontext);

   }

	
} // namespace video_input_video_avfoundation



