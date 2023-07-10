// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "video_input.h"
#include "device.h"
#include "acme/parallelization/synchronous_lock.h"
#if defined(FREEBSD)
#define __BSD_VISIBLE 1
#endif
#include <dirent.h>
#include <fcntl.h>


namespace video_input_video_for_linux
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

      v4l2_init_udev();

	}


	void video_input::_update_device_list()
	{

		synchronous_lock synchronouslock(this->synchronization());

      DIR *dirp;
      struct dirent *dp;
      string strDevice;
      bool cur_device_found;
      size_t cur_device_index;
      const char *cur_device_name;

#ifdef FREEBSD

      dirp = opendir("/dev");

#else

      dirp = opendir("/sys/class/video4linux");

#endif

      if (!dirp)
      {

         m_estatusAccessToDevices = ::success;

         return;

      }

      string strFolder = "/dev/";

      index iDevice = 0;

      string_array straDevice;

      while ((dp = readdir(dirp)) != nullptr)
      {

         int fd;

         uint32_t caps;

         struct v4l2_capability video_cap;

#ifdef FREEBSD

         if (strstr(dp->d_name, "video") == NULL)
         {

            continue;

         }

#endif

         if (dp->d_type == DT_DIR)
         {

            continue;

         }

         strDevice = strFolder + dp->d_name;

         if ((fd = v4l2_open(strDevice, O_RDWR | O_NONBLOCK)) == -1)
         {

            auto cerrornumber = c_error_number();

            auto strErrorDescription = cerrornumber.get_error_description();

            information("Unable to open %s - %s", strDevice.c_str(), strErrorDescription.c_str());

            continue;

         }

         if (v4l2_ioctl(fd, VIDIOC_QUERYCAP, &video_cap) == -1)
         {

            information("Failed to query capabilities for %s", strDevice.c_str());

            v4l2_close(fd);

            continue;

         }

#ifndef V4L2_CAP_DEVICE_CAPS

         caps = video_cap.capabilities;

#else

         /* ... since Linux 3.3 */
         caps = (video_cap.capabilities & V4L2_CAP_DEVICE_CAPS)
                ? video_cap.device_caps
                : video_cap.capabilities;

#endif

         if (!(caps & V4L2_CAP_VIDEO_CAPTURE))
         {

            information("%s seems to not support video capture", strDevice.c_str());

            v4l2_close(fd);

            continue;

         }

         straDevice.add(strDevice);

         string strHardwareId;

         strHardwareId.format("%s (%s)", video_cap.card, video_cap.bus_info);

         auto pdevice = find_device_with_hardware_id(strHardwareId);

         if(pdevice)
         {

            ::pointer < device > pdev = pdevice;

            pdev->m_strDevice = strDevice;

         }
         else
         {

            auto pdev = __new(device(iDevice++, (const char *) video_cap.card, strDevice, strHardwareId));

            pdev->initialize(this);

            m_devicea.add(pdev);

            pdevice = pdev;

         }

         information("Found device '%s' at %s", video_cap.card, strDevice.c_str());

         v4l2_close(fd);

      }

      closedir(dirp);

      for(::index i = 0; i < m_devicea.get_size();)
      {

         auto pdev = m_devicea[i].cast < device >();

         if(!straDevice.case_insensitive_contains(pdev->m_strDevice))
         {

            m_devicea.erase_at(i);

         }
         else
         {

            i++;

         }

      }

      m_estatusAccessToDevices = ::success;

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
		
		return m_estatusAccessToDevices.ok();

	}


	void video_input::set_verbose(bool state)
	{

	}


   void video_input::handle(::topic * ptopic, ::context * pcontext)
   {

      ::video_input::video_input::handle(ptopic, pcontext);

   }

	
} // namespace video_input_video_for_linux



