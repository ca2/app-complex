#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct media_frames_per_second {
	u32 numerator;
	u32 denominator;
};

static inline double media_frames_per_second_to_frame_interval(
		struct media_frames_per_second fps)
{
	return (double)fps.denominator / fps.numerator;
}

static inline double media_frames_per_second_to_fps(
		struct media_frames_per_second fps)
{
	return (double)fps.numerator / fps.denominator;
}

static inline bool media_frames_per_second_is_valid(
		struct media_frames_per_second fps)
{
	return fps.numerator && fps.denominator;
}

#ifdef __cplusplus
}
#endif
