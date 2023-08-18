// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "device.h"
#include "media_format.h"
#include "render.h"
#include "apex/platform/system.h"
#include "aura/graphics/image/image.h"

//#pragma comment(lib, "Strmiids")


namespace video_input
{


	device::device() : 
		m_bSetup(false),
		m_elock(e_lock_open), 
		m_emergencystopcallback(NULL)
	{

      m_item.m_eelement = e_element_item;
	   m_edevicestate = e_device_state_initial;

	}


	device::~device()
	{

		close();

	}


	void device::set_camera_parameters(camera_parameters parameters)
	{

		if (m_bSetup)
		{

			//if (m_pmediasource)
			//{

			//	::u32 shift = sizeof(parameter);

			//	parameter * pParametr = (parameter *)(&parameters);

			//	parameter * pPrevParametr = (parameter *)(&m_cameraparametersPrevious);

			//	comptr<IAMVideoProcAmp> pProcAmp;
			//	HRESULT hr = m_pmediasource->QueryInterface(IID_PPV_ARGS(&pProcAmp));

			//	if (SUCCEEDED(hr))
			//	{

			//		for (::u32 i = 0; i < 10; i++)
			//		{

			//			if (pPrevParametr[i].m_lCurrentValue != pParametr[i].m_lCurrentValue || pPrevParametr[i].m_lFlag != pParametr[i].m_lFlag)
			//			{

			//				hr = pProcAmp->Set(VideoProcAmp_Brightness + i, pParametr[i].m_lCurrentValue, pParametr[i].m_lFlag);

			//			}

			//		}

			//	}

			//	comptr<IAMCameraControl> pProcControl;

			//	hr = m_pmediasource->QueryInterface(IID_PPV_ARGS(&pProcControl));

			//	if (SUCCEEDED(hr))
			//	{

			//		for (::u32 i = 0; i < 7; i++)
			//		{

			//			if (pPrevParametr[10 + i].m_lCurrentValue != pParametr[10 + i].m_lCurrentValue || pPrevParametr[10 + i].m_lFlag != pParametr[10 + i].m_lFlag)
			//			{

			//				hr = pProcControl->Set(CameraControl_Pan + i, pParametr[10 + i].m_lCurrentValue, pParametr[10 + i].m_lFlag);

			//			}

			//		}

			//	}

			//	m_cameraparametersPrevious = parameters;

			//}

		}

	}


	camera_parameters device::get_camera_parameters()
	{

		camera_parameters out;

		//if (m_bSetup)
		//{

		//	if (m_pmediasource)
		//	{

		//		::u32 shift = sizeof(parameter);

		//		parameter * pParametr = (parameter *)(&out);

		//		comptr<IAMVideoProcAmp> pProcAmp;

		//		HRESULT hr = m_pmediasource->QueryInterface(IID_PPV_ARGS(&pProcAmp));

		//		if (SUCCEEDED(hr))
		//		{

		//			for (::u32 i = 0; i < 10; i++)
		//			{

		//				parameter temp;

		//				hr = pProcAmp->GetRange(VideoProcAmp_Brightness + i, &temp.m_lMin, &temp.m_lMax, &temp.m_lStep, &temp.m_lDefault, &temp.m_lFlag);

		//				if (SUCCEEDED(hr))
		//				{

		//					long currentValue = temp.m_lDefault;

		//					hr = pProcAmp->Get(VideoProcAmp_Brightness + i, &currentValue, &temp.m_lFlag);

		//					temp.m_lCurrentValue = currentValue;

		//					pParametr[i] = temp;

		//				}

		//			}

		//		}

		//		comptr<IAMCameraControl> pProcControl;

		//		hr = m_pmediasource->QueryInterface(IID_PPV_ARGS(&pProcControl));

		//		if (SUCCEEDED(hr))
		//		{

		//			for (::u32 i = 0; i < 7; i++)
		//			{

		//				parameter temp;

		//				hr = pProcControl->GetRange(CameraControl_Pan + i, &temp.m_lMin, &temp.m_lMax, &temp.m_lStep, &temp.m_lDefault, &temp.m_lFlag);

		//				if (SUCCEEDED(hr))
		//				{

		//					long currentValue = temp.m_lDefault;

		//					hr = pProcAmp->Get(CameraControl_Pan + i, &currentValue, &temp.m_lFlag);

		//					temp.m_lCurrentValue = currentValue;

		//					pParametr[10 + i] = temp;

		//				}

		//			}

		//		}

		//	}

		//}

		return out;

	}


