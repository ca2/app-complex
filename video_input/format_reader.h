#pragma once

namespace video_input
{

	/// Class for parsing info from IMFMediaType into the local media_format
	class CLASS_DECL_VIDEO_INPUT format_reader
	{
	public:
		//static media_format Read(IMFMediaType * pmediatype);
		~format_reader(void);
	private:
		format_reader(void);
	};



} // namespace video_input



