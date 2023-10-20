#include "framework.h"

#include <math.h>


namespace wave
{


   buffer::buffer()
   {

      m_uiBufferSize             = 0;
      m_uiAnalysisSize           = 0;
      m_uiAnalysisSizeOrder      = 0;
      m_uiAllocationSize         = 0;
      m_uiInterestSize           = 0;
      m_iSkippedSamplesCount     = 2;

   }

   buffer::~buffer()
   {

      critical_section_lock slProcLevel2(&m_csProcLevel2);
      critical_section_lock slProcLevel1(&m_csProcLevel1);

      critical_section_lock slProcResult(&m_csResult);
      m_buffera.erase_all();


   }

   bool buffer::PCMOutOpen(base * pusermessage, memsize uiBufferSize, ::count uiBufferCount, memsize uiAlign, format * lpwfexIn, format * lpwfexOut)
   {

      m_waveformatIn       = *lpwfexIn;
      m_waveformatOut      = *lpwfexOut;

      critical_section_lock slRead1(&m_csProcLevel2);

      m_uiAllocationSize = uiBufferSize * uiBufferCount;
      m_uiBufferSize = uiBufferSize;
      m_uiAlign = uiAlign;
      m_baData.set_size(m_uiAllocationSize);
      m_baBuffer.set_size(m_uiBufferSize);
      memory_set(m_baBuffer.get_data(), 0, m_uiBufferSize);

      index i;
      
      auto iSize = uiBufferCount;

      m_buffera.set_size(iSize);

      for(i = 0; i < iSize; i++)
      {

         ::wave::buffer::item * pbuffer = get_buffer(i);

         if(pbuffer == nullptr)
         {

            return false;

         }

         pusermessage->allocate_buffer_data(pbuffer, m_uiBufferSize, m_uiAlign);

         // pbuffer->m_pData = (char *) PCMOutGetBuffer(i);

         pbuffer->m_iIndex = i;

      }

      return true;

   }


   void buffer::Close(base * pusermessage)
   {

      for(index i = 0; i < m_buffera.get_size(); i++)
      {

         ::wave::buffer::item * pbuffer = m_buffera[i];

         pusermessage->free_buffer_data(pbuffer);


      }
      m_buffera.erase_all();

   }