	//long device::resetDevice(IMFActivate * pActivate)
	//{

	//	HRESULT hr = E_FAIL;

	//	m_mediaformata.clear();

	//	if (pActivate)
	//	{

	//		cotaskptr < PWCHAR > pFriendlyName;

	//		hr = pActivate->GetAllocatedString(
	//			MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
	//			&pFriendlyName,
	//			NULL
	//		);

	//		m_strName = pFriendlyName;

	//		hr = pActivate->ActivateObject(__uuidof(IMFMediaSource), (void **) &m_pmediasource);

	//		if (FAILED(hr))
	//		{

	//			m_strName.empty();

	//			debug_print_out * pdebugprintout = &debug_print_out::get_instance();

	//			pdebugprintout->print_out(L"VIDEODEVICE %i: IMFMediaSource interface cannot be created \n", m_uCurrentNumber);

	//			return hr;

	//		}

	//		enumerateCaptureFormats();

	//		buildLibraryofTypes();

	//	}

	//	return hr;

	//}

	//long device::readInfoOfDevice(IMFActivate * pActivate, ::u32 Num)
	//{
	//	HRESULT hr = -1;

	//	m_uCurrentNumber = Num;

	//	hr = resetDevice(pActivate);

	//	return hr;

	//}


	//long device::checkDevice(IMFAttributes * pAttributes, IMFActivate ** pDevice)
	//{
	//	HRESULT hr = S_OK;

	//	IMFActivate ** ppDevices = NULL;

	//	debug_print_out * pdebugprintout = &debug_print_out::get_instance();

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

	//						pdebugprintout->print_out(L"VIDEODEVICE %i: Chosen device cannot be found \n", m_uCurrentNumber);

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
	//					pdebugprintout->print_out(L"VIDEODEVICE %i: Name of device cannot be gotten \n", m_uCurrentNumber);
	//				}

	//			}
	//			else
	//			{
	//				pdebugprintout->print_out(L"VIDEODEVICE %i: Number of devices more than corrent number of the device \n", m_uCurrentNumber);

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
	//			hr = -1;
	//	}
	//	else
	//	{
	//		pdebugprintout->print_out(L"VIDEODEVICE %i: List of DeviceSources cannot be enumerated \n", m_uCurrentNumber);
	//	}

	//	return hr;
	//}


	void device::initialize_device()
	{

		//HRESULT hr = -1;

		//comptr<IMFAttributes > pAttributes;

		//comptr<IMFActivate>  pactivate;

		//debug_print_out * pdebugprintout = &debug_print_out::get_instance();

		//hr = MFCreateAttributes(&pAttributes, 1);

		//if (SUCCEEDED(hr))
		//{

		//	hr = pAttributes->SetGUID(
		//		MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
		//		MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
		//	);
		//}

		//if (SUCCEEDED(hr))
		//{

		//	hr = checkDevice(pAttributes, &pactivate);

		//	if (SUCCEEDED(hr) && pactivate)
		//	{
		//		
		//		hr = pactivate->ActivateObject(
		//			__uuidof(IMFMediaSource),
		//			(void **)&m_pmediasource
		//		);

		//		if (SUCCEEDED(hr))
		//		{

		//		}

		//	}
		//	else
		//	{
		//		pdebugprintout->print_out(L"VIDEODEVICE %i: Device there is not \n", m_uCurrentNumber);
		//	}
		//}
		//else
		//{

		//	pdebugprintout->print_out(L"VIDEODEVICE %i: The attribute of video cameras cannot be getting \n", m_uCurrentNumber);

		//}

		//return hr;

	}


	::pointer<media_format>device::get_media_format(::index iIndex)
	{

		if (iIndex < 0 || iIndex >= m_mediaformata.size())
		{

			return nullptr;

		}

		return m_mediaformata[iIndex];

	}


	::count device::get_media_format_count()
	{

		return m_mediaformata.size();

		//return 0;

	}


