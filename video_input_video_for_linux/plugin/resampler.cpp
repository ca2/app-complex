#include "framework.h"



/******************************* SOURCE LICENSE *********************************
Copyright (c) 2018 MicroModeler.

A non-exclusive, nontransferable, perpetual, royalty-free license is granted to the Licensee to
use the following Information for academic, non-profit, or government-sponsored research purposes.
Use of the following Information under this License is restricted to NON-COMMERCIAL PURPOSES ONLY.
Commercial use of the following Information requires a separately executed written license agreement.

This Information is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

******************************* END OF LICENSE *********************************/

// A commercial license for MicroModeler DSP can be obtained at http://www.micromodeler.com/launch.jsp

// Begin header file, filter1.h

#ifndef FILTER1_H_ // Include guards
#define FILTER1_H_

static const int filter1_length = 20;
extern float filter1_coefficients[20];

template < typename TYPE >
void move_insert(TYPE* p, ::index i, const TYPE & t, ::count c)
{

   memory_transfer(p + i + 1,  p + i,  ((c - i) - 1) * sizeof(TYPE));
   p[i] = t;

}

filter1Type *filter1_create(void);
void filter1_destroy(filter1Type *pObject);
void filter1_init(filter1Type * pThis);
void filter1_reset(filter1Type * pThis);
#define filter1_writeInput( pThis, input )  \
	filter1_filterBlock( pThis, &input, &pThis->output, 1 );

#define filter1_readOutput( pThis )  \
	pThis->output

int filter1_filterBlock(filter1Type * pThis, float * pInput, float * pOutput, unsigned int count);
#define filter1_outputToFloat( output )  \
	(output)

#define filter1_inputFromFloat( input )  \
	(input)

void filter1_dotProduct(float * pInput, float * pKernel, float * pAccumulator, short count);
#endif // FILTER1_H_


float filter1_coefficients[20] =
{
   0.0000000, 0.029721159, 0.022866987, -0.0027099693, 0.032310253, -0.063501886,
   -0.053294540, -0.023067688, -0.28084836, 0.061141540, 0.57424679, 0.061141540,
   -0.28084836, -0.023067688, -0.053294540, -0.063501886, 0.032310253, -0.0027099693,
   0.022866987, 0.029721159
};


filter1Type *filter1_create(void)
{
   filter1Type *result = (filter1Type *)memory_allocate(sizeof(filter1Type));	// Allocate memory for the object
   filter1_init(result);											// Initialize it
   return result;																// Return the result
}

void filter1_destroy(filter1Type *pObject)
{
   memory_free(pObject);
}

void filter1_init(filter1Type * pThis)
{
   filter1_reset(pThis);

}

void filter1_reset(filter1Type * pThis)
{
   memory_set(&pThis->state, 0, sizeof(pThis->state)); // Reset state to 0
   pThis->pointer = pThis->state;						// History buffer points to start of state buffer
   pThis->output = 0;									// Reset output

}

int filter1_filterBlock(filter1Type * pThis, float * pInput, float * pOutput, unsigned int count)
{
   float *pOriginalOutput = pOutput;	// Save original output so we can track the number of samples processed
   float accumulator;

   for (; count; --count)
   {
      pThis->pointer[filter1_length] = *pInput;						// Copy sample to top of history buffer
      *(pThis->pointer++) = *(pInput++);										// Copy sample to bottom of history buffer

      if (pThis->pointer >= pThis->state + filter1_length)				// Handle wrap-around
         pThis->pointer -= filter1_length;

      accumulator = 0;
      filter1_dotProduct(pThis->pointer, filter1_coefficients, &accumulator, filter1_length);
      *(pOutput++) = accumulator;	// Store the result
   }

   return (int) (pOutput - pOriginalOutput);

}


void filter1_dotProduct(float * pInput, float * pKernel, float * pAccumulator, short count)
{
   float accumulator = *pAccumulator;
   while (count--)
      accumulator += ((float)*(pKernel++)) * *(pInput++);
   *pAccumulator = accumulator;

}



//Sample Hz :
//1
//Class :
//   filter1
//   Math : Biquad
//
// // For malloc/free
//#include <string.h> // For memory_set



//
//Sample Hz :
//1
//Class :
//   filter1
//   Math : Biquad
//
//
float g_daa[] =
{
   -0.0184869710,
   0.0721764290,
   -0.5963144904,
   2.0107675534,
   -3.8726114221,
   5.8219491055,
   -6.3912114796,
   3.9737312753
};

//x[5] y[4]
float the_filter(float * y, float * x)
{

   //y.set_size(8);
   //x.set_size(9);

   //float * b = g_daa;

//#include "Z:/f1.cpp";

   //Recurrence relation:
   //x.set_size(5);
   //y.set_size(4);
   return
   (1.0000000000f * x[4])
   + (-2.0000000000f * x[2])
   + (1.0000000000f * x[0])

   + (-0.4092316589f * y[3])
   + (-0.3103421481f * y[2])
   + (0.8709080543f * y[1])
   + (0.8485651097f * y[0])
   ;

   //mkfilter -f Z:\f1.cpp -Bu -Bp -o 2 -a 0.001 0.4

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   //return
   //   +  x[0]
   //   - (4.0 * x[2])
   //   + (6.0 * x[4])
   //   - (4.0 *x[6])
   //   + x[8]
   //   + (b[0] * y[7])
   //   + (b[1] * y[6])
   //   + (b[2] * y[5])
   //   + (b[3] * y[4])
   //   + (b[4] * y[3])
   //   + (b[5] * y[2])
   //   + (b[6] * y[1])
   //   + (b[7] * y[0]);

}

