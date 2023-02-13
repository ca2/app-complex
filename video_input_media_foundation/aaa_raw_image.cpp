// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"



::image::image(::u32 size_i32): ri_new(false), ri_pixels(NULL)
{
	ri_size = size;

	ri_pixels.reset(memory_new unsigned char[size_i32]);

	memset((void *)ri_pixels.get(),0,ri_size);
}

bool ::image::isNew()
{
	return ri_new;
}

::u32 ::image::getSize()
{
	return ri_size;
}

::image::~::image(void)
{
}

long ::image::CreateInstance(::image **ppRImage,::u32 size_i32)
{
	*ppRImage = memory_new (std::nothrow) ::image(size);

    if (ppRImage == NULL)
    {
        return E_OUTOFMEMORY;
    }
    return S_OK;
}

void ::image::setCopy(const BYTE * pSampleBuffer)
{
	memcpy(ri_pixels.get(), pSampleBuffer, ri_size);

	ri_new = true;
}

void ::image::fastCopy(const BYTE * pSampleBuffer)
{

	int *bsrc = (int *)pSampleBuffer;

	int *dst = (int *)ri_pixels.get();

	::u32 buffersize = ri_size;

	memcpy(dst, bsrc, buffersize);

	ri_new = true;

}

unsigned char * ::image::get_data()
{
	return ri_pixels.get();

	ri_new = false;
}
