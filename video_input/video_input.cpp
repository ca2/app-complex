// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "video_input.h"
#include "device.h"
#include "media_format.h"
#include "acme/constant/id.h"
////#include "acme/exception/exception.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"


namespace video_input
{


	video_input::video_input(void) 
	{

		m_estatusAccessToDevices = error_not_initialized;

	}


	video_input::~video_input(void)
	{

	}


	void video_input::initialize(::particle * pparticle)
	{

		::object::initialize(pparticle);

      __defer_construct_new(m_pitemaDevice);

      register_device_listener(::hardware::e_device_video_input);



	}


	void video_input::destroy()
	{

		::object::destroy();
		::video_input::device_array::destroy();
		::source::destroy();
		::hardware::device_listener::destroy();


	}


	void video_input::_update_device_list()
	{

	}


	void video_input::update_device_list()
	{

		synchronous_lock synchronouslock(this->synchronization());

		_update_device_list();

		if (!m_estatusAccessToDevices)
		{

			throw ::exception(error_failed);

		}
      
      notify_topic(id_update);

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


} // namespace video_input






namespace video_input
{


	void processPixels(color32_t* src, color32_t* dst, unsigned int width, unsigned int height, unsigned int bpp, bool bRGB, bool bFlip)
	{

		unsigned int widthInBytes = width * bpp;

		unsigned int numBytes = widthInBytes * height;

		//unsigned int numInts = numBytes >> 2;

		//unsigned int widthInInts = widthInBytes >> 2;

		int* dstInt, * srcInt;

		if (!bRGB)
		{

			//int x = 0;
			//int y = 0;

			if (bFlip)
			{

				for (unsigned int y = 0; y < height; y++)
				{

					dstInt = (int*)(dst + (y * widthInBytes));

					srcInt = (int*)(src + ((height - y - 1) * widthInBytes));

					memory_copy(dstInt, srcInt, widthInBytes);

				}

			}
			else
			{

				memory_copy(dst, src, numBytes);

				unsigned char* pbyteDst = (unsigned char*)dst;

				pbyteDst += 3;

				for (unsigned int u = 0; u < numBytes; u += 4)
				{

					pbyteDst[0] = 255;
					pbyteDst += 4;

				}

			}
			
		}
		else
		{
			if (bFlip)
			{

				unsigned int x = 0;
				int y = (height - 1) * widthInBytes;
				src += y;

				auto w2 = widthInBytes * 2;

				for (unsigned int i = 0; i < numBytes; i += 4)
				{

					if (x >= width)
					{
						
						x = 0;

						src -= w2;

					}

					*dst = *(src + 2);
					dst++;

					*dst = *(src + 1);
					dst++;

					*dst = *src;
					dst++;

					src += 3;

					x++;

				}

			}
			else
			{

				for (unsigned int u = 0; u < numBytes; u += 4)
				{

					*dst = *(src + 3);

					dst++;

					*dst = *(src + 2);
					dst++;

					*dst = *(src + 1);
					dst++;

					*dst = *src;
					dst++;

					src += 4;

				}

			}

		}

	}


   void video_input::on_device_plugged(::hardware::enum_device edevice)
   {

		if(edevice == ::hardware::e_device_video_input)
		{

			update_device_list();

		}

   }


   void video_input::on_device_unplugged(::hardware::enum_device edevice)
   {

		if(edevice == ::hardware::e_device_video_input)
		{

			update_device_list();

		}

   }


	device * video_input::find_device_with_hardware_id(const ::scoped_string & scopedstrHardwareId) const
	{

      if (!m_pitemaDevice)
      {

         return nullptr;

      }

		for (auto & pitem : itema())
		{

         ::pointer < ::video_input::device > pdevice = pitem;

			if (pdevice->m_strHardwareId == scopedstrHardwareId)
			{

				return pdevice;

			}

		}

		return nullptr;

	}


	bool video_input::contains_device_with_hardware_id(const ::scoped_string & scopedstrHardwareId) const
	{

		auto pdevice = find_device_with_hardware_id(scopedstrHardwareId);

		if (::is_null(pdevice))
		{

			return false;

		}
			
		return true;

	}


   void video_input::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(ptopic->id() == id_video_input_device_added)
      {

         fork([this]()
         {

            _update_device_list();

         });

      }
      else if(ptopic->id() == id_video_input_device_removed)
      {

         fork([this]()
              {

                 _update_device_list();

              });


      }


   }


} // namespace video_input