float filter1(float_array & y, float_array&x)
{

   //y.set_size(8);
   //x.set_size(9);

   //float * b = g_daa;
   //Recurrence relation:
   x.set_size(5);
   y.set_size(4);
   return
   (1.0000000000f * x[4])
   + (-2.0000000000f * x[2])
   + (1.0000000000f * x[0])

   + (-0.4092316589f * y[3])
   + (-0.3103421481f * y[2])
   + (0.8709080543f * y[1])
   + (0.8485651097f * y[0])
   ;

   //#include "Z:/f2.cpp";

   //mkfilter - f Z:\f2.cpp - Bu - Bp - o 2 - a 0.001 0.4

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   //return
   //   +  x[0]
   //   - (4.0 * x[2])
   //   + (6.0 * x[4])
   //   - (4.0 *x[6])
   //   + x[8]
   //   + (b[0] * y[7])
   //   + (b[1] * y[6])
   //   + (b[2] * y[5])
   //   + (b[3] * y[4])
   //   + (b[4] * y[3])
   //   + (b[5] * y[2])
   //   + (b[6] * y[1])
   //   + (b[7] * y[0]);

}

float g_d8a[] =
{
   -0.1906700175,
   1.8290880199,
   -7.7370157199,
   18.8444441947,
   -28.9146767296,
   28.6152620436,
   -17.8190300249,
   6.3725982336
};

float chebyshev_2rd_0025_0100__6(float_array& y, float_array&x)
{

   y.set_size(8);
   x.set_size(9);

   float *b = g_d8a;

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return
   +x[0]
   - (4.0f * x[2])
   + (6.0f * x[4])
   - (4.0f *x[6])
   + x[8]
   + (b[0] * y[7])
   + (b[1] * y[6])
   + (b[2] * y[5])
   + (b[3] * y[4])
   + (b[4] * y[3])
   + (b[5] * y[2])
   + (b[6] * y[1])
   + (b[7] * y[0]);

}
float g_d8[] =
{
   -0.8183065896,
   3.3034520307,
   -5.1507927062,
   3.6656070924
};

float chebyshev_2rd_002_0084__6(float_array& y, float_array&x)
{

   y.set_size(4);
   x.set_size(5);

   float * b = g_d8;

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return
   (x[0])
   - (2.0f * x[2])
   + (x[4])
   + (b[0] * y[3])
   + (b[1] * y[2])
   + (b[2] * y[1])
   + (b[3] * y[0]);

}

int total_sum(short * psh, int c)
{

   int sum = 0;
   while (c > 0)
   {
      sum += *psh++;
      c--;
   }

   return sum;

}


int total_sum(char * pch, int c)
{

   int sum = 0;
   while (c > 0)
   {
      sum += *pch++;
      c--;
   }

   return sum;

}


int total_sum(int * pi, int c)
{

   int sum = 0;
   while (c > 0)
   {
      sum += *pi++;
      c--;
   }

   return sum;

}


float butterworth_3_1_8_fs_lo_pass(float_array& ya, float_array&xa)
{

   ya.set_size(3);

   xa.set_size(4);

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return xa[3] + xa[2] * 3.0f + xa[1] * 3.0f + xa[0] + ya[2] * 1.4590290622f - ya[1] * 0.9103690003f + ya[0] * 0.1978251873f;

}


//(7.4749284307 * y[n - 1])
float butterworth_3_001_fs_hi_pass(float_array & ya, float_array &xa)
{

   ya.set_size(3);

   xa.set_size(4);

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return xa[3] - xa[2] * 3.0f + xa[1] * 3.0f - xa[0] + ya[2] * 2.9874336501f - ya[1] * 2.9749461327f + ya[0] * 0.9875122361f;

}


float butterworth_3rd_bp_001_125(float_array & ya, float_array &xa)
{

   ya.set_size(7);

   xa.set_size(7);

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return xa[0] - xa[2] * 3.0f + xa[4] * 3.0f - xa[6] + ya[0] * 4.4593712907f - ya[1] * 8.2974668063f + ya[2] * 8.3335630369f - ya[3] * 4.8128344432f + ya[4] * 1.5179704346f - ya[5] * 0.2006035757f;

}


