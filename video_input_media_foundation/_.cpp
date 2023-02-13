#include "framework.h"
#include "acme/_library.h"


namespace video_input_media_foundation
{


	void processPixels(color32_t* src, color32_t* dst, ::i32 width, ::i32 height, ::u32 bpp, bool bRGB, bool bFlip)
	{

		::i32 widthInBytes = width * bpp;

		::i32 numBytes = widthInBytes * height;

		::i32 numInts = numBytes >> 2;

		::i32 widthInInts = widthInBytes >> 2;

		int* dstInt, * srcInt;

		if (!bRGB)
		{

			int x = 0;
			int y = 0;

			if (bFlip)
			{
				for (int y = 0; y < height; y++)
				{
					dstInt = (int*)(dst + (y * widthInBytes));

					srcInt = (int*)(src + ((height - y - 1) * widthInBytes));

					memcpy(dstInt, srcInt, widthInBytes);

				}

			}
			else
			{

				memcpy(dst, src, numBytes);

				byte* pbyteDst = (byte*)dst;

				pbyteDst += 3;

				for (int i = 0; i < numBytes; i += 4)
				{

					pbyteDst[0] = 255;
					pbyteDst += 4;

				}

			}
			
		}
		else
		{
			if (bFlip)
			{

				::i32 x = 0;
				::i32 y = (height - 1) * widthInBytes;
				src += y;

				for (::i32 i = 0; i < numBytes; i += 4)
				{
					if (x >= width)
					{
						x = 0;
						src -= widthInBytes * 2;
					}

					*dst = *(src + 2);
					dst++;

					*dst = *(src + 1);
					dst++;

					*dst = *src;
					dst++;

					src += 3;
					x++;
				}
			}
			else
			{
				for (::i32 i = 0; i < numBytes; i += 4)
				{
					*dst = *(src + 3);
					dst++;

					*dst = *(src + 2);
					dst++;

					*dst = *(src + 1);
					dst++;

					*dst = *src;
					dst++;

					src += 4;
				}
			}
		}

	}


} // namespace video_input_media_foundation