   void buffer::FFTDoubleSetADoubleSetB(bool   bInverseTransform)
   {


      //   u32 dwTimeIn = papp->multimedia_get_time();
      //   informationf("FFT time In: %d ", dwTimeIn);
      critical_section_lock synchronouslock(&m_csProcLevel1);
      /*   m_fft.fft_double(
      m_uiAnalysisSize,
      bInverseTransform,
      m_pdProcRealA,
      m_pdProcImagA,
      m_pdProcRealB,
      m_pdProcImagB);*/
      //nspsRealFftNip(const float * inSamps, SCplx *outSamps, i32 order, i32 flags);
      //   rfftw_one((rfftw_plan) m_rfftwplan, m_pdSetA, m_pdSetB);


      //   ::time tickTimeout = papp->multimedia_get_time();
      //   informationf(" FFT time Out: %d ", tickTimeout);
      //   informationf(" FFT time delta: %d \n", tickTimeout - dwTimeIn);
      return;

      //   u32 uiNumBits;    /* Number of bits needed to store indices */
//         u32 i, j, k, n;
//         u32 uiBlockSize, uiBlockEnd;
//
//         double dAngleNumerator = 2.0 * pmathematics->get_pi();
//         //   double dTr, dTi;    /* temp real, temp imaginary */
//
//         ASSERT(::math::math::IsPowerOfTwo(m_uiBufferSize));
//
//         if (bInverseTransform)
//            dAngleNumerator = -dAngleNumerator;
//
//         //    ASSERT(m_pdProcRealA != nullptr);
//         //  ASSERT(m_pdProcRealB != nullptr);
//         //ASSERT(m_pdProcImagA != nullptr);
//         //ASSERT(m_pdProcImagB != nullptr);
//
//
//         /*
//         **    Do simultaneous data copy and bit-reversal ordering into outputs...
//         */
//         //   u32 dwTimeIn = papp->multimedia_get_time();
//         for (i = 0; i < m_uiBufferSize; i++)
//         {
//            //      j = math::ReverseBits (i, m_uiBufferSizeLog2);
//            //      m_pdProcRealB[j] = m_pdProcRealA[i];
//            //      m_pdProcImagB[j] = m_pdProcImagA[i];
//         }
//         return;
//         /*
//         **    Do the FFT itself...
//         */
//
//         uiBlockEnd = 1;
//         for (uiBlockSize = 2; uiBlockSize <= m_uiBufferSize; uiBlockSize <<= 1 )
//         {
//            double dDeltaAngle = dAngleNumerator / (double) uiBlockSize;
//            double dSinM1 = sin(-dDeltaAngle);
//            double dCosM1 = cos(-dDeltaAngle);
//            //      double dCosM2 = sqrt(1 - dSinM1 * dSinM1);
//            //      double dSinM2 = 2 * dSinM1 * dCosM1;
//            //      double cm2 = cos ( -2 * delta_angle );
//            double dSinM2 = sin(-2 * dDeltaAngle);
//            double dCosM2 = cos(-2 * dDeltaAngle);
//
//            double dW = 2 * dCosM1;
//            double ar[3], ai[3];
//            //      double dAr0, dAr1, dAr2;
//            //      double dAi0, dAi1, dAi2;
//            //      double dTemp;
//
//            for ( i=0; i < m_uiBufferSize; i += uiBlockSize)
//            {
//               ar[2] = dCosM2;
//               ar[1] = dCosM1;
//
//               //         dAr2 = dCosM2;
//               //         dAr1 = dCosM1;
//
//               ai[2] = dSinM2;
//               ai[1] = dSinM1;
//
//               //         dAi2 = dSinM2;
//               //         dAi1 = dSinM1;
//
//               for (j = i, n = 0; n < uiBlockEnd; j++, n++ )
//               {
//                  ar[0] = dW*ar[1] - ar[2];
//                  ar[2] = ar[1];
//                  ar[1] = ar[0];
//
//                  //            dAr0 = dW*dAr1 - dAr2;
//                  //            dAr2 = dAr1;
//                  //            dAr1 = dAr0;
//
//                  ai[0] = dW*ai[1] - ai[2];
//                  ai[2] = ai[1];
//                  ai[1] = ai[0];
//
//                  //            dAi0 = dW*dAi1 - dAi2;
//                  //            dAi2 = dAi1;
//                  //            dAi1 = dAi0;
//
//                  k = j + uiBlockEnd;
//                  //            dTr = ar[0] * m_pdProcRealB[k] - ai[0] * m_pdProcImagB[k];
//                  //            dTi = ar[0] * m_pdProcImagB[k] + ai[0] * m_pdProcRealB[k];
//
//                  //            m_pdProcRealB[k] = m_pdProcRealB[j] - dTr;
//                  //            m_pdProcImagB[k] = m_pdProcImagB[j] - dTi;
//
//                  //            m_pdProcRealB[j] += dTr;
//                  //            m_pdProcImagB[j] += dTi;
//               }
//            }
//
//            uiBlockEnd = uiBlockSize;
//         }
//
//         /*
//         **    Need to normalize if inverse transform...
//         */
//
//         //   if (bInverseTransform)
//         {
//            //      double denom = (double)m_uiBufferSize;
//
//            for ( i=0; i < m_uiBufferSize; i++ )
//            {
//               //         m_pdProcRealB[i] /= denom;
//               //         m_pdProcRealB[i] /= denom;
//            }
//         }
//         //   ::time tickTimeout = papp->multimedia_get_time();
//         //   informationf(" FFT time Out: %d ", tickTimeout);
//         //   informationf(" FFT time delta: %d \n", tickTimeout - dwTimeIn);
   }