//(-1 * x[n - 10])
//(0 * x[n - 9])
//(5 * x[n - 8])
//(0 * x[n - 7])
//(-10 * x[n - 6])
//(0 * x[n - 5])
//(10 * x[n - 4])
//(0 * x[n - 3])
//(-5 * x[n - 2])
//(0 * x[n - 1])
//(1 * x[n - 0])
//
//(-0.0739564948 * y[n - 10])
//(0.9226664884 * y[n - 9])
//(-5.2240185978 * y[n - 8])
//(17.6922709137 * y[n - 7])
//(-39.6945017106 * y[n - 6])
//(61.6588561462 * y[n - 5])
//(-67.1521313109 * y[n - 4])
//(50.5963730152 * y[n - 3])
//(-25.2004868800 * y[n - 2])
//(7.4749284307 * y[n - 1])
float butterworth_5rd_bp_001_125(float_array & ya, float_array &xa)
{

   ya.set_size(10);
   xa.set_size(11);

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return xa[0] - xa[2] * 5.0f + xa[4] * 10.0f - xa[6] * 10.0f + xa[8] * 5.0f - xa[10] + ya[0] * 7.4749284307f - ya[1] * 25.2004868800f + ya[2] * 50.5963730152f - ya[3] * 67.1521313109f + ya[4] * 61.658856146f - ya[5] * 39.6945017106f + ya[6] * 17.6922709137f - ya[7] * 5.2240185978f + ya[8] * 0.9226664884f - ya[9] * 0.0739564948f;

}


//y[n] = (1 * x[n - 8])
//+ (0 * x[n - 7])
//+ (-4 * x[n - 6])
//+ (0 * x[n - 5])
//+ (6 * x[n - 4])
//+ (0 * x[n - 3])
//+ (-4 * x[n - 2])
//+ (0 * x[n - 1])
//+ (1 * x[n - 0])
//
//+ ( -0.0776258711 * y[n - 8])
//+ ( 0.8005292567 * y[n - 7])
//+ ( -3.7073367389 * y[n - 6])
//+ ( 9.9498321474 * y[n - 5])
//+ ( -17.0148289141 * y[n - 4])
//+ ( 19.0410262179 * y[n - 3])
//+ ( -13.5600048398 * y[n - 2])
//+ ( 5.5684087416 * y[n - 1])


float g_d1[] =
{
   -0.1214770482,
   1.2144296844,
   -5.3833874879,
   13.7887791225,
   -22.3568059914,
   23.5061853996,
   -15.6163706314,
   5.9686469524
};


float butterworth_4rd_bp_001_125(float_array & y, float_array &xa)
{

   y.set_size(8);
   xa.set_size(9);

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return xa[0] - xa[2] * 4.0f + xa[4] * 6.0f - xa[6] * 4.0f + xa[8]
          + (g_d1[0] * y[7])
          + (g_d1[1] * y[6])
          + (g_d1[2] * y[5])
          + (g_d1[3] * y[4])
          + (g_d1[4] * y[3])
          + (g_d1[5] * y[2])
          + (g_d1[6] * y[1])
          + (g_d1[7] * y[0]);

}


float g_d2[] =
{
   1.0,
   -7.8030134495,
   26.8326320850,
   -53.1029295565,
   66.1466277237,
   -53.1029295565,
   26.8326320850,
   -7.8030134495,
   1.0
};


float g_d3[] =
{
   -0.9263539751,
   7.2974685787,
   -25.3344515879,
   50.6186792427,
   -63.6575660681,
   51.5960817838,
   -26.3222662309,
   7.7284025956
};


float chebyshevy_4rd_bs_025_05__05(float_array & y, float_array &x)
{

   y.set_size(8);
   x.set_size(9);

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return
   (g_d2[0] * x[8])
   + (g_d2[1] * x[7])
   + (g_d2[2] * x[6])
   + (g_d2[3] * x[5])
   + (g_d2[4] * x[4])
   + (g_d2[5] * x[3])
   + (g_d2[6] * x[2])
   + (g_d2[7] * x[1])
   + (g_d2[8] * x[0])
   + (g_d3[0] * y[7])
   + (g_d3[1] * y[6])
   + (g_d3[2] * y[5])
   + (g_d3[3] * y[4])
   + (g_d3[4] * y[3])
   + (g_d3[5] * y[2])
   + (g_d3[6] * y[1])
   + (g_d3[7] * y[0]);

}


float g_d4[] =
{
   -0.4160550644,
   1.4142135624
};


float butterworth_1rd_0005_0125(float_array & y, float_array &x)
{

   y.set_size(2);
   x.set_size(3);

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return
   (x[0])
   - (x[2])
   + (g_d4[0] * y[1])
   + (g_d4[1] * y[0]);

}


float g_d5[] =
{
   -0.3347332560,
   1.6141240047,
   -3.2223218138,
   2.9429272068
};


float butterworth_2rd_0005_0125(float_array & y, float_array &x)
{

   y.set_size(4);
   x.set_size(5);

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return
   (x[0])
   - (2.0f * x[2])
   + (x[4])
   + (g_d5[0] * y[3])
   + (g_d5[1] * y[2])
   + (g_d5[2] * y[1])
   + (g_d5[3] * y[0]);

}

float g_d6[] =
{
   -0.7419772820,
   2.9104430057,
   -4.5942884415,
   3.4258173530
};

float chebyshev_2rd_0005_0125__6(float_array & y, float_array &x)
{

   y.set_size(4);
   x.set_size(5);

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return
   (x[0])
   - (2.0f * x[2])
   + (x[4])
   + (g_d6[0] * y[3])
   + (g_d6[1] * y[2])
   + (g_d6[2] * y[1])
   + (g_d6[3] * y[0]);

}

