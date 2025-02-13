/******************************************************************************
    Copyright (C) 2013 by Hugh Bailey <obs.jim@gmail.com>

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
******************************************************************************/

#pragma once

#include "../util/c99defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Functions for converting to and from packed 444 YUV
 */

EXPORT void compress_uyvx_to_i420(
		const unsigned char *input, unsigned int in_linesize,
		unsigned int start_y, unsigned int end_y,
		unsigned char *output[], const unsigned int out_linesize[]);

EXPORT void compress_uyvx_to_nv12(
		const unsigned char *input, unsigned int in_linesize,
		unsigned int start_y, unsigned int end_y,
		unsigned char *output[], const unsigned int out_linesize[]);

EXPORT void convert_uyvx_to_i444(
		const unsigned char *input, unsigned int in_linesize,
		unsigned int start_y, unsigned int end_y,
		unsigned char *output[], const unsigned int out_linesize[]);

EXPORT void decompress_nv12(
		const unsigned char *const input[], const unsigned int in_linesize[],
		unsigned int start_y, unsigned int end_y,
		unsigned char *output, unsigned int out_linesize);

EXPORT void decompress_420(
		const unsigned char *const input[], const unsigned int in_linesize[],
		unsigned int start_y, unsigned int end_y,
		unsigned char *output, unsigned int out_linesize);

EXPORT void decompress_422(
		const unsigned char *input, unsigned int in_linesize,
		unsigned int start_y, unsigned int end_y,
		unsigned char *output, unsigned int out_linesize,
		bool leading_lum);

#ifdef __cplusplus
}
#endif