   void buffer::CopyDataToDoubleSetA(index iIndex)
   {

      critical_section_lock synchronouslock(&m_csProcLevel1);

      iptr iMinA = 0;
      iptr iMaxA = 0;
      iptr iMinC = 0;
      iptr iMaxC = 0;
      iptr iMaxB = iIndex * m_uiBufferSize + m_uiBufferSize;
      iptr iMinB = iMaxB - (m_iSkippedSamplesCount * m_uiAnalysisSize);

      if(iMinB < 0)
      {

         iMinA = m_uiAllocationSize + iMinB;

         iMaxA = m_uiAllocationSize;

      }

      if(m_uiAllocationSize > iMaxB)
      {

         iMinC = 0;

         iMaxC = iMaxB - m_uiAllocationSize;

      }

      memsize i;

      memsize j = 0;

      for(i = iMinA; ::comparison::lt(i, iMaxA); i += m_iSkippedSamplesCount)
      {

         m_daSetA[j] = (double) (m_bdaData[i]);

         j++;

      }

      for(i = iMinB; ::comparison::lt(i, iMaxB); i += m_iSkippedSamplesCount)
      {

         m_daSetA[j] = (double) (m_bdaData[i]);

         j++;

      }

      for(i = iMinC; ::comparison::lt(i, iMaxC); i += m_iSkippedSamplesCount)
      {

         m_daSetA[j] = (double) (m_bdaData[i]);

         j++;

      }

   }


   void buffer::CopyDataToSetA(index iIndex)
   {

      critical_section_lock synchronouslock(&m_csProcLevel1);

      iptr iMinA = 0;
      iptr iMaxA = 0;
      iptr iMinC = 0;
      iptr iMaxC = 0;
      iptr iMaxB = iIndex * m_uiBufferSize + m_uiBufferSize;
      iptr iMinB = iMaxB - (m_iSkippedSamplesCount * m_uiAnalysisSize);

      if(iMinB < 0)
      {
         iMinA = m_uiAllocationSize + iMinB;
         iMaxA = m_uiAllocationSize;
         iMinB = 0;
      }
      if(iMaxB > m_uiAllocationSize)
      {
         iMaxB = m_uiAllocationSize;
         iMinC = 0;
         iMaxC = iMaxB - m_uiAllocationSize;
      }

      iptr i;

      iptr j = 0;

      for(i = iMinA; i < iMaxA; i += m_iSkippedSamplesCount)
      {
         m_daSetA[j] = (double) (m_bdaData[i]);
         j++;
      }
      for(i = iMinB; i < iMaxB; i += m_iSkippedSamplesCount)
      {
         m_daSetA[j] = (double) (m_bdaData[i]);
         j++;
      }
      for(i = iMinC; i < iMaxC; i += m_iSkippedSamplesCount)
      {
         m_daSetA[j] = (double) (m_bdaData[i]);
         j++;
      }

   }

   void buffer::ZeroDoubleSetAImaginary()
   {


      return;

      /*
      u32 dwTimeIn = papp->multimedia_get_time();
      informationf("zeroproc a In: %d ", dwTimeIn);
      u32 user;
      critical_section_lock synchronouslock(&m_csProcLevel1);
      for(user = 0; user < m_uiAnalysisSize; user++)
      {
         //      m_pdProcImagA[user] = 0.0;
      }
      ::time tickTimeout = papp->multimedia_get_time();
      informationf(" zeroproc a Out: %d ", tickTimeout);
      informationf(" zeroproc atime delta: %d \n", tickTimeout - dwTimeIn);
      */
   }


