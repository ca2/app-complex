/*
 * Copyright (c) 2015 Hugh Bailey <obs.jim@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once

struct util_::u32128 {
	union {
		u32 int[4];
		struct {
			u64 low;
			u64 high;
		};
	};
};

typedef struct util_::u32128 util_::u32128_t;

static inline util_::u32128_t util_add128(util_::u32128_t a, util_::u32128_t b)
{
	util_::u32128_t out;
	u64 val;

	val = (a.low & 0xFFFFFFFFULL) + (b.low & 0xFFFFFFFFULL);
	out.int[0] = (u32)(val & 0xFFFFFFFFULL);
	val >>= 32;

	val += (a.low >> 32) + (b.low >> 32);
	out.int[1] = (u32)val;
	val >>= 32;

	val += (a.high & 0xFFFFFFFFULL) + (b.high & 0xFFFFFFFFULL);
	out.int[2] = (u32)(val & 0xFFFFFFFFULL);
	val >>= 32;

	val += (a.high >> 32) + (b.high >> 32);
	out.int[3] = (u32)val;

	return out;
}

static inline util_::u32128_t util_lshift64(u64 a, int num)
{
	util_::u32128_t val;
	val.low = a << num;
	val.high = a >> (64 - num);
	return val;
}

static inline util_::u32128_t util_mul64_64(u64 a, u64 b)
{
	util_::u32128_t out;
	u64 m;

	m = (a & 0xFFFFFFFFULL) * (b & 0xFFFFFFFFULL);
	out.low = m;
	out.high = 0;

	m = (a >> 32) * (b & 0xFFFFFFFFULL);
	out = util_add128(out, util_lshift64(m, 32));

	m = (a & 0xFFFFFFFFULL) * (b >> 32);
	out = util_add128(out, util_lshift64(m, 32));

	m = (a >> 32) * (b >> 32);
	out = util_add128(out, util_lshift64(m, 64));

	return out;
}

static inline util_::u32128_t util_div128_32(util_::u32128_t a, u32 b)
{
	util_::u32128_t out;
	u64 val = 0;

	for (int i = 3; i >= 0; i--) {
		val = (val << 32) | a.int[i];
		if (val < b) {
			out.int[i] = 0;
			continue;
		}

		out.int[i] = (u32)(val / b);
		val = val % b;
	}

	return out;
}
