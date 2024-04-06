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

#include "format-conversion.h"
#include <xmmintrin.h>
#include <emmintrin.h>

/* ...surprisingly, if I don't use a macro to force inlining, it causes the
 * CPU usage to boost by a tremendous amount in debug builds. */

#define get_m128_32_0(val) (*((u32*)&val))
#define get_m128_32_1(val) (*(((u32*)&val)+1))

#define pack_shift(lum_plane, lum_pos0, lum_pos1, line1, line2, mask, sh)     \
do {                                                                          \
	__m128i pack_val = _mm_packs_epi32(                                   \
			_mm_srli_si128(_mm_and_si128(line1, mask), sh),       \
			_mm_srli_si128(_mm_and_si128(line2, mask), sh));      \
	pack_val = _mm_packus_epi16(pack_val, pack_val);                      \
                                                                              \
	*(u32*)(lum_plane+lum_pos0) = get_m128_32_0(pack_val);           \
	*(u32*)(lum_plane+lum_pos1) = get_m128_32_1(pack_val);           \
} while (false)

#define pack_val(lum_plane, lum_pos0, lum_pos1, line1, line2, mask)           \
do {                                                                          \
	__m128i pack_val = _mm_packs_epi32(                                   \
			_mm_and_si128(line1, mask),                           \
			_mm_and_si128(line2, mask));                          \
	pack_val = _mm_packus_epi16(pack_val, pack_val);                      \
                                                                              \
	*(u32*)(lum_plane+lum_pos0) = get_m128_32_0(pack_val);           \
	*(u32*)(lum_plane+lum_pos1) = get_m128_32_1(pack_val);           \
} while (false)

#define pack_ch_1plane(uv_plane, chroma_pos, line1, line2, uv_mask)           \
do {                                                                          \
	__m128i add_val = _mm_add_epi64(                                      \
			_mm_and_si128(line1, uv_mask),                        \
			_mm_and_si128(line2, uv_mask));                       \
	__m128i avg_val = _mm_add_epi64(                                      \
			add_val,                                              \
			_mm_shuffle_epi32(add_val, _MM_SHUFFLE(2, 3, 0, 1))); \
	avg_val = _mm_srai_epi16(avg_val, 2);                                 \
	avg_val = _mm_shuffle_epi32(avg_val, _MM_SHUFFLE(3, 1, 2, 0));        \
	avg_val = _mm_packus_epi16(avg_val, avg_val);                         \
                                                                              \
	*(u32*)(uv_plane+chroma_pos) = get_m128_32_0(avg_val);           \
} while (false)

#define pack_ch_2plane(u_plane, v_plane, chroma_pos, line1, line2, uv_mask)   \
do {                                                                          \
	u32 packed_vals;                                                 \
                                                                              \
	__m128i add_val = _mm_add_epi64(                                      \
			_mm_and_si128(line1, uv_mask),                        \
			_mm_and_si128(line2, uv_mask));                       \
	__m128i avg_val = _mm_add_epi64(                                      \
			add_val,                                              \
			_mm_shuffle_epi32(add_val, _MM_SHUFFLE(2, 3, 0, 1))); \
	avg_val = _mm_srai_epi16(avg_val, 2);                                 \
	avg_val = _mm_shuffle_epi32(avg_val, _MM_SHUFFLE(3, 1, 2, 0));        \
	avg_val = _mm_shufflelo_epi16(avg_val, _MM_SHUFFLE(3, 1, 2, 0));      \
	avg_val = _mm_packus_epi16(avg_val, avg_val);                         \
                                                                              \
	packed_vals = get_m128_32_0(avg_val);                                 \
                                                                              \
	*(u16*)(u_plane+chroma_pos) = (u16)(packed_vals);           \
	*(u16*)(v_plane+chroma_pos) = (u16)(packed_vals>>16);       \
} while (false)


static FORCE_INLINE u32 min_uint32(u32 a, u32 b)
{
	return a < b ? a : b;
}