   void buffer::FFTOpen(
   memsize uiAllocationSize,
   memsize uiBufferSize,
   memsize uiAnalysisSize,
   memsize uiInterestSize,
   ::count uiSkippedSamplesCount)
   {
      critical_section_lock slRead1(&m_csProcLevel2);

      if(m_uiAllocationSize != uiAllocationSize)
      {
         m_uiAllocationSize = uiAllocationSize;
         m_bdaData.set_size(uiAllocationSize);
      }
      if(m_uiAnalysisSize != uiAnalysisSize)
      {

         m_uiAnalysisSize = uiAnalysisSize;
         // soma-se 0.5 para ter certeza que o arredondamento
         // acontecera correatamente
         m_uiAnalysisSizeOrder = (u32) (log((double) m_uiAnalysisSize) / log(2.0) + 0.5);


         m_daSetA.set_size(m_uiAnalysisSize);
         m_daSetB.set_size(m_uiAnalysisSize + 2);
         //m_complexa.set_size(m_uiAnalysisSize);

         m_dNominalMaxLevel = 1 << (sizeof(WAVEBUFFERDATA) * 8 - 3); //1024.0;
         m_dNominalMaxLevel = 1.0;

      }
      if(m_uiInterestSize != uiInterestSize)
      {
         m_uiInterestSize = uiInterestSize;
         m_daModuleSet.set_size(m_uiInterestSize);
         m_daResultSet.set_size(m_uiInterestSize);
      }

      m_iSkippedSamplesCount = uiSkippedSamplesCount;
      m_uiBufferSize = uiBufferSize;


      index user;

      for(user = 0; user < m_uiInterestSize; user++)
      {

         m_daResultSet[user] = 0.0f;

      }

      ::index i;

      auto iSize = GetBufferCount();

      m_buffera.set_size(iSize);

      for(i = 0; i < iSize; i++)
      {

         auto pitem = m_buffera.element_at(i);

         pitem->m_pData = &m_bdaData[i * m_uiBufferSize / sizeof(WAVEBUFFERDATA)];

         pitem->m_iIndex = (i32) i;

      }


      ZeroDoubleSetAImaginary();

      //if(m_pfft != nullptr)
      //{
      //   delete m_pfft;
      //   m_pfft = nullptr;
      //}
      //auto iPlanSize = 1 << m_uiAnalysisSizeOrder;
      //m_pfft = memory_new kissfft::fftd(iPlanSize);
   }

   void buffer::InterestCalcDoubleSetBModule()
   {

      index user;
      index uj;
      index uk;
      critical_section_lock synchronouslock(&m_csProcLevel1);
      auto iPlanSize = 1 << m_uiAnalysisSizeOrder;
      for(user = 0, uj = 0, uk = iPlanSize -1; user < m_uiInterestSize; user++)
      {
         m_daModuleSet[user] = sqrt(m_daSetB[uj] * m_daSetB[uj] + m_daSetB[uk] * m_daSetB[uk]);
         uj += 1;
         uk -= 1;
      }

   }

   void buffer::InterestCalcSetBModule()
   {

      index user;
      critical_section_lock synchronouslock(&m_csProcLevel1);
      for(user = 0; user < m_uiInterestSize; user++)
      {
         m_daModuleSet[user] = m_daSetB[user];
      }

   }


   void buffer::InterestCopyModuleToResult(double * lpdMax)
   {
      critical_section_lock slResult(&m_csResult);
      critical_section_lock slProcLevel1(&m_csProcLevel1);
      index user;
      if(lpdMax == nullptr)
      {
         for(user = 0; user < m_uiInterestSize; user++)
         {
            m_daResultSet[user] = m_daModuleSet[user];
         }
      }
      else
      {
         double d;
         double dMax = 0.0;
         for(user = 0; user < m_uiInterestSize; user++)
         {
            d = m_daResultSet[user] = m_daModuleSet[user];
            if(d > dMax)
               dMax = d;
         }
         *lpdMax = dMax;
      }

   }


   void buffer::PCMOutProcess(index iBuffer)
   {

      m_iCurrentBuffer = iBuffer;

      critical_section_lock slRead1(&m_csProcLevel2);

      ::memory_copy(PCMOutGetBuffer(iBuffer), PCMOutGetInBuffer(), PCMOutGetInBufferSize());

   }


