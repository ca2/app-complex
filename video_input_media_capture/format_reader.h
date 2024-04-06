#pragma once

#include <guiddef.h>

//#include "video_input_media_capture.h"

struct IMFMediaType;

namespace video_input_media_capture
{

	/// Class for parsing info from IMFMediaType into the local media
	class format_reader :
		virtual public ::object
	{
	public:
		
		::pointer<::video_input::media_format> Read(IMFMediaType * pmediatype);
		
		~format_reader(void);
		format_reader(void);

	};



} // namespace video_input_media_capture