float g_d7[] =
{
   -0.7853408677f,
   3.1495773352f,
   -4.9426975626f,
   3.5784575898f
};

float chebyshev_2rd_0005_0100__6(float_array & y, float_array &x)
{

   y.set_size(4);
   x.set_size(5);

   float * b = g_d7;

   //return da[4] * 0.3 + da[3] * 0.6  + da[2] * 0.3 - da[1] - da[0];
   return
   (x[0])
   - (2.0f * x[2])
   + (x[4])
   + (b[0] * y[3])
   + (b[1] * y[2])
   + (b[2] * y[1])
   + (b[3] * y[0]);

}


namespace audio
{


   resampler::resampler()
   {

      m_bUnsignedSource = true;

      m_pfilter1 = nullptr;

      m_dwTargetSamplesPerSecond = 44100;

      m_iTargetChannelCount = 2;

      m_iTargetBitsPerSample = 16;

      m_chCountDown = 128;

      m_bEof = false;

      m_bNonStopOnEof = false;

      m_bExtra = false;

      m_xa1.set_size(2);

      m_ya1.set_size(2);

      for (index i = 0; i < 2; i++)
      {

         m_xa1[i].set_size(5);

         m_ya1[i].set_size(4);

         for (index j = 0; j < m_xa1[i].get_size(); j++)
         {

            m_xa1[i][j] = 0.0;

         }

         for (index j = 0; j < m_ya1[i].get_size(); j++)
         {

            m_ya1[i][j] = 0.0;

         }

      }

   }


   resampler::~resampler()
   {

      if (m_pfilter1 != nullptr)
      {

         filter1_destroy(m_pfilter1);

      }

   }


