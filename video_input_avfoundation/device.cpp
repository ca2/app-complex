#include "framework.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/include/_c_swap.h"
#include "apex/platform/system.h"
#include "aura/graphics/image/image.h"
#include "app-complex/video_input/media_format.h"

void avcapture_stop(CFTypeRef typerefCapture);
bool avcapture_device_set_best_format_001(CFTypeRef typerefCapture, int * w, int * h);

namespace video_input_video_avfoundation
{



	device::device(::collection::index iIndex, const ::string & strName, const ::string & strDevice, const ::string & strHardwareId) :
   m_iIndex(iIndex),
   m_strDevice(strDevice)
	{
      m_item.m_iItem = iIndex;
      m_item.m_eelement = e_element_item;
      m_strHardwareId = strHardwareId;
      m_strName = strName;
      m_bAutoReset = false;

	}


	device::~device()
	{

		close();

	}



	void device::initialize_device()
	{

      if(m_bSetup)
      {

         return;

      }

//      informationf("Initialize video capture device from %s", m_strDevice.c_str());
//
//      m_iDevice = v4l2_open(m_strDevice, O_RDWR | O_NONBLOCK);
//
//      if (m_iDevice == -1)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         auto estatus = cerrornumber.estatus();
//
//         errorf("Unable to open device");
//
//         throw ::exception(estatus, "Unable to open device");
//
//      }
//
      enumerate_capture_formats();
      
      int w = 0;
      int h = 0;
      avcapture_device_set_best_format_001(m_ptyperefAVCaptureDevice, &w, &h);
      
      m_size.cx() = w;
      m_size.cy() = h;
      
      __øconstruct(m_prender);
      
      __øconstruct(m_prender->m_pimage);
//
      m_bSetup = true;
//
	}



	void device::set_emergency_stop_event(void(*func)(int, void *))
	{

		m_emergencystopcallback = func;

	}


	void device::close()
	{

		if (m_bSetup)
		{

         stop_capturing();

			m_bSetup = false;

         //m_pmemorymap.release();

	   	m_pthread.release();

			m_elock = ::video_input::e_lock_open;

//         m_pmjpegdecoder.release();
//
//         m_pmemorymap.release();

//         if (m_iDevice != -1)
//         {
//
//            v4l2_close(m_iDevice);
//
//            m_iDevice = -1;
//
//         }

		}

	}

void device::avcapture_device_on_frame(const void * pdata, int width, int height, int scan)
{
   synchronous_lock synchronouslock(m_prender->synchronization());
   
   m_prender->m_pimage->create({width, height});
   m_prender->m_pimage->image32()->vertical_swap_copy(
                           minimum(width,m_prender->m_pimage->width()),
                           minimum(height,m_prender->m_pimage->height()),
                           m_prender->m_pimage->m_iScan,
                           (image32_t *) pdata,
                           scan);
                           
                           
   
}

//   int device::ioctl(int request, void * arg)
//   {
//
//      int iReturn = v4l2_ioctl(m_iDevice, request, arg);
//
//      return iReturn;
//
//   }
//

   unsigned int device::get_width()
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


	unsigned int device::get_height()
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


	::int_size device::get_size()
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


	int device::findType(unsigned int size, unsigned int frameRate)
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

		unsigned int frameRateMax = 0;  
		
		subtype_map * psubtypemap = nullptr;

