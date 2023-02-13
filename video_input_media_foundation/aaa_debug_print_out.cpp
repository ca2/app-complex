// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"

#include "_video_input_media_foundation.h"


debug_print_out::debug_print_out(void):m_bVerbose(true)
{
}

debug_print_out::~debug_print_out(void)
{
}

debug_print_out& debug_print_out::get_instance()
{
	static debug_print_out instance;

	return instance;
}

void debug_print_out::print_out(const wchar_t *format, ...)
{
	if(m_bVerbose)
	{
		int i = 0;

		wchar_t *p = NULL;

		va_list args;

		va_start(args, format);

		bool state = true;

	
		if(wcscmp(format, L"%i"))
		{
				i = va_arg (args, int);
		}
 
		if(wcscmp(format, L"%s"))
		{
				p = va_arg (args, wchar_t *);
		}
		
		wprintf(format, i,p);

		va_end (args);
	}
}

void debug_print_out::set_verbose(bool state)
{
	m_bVerbose = state;
}
