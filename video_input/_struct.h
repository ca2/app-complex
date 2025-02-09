// Global structs from video.h by camilo on 2022-09-08 22:10 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/geometry2d/size.h"


//#ifndef GUID_DEFINED
//#define GUID_DEFINED
//#if defined(__midl)
//typedef struct {
//	unsigned long  Data1;
//	unsigned short Data2;
//	unsigned short Data3;
//	unsigned char           Data4[8];
//} GUID;
//#else
//typedef struct _GUID {
//	unsigned long  Data1;
//	unsigned short Data2;
//	unsigned short Data3;
//	unsigned char  Data4[8];
//} GUID;
//#endif
//#endif

namespace video_input
{



	// Structure for collecting info about one parametr of current video device
	struct CLASS_DECL_VIDEO_INPUT parameter
	{

		long m_lCurrentValue;

		long m_lMin;

		long m_lMax;

		long m_lStep;

		long m_lDefault;

		long m_lFlag;

		parameter();
	};

	// Structure for collecting info about 17 parameters of current video device
	struct CLASS_DECL_VIDEO_INPUT camera_parameters
	{
		parameter Brightness;
		parameter Contrast;
		parameter Hue;
		parameter Saturation;
		parameter Sharpness;
		parameter Gamma;
		parameter ColorEnable;
		parameter WhiteBalance;
		parameter BacklightCompensation;
		parameter Gain;


		parameter Pan;
		parameter Tilt;
		parameter Roll;
		parameter Zoom;
		parameter Exposure;
		parameter Iris;
		parameter Focus;
	};


} // namespace video_input


struct video_frame;

/* Base video output component.  Use this to create a video output track. */

struct video_output;
typedef struct video_output video_t;


//struct video_data {
//   unsigned char *data[max_av_planes];
//   unsigned int linesize[max_av_planes];
//   unsigned long long timestamp;
//};

struct video_output_info
{

	string m_strName;

   enum_video_format m_eformat;
   unsigned int m_uFpsNumerator;
   unsigned int m_uFpsDenominator;
	::int_size m_size;
   memsize m_memsizeCache;

   enum_video_colorspace m_ecolorspace;
   enum_video_range_type m_erangetype;
};




struct e_video_scale_info {
   enum_video_format m_eformat;
   ::int_size m_size;
   enum_video_range_type m_erangetype;
   enum_video_colorspace m_ecolorspace;
};
