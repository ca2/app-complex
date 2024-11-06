#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct media_frames_per_second {
	unsigned int numerator;
	unsigned int denominator;
};

static inline double media_frames_per_second_to_frame_interval(
		struct media_frames_per_second fps)
{
	return (double)fps.denominator / fps.numerator;
}

static inline double media_frames_per_second_to_per_second(
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