   void buffer::FFTProcess(index iBuffer)
   {

      auto pitem = get_buffer(iBuffer);

      if (pitem->FFTProcessed())
      {

         return;

      }

      m_iCurrentBuffer = iBuffer;

      critical_section_lock slRead1(&m_csProcLevel2);

      //HighPassFilterData(); // Needed in 16 bits data samples
      //CopyDataToDoubleSetA(iBuffer);
      CopyDataToSetA(iBuffer);
      //    informationf("buffer::Process FFT In %d\n", papp->multimedia_get_time());
      //FFTDoubleSetADoubleSetB(false);
      FFTSetASetB();
      //   informationf("buffer::Process FFT Out %d\n", papp->multimedia_get_time());
      //InterestCalcDoubleSetBModule();
      InterestCalcSetBModule();
      //InterestCompressModuleSet();
      double dMax = 0.0;
      InterestCopyModuleToResult(&dMax);

      pitem->m_bFFT = true;

   }


   void buffer::HighPassFilterData()
   {

      //u32 dwTimeIn = papp->multimedia_get_time();
      WAVEBUFFERDATA wbdLast, wbdNew;
      //informationf("data to real A In: %d ", dwTimeIn);
      index user;
      critical_section_lock synchronouslock(&m_csProcLevel1);
      wbdLast = 0;
      for(user = 0; user < m_uiBufferSize; user++)
      {
         wbdNew = m_bdaData[user];
         m_bdaData[user] -= wbdLast;
         wbdLast = wbdNew;
      }
      //::time tickTimeout = papp->multimedia_get_time();
      //informationf(" data to real a Out: %d ", tickTimeout);
      //informationf(" data to real a delta: %d \n", tickTimeout - dwTimeIn);

   }


   double buffer::PeakValueFrequency(double dSampleFrequency, double * dAmplitude)
   {

      auto user = m_uiInterestSize / 20;

      double dMaxAmplitude = 0.0;

      double dPeakValue = 0.0;

      for(; user < m_uiInterestSize; user++)
      {

         if(m_daResultSet[user] > dMaxAmplitude)
         {

            dPeakValue = (double) (user);

            dMaxAmplitude = m_daResultSet[user];

         }

      }

      *dAmplitude = dMaxAmplitude;
      return dPeakValue * dSampleFrequency / m_uiAnalysisSize;
   }


   double buffer::PeakValueFrequency(double dMin, double dMax, double dSampleFrequency, double * dAmplitude)
   {
      index user;
      double dMaxAmplitude = 0.0;
      double dPeakValue = 0.0;
      index uiMax = (u32) (dMax * m_uiAnalysisSize / dSampleFrequency);
      index uiMin = (u32) (dMin * m_uiAnalysisSize / dSampleFrequency);
      for(user = uiMin; user <= uiMax; user++)
      {
         if(m_daResultSet[user] > dMaxAmplitude)
         {
            dPeakValue = (double) user;
            dMaxAmplitude = m_daResultSet[user];
         }
      }
      *dAmplitude = dMaxAmplitude;
      return dPeakValue * dSampleFrequency / m_uiAnalysisSize;
   }


   double buffer::PeakValueFrequency(double * dAmplitude)
   {
      index user;
      double dMaxAmplitude = 0.0;
      double dPeakValue = 0.0;
      for(user = 0; user < m_uiInterestSize; user++)
      {
         if(m_daResultSet[user] > dMaxAmplitude)
         {
            dPeakValue = (double) user;
            dMaxAmplitude = m_daResultSet[user];
         }

      }

      *dAmplitude = dMaxAmplitude;

      return dPeakValue;

   }