	void device::close()
	{

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


	::index device::find_argb_32_format()
	{

		::index iBest = 0;

		::i64 iScoreMax = 0;

		for (::index i = 0; i < m_mediaformata.get_count(); i++)
		{

			auto pmediaformat = m_mediaformata[i];

			int iSampleSize = pmediaformat->m_uSampleSize;

			//int cx = pmediaformat->m_size.cx();

			//int cy = pmediaformat->m_size.cy();

			//int iFrameRate = pmediaformat->m_uFrameRate;

         if (iSampleSize == 32)
         {

            ::i64 iScore = pmediaformat->m_size.area() * pmediaformat->m_uFrameRate;

            if (iScore > iScoreMax)
            {

               iBest = i;

               iScoreMax = iScore;

            }

         }

		}

		return iBest;

	}


	//IMFMediaSource * device::get_media_source()
	//{

	//	IMFMediaSource * out = NULL;

	//	if (m_elock == e_lock_open)
	//	{

	//		m_elock = e_lock_media_source;

	//		out = m_pmediasource;

	//	}

	//	return out;

	//}


	int device::findType(::u32 size, ::u32 frameRate)
	{

		if (m_mapCaptureFormat.size() == 0)
		{

			return 0;

		}

		return 0;

		//auto & FRM = m_mapCaptureFormat[size_i32];

		//if (FRM.size() == 0)
		//{

		//	return 0;

		//}

		//::u32 frameRateMax = 0;  
		//
		//subtype_map * psubtypemap = nullptr;

		//if (frameRate == 0)
		//{

		//	for (auto & pair :FRM)
		//	{

		//		if (pair.element1() >= frameRateMax)
		//		{

		//			frameRateMax = pair.element1();

		//			psubtypemap = &pair.element2();

		//		}

		//	}

		//}
		//else
		//{

		//	for (auto & pair : FRM)
		//	{

		//		if (pair.element1() >= frameRateMax)
		//		{

		//			if (frameRate > pair.element1())
		//			{

		//				frameRateMax = pair.element1();

		//				psubtypemap = &pair.element2();

		//			}

		//		}

		//	}

		//}

		//if (!psubtypemap || psubtypemap->is_empty())
		//{

		//	return 0;

		//}

		//auto it = psubtypemap->begin();

		//auto n = it->element2();

		//if (n.size() == 0)
		//{

		//	return 0;

		//}

		//return n[0];

	}


	void device::buildLibraryofTypes()
	{

		//::u32 size;

		//::u32 framerate;

		//int m_cCount = 0;

		//for (auto & mediatype :m_mediaformata)
		//{

		//	size = mediatype.m_uFrameSize;

		//	framerate = mediatype.m_uFrameRate;

		//	auto & FRM = m_mapCaptureFormat[size_i32];

		//	auto & STM = FRM[framerate];

		//	string subType(mediatype.m_strSubtypeName);

		//	auto & VN = STM[subType];

		//	VN.add(m_cCount);

		//	//STM[subType] = VN;

		//	//FRM[framerate] = STM;

		//	//m_mapCaptureFormat[size_i32] = FRM;

		//	m_cCount++;

		//}

	}


	//long device::setDeviceFormat(IMFMediaSource * pSource, unsigned long  dwFormatIndex)
	//{

	//	comptr<IMFPresentationDescriptor> ppresentationdescriptor;
	//	comptr < IMFStreamDescriptor> pstreamdescriptor;
	//	comptr <IMFMediaTypeHandler > pmediatypehandler;
	//	comptr < IMFMediaType> pmediatype;

	//	HRESULT hr = pSource->CreatePresentationDescriptor(&ppresentationdescriptor);

	//	if (FAILED(hr))
	//	{

	//		return hr;

	//	}

	//	BOOL fSelected;
	//	hr = ppresentationdescriptor->GetStreamDescriptorByIndex(0, &fSelected, &pstreamdescriptor);
	//	if (FAILED(hr))
	//	{
	//		return hr;
	//	}

	//	hr = pstreamdescriptor->GetMediaTypeHandler(&pmediatypehandler);
	//	if (FAILED(hr))
	//	{
	//		return hr;
	//	}

	//	hr = pmediatypehandler->GetMediaTypeByIndex((DWORD)dwFormatIndex, &pmediatype);
	//	if (FAILED(hr))
	//	{
	//		return hr;
	//	}

	//	hr = pmediatypehandler->SetCurrentMediaType(pmediatype);

	//	return hr;

	//}


	bool device::is_setup()
	{

		return m_bSetup;

	}


	::memory * device::get_out_memory()
	{

		if (!m_bSetup) return NULL;

		//if (m_pthreadImageGrabber.get())
		//{
		//
		//	return m_pthreadImageGrabber->get_image_grabber()->get_memory();

		//}
		//else
		//{
		//	debug_print_out * pdebugprintout = &debug_print_out::get_instance();

		//	pdebugprintout->print_out(L"VIDEODEVICE %i: The instance of image_grabber_thread class does not exist  \n", m_uCurrentNumber);
		//}

		return nullptr;

	}


	//bool device::is_frame_new()
	//{

	//	if (!m_bSetup)
	//	{

	//		return false;

	//	}

	//	if (is_media_source())
	//	{

	//		return false;

	//	}

	//	if (m_elock == e_lock_raw_data || m_elock == e_lock_open)
	//	{
	//		if (m_elock == e_lock_open)
	//		{
	//			m_elock = e_lock_raw_data;

	//			//image_grabber_thread * temp;

	//			//HRESULT hr = image_grabber_thread::CreateInstance(&temp, m_pmediasource, m_uCurrentNumber, m_emergencystopcallback);

	//			//if (FAILED(hr))
	//			//{
	//			//	debug_print_out * pdebugprintout = &debug_print_out::get_instance();

	//			//	pdebugprintout->print_out(L"VIDEODEVICE %i: The instance of image_grabber_thread class cannot be created.\n", m_uCurrentNumber);

	//			//	return false;
	//			//}
	//			//m_pthreadImageGrabber.reset(temp);


	//			////m_pthreadImageGrabber->set_emergency_stop_event();

	//			////m_pthreadImageGrabber->start();

	//			return false;
	//		}

	//		//if (m_pthreadImageGrabber.get())
	//		//{

	//		//	return m_pthreadImageGrabber->get_image_grabber()->get_memory()->m_eobject.is(e_object_changed);

	//		//}

	//	}

	//	return false;
	//}


	string device::get_id2()
	{

		auto psystem = acmesystem()->m_papexsystem;

		return psystem->crypto_md5_text(m_strName);

	}


	bool device::get_pixels(color32_t * dstBuffer, bool flipRedAndBlue, bool flipImage)
	{
		bool success = false;

		::u32 bytes = 4;

		if (!is_raw_data_source())
		{

		
			return false;

		}

		auto pmemory =get_out_memory();

		if (pmemory)
		{
			::u32 height = get_height();
			::u32 width = get_width();

			::u32 size = bytes * width * height;

			if (size == pmemory->size())
			{

				processPixels((color32_t *)pmemory->data(), dstBuffer, width, height, bytes, flipRedAndBlue, flipImage);

				pmemory->m_eflagElement -= e_flag_changed;

				success = true;

			}

		}

		return true;

	}


	bool device::is_media_source()
	{

		if (m_elock == e_lock_media_source)
		{

			return true;

		}

		return false;

	}


	bool device::is_raw_data_source()
	{
		
		if (m_elock == e_lock_raw_data)
		{

			return true;

		}

		return false;

	}


	void device::start_capturing()
	{


	}


	void device::stop_capturing()
	{

	   if (m_prender)
	   {

		  if (m_prender->m_pimage.ok())
		  {

			 m_prender->m_pimage->clear(::color::transparent);

		  }

	   }

	}


	void device::set_format(::index iIndex)
	{

		initialize_device();

		m_size = m_mediaformata[iIndex]->m_size;

	}


	::index device::find_format(::u32 w, ::u32 h, ::u32 idealFramerate)
	{

		//::u32 atom = findType(w * h, idealFramerate);

		//return setup_device(atom);

		return -1;

	}

	
	string device::get_name()
	{
		
		return m_strName;

	}


	void device::enumerate_capture_formats()
	{

	}


	render * device::get_render()
	{

		if (!m_prender)
		{

			create_render();

		}


		return m_prender;

	}


} // namespace video_input