   bool resampler::audio_initialize()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!::audio::plugin::audio_initialize())
      {

         return false;

      }

      if (m_pplugin)
      {

         if (m_bLoop)
         {

            m_pplugin->m_bLoop = true;

         }

      }

      m_iReadPointer = 0;

      m_memSource.set_size(512);

      int iDstSamplesPerSecond = audio_get_samples_per_second();

      int iDstChannelCount = audio_get_channel_count();

      int iSrcSamplesPerSecond = m_pplugin->audio_get_samples_per_second();

      int iSrcChannelCount = m_pplugin->audio_get_channel_count();

      m_da.set_size(maximum(iDstChannelCount, iSrcChannelCount));

      m_xa1.set_size(maximum(iDstChannelCount, iSrcChannelCount));

      m_ya1.set_size(maximum(iDstChannelCount, iSrcChannelCount));

      m_xa2.set_size(maximum(iDstChannelCount, iSrcChannelCount));

      m_ya2.set_size(maximum(iDstChannelCount, iSrcChannelCount));

      m_iaUpperPos.set_size(maximum(iDstChannelCount, iSrcChannelCount));

      m_iaLowerPos.set_size(maximum(iDstChannelCount, iSrcChannelCount));

      m_daLastSample.set_size(maximum(iDstChannelCount, iSrcChannelCount));

      for (index i = 0; i < maximum(iDstChannelCount, iSrcChannelCount); i++)
      {

         m_iaUpperPos[i] = 0;

         m_iaLowerPos[i] = 0;

      }

      for (int i = 0; i < m_daLastSample.get_size(); i++)
      {

         m_daLastSample[i] = 0.0;

      }

      m_den = iDstSamplesPerSecond;

      m_num = iSrcSamplesPerSecond;

      while (m_den % 2 == 0 && m_num % 2 == 0)
      {

         m_den /= 2;

         m_num /= 2;

      }

      while (m_den % 3 == 0 && m_num % 3 == 0)
      {

         m_den /= 3;

         m_num /= 3;

      }

      while (m_den % 5 == 0 && m_num % 5 == 0)
      {

         m_den /= 5;

         m_num /= 5;

      }

      m_posSrc = 0;

      m_posDst = 0;

      m_fNextSample = 0.0f;


      return true;

   }


   bool resampler::audio_finalize()
   {

      return true;

   }


   void resampler::audio_move_next()
   {

   }


   bool resampler::audio_is_loop()
   {

      if (m_pplugin == nullptr)
      {

         return false;

      }

      return m_pplugin->m_bLoop;

   }


   bool resampler::audio_eof()
   {

      return m_bEof && audio_file().get_size() <= 0;

   }


   u32 resampler::audio_get_samples_per_second() const
   {

      return m_dwTargetSamplesPerSecond;

   }


   u32 resampler::audio_get_channel_count() const
   {

      return m_iTargetChannelCount;

   }


   u32 resampler::audio_get_bits_per_sample() const
   {

      return m_iTargetBitsPerSample;

   }


   memsize resampler::audio_read_raw(void * lpvoidBuffer, memsize uiBufferSize)
   {

      if (audio_eof())
      {

         return 0;

      }

      ::u32 uTotal = 1024;

      if(m_src.get_size() <= 0)
      {

         read_source();

      }

      m_src.seek_to_begin();

      ::u32 uRead = 1024;

      memsize consumed;

      short shInterpolation;

      short shSrc;

      int iDstChannelCount = audio_get_channel_count();

      int iSrcChannelCount = m_pplugin->audio_get_channel_count();

      int iSrcSampFreq = m_pplugin->audio_get_samples_per_second();

      int iDstSampFreq = audio_get_samples_per_second();

      ::u32 dwRead = 0;

      int iSrcBits = m_pplugin->audio_get_bits_per_sample();

      if (iSrcBits == 8)
      {

         int iSample;
         //unsigned char uch;
         char ch;
         int iSample1;
         float dInterpolation;

         int rate;

         //if (m_den % m_num == 0)
         {

            //information("perfect match of m_den and m_num");

         }

         if(m_num == 0)
         {

            rate = 1;

         }
         else
         {

            rate = m_den / m_num;

         }

         float dSample1;

         for (;;)
         {

            consumed = m_src.erase_begin(&ch, 1);

            if (consumed <= 0)
               break;

               ch ^= 0x80;
            iSample1 = ch;
            iSample1 *= 127;
            dSample1 = (float) iSample1;

            //m_xa2.insert_at(0,dSample1);

            //dInterpolation = filter1(m_ya2,m_xa2);

            //m_ya2.insert_at(0,dInterpolation);

            //dSample1 = dInterpolation;

            //m_flt.write(&iSample1,sizeof(iSample1));
            //int iAcc = total_sum((int *)m_flt.get_data(),m_flt.get_length() / sizeof(int));
            //if(m_flt.get_length() > 2*sizeof(int))
            //{
            // m_flt.erase_begin(nullptr,m_flt.get_length() - 2 * sizeof(int));
            //}

            for (iSample = 0; iSample < rate; iSample++)
            {

               float dLast = 0.0;

               if (m_daLastSample.has_elements())
               {

                  dLast = m_daLastSample[0];

               }

               dInterpolation = (dSample1 * (float)iSample + dLast * (float)(rate - iSample)) / (float)rate;

               move_insert(m_xa1[0].get_data(), 0, dInterpolation, m_xa1[0].get_size());
               //m_xa1[0].insert_at(0,);;

               dInterpolation = the_filter(m_ya1[0].get_data(), m_xa1[0].get_data());

               move_insert(m_ya1[0].get_data(), 0, dInterpolation, m_ya1[0].get_size());
               //m_ya1[0].insert_at(0, dInterpolation);

               //dInterpolation = chebyshevy_4rd_bs_025_05__05(m_ya1,m_xa1);

               //m_xa1.add(dInterpolation);

               //dInterpolation = butterworth_3_1_8_fs_lo_pass(m_ya1, m_xa1);

               //m_ya1.add(dInterpolation);

               //m_xa2.insert_at(0,dInterpolation);

               //dInterpolation = butterworth_4rd_bp_001_125(m_ya2,m_xa2);

               //m_ya2.insert_at(0,dInterpolation);

               //iInterpolation = iInterpolation  / iFilterSize1;

               //m_iaFilter2.add(iInterpolation);

               //if(m_iaFilter2.get_size() > iFilterSize2)
               //{
               //
               //   m_iaFilter2.erase_at(0,m_iaFilter2.get_size() - iFilterSize2);

               //}

               //int iBas = m_iaFilter2.get_total();

               dInterpolation *= 0.5;

               shInterpolation = (short)dInterpolation;

               if (dInterpolation > 32768.0)
               {

                  ::information("iInterpolation >= 32768\n");

               }
               else if (dInterpolation < -32767.0)
               {

                  ::information("iInterpolation <= -32769\n");

               }

               for (index iDstChannel = 0; iDstChannel < iDstChannelCount; iDstChannel++)
               {

                  m_pfileFrame->write(&shInterpolation, sizeof(shInterpolation));

                  dwRead += sizeof(shInterpolation);

               }

            }

            m_daLastSample.set_at_grow(0, dSample1);

         }


      }
      else if(iSrcBits == 16)
      {

         //if (m_den >= m_num)
         {

            if (iSrcChannelCount == iDstChannelCount)
            {

               if (iSrcSampFreq == iDstSampFreq)
               {

                  //                     ::u32 uPos4;
                  //                     int sh;
                  //                     int i1;

                  while (true)
                  {

                     consumed = m_src.read(&shSrc, sizeof(shSrc));

                     if (consumed < sizeof(short))
                     {

                        if (consumed == 1)
                        {

                           information("OMG");

                        }

                        break;

                     }

                     m_pfileFrame->write(&shSrc, sizeof(shSrc));

                     dwRead += sizeof(shSrc);

                  }

               }

               else if (iDstSampFreq < iSrcSampFreq)
               {

                  //int sizeShSrc = sizeof(shSrc);

                  //while (true)
                  //{

                  //   consumed = m_src.read(&shSrc, sizeShSrc);

                  //   if (consumed < sizeof(short))
                  //   {

                  //      if (consumed == 1)
                  //      {

                  //         information("OMG");

                  //      }

                  //      break;

                  //   }

                  //   m_pfileFrame->write(&shSrc, sizeShSrc);

                  //   dwRead += sizeof(shSrc);

                  //}

                  if (m_pfilter1 == nullptr)
                  {

                     m_pfilter1 = filter1_create();

                  }

                  //if (0)
                  {

                     //                     int uiPos4;
                     short sh;

                     //                     int iSample;
                     //                     char ch;
                     //                     int iSample1;
                     float dInterpolation;


                     //float dRate = (float)m_den / (float)m_num;

                     float dInverse = (float)m_num / (float)m_den;

                     //float dRate = 1.0;

                     //                     float dSample1;
                     bool bEos = false;
                     while (true)
                     {

                        i64 iBeg = (m_posSrc * (i64)m_den / (i64)m_num);

                        for (index iChannel = 0; iChannel < iSrcChannelCount; iChannel++)
                        {
                           if (bEos || m_posDst < iBeg)
                           {

                              if (m_da[iChannel].get_count() > 0)
                              {

                                 dInterpolation = m_da[iChannel].get_total() / (float) m_da[iChannel].get_size();

                                 //m_xa1[iChannel].insert_at(0, dInterpolation);

                                 //dInterpolation = chebyshevy_4rd_bs_025_05__05(m_ya1[iChannel], m_xa1[iChannel]);

                                 float f =(float) ( dInterpolation / 32768.0);

                                 //filter1_writeInput(m_pfilter1, f);

                                 //dInterpolation = filter1_readOutput(m_pfilter1);

                                 dInterpolation = f * 32768.0f;

                                 //m_ya1[iChannel].insert_at(0, dInterpolation);

                                 shInterpolation = (short)dInterpolation;

                                 if (dInterpolation >= 32768.0f)
                                 {

                                    ::information("iInterpolation >= 32768\n");

                                 }
                                 else if (dInterpolation <= -32769.0f)
                                 {

                                    ::information("iInterpolation <= -32769\n");

                                 }

                                 m_pfileFrame->write(&shInterpolation, sizeof(shInterpolation));

                                 dwRead += sizeof(shInterpolation);

                              }

                              ::count iSize = m_da[iChannel].get_size();

                              if (iSize == 0)
                              {

                                 goto end4;

                              }

                              if (iSize > dInverse || bEos)
                              {

                                 //while (m_da[iChannel].get_size() > 16 * dInverse)
                                 while (
                                 m_da[iChannel].has_elements()
                                 && (m_da[iChannel].get_size() > dInverse || bEos))
                                 {

                                    m_da[iChannel].erase_at(0);

                                 }

                                 //m_da[iChannel].erase_at(0);

                              }

                           }

                           if (!bEos)
                           {

                              consumed = m_src.erase_begin(&sh, 2);

                              if (consumed <= 1)
                              {
                                 if (!m_pplugin->audio_eof())
                                 {

                                    goto end4;

                                 }
                                 bEos = true;

                              }

                              m_da[iChannel].add(sh);

                           }



                        }
                        if (m_posDst < iBeg)
                        {

                           m_posDst = iBeg;

                        }
                        m_posSrc++;


                     }

                  }

               }
               else
               {
                  //                     int uiPos4;
                  int sh;

                  //                     int iSample;
                  //                     char ch;
                  //                     int iSample1;
                  float dInterpolation;


                  float dRate = (float)m_den / (float)m_num;

                  float dSample1;

                  for (; 1; m_iaLowerPos[0]++)
                  {

                     for (index iChannel = 0; iChannel < iSrcChannelCount; iChannel++)
                     {

                        consumed = m_src.erase_begin(&sh, 2);

                        if (consumed <= 1)
                           goto end4;

                        dSample1 = (float) sh;

                        i64 iBeg = m_iaLowerPos[0] * m_num / m_den;

                        i64 iEnd = (m_iaLowerPos[0] + m_den) * m_num / m_den;

                        for (; m_iaUpperPos[0] < iEnd; m_iaUpperPos[0]++)
                        {

                           dInterpolation = (dSample1 * (float)(m_iaUpperPos[0] - iBeg) + m_daLastSample[iChannel] * (float)(m_num - m_iaUpperPos[0] - iBeg)) / (float)m_num;

                           move_insert(m_xa1[0].get_data(), 0, dInterpolation, m_xa1[0].get_size());

                           dInterpolation = the_filter(m_ya1[iChannel], m_xa1[iChannel]);

                           move_insert(m_ya1[0].get_data(), 0, dInterpolation, m_ya1[0].get_size());

                           dInterpolation /= dRate;

                           shInterpolation = (short)dInterpolation;

                           if (dInterpolation >= 32768.0)
                           {

                              ::information("iInterpolation >= 32768\n");

                           }
                           else if (dInterpolation <= -32769.0)
                           {

                              ::information("iInterpolation <= -32769\n");

                           }

                           m_pfileFrame->write(&shInterpolation, sizeof(shInterpolation));

                           dwRead += sizeof(shInterpolation);

                        }

                        m_daLastSample[iChannel] = dSample1;

                     }

                  }

               }
end4:
               ;

            }
            else if (iSrcChannelCount == 1)
            {

               bool bOk = false;

               if (iSrcSampFreq == iDstSampFreq)
               {

                  //                     ::u32 uPos4;
                  //                     int sh;
                  //                     int i1;
                  while (true)
                  {

                     consumed = m_src.read(&shSrc, sizeof(short));
                     if (consumed <= 0)
                        break;


                     for (int j = 0; j < iDstChannelCount; j++)
                     {

                        m_pfileFrame->write(&shSrc, sizeof(shSrc));

                        dwRead += sizeof(shSrc);

                     }

                  }

                  bOk = true;

               }

               if (!bOk)
               {

                  //                     int uiPos4;
                  short sh;

                  //                     int iSample;
                  //                     char ch;
                  //                     int iSample1;
                  //float dInterpolation;


                  float dRate = (float)m_den / (float)m_num;

                  //float dSample1;

                  //                     int uiPos4;
//                     short sh;

                  //                     int iSample;
                  //                     char ch;
                  //                     int iSample1;
                  //float dInterpolation;


                  //float dRate = (float)m_den / (float)m_num;

                  //                     float dSample1;

                  //int iMeanCount = m_den / m_num;

                  if (dRate == 2.0)
                  {

                     while (m_da[0].get_count() < 2)
                     {

                        m_da[0].add(0);

                     }


                     while (true)
                     {

                        consumed = m_src.erase_begin(&sh, 2);

                        if (consumed <= 1)
                           goto end4;

                        m_da[0].erase_at(0);
                        m_da[0].add(sh);

                        shInterpolation = (short) (m_da[0].GetMean());

                        for (index i = 0; i < iDstChannelCount; i++)
                        {

                           m_pfileFrame->write(&shInterpolation, sizeof(shInterpolation));

                           dwRead += sizeof(shInterpolation);

                        }

                        for (index i = 0; i < iDstChannelCount; i++)
                        {

                           m_pfileFrame->write(&sh, sizeof(sh));

                           dwRead += sizeof(sh);

                        }

                     }

                  }
                  else if (dRate == 4.0)
                  {
                     while (m_da[0].get_count() < 2)
                     {

                        m_da[0].add(0);

                     }

                     short shInterpolation0;
                     short shInterpolation2;
                     short shLast;

                     while (true)
                     {

                        consumed = m_src.erase_begin(&sh, 2);

                        if (consumed <= 1)
                           goto end4;

                        shLast = (short)(m_da[0].pop());

                        m_da[0].add(sh);

                        shInterpolation = (short) (m_da[0].GetMean());

                        shInterpolation0 = (shInterpolation + shLast) / 2;

                        for (index i = 0; i < iDstChannelCount; i++)
                        {

                           m_pfileFrame->write(&shInterpolation0, sizeof(shInterpolation0));

                           dwRead += sizeof(shInterpolation0);

                        }


                        for (index i = 0; i < iDstChannelCount; i++)
                        {

                           m_pfileFrame->write(&shInterpolation, sizeof(shInterpolation));

                           dwRead += sizeof(shInterpolation);

                        }

                        shInterpolation2 = (sh + shInterpolation) / 2;

                        for (index i = 0; i < iDstChannelCount; i++)
                        {

                           m_pfileFrame->write(&shInterpolation2, sizeof(shInterpolation2));

                           dwRead += sizeof(shInterpolation2);

                        }


                        for (index i = 0; i < iDstChannelCount; i++)
                        {

                           m_pfileFrame->write(&sh, sizeof(sh));

                           dwRead += sizeof(sh);

                        }

                     }

                  }
                  else
                  {

                     //                     int uiPos4;
                     short sh;

                     //                     int iSample;
                     //                     char ch;
                     //                     int iSample1;
                     float dInterpolation;


                     float dRate = (float)m_den / (float)m_num;



                     while(true)
                     {

                        i64 iBegDst = m_posSrc * m_den / m_num;

                        i64 iEndDst = (m_posSrc + m_num) * m_den / m_num;

                        if(m_posDst >= iEndDst)
                        {

                           break;

                        }

                        for (; m_posDst < iEndDst; m_posDst++)
                        {

                           while (m_posDst * m_num / m_den >= m_posSrc)
                           {

                              consumed = m_src.erase_begin(&sh, 2);

                              if (consumed <= 1)
                                 goto end4;

                              m_posSrc++;

                              m_daLastSample[0] = m_fNextSample;

                              m_fNextSample = sh;

                           }


                           dInterpolation = (m_fNextSample * (float)(m_posDst- iBegDst) + m_daLastSample[0] * (float)(m_den - m_posDst + iBegDst)) / (float)m_den;

                           move_insert(m_xa1[0].get_data(), 0, dInterpolation, m_xa1[0].get_size());

                           dInterpolation = the_filter(m_ya1[0], m_xa1[0]);

                           move_insert(m_ya1[0].get_data(), 0, dInterpolation, m_ya1[0].get_size());

                           dInterpolation /= dRate;

                           shInterpolation = (short)dInterpolation;

                           if (dInterpolation >= 32768.0)
                           {

                              ::information("iInterpolation >= 32768\n");

                           }
                           else if (dInterpolation <= -32769.0)
                           {

                              ::information("iInterpolation <= -32769\n");

                           }

                           for (index i = 0; i < iDstChannelCount; i++)
                           {

                              m_pfileFrame->write(&shInterpolation, sizeof(shInterpolation));

                              dwRead += sizeof(shInterpolation);

                           }

                        }


                     }


                  }

                  //end5:;
               }
               else
               {
                  ::u32 uPos4;
                  //                     int sh;
                  //                     int i1;
                  for (::u32 uPos3 = 0; uPos3 < uRead; uPos3++)
                  {

                     consumed = m_src.read(&shSrc, sizeof(short));

                     if (consumed <= 0)
                     {

                        break;

                     }

                     for (uPos4 = 0; uPos4 < m_den; uPos4++)
                     {

                        shInterpolation = minimum(SHRT_MAX, maximum(SHRT_MIN, shSrc));

                        m_pfileFrame->write(&shInterpolation, sizeof(shInterpolation));

                        dwRead += sizeof(shInterpolation);

                     }

                  }

               }

            }

         }
         //else if (iDstChannelCount == iSrcChannelCount)
         //{
         //   int uiPos4;
         //   int sh;

         //   int iSample;
         //   char ch;
         //   int iSample1;
         //   float dInterpolation;

         //   short sh1;
         //   float dRate = (float)m_den / (float)m_num;

         //   dRate *= 4.0;

         //   float dSample1;


         //   for (; 1; )
         //   {

         //      for (index iChannel = 0; iChannel < iSrcChannelCount; iChannel++)
         //      {

         //         consumed = m_src.erase_begin(&sh1, 2);

         //         if (consumed <= 1)
         //            goto end6;

         //         dSample1 = sh1;

         //         int iBeg = m_iaUpperPos[iChannel] * m_den / m_num;

         //         int iEnd = (m_iaUpperPos[iChannel] + 1) * m_den / m_num;

         //         int iBigBeg = (iBeg / m_den) * m_den;

         //         int iBigEnd = ((iBeg + m_den) / m_den) * m_den;

         //         m_iaUpperPos[0]++;

         //         for (; m_iaLowerPos[iChannel] < iEnd; )
         //         {

         //            dInterpolation = (dSample1 * (float)(m_iaLowerPos[iChannel] - iBigBeg) + m_daLastSample[iChannel] * (float)(m_den - m_iaLowerPos[iChannel] + iBigBeg)) / (float)m_den;

         //            m_xa1[iChannel].insert_at(0, dInterpolation);

         //            dInterpolation = the_filter(m_ya1[iChannel], m_xa1[iChannel]);

         //            m_ya1[iChannel].insert_at(0, dInterpolation);


         //            dInterpolation /= dRate;

         //            shInterpolation = (short)dInterpolation;

         //            if (dInterpolation >= 32768.0)
         //            {

         //               ::information("iInterpolation >= 32768\n");

         //            }
         //            else if (dInterpolation <= -32769.0)
         //            {

         //               ::information("iInterpolation <= -32769\n");

         //            }

         //            GetMemoryFile().write(&shInterpolation, sizeof(shInterpolation));
         //            m_iaLowerPos[iChannel]++;
         //         }

         //         m_daLastSample[iChannel] = dSample1;

         //      }

         //   }
         //end6:;

         //}
      }
      else
      {

         throw ::exception(todo);

      }

      m_src.erase_begin(nullptr, (memsize)m_src.get_position());

      auto iRead = frame_file().erase_begin(lpvoidBuffer, uiBufferSize);

      if (m_pplugin->audio_eof() && iRead <= 0)
      {

         m_bDecodeEof = true;

      }

      return iRead;

   }


   bool resampler::read_source()
   {

      plugin * pplugin = m_pplugin;

      if (!pplugin->audio_is_initialized())
      {

         init_child(pplugin);

      }

      if (pplugin->audio_eof())
      {

         if (pplugin->m_bLoop || m_iAudioRead <= 0)
         {

            pplugin->audio_restart();

         }
         else
         {

            return false;

         }

      }

      ::u8 * pdata = m_memSource.get_data();

      memsize s = m_memSource.get_size();

      memsize uRead = pplugin->audio_read(pdata, s);

      //m_src.seek_to_end();

      //m_src.write(m_memSource.get_data(), uRead);

      m_src.get_memory()->append(pdata, uRead);

      return !pplugin->audio_eof();

   }


   void resampler::audio_stop()
   {

      m_bEof = true;

   }


   void resampler::audio_seek_begin()
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_iSourcePointer = 0;

      plugin::audio_seek_begin();

      //if (m_pplugin != nullptr)
      //{

      //   init_child(m_pplugin);

      //}

      m_iReadPointer = 0;

   }


   void resampler::audio_seek_end()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if(m_pplugin.is_set())
      {

         m_pplugin->audio_seek_end();

      }

      plugin::audio_seek_end();

      m_bStop = false;

      m_iReadPointer = 0;

      m_bEof = true;

   }


   i64 resampler::audio_get_sample_count()
   {

      return m_nSampleCount;

   }


   bool resampler::audio_set_non_stop_on_eof(bool bSet)
   {

      m_bNonStopOnEof = bSet;

      return m_bNonStopOnEof;

   }


   void resampler::audio_on_event(e_event eevent)
   {

      if (m_pplugin)
      {

         m_pplugin->audio_on_event(eevent);

      }

      ::audio::plugin::audio_on_event(eevent);

   }



} // namespace audio



