#pragma once

//#include <guiddef.h>

//#include "video_input_video_for_linux.h"

//struct IMFMediaType;

namespace video_input_video_for_linux
{

	/// Class for parsing info from IMFMediaType into the local media
	class format_reader
	{
	public:
		//static ::video_input::media_format Read(IMFMediaType * pmediatype);
		~format_reader(void);
	private:
		format_reader(void);
	};



} // namespace video_input_video_for_linux



