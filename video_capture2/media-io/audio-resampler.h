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
#include "audio-io.h"

#ifdef __cplusplus
extern "C" {
#endif

struct audio_resampler;
typedef struct audio_resampler audio_resampler_t;

struct resample_info {
	unsigned int            samples_per_sec;
	enum audio_format   format;
	enum speaker_layout speakers;
};

EXPORT audio_resampler_t *audio_resampler_create(const struct resample_info *dst,
		const struct resample_info *src);
EXPORT void audio_resampler_destroy(audio_resampler_t *resampler);

EXPORT bool audio_resampler_resample(audio_resampler_t *resampler,
		 unsigned char *output[], unsigned int *out_frames, unsigned long long *ts_offset,
		 const unsigned char *const input[], unsigned int in_frames);

#ifdef __cplusplus
}
#endif
