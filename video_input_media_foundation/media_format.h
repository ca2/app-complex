// Created on 2022-03-12 by camilo 14:04 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "app-complex/video_input/media_format.h"


namespace video_input_media_foundation
{


	// Structure for collecting info about types of video, which are supported by current video device
	class CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION media_format :
		virtual public ::video_input::media_format
	{
	public:
		//int m_iPixFmt;
		//int m_iFrameRateDenominator;
		//int m_iFrameRateNumerator;
		::u32				m_uYuvMatrix;
		::u32				m_uVideoLighting;
		::u32				m_uDefaultStride;
		::u32				m_uVideoChromaSiting;
		GUID				m_guidAmFormatType;
		string			m_strAmFormatTypeName;
		::u32				m_uFixedSizeSamples;
		::u32				m_uVideoNominalRange;
		::u32				m_uFrameRateLow;
		::u32				m_uPixelAspectRatio;
		::u32				m_uPixelAspectRatioLow;
		::u32				m_uAllSamplesIndependent;
		::u32				m_uFrameRateRangeMin;
		::u32				m_uFrameRateRangeMinLow;
		::u32				m_uVideoPrimaries;
		::u32				m_uInterlaceMode;
		::u32				m_uFrameRateRangeMax;
		::u32				m_uFrameRateRangeMaxLow;
		GUID				m_guidMajorType;
		string			m_strMajorTypeName;
		GUID				m_guidSubtype;

		media_format();
		~media_format() override;


		void Clear() override;


	};



} // namespace video_input_media_foundation




