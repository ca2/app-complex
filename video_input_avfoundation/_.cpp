#include "framework.h"

#include "acme/_library.h"




namespace video_input_video_avfoundation
{


	void processPixels(color32_t* src, color32_t* dst, unsigned int width, unsigned int height, unsigned int bpp, bool bRGB, bool bFlip)
	{

		unsigned int widthInBytes = width * bpp;

		unsigned int numBytes = widthInBytes * height;

		//unsigned int numInts = numBytes >> 2;

		//unsigned int widthInInts = widthInBytes >> 2;

		int* dstInt, * srcInt;

		if (!bRGB)
		{

			//int x = 0;
			//int y = 0;

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

				unsigned char* pbyteDst = (unsigned char*)dst;

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

				int x = 0;
				int y = (height - 1) * widthInBytes;
				src += y;

				for (unsigned int i = 0; i < numBytes; i += 4)
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
				for (unsigned int i = 0; i < numBytes; i += 4)
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


} // namespace video_input_video_avfoundation



