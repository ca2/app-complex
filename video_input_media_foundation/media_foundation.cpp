// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"

#include "_video_input.h"


namespace video_input_media_foundation
{

	media_foundation::media_foundation()
	{


	}
		
		
		void media_foundation::initialize_media_foundation(::particle * pparticle);)
	{

		m_pvideoinput = pvideoinput;

		HRESULT hr = MFStartup(MF_VERSION);

		if (FAILED(hr))
		{
			debug_print_out * pdebugprintout = &debug_print_out::get_instance();

			pdebugprintout->print_out(L"MEDIA FOUNDATION: It cannot be created!!!\n");
		}
	}


	media_foundation::~media_foundation(void)
	{
		HRESULT hr = MFShutdown();

		if (FAILED(hr))
		{
			
			debug_print_out * pdebugprintout = &debug_print_out::get_instance();

			pdebugprintout->print_out(L"MEDIA FOUNDATION: Resources cannot be released\n");

		}

	}


	bool media_foundation::buildListOfDevices()
	{
		HRESULT hr = S_OK;

		comptr<IMFAttributes> pAttributes;

		CoInitialize(NULL);

		hr = MFCreateAttributes(&pAttributes, 1);

		if (SUCCEEDED(hr))
		{

			hr = pAttributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);

		}

		if (SUCCEEDED(hr))
		{

			hr = m_pvideoinput->initDevices(pAttributes);

		}
		else
		{

			debug_print_out * pdebugprintout = &debug_print_out::get_instance();

			pdebugprintout->print_out(L"MEDIA FOUNDATION: The access to the video cameras denied\n");

		}

		//SafeReleaseAllCount(&pAttributes);

		return (SUCCEEDED(hr));

	}


	//media_foundation & media_foundation::get_instance()
	//{
	//	static media_foundation instance;

	//	return instance;
	//}


} // namespace video_input_media_foundation