   void buffer::PeakValueFrequencies(f64_array & daFreq, f64_array & daAmp, ::count iCount)
   {

      UNREFERENCED_PARAMETER(daAmp);

      index user;

      double dLimitAmplitude = 0.0;

      double dMaxAmplitude;

      double dPeakValue;

      for(auto i = 0; i < iCount; i++)
      {
         dMaxAmplitude = 0.0;
         dPeakValue = 0.0;
         for(user = 0; user < m_uiInterestSize; user++)
         {
            if(m_daResultSet[user] > dMaxAmplitude && daFreq.find_first((double) user) < 0)
            {
               dPeakValue = (double) user;
               dMaxAmplitude = m_daResultSet[user];
            }
         }
         if(dMaxAmplitude < 0.5)
            break;
         daFreq.add(dPeakValue);
         daFreq.add(dMaxAmplitude);
         dLimitAmplitude = dMaxAmplitude;
      }
   }

   void * buffer::get_buffer_data(index iIndex)
   {

      ASSERT(iIndex >= 0);

      ASSERT((iIndex * m_uiBufferSize) < m_uiAllocationSize);

      return &m_bdaData[iIndex * m_uiBufferSize];

   };


   ::u8 * buffer::PCMOutGetBuffer(index iIndex)
   {

      ASSERT(iIndex >= 0);

      ASSERT((iIndex * m_uiBufferSize) < m_uiAllocationSize);

      return (::u8 *) m_buffera[iIndex]->m_pData;

   }


   ::count buffer::GetBufferCount()
   {

      if(m_uiBufferSize == 0)
         return 0;

      return m_uiAllocationSize / m_uiBufferSize;

   }


   buffer::item * buffer::get_buffer(index iIndex)
   {

      if(iIndex < 0 || iIndex >= GetBufferCount())
      {

         return nullptr;

      }

      if (!m_buffera[iIndex].is_set())
      {

         m_buffera[iIndex].create_new();

      }

      return m_buffera[iIndex];

   }


   void buffer::InterestCompressModuleSet()
   {
      //u32 dwTimeIn = papp->multimedia_get_time();
      //informationf("compress module In: %d ", dwTimeIn);

      index user;
      critical_section_lock synchronouslock(&m_csProcLevel1);
      double dr = 32767.0 / log(32767.0);
      for(user = 0; user < m_uiInterestSize; user++)
      {
         m_daModuleSet[user] = log(m_daModuleSet[user]) * dr;
      }
      //::time tickTimeout = papp->multimedia_get_time();
      //informationf(" compress module Out: %d ", tickTimeout);
      //informationf(" compress module delta: %d \n", tickTimeout - dwTimeIn);

   }

   double buffer::GetMaxLevel()
   {
      return m_dNominalMaxLevel;
   }


   bool buffer::item::OnMultimediaDone()
   {

      m_bFFT = false;

      return true;

   }


   bool buffer::item::FFTProcessed()
   {

      return m_bFFT;

   }


   void buffer::FFTSetASetB()
   {

      critical_section_lock synchronouslock(&m_csProcLevel1);

      //m_pfft->fft(m_daSetA.get_data(), m_complexa.get_data());

      //double dLog = log(sizeof(m_pucData[0]) * 8.0) / log(2.0);
      //double dLog = 1.0;
      //double dDiv = pow(2.0, sizeof(m_baData[0]) * 8.0 / 2.0) * m_uiAnalysisSize * dLog;
      //double dPeakValue = 0.0;
      //auto iCount = m_uiAnalysisSize / 2 + 1;
      //for(memsize i = 0; i < iCount; i++)
      //{
      //   m_daSetB[i] = m_complexa[i].mod() / (double) dDiv;
      //   if(m_daSetB[i] > dPeakValue)
      //   {
      //      dPeakValue = m_daSetB[i];
      //   }
      //}


      //informationf("FFT Peak Value: %f\n", dPeakValue);

   }



   double * buffer::FFTGetResult()
   {
      return m_daResultSet.get_data();
   };


   void * buffer::PCMOutGetInBuffer()
   {

      return m_baBuffer.get_data();

   }


   memsize buffer::PCMOutGetInBufferSize()
   {

      return m_uiBufferSize;

   }

   void * buffer::item::get_os_data()
   {

      return m_posdata;

   }


} // namespace wave