void compress_uyvx_to_i420(
		const u8 *input, u32 in_linesize,
		u32 start_y, u32 end_y,
		u8 *output[], const u32 out_linesize[])
{
	u8  *lum_plane   = output[0];
	u8  *u_plane     = output[1];
	u8  *v_plane     = output[2];
	u32 width        = min_uint32(in_linesize, out_linesize[0]);
	u32 y;

	__m128i lum_mask = _mm_set1_epi32(0x0000FF00);
	__m128i uv_mask  = _mm_set1_epi16(0x00FF);

	for (y = start_y; y < end_y; y += 2) {
		u32 y_pos        = y      * in_linesize;
		u32 chroma_y_pos = (y>>1) * out_linesize[1];
		u32 lum_y_pos    = y      * out_linesize[0];
		u32 x;

		for (x = 0; x < width; x += 4) {
			const u8 *img = input + y_pos + x*4;
			u32 lum_pos0  = lum_y_pos + x;
			u32 lum_pos1  = lum_pos0 + out_linesize[0];

			__m128i line1 = _mm_load_si128((const __m128i*)img);
			__m128i line2 = _mm_load_si128(
					(const __m128i*)(img + in_linesize));

			pack_shift(lum_plane, lum_pos0, lum_pos1,
					line1, line2, lum_mask, 1);
			pack_ch_2plane(u_plane, v_plane,
					chroma_y_pos + (x>>1),
					line1, line2, uv_mask);
		}
	}
}

void compress_uyvx_to_nv12(
		const u8 *input, u32 in_linesize,
		u32 start_y, u32 end_y,
		u8 *output[], const u32 out_linesize[])
{
	u8 *lum_plane    = output[0];
	u8 *chroma_plane = output[1];
	u32 width        = min_uint32(in_linesize, out_linesize[0]);
	u32 y;

	__m128i lum_mask = _mm_set1_epi32(0x0000FF00);
	__m128i uv_mask  = _mm_set1_epi16(0x00FF);

	for (y = start_y; y < end_y; y += 2) {
		u32 y_pos        = y      * in_linesize;
		u32 chroma_y_pos = (y>>1) * out_linesize[1];
		u32 lum_y_pos    = y      * out_linesize[0];
		u32 x;

		for (x = 0; x < width; x += 4) {
			const u8 *img = input + y_pos + x*4;
			u32 lum_pos0  = lum_y_pos + x;
			u32 lum_pos1  = lum_pos0 + out_linesize[0];

			__m128i line1 = _mm_load_si128((const __m128i*)img);
			__m128i line2 = _mm_load_si128(
					(const __m128i*)(img + in_linesize));

			pack_shift(lum_plane, lum_pos0, lum_pos1,
					line1, line2, lum_mask, 1);
			pack_ch_1plane(chroma_plane, chroma_y_pos + x,
					line1, line2, uv_mask);
		}
	}
}

void convert_uyvx_to_i444(
		const u8 *input, u32 in_linesize,
		u32 start_y, u32 end_y,
		u8 *output[], const u32 out_linesize[])
{
	u8  *lum_plane   = output[0];
	u8  *u_plane     = output[1];
	u8  *v_plane     = output[2];
	u32 width        = min_uint32(in_linesize, out_linesize[0]);
	u32 y;

	__m128i lum_mask = _mm_set1_epi32(0x0000FF00);
	__m128i u_mask   = _mm_set1_epi32(0x000000FF);
	__m128i v_mask   = _mm_set1_epi32(0x00FF0000);

	for (y = start_y; y < end_y; y += 2) {
		u32 y_pos        = y      * in_linesize;
		u32 lum_y_pos    = y      * out_linesize[0];
		u32 x;

		for (x = 0; x < width; x += 4) {
			const u8 *img = input + y_pos + x*4;
			u32 lum_pos0  = lum_y_pos + x;
			u32 lum_pos1  = lum_pos0 + out_linesize[0];

			__m128i line1 = _mm_load_si128((const __m128i*)img);
			__m128i line2 = _mm_load_si128(
					(const __m128i*)(img + in_linesize));

			pack_shift(lum_plane, lum_pos0, lum_pos1,
					line1, line2, lum_mask, 1);
			pack_val(u_plane, lum_pos0, lum_pos1,
					line1, line2, u_mask);
			pack_shift(v_plane, lum_pos0, lum_pos1,
					line1, line2, v_mask, 2);
		}
	}
}

