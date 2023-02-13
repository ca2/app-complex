/*
Copyright (C) 2014 by Leonhard Oelke <leonhard@in-verted.de>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "framework.h"
#include "acme/exception/resource.h"
#include <sys/mman.h>

//#include <util/bmem.h>

#include "helpers.h"

//#define blog(level, msg, ...) blog(level, "v4l2-helpers: " msg, ##__VA_ARGS__)


namespace video_input_video_for_linux
{


   memory_map::memory_map(int_fast32_t iDevice)
   {
      struct v4l2_requestbuffers req;
      struct v4l2_buffer map;

      memset(&req, 0, sizeof(req));
      req.count = 4;
      req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      req.memory = V4L2_MEMORY_MMAP;

      if (v4l2_ioctl(iDevice, VIDIOC_REQBUFS, &req) < 0)
      {
         //blog(LOG_ERROR, "Request for buffers failed !");
         throw resource_exception("Request for buffers failed !");
      }

      if (req.count < 2)
      {
         //blog(LOG_ERROR, "Device returned less than 2 buffers");
         throw resource_exception("Device returned less than 2 buffers");
      }

      //buf->count = req.count;
      //buf->info = ne (req.count * sizeof(struct v4l2_mmap_info));

      memset(&map, 0, sizeof(map));
      map.type = req.type;
      map.memory = req.memory;

      for (map.index = 0; map.index < req.count; ++map.index)
      {
         if (v4l2_ioctl(iDevice, VIDIOC_QUERYBUF, &map) < 0)
         {
            //blog(LOG_ERROR, "Failed to query buffer details");
            throw resource_exception("Failed to query buffer details");
         }

         auto & info = m_itema.add_new();

         info.length = map.length;
         info.start =
            v4l2_mmap(NULL, map.length, PROT_READ | PROT_WRITE,
                      MAP_SHARED, iDevice, map.m.offset);

         if (info.start == MAP_FAILED)
         {
            //blog(LOG_ERROR, "mmap for buffer failed");
            //return -1;
            throw resource_exception("mmap for buffer failed");
         }
      }

      //return 0;
   }


   memory_map::~memory_map()
   {

      for (auto & info: m_itema)
      {

         if (info.start != MAP_FAILED && info.start != 0)
         {

            v4l2_munmap(info.start, info.length);

         }

      }

      m_itema.erase_all();

   }


} // namespace video_input_video_for_linux



int_fast32_t v4l2_set_input(int_fast32_t iDevice, int *input)
{
	if (!iDevice || !input)
		return -1;

	return (*input == -1) ? v4l2_ioctl(iDevice, VIDIOC_G_INPUT, input)
			      : v4l2_ioctl(iDevice, VIDIOC_S_INPUT, input);
}

int_fast32_t v4l2_get_input_caps(int_fast32_t iDevice, int input, uint32_t *caps)
{
	if (!iDevice || !caps)
		return -1;

	if (input == -1) {
		if (v4l2_ioctl(iDevice, VIDIOC_G_INPUT, &input) < 0)
			return -1;
	}

	struct v4l2_input in;
	memset(&in, 0, sizeof(in));
	in.index = input;

	if (v4l2_ioctl(iDevice, VIDIOC_ENUMINPUT, &in) < 0)
		return -1;

	*caps = in.capabilities;
	return 0;
}

int_fast32_t v4l2_set_format(int_fast32_t iDevice, int *pwidth, int *pheight,
			     int *ppixelformat, int *pbytesperline)
{
	bool set = false;
	struct v4l2_format fmt;

	if (!iDevice || !pwidth || !pheight || !ppixelformat || !pbytesperline)
		return -1;

	/* We need to set the type in order to query the settings */
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (v4l2_ioctl(iDevice, VIDIOC_G_FMT, &fmt) < 0)
		return -1;

	if (*pwidth != -1 && *pheight != -1)
   {
      fmt.fmt.pix.width = *pwidth;
      fmt.fmt.pix.height = *pheight;
      set = true;
   }

	if (*ppixelformat != -1)
   {
		fmt.fmt.pix.pixelformat = *ppixelformat;
		set = true;
	}

	if (set && (v4l2_ioctl(iDevice, VIDIOC_S_FMT, &fmt) < 0))
		return -1;

	*pwidth = fmt.fmt.pix.width;
   *pheight = fmt.fmt.pix.height;
	*ppixelformat = fmt.fmt.pix.pixelformat;
	*pbytesperline = fmt.fmt.pix.bytesperline;
	return 0;
}

int_fast32_t v4l2_set_framerate(int_fast32_t iDevice, int *pdenominator, int * pnumerator)
{
	bool set = false;
	struct v4l2_streamparm par;

	if (!iDevice || !pdenominator || !pnumerator)
		return -1;

	/* We need to set the type in order to query the stream settings */
	par.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (v4l2_ioctl(iDevice, VIDIOC_G_PARM, &par) < 0)
		return -1;

	if (*pnumerator != -1 && *pdenominator != -1)
   {
      par.parm.capture.timeperframe.numerator = *pnumerator;
		par.parm.capture.timeperframe.denominator = *pdenominator;
		set = true;
	}

	if (set && (v4l2_ioctl(iDevice, VIDIOC_S_PARM, &par) < 0))
		return -1;

	*pnumerator = par.parm.capture.timeperframe.numerator;

   *pdenominator = par.parm.capture.timeperframe.denominator;

	return 0;

}


int_fast32_t v4l2_set_standard(int_fast32_t iDevice, int *standard)
{
	if (!iDevice || !standard)
		return -1;

	if (*standard == -1) {
		if (v4l2_ioctl(iDevice, VIDIOC_G_STD, standard) < 0)
			return -1;
	} else {
		if (v4l2_ioctl(iDevice, VIDIOC_S_STD, standard) < 0)
			return -1;
	}

	return 0;
}

int_fast32_t v4l2_enum_dv_timing(int_fast32_t iDevice, struct v4l2_dv_timings *dvt,
				 int index)
{
#if !defined(VIDIOC_ENUM_DV_TIMINGS) || !defined(V4L2_IN_CAP_DV_TIMINGS)
	UNUSED_PARAMETER(iDevice);
	UNUSED_PARAMETER(dvt);
	UNUSED_PARAMETER(index);
	return -1;
#else
	if (!iDevice || !dvt)
		return -1;

	struct v4l2_enum_dv_timings iter;
	memset(&iter, 0, sizeof(iter));
	iter.index = index;

	if (v4l2_ioctl(iDevice, VIDIOC_ENUM_DV_TIMINGS, &iter) < 0)
		return -1;

	memcpy(dvt, &iter.timings, sizeof(struct v4l2_dv_timings));

	return 0;
#endif
}

int_fast32_t v4l2_set_dv_timing(int_fast32_t iDevice, int *timing)
{
	if (!iDevice || !timing)
		return -1;

	if (*timing == -1)
		return 0;

	struct v4l2_dv_timings dvt;

	if (v4l2_enum_dv_timing(iDevice, &dvt, *timing) < 0)
		return -1;

	if (v4l2_ioctl(iDevice, VIDIOC_S_DV_TIMINGS, &dvt) < 0)
		return -1;

	return 0;
}