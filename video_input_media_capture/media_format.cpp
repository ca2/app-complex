// Created on 2022-03-12 by camilo 14:11 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "media_format.h"


namespace video_input_media_capture
{



	media_format::media_format()
	{

		Clear();

	}


	media_format::~media_format()
	{

	}


	void media_format::Clear() 
	{

		::video_input::media_format::Clear();

   	m_uYuvMatrix = 0;

		m_uVideoLighting = 0;

		m_uDefaultStride = 0;

		m_uVideoChromaSiting = 0;

		m_uFixedSizeSamples = 0;

		m_uVideoNominalRange = 0;

		m_uFrameRateLow = 0;

		m_uPixelAspectRatio = 0;

		m_uPixelAspectRatioLow = 0;

		m_uAllSamplesIndependent = 0;

		m_uFrameRateRangeMin = 0;

		m_uFrameRateRangeMinLow = 0;

		m_uVideoPrimaries = 0;

		m_uInterlaceMode = 0;

		m_uFrameRateRangeMax = 0;

		m_uFrameRateRangeMaxLow = 0;

		//memset(&m_guidMajorType, 0, sizeof(GUID));

		//memset(&m_guidAmFormatType, 0, sizeof(GUID));

		//memset(&m_guidSubtype, 0, sizeof(GUID));


	}


} // namespace video_input_media_capture