void decompress_420(
		const u8 *const input[], const u32 in_linesize[],
		u32 start_y, u32 end_y,
		u8 *output, u32 out_linesize)
{
	u32 start_y_d2 = start_y/2;
	u32 width_d2   = min_uint32(in_linesize[0], out_linesize)/2;
	u32 height_d2  = end_y/2;
	u32 y;

	for (y = start_y_d2; y < height_d2; y++) {
		const u8 *chroma0 = input[1] + y * in_linesize[1];
		const u8 *chroma1 = input[2] + y * in_linesize[2];
		register const u8 *lum0, *lum1;
		register u32 *output0, *output1;
		u32 x;

		lum0 = input[0] + y * 2 * in_linesize[0];
		lum1 = lum0 + in_linesize[0];
		output0 = (u32*)(output + y * 2 * in_linesize[0]);
		output1 = (u32*)((u8*)output0 + in_linesize[0]);

		for (x = 0; x < width_d2; x++) {
			u32 out;
			out = (*(chroma0++) << 8) | (*(chroma1++) << 16);

			*(output0++) = *(lum0++) | out;
			*(output0++) = *(lum0++) | out;

			*(output1++) = *(lum1++) | out;
			*(output1++) = *(lum1++) | out;
		}
	}
}

void decompress_nv12(
		const u8 *const input[], const u32 in_linesize[],
		u32 start_y, u32 end_y,
		u8 *output, u32 out_linesize)
{
	u32 start_y_d2 = start_y/2;
	u32 width_d2   = min_uint32(in_linesize[0], out_linesize)/2;
	u32 height_d2  = end_y/2;
	u32 y;

	for (y = start_y_d2; y < height_d2; y++) {
		const u16 *chroma;
		register const u8 *lum0, *lum1;
		register u32 *output0, *output1;
		u32 x;

		chroma = (const u16*)(input[1] + y * in_linesize[1]);
		lum0 = input[0] + y * 2 * in_linesize[0];
		lum1 = lum0 + in_linesize[0];
		output0 = (u32*)(output + y * 2 * out_linesize);
		output1 = (u32*)((u8*)output0 + out_linesize);

		for (x = 0; x < width_d2; x++) {
			u32 out = *(chroma++) << 8;

			*(output0++) = *(lum0++) | out;
			*(output0++) = *(lum0++) | out;

			*(output1++) = *(lum1++) | out;
			*(output1++) = *(lum1++) | out;
		}
	}
}

void decompress_422(
		const u8 *input, u32 in_linesize,
		u32 start_y, u32 end_y,
		u8 *output, u32 out_linesize,
		bool leading_lum)
{
	u32 width_d2 = min_uint32(in_linesize, out_linesize)/2;
	u32 y;

	register const u32 *input32;
	register const u32 *input32_end;
	register u32       *output32;

	if (leading_lum) {
		for (y = start_y; y < end_y; y++) {
			input32     = (const u32*)(input + y*in_linesize);
			input32_end = input32 + width_d2;
			output32    = (u32*)(output + y*out_linesize);

			while(input32 < input32_end) {
				register u32 dw = *input32;

				output32[0] = dw;
				dw &= 0xFFFFFF00;
				dw |= (u8)(dw>>16);
				output32[1] = dw;

				output32 += 2;
				input32++;
			}
		}
	} else {
		for (y = start_y; y < end_y; y++) {
			input32     = (const u32*)(input + y*in_linesize);
			input32_end = input32 + width_d2;
			output32    = (u32*)(output + y*out_linesize);

			while (input32 < input32_end) {
				register u32 dw = *input32;

				output32[0] = dw;
				dw &= 0xFFFF00FF;
				dw |= (dw>>16) & 0xFF00;
				output32[1] = dw;

				output32 += 2;
				input32++;
			}
		}
	}
}
