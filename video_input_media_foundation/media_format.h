// Created on 2022-03-12 by camilo 14:04 BRT <3ThomasBorregaardSorensen!!
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
		unsigned int				m_uYuvMatrix;
		unsigned int				m_uVideoLighting;
		unsigned int				m_uDefaultStride;
		unsigned int				m_uVideoChromaSiting;
		GUID				m_guidAmFormatType;
		string			m_strAmFormatTypeName;
		unsigned int				m_uFixedSizeSamples;
		unsigned int				m_uVideoNominalRange;
		unsigned int				m_uFrameRateLow;
		unsigned int				m_uPixelAspectRatio;
		unsigned int				m_uPixelAspectRatioLow;
		unsigned int				m_uAllSamplesIndependent;
		unsigned int				m_uFrameRateRangeMin;
		unsigned int				m_uFrameRateRangeMinLow;
		unsigned int				m_uVideoPrimaries;
		unsigned int				m_uInterlaceMode;
		unsigned int				m_uFrameRateRangeMax;
		unsigned int				m_uFrameRateRangeMaxLow;
		GUID				m_guidMajorType;
		string			m_strMajorTypeName;
		GUID				m_guidSubtype;

		media_format();
		~media_format() override;


		void Clear() override;


	};



} // namespace video_input_media_foundation




