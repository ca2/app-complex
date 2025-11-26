// Created from _struct.cpp by camilo on 2022-03-12 14:27 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "media_format.h"


namespace video_input
{


	media_format::media_format()
	{

		Clear();

	}

	media_format::~media_format()
	{
		Clear();
	}


	void media_format::Clear()
	{

		m_eformat = e_format_none;

		m_size.cx = 0;

		m_size.cy = 0;

		m_uFrameRate = 0;

		m_uSampleSize = 0;

		m_uFrameSize = 0;



	}


} // namespace video_input