		if (frameRate == 0)
		{

			for (auto & pair :FRM)
			{

				if (pair.element1() >= frameRateMax)
				{

					frameRateMax = (unsigned int) pair.element1();

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

						frameRateMax = (unsigned int) pair.element1();

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

		unsigned int size;

		unsigned int framerate;

		int m_cCount = 0;

		for (auto & pmediaformat :m_mediaformata)
		{

			size = pmediaformat->m_uFrameSize;

			framerate = pmediaformat->m_uFrameRate;

			auto & FRM = m_mapCaptureFormat[size];

			auto & STM = FRM[framerate];

			string subType(pmediaformat->m_strSubtypeName);

			auto & VN = STM[subType];

			VN.add(m_cCount);

			//STM[subType] = VN;

			//FRM[framerate] = STM;

			//m_mapCaptureFormat[int_size] = FRM;

			m_cCount++;

		}

	}


	bool device::is_setup()
	{

		return m_bSetup;

	}


	::memory * device::get_out_memory()
	{

		return nullptr;

	}


	void device::start_capturing()
	{

		if (!m_bSetup)
		{

			throw ::exception(error_wrong_state);

		}

		if (m_pthread)
		{

			return;

		}

		m_pthread = __allocate ::video_input_video_avfoundation::thread(this);

		m_pthread->initialize(this);

		m_pthread->branch();

	}


   void device::stop_capturing()
   {

      if (!m_bSetup)
      {

         return;

      }

      auto pthread = m_pthread;

      if (!pthread)
      {

         return;

      }

      avcapture_stop(pthread->m_ptyperefCapture);
//      auto pcallback = ;
//
//      if(pcallback)
//      {
//
//         pcallback->stop_capturing();
//
//      }

      m_pthread.release();

   }


   string device::get_id2()
	{

		auto psystem = system();

		return psystem->crypto_md5_text(m_strName);

	}


	bool device::get_pixels(color32_t * dstBuffer, bool flipRedAndBlue, bool flipImage)
	{

		bool success = false;

		unsigned int bytes = 4;

		//debug_print_out * pdebugprintout = &debug_print_out::get_instance();

		if (!is_raw_data_source())
		{

			
			//pdebugprintout->print_out(L"error: GetPixels() - Unable to grab frame for device %s\n", m_strName.c_str());

			return false;

		}

		auto pmemory =get_out_memory();

		if (pmemory)
		{

			unsigned int height = get_height();

			unsigned int width = get_width();

			unsigned int size = bytes * width * height;

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


	void device::set_format(::collection::index iIndex)
	{

		if (!m_bSetup)
      {

         initialize_device();

      }

//
//      m_pmemorymap.release();
//
//      /** Leonhard Oelke
//       * Initialize the v4l2 device
//       *
//       * This function:
//       * - tries to open the device
//       * - sets pixelformat and requested resolution
//       * - sets the requested framerate
//       * - maps the buffers
//       * - starts the capture thread
//       */
//
//      uint32_t input_caps;
//      int fps_num, fps_denom;
//
//      auto pmediaformat = m_mediaformata[iIndex];
//
//      m_iInput = m_inputa.is_empty()? 0:m_inputa[0]->m_iInput;
//      m_iStandard = m_standarda.is_empty() ? 0: m_standarda[0]->m_iStandard;
//      m_iPixFmt = pmediaformat->m_iPixFmt;
//      m_size = pmediaformat->m_size;
//      m_iFrameRateDenominator = pmediaformat->m_iFrameRateDenominator;
//      m_iFrameRateNumerator = pmediaformat->m_iFrameRateNumerator;
//
//      if (v4l2_set_input(m_iDevice, &m_iInput) < 0)
//      {
//
//         errorf("Unable to set input %d", m_iInput);
//
//         goto fail;
//
//      }
//
//      informationf("Input: %d", m_iInput);
//
//      if (v4l2_get_input_caps(m_iDevice, -1, &input_caps) < 0)
//      {
//
//         errorf("Unable to get input capabilities");
//
//         goto fail;
//
//      }
//
//      /* set video standard if supported */
//      if (input_caps & V4L2_IN_CAP_STD)
//      {
//
//         if (v4l2_set_standard(m_iDevice, &m_iStandard) < 0)
//         {
//
//            errorf("Unable to set video standard");
//
//            goto fail;
//
//         }
//
//         m_size.cx()  = -1;
//         m_size.cy()  = -1;
//         m_iFrameRateDenominator = -1;
//         m_iFrameRateNumerator = -1;
//
//      }
//
//      /* set dv timing if supported */
//      if (input_caps & V4L2_IN_CAP_DV_TIMINGS)
//      {
//
//         if (v4l2_set_dv_timing(m_iDevice, &m_iDvTiming) < 0)
//         {
//
//            errorf("Unable to set dv timing");
//
//            goto fail;
//
//         }
//
//         m_size.cx()  = -1;
//         m_size.cy()  = -1;
//         m_iFrameRateDenominator = -1;
//         m_iFrameRateNumerator = -1;
//
//      }
//
//      /* set pixel format and resolution */
//      if (v4l2_set_format(m_iDevice, &m_size.cx(), &m_size.cy(), &m_iPixFmt, &m_iLineSize) < 0)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         errorf("Unable to set format");
//
//         goto fail;
//
//      }
//
//      if (v4l2_pix_fmt_to_video_format(m_iPixFmt) == e_video_format_none)
//      {
//
//         errorf("Selected video format not supported");
//
//         goto fail;
//
//      }
//
//      informationf("Resolution: %greekdeltax%d", m_size.cx(), m_size.cy());
//      informationf("Pixelformat: %s", ::string((const char *) &m_iPixFmt, 5).c_str());
//      informationf("Linesize: %d Bytes", m_iLineSize);
//
//      /* set framerate */
//      if (v4l2_set_framerate(m_iDevice, &m_iFrameRateDenominator, &m_iFrameRateNumerator) < 0)
//      {
//
//         errorf("Unable to set framerate");
//
//         goto fail;
//
//      }
//
//      informationf("Framerate: %.2f fps", (float)m_iFrameRateDenominator / m_iFrameRateNumerator);
//
//      m_pmemorymap = __allocate memory_map(m_iDevice);
//
//      __construct_new(m_pmjpegdecoder);
//
//      return;
//
//      fail:
//
//      errorf("Initialization failed");
//
//      close();

	}


	string device::get_name()
	{
		
		return m_strName;

	}


   void device::_001_list_input()
   {

//      struct v4l2_input in;
//
//      memset(&in, 0, sizeof(in));
//
//      while (ioctl(VIDIOC_ENUMINPUT, &in) == 0)
//      {
//
//         auto pinput = __allocate input();
//
//         pinput->m_strDescription = (const char *) in.name;
//
//         pinput->m_iInput = in.index;
//
//         m_inputa.add(pinput);
//
//         informationf("Found input '%s' (Index %d)", in.name, in.index);
//
//         in.index++;
//
//      }
//
   }


   /*
   * List video standards for the device
   */
   void device::_002_list_standard()
   {

//      struct v4l2_standard std;
//
//      std.index = 0;
//
//      while (ioctl( VIDIOC_ENUMSTD, &std) == 0)
//      {
//
//         auto pstandard = __allocate standard();
//
//         pstandard->m_strDescription = (const char *) std.name;
//
//         pstandard->m_iStandard = std.id;
//
//         std.index++;
//
//      }
//
   }


   /*
   * List formats for device
   */
   void device::_003_list_pixel_format()
   {

//      struct v4l2_fmtdesc fmt;
//
//      fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//
//      fmt.index = 0;
//
//      while (ioctl(VIDIOC_ENUM_FMT, &fmt) == 0)
//      {
//
//         auto ppixelformat = __allocate pixel_format();
//
//         ppixelformat->m_iPixFmt = fmt.pixelformat;
//
//         ppixelformat->m_strDescription = (const char *) fmt.description;
//
//         if (fmt.flags & V4L2_FMT_FLAG_EMULATED)
//         {
//
//            ppixelformat->m_strDescription += " (Emulated)";
//
//         }
//
//         if (v4l2_pix_fmt_to_video_format(ppixelformat->m_iPixFmt) != e_video_format_none)
//         {
//
//            m_pixelformata.add(ppixelformat);
//
//            informationf("Pixelformat: %s (available)", ppixelformat->m_strDescription.c_str());
//
//         }
//         else
//         {
//
//            informationf("Pixelformat: %s (unavailable)", ppixelformat->m_strDescription.c_str());
//
//         }
//
//         fmt.index++;
//
//      }
//
   }


   void device::_004_list_resolution()
   {

      for(auto & ppixelformat : m_pixelformata)
      {

         ppixelformat->_list_resolution(this);

      }

   }


   void pixel_format::_list_resolution(device * pdevice)
   {

//      m_resolutiona.clear();
//
//      struct v4l2_frmsizeenum frmsize;
//
//      frmsize.pixel_format = m_iPixFmt;
//
//      frmsize.index = 0;
//
//      pdevice->ioctl(VIDIOC_ENUM_FRAMESIZES, &frmsize);
//
//      if(frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE)
//      {
//
//         while (pdevice->ioctl(VIDIOC_ENUM_FRAMESIZES, &frmsize) == 0)
//         {
//
//            auto presolution = __allocate resolution();
//
//            presolution->m_size.cx() = frmsize.discrete.width;
//
//            presolution->m_size.cy() = frmsize.discrete.height;
//
//            presolution->m_strDescription.formatf("%greekdeltax%d", presolution->m_size.cx(), presolution->m_size.cy());
//
//            m_resolutiona.add(presolution);
//
//            frmsize.index++;
//
//         }
//
//      }
//      else
//      {
//
//         information() << "Stepwise and Continuous framesizes are currently hardcoded";
//
//         for (const int *packed = v4l2_framesizes; *packed; ++packed)
//         {
//
//            auto presolution = __allocate resolution();
//
//            presolution->m_size.cx() = second_unsigned_short(*packed);
//
//            presolution->m_size.cy() = first_unsigned_short(*packed);
//
//            presolution->m_strDescription.formatf("%greekdeltax%d", presolution->m_size.cx(), presolution->m_size.cy());
//
//            m_resolutiona.add(presolution);
//
//         }
//
//      }

   }


   void device::_005_list_frame_rate()
   {

//      for(auto & ppixelformat : m_pixelformata)
//      {
//
//         for(auto & presolution : ppixelformat->m_resolutiona)
//         {
//
//            presolution->_list_frame_rate(ppixelformat, this);
//
//         }
//
//      }

   }


   void device::_006_erase_resolution_with_empty_frame_rate_list()
   {

//      for (auto & ppixelformat: m_pixelformata)
//      {
//
//         for (::collection::index iResolution = 0; iResolution <  ppixelformat->m_resolutiona.get_count();)
//         {
//
//            auto presolution = ppixelformat->m_resolutiona[iResolution];
//
//            if (presolution->m_frameratea.is_empty())
//            {
//
//               ppixelformat->m_resolutiona.erase_at(iResolution);
//
//            }
//            else
//            {
//
//               iResolution++;
//
//            }
//
//         }
//
//      }

   }


   void device::_007_erase_pixel_format_with_empty_resolution_list()
   {

      for (::collection::index iPixelFormat = 0; iPixelFormat <  m_pixelformata.get_count();)
      {

         auto ppixelformat = m_pixelformata[iPixelFormat];

         if (ppixelformat->m_resolutiona.is_empty())
         {

            m_pixelformata.erase_at(iPixelFormat);

         }
         else
         {

            iPixelFormat++;

         }

      }

   }


   void resolution::_list_frame_rate(pixel_format * ppixelformat, device * pdevice)
   {

//      struct v4l2_frmivalenum frmival;
//
//      frmival.pixel_format = ppixelformat->m_iPixFmt;
//
//      frmival.width = m_size.cx();
//
//      frmival.height = m_size.cy();
//
//      frmival.index = 0;
//
//      pdevice->ioctl(VIDIOC_ENUM_FRAMEINTERVALS, &frmival);
//
//      if(frmival.type == V4L2_FRMIVAL_TYPE_DISCRETE)
//      {
//
//         while (pdevice->ioctl(VIDIOC_ENUM_FRAMEINTERVALS, &frmival) == 0)
//         {
//
//            auto pframerate = __allocate frame_rate();
//
//            pframerate->m_iDenominator = frmival.discrete.denominator;
//
//            pframerate->m_iNumerator = frmival.discrete.numerator;
//
//            pframerate->m_fFps = (float) pframerate->m_iDenominator / (float) pframerate->m_iNumerator;
//
//            pframerate->m_strDescription.formatf("%.2f", pframerate->m_fFps);
//
//            m_frameratea.add(pframerate);
//
//            frmival.index++;
//
//         }
//
//      }
//      else
//      {
//
//         information() << "Stepwise and Continuous framerates are currently hardcoded";
//
//         for (const int *packed = v4l2_framerates; *packed; ++packed)
//         {
//
//            auto pframerate = __allocate frame_rate();
//
//            pframerate->m_iDenominator = first_unsigned_short(*packed);
//
//            pframerate->m_iNumerator = second_unsigned_short(*packed);
//
//            pframerate->m_fFps = (float) pframerate->m_iDenominator / (float) pframerate->m_iNumerator;
//
//            pframerate->m_strDescription.formatf("%.2f", pframerate->m_fFps);
//
//            m_frameratea.add(pframerate);
//
//         }
//
//      }

   }


   void device::enumerate_capture_formats()
	{

      _001_list_input();

      _002_list_standard();

      _003_list_pixel_format();

      _004_list_resolution();

      _005_list_frame_rate();

      _006_erase_resolution_with_empty_frame_rate_list();

      _007_erase_pixel_format_with_empty_resolution_list();

      for (auto & ppixelformat: m_pixelformata)
      {

         for (auto & presolution: ppixelformat->m_resolutiona)
         {

            for (auto & pframerate: presolution->m_frameratea)
            {

               auto pmediaformat = __create_new < ::video_input::media_format >();

               pmediaformat->m_iPixFmt = ppixelformat->m_iPixFmt;
               pmediaformat->m_size = presolution->m_size;
               pmediaformat->m_iFrameRateDenominator = pframerate->m_iDenominator;
               pmediaformat->m_iFrameRateNumerator = pframerate->m_iNumerator;

               m_mediaformata.add(pmediaformat);

            }

         }

      }

   }


   void device::_start_capture()
   {

//      enum v4l2_buf_type type;
//
//      struct v4l2_buffer enq;
//
//      memset(&enq, 0, sizeof(enq));
//      enq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//      enq.memory = V4L2_MEMORY_MMAP;
//
//      for (enq.index = 0; enq.index < m_pmemorymap->m_itema.get_size(); ++enq.index)
//      {
//
//         if (v4l2_ioctl(m_iDevice, VIDIOC_QBUF, &enq) < 0)
//         {
//
//            //blog(LOG_ERROR, "unable to queue buffer");
//            throw ::exception(error_failed, "unable to queue buffer");
//
//         }
//
//      }
//
//      m_iBufferedCount = m_pmemorymap->m_itema.get_size();
//
//      type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//
//      if (v4l2_ioctl(m_iDevice, VIDIOC_STREAMON, &type) < 0)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         //blog(LOG_ERROR, "unable to start stream");
//
//         auto estatus = cerrornumber.estatus();
//
//         throw ::exception(estatus, "unable to start stream");
//
//      }
//

   }


   void device::_stop_capture()
   {

//      enum v4l2_buf_type type;
//
//      type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//
//      if (v4l2_ioctl(m_iDevice, VIDIOC_STREAMOFF, &type) < 0)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         if(iErrNo != ENODEV)
//         {
//
//            auto estatus = cerrornumber.estatus();
//
//            throw ::exception(error_failed, "unable to stop stream");
//
//         }
//
//      }
//

   }


   void device::_reset_capture()
   {

      information() << "attempting to reset capture";

      _stop_capture();

      _start_capture();

   }


#ifdef _DEBUG


   void device::_query_all_buffers()
   {

//      struct v4l2_buffer buf;
//
//      informationf("attempting to read buffer data for %ld buffers", m_pmemorymap->m_itema.get_count());
//
//      for (uint_fast32_t i = 0; i < m_pmemorymap->m_itema.get_count(); i++)
//      {
//
//         buf.index = i;
//         buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//         buf.memory = V4L2_MEMORY_MMAP;
//
//         if (v4l2_ioctl(m_iDevice, VIDIOC_QUERYBUF, &buf) < 0)
//         {
//            //blog(LOG_DEBUG,
//            //   "failed to read buffer data for buffer #%ld", i);
//         }
//         else
//         {
//            //blog(LOG_DEBUG,
//            //   "query buf #%ld info: ts: %06ld buf id #%d, flags 0x%08X, seq #%d, len %d, used %d",
//            /// i, buf.timestamp.tv_usec, buf.index, buf.flags,
//            //buf.sequence, buf.length, buf.bytesused);
//         }
//
//      }

      //return 0;
   }
#endif



} // namespace video_input_video_avfoundation



