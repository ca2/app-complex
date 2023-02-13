// Created on 2022-03-12 by camilo 14:02 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"


namespace video_input
{


	// Structure for collecting info about types of video, which are supported by current video device
	class CLASS_DECL_VIDEO_INPUT media_format :
		virtual public ::matter
	{
	public:


		enum_format			m_eformat;


      int               m_iPixFmt;
      int               m_iFrameRateDenominator;
      int               m_iFrameRateNumerator;


      ::size_i32			m_size;
		::u32					m_uSampleSize;
		::u32					m_uFrameRate;
		::u32					m_uFrameSize;

      string			   m_strSubtypeName;



		media_format();
		~media_format() override;


		virtual void Clear();


	};


} // namespace video_input




