#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct media_frames_per_second {
	::u32 numerator;
	::u32 denominator;
};

static inline ::f64 media_frames_per_second_to_frame_interval(
		struct media_frames_per_second fps)
{
	return (::f64)fps.denominator / fps.numerator;
}

static inline ::f64 media_frames_per_second_to_per_second(
		struct media_frames_per_second fps)
{
	return (::f64)fps.numerator / fps.denominator;
}

static inline bool media_frames_per_second_is_valid(
		struct media_frames_per_second fps)
{
	return fps.numerator && fps.denominator;
}

#ifdef __cplusplus
}
#endif
