// Created on 2022-03-12 by camilo 14:02 BRT <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/size.h"


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


      ::int_size			m_size;
		unsigned int					m_uSampleSize;
		unsigned int					m_uFrameRate;
		unsigned int					m_uFrameSize;

      string			   m_strSubtypeName;



		media_format();
		~media_format() override;


		virtual void Clear();


	};


} // namespace video_input




