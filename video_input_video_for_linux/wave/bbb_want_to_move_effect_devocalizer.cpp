#include "framework.h"

#include <math.h>


namespace wave
{


   wave_effect_devocalizer::wave_effect_devocalizer(bool bEnable, i32 iSampleCount, i32 iSamplesPerSecond, i32 iDivisionCount, i32 iGroupCount)
   {


      m_iChannelCount = 2;

      m_bEnable = bEnable;

      m_iSamplesPerSecond = iSamplesPerSecond;
      m_iDivisionCount = iDivisionCount;
      m_iGroupCount = iGroupCount;
      m_iSampleCount = iSampleCount;
      m_pfft = __new(kissfft::fftd(m_iSampleCount));
      m_pifft = __new(kissfft::ifftd(m_iSampleCount));

      double fMinFreq = 110.0; // Hz
      double fMaxFreq = 1000.0; // Hz

      m_iMin = GetFrequencyIndex(fMinFreq);
      m_iMax = GetFrequencyIndex(fMaxFreq);
      m_iCancelNoteCount = 1;
      m_wDiv = 30;

      m_iInputDivisionCount = 0;
      m_iFirstInputDivision = 0;
      m_iFirstChunk = 0;
      m_iChunkCount = 0;
      m_iFirstInputGroup = 0;
      m_iInputGroupCount = 0;
      m_iOutChunk = 0;
      m_iOutDivision = 0;
      m_iOutputCount = 0;
      m_iOutputGroup = 0;
      m_iFirstOutput = 0;

      //m_f2aMax.set_size(m_iChannelCount);
      //m_i2aMax.set_size(m_iChannelCount);

      //index i;
      //for(i = 0; i < m_iChannelCount; i++)
      //{
      //   m_f2aMax[i].set_size(m_iMax - m_iMin + 1);
      //   //m_f2aMax[i].AddCoupledSwapInterface(&m_i2aMax[i]);
      //   m_i2aMax[i].set_size(m_iMax - m_iMin + 1);
      //}


      m_chunka.set_size(iGroupCount / iDivisionCount + 2);
      m_chunkaOut.set_size(m_chunka.get_size());
      m_groupa.set_size(m_chunka.get_size() * m_iDivisionCount);

      //for(i = 0; i < m_groupa.get_size(); i++)
      //{
      //   m_groupa[i]->Initialize(this);
      //}

      //for(i = 0; i < m_chunka.get_size(); i++)
      //{
      //   m_chunka[i].Initialize(this);
      //}

      //for(i = 0; i < m_chunkaOut.get_size(); i++)
      //{
      //   m_chunkaOut[i].Initialize(this);
      //}

      m_chunk.Initialize(this);

      m_iDivisionSampleCount = m_iSampleCount / m_iDivisionCount;

   }

   effect_devocalizer::~effect_devocalizer()
   {
         
   }

   void effect_devocalizer::Chunk::Initialize(effect_devocalizer * pparent)
   {
      m_pparent = pparent;
      i32 iSampleCount = pparent->m_iSampleCount;
      i32 iChannelCount = m_pparent->m_iChannelCount;
      m_sha.set_size(iSampleCount * iChannelCount);
      memory_set(m_sha.get_data(), 0, sizeof(i16) * iSampleCount * iChannelCount);
   }


   bool effect_devocalizer::Process(i16 * pshIn, i16 * pshOut)
   {
      if(!m_bEnable)
      {
         ::memory_copy(pshOut, pshIn, m_iSampleCount * 2 * 2);
         return true;
      }

      if(m_iChunkCount <= 0)
      {
         m_iFirstChunk = 0;
         m_iChunkCount = 1;
      }
      else
      {
         m_iChunkCount++;
      }

      m_iInputDivisionCount += m_iDivisionCount;

      i32 iChunk = (m_iFirstChunk + m_iChunkCount - 1) % m_chunka.get_size();


      m_chunka[iChunk].Input(pshIn);

      ChunkToGroup();

      GroupToOutput();

      return Output(pshOut);

   }


   memsize effect_devocalizer::Process16bits(i16 * pshStream, ::count iCount)
   {
      __UNREFERENCED_PARAMETER(pshStream);
      /* bool bDiff     = false;
      bool bFilter   = true;

      double * pfL = m_pfL1;
      double * pfR = m_pfR1;
      i16 * psh = pshStream;
      double * pfL2;
      double * pfR2;

      i32 iDivisor;

      for(i32 i = 0; i < 16 * 1024; i++)
      {
      *pfL++ = *psh++;
      *pfR++ = *psh++;
      }

      pfL = m_pfL1;
      pfR = m_pfR1;
      double * pfL3 = m_pfL3;
      double * pfR3 = m_pfR3;

      iDivisor = 0;

      if(bDiff)
      {
      iDivisor += 3;
      for(i = 0; i < 16 * 1024; i++)
      {
      *pfL3 = (*pfL++ - *pfR++) * 3;
      *pfR3 = *pfL3;
      *pfL3++;
      *pfR3++;
      }
      }
      else
      {
      iDivisor += 1;
      for(i = 0; i < 16 * 1024; i++)
      {
      *pfL3++ = 0.0f;
      *pfR3++ = 0.0f;
      }
      }

      if(bFilter)
      {
      iDivisor += 1;

      double fMod;
      const i32 iMaxCount = 3;
      CBaseSortArray < double, double > m_faMax;
      Carray < i32, i32 > m_iaMax;

      m_faMax.AddCoupledSwapInterface(&m_iaMax);
      //double pfMax[iMaxCount];
      //i32 piMax[iMaxCount];

      m_pfftd->Fft(m_pfL1, m_pcpxL);
      double fMean;
      double fArea = 0.0;
      for(i = 0; i < 8 * 1024 + 1; i++)
      {
      m_pcpxL[i].r /= 16384 / 2;
      m_pcpxL[i].i /= 16384 / 2;
      m_pfMod[i] = sqrt(m_pcpxL[i].r * m_pcpxL[i].r + m_pcpxL[i].i * m_pcpxL[i].i);
      fArea += m_pfMod[i];
      }
      fMean = fArea / (8 * 1024 + 1);
      // 82 -> 220 Hz
      // 163 -> 440 Hz
      i32 j;
      i32 iBin;
      for(i = 82; i <= 326; i++)
      {
      fMod = 0.0f;
      for(j = 1;;j++)
      {
      iBin = i * j;
      if(iBin > (2 * 1024 + 1))
      break;
      fMod += m_pfMod[iBin];
      }
               for(j = 2;;j++)
      {
      iBin = i / j;
      if(iBin < 82)
      break;
      fMod += m_pfMod[iBin];
      }*/

      /*     m_faMax.add(fMod);
      m_iaMax.add(i);
      }
      i32 wDiv = 10;
      //goto breakFilter1;
      m_faMax.quick_sort();

      double wHalf;

      //if(false)
      i32 k;
      i32 iMax;
      double fMax;
      double fFirstMax = m_faMax[m_iaMax.get_size() - 1];
      double fRate = fMean * 5.0f / fFirstMax;
      double fDiv;
      double fTonic;
      for(k = 0; k < 5; k++)
      {
      fMax = m_faMax[m_iaMax.get_size() - k - 1];
      if(fMax < 100)
      break;
      iMax = m_iaMax[m_iaMax.get_size() - k - 1];
      double dFreq = iMax * (44100.0 / 2)/ (16 * 1024 / 2);
      for(i = 1;;i++)
      {
      iBin = iMax * i;
      if(iBin > 1536)
      break;
      fTonic = maximum(11.0f - i, 1.0) * 10.0;
      wHalf = iBin / wDiv;
      for(j = - wHalf + 1; j < wHalf; j++)
      {
      fDiv = fTonic * (wHalf - abs(j));
      m_pcpxL[iBin + j].r /= fDiv;
      m_pcpxL[iBin + j].i /= fDiv;
      }
                  m_pcpxL[iBin - 1].r = 0;
      m_pcpxL[iBin - 1].i = 0;
      m_pcpxL[iBin].r = 0;
      m_pcpxL[iBin].i = 0;
      m_pcpxL[iBin + 1].r = 0;
      m_pcpxL[iBin + 1].i = 0;
      m_pcpxL[iBin + 2].r = 0;
      m_pcpxL[iBin + 2].i = 0;*/
      //   }
      /*         for(i = 2;;i++)
      {
      iBin = iMax / i;
      if(iBin < 82)
      break;
      wHalf = iBin / wDiv;
      for(j = -wHalf; j <= wHalf; j++)
      {
      m_pcpxL[iBin + j].r /= (wHalf - abs(j));
      m_pcpxL[iBin + j].i /= (wHalf - abs(j));
      }
      }*/
      /*      }
      //m_pcpxL[i].r /= 16384;
      //m_pcpxL[i].i /= 16384;
      breakFilter1:
      m_pffti->Fft(m_pcpxL, m_pfL2);



      m_pfftd->Fft(m_pfR1, m_pcpxR);
      for(i = 0; i < 8 * 1024 + 1; i++)
      {
      //m_pcpxR[i].r /= 16384;
      //m_pcpxR[i].i /= 16384;
      m_pcpxR[i].r = 0;
      m_pcpxR[i].i = 0;
      }
      m_pffti->Fft(m_pcpxR, m_pfR2);
      }
      else
      {
      pfL  = m_pfL1;
      pfR  = m_pfR1;
      pfL2 = m_pfL2;
      pfR2 = m_pfR2;
      iDivisor += 1;
      for(i = 0; i < 16 * 1024; i++)
      {
      *pfL2++ = 0;
      *pfR2++ = 0;
      }
      }


      pfL  = m_pfL1;
      pfR  = m_pfR1;
      pfL2 = m_pfL2;
      pfR2 = m_pfR2;
      pfL3 = m_pfL3;
      pfR3 = m_pfR3;

      for(i = 0; i < 16 * 1024; i++)
      {
      *pfL++ = *pfL2++ + *pfL3++;
      *pfR++ = *pfR2++ + *pfR3++;
      }

      pfL = m_pfL1;
      pfR = m_pfR1;
      psh = pshStream;

      iDivisor *= 2;

      for(i = 0; i < 16 * 1024; i++)
      {
      *psh++ = *pfL++ / iDivisor;
      *psh++ = *pfR++ / iDivisor;
      }
      return iCount;
      */
      return iCount;
   }

   effect_devocalizer::Group::Group()
   {
   }

   void effect_devocalizer::Group::Initialize(effect_devocalizer * pparent)
   {
      m_pparent = pparent;
      i32 iSampleCount = pparent->m_iSampleCount;
      m_channela.set_size(pparent->m_iChannelCount);

      for(i32 i = 0; i < m_channela.get_size(); i++)
      {
         m_channela[i]->Initialize(this);
      }
      m_daMod.set_size(iSampleCount);
   }

   void effect_devocalizer::Group::Channel::Initialize(Group * pgroup)
   {
      m_pgroup = pgroup;
      i32 iSampleCount = m_pgroup->m_pparent->m_iSampleCount;
      m_da1.set_size(iSampleCount);
      m_da2.set_size(iSampleCount);
      m_da3.set_size(iSampleCount);
      m_complexa.set_size(iSampleCount / 2 + 1);
      m_faMax.set_size(m_pgroup->m_pparent->m_iMax - m_pgroup->m_pparent->m_iMin + 1);
      m_iaMax.set_size(m_pgroup->m_pparent->m_iMax - m_pgroup->m_pparent->m_iMin + 1);
   }


   bool effect_devocalizer::GroupToOutput()
   {

      //index i;
      //index iGroup;
      //index j;
      //index k;

      //while(m_iInputGroupCount >= m_iGroupCount)
      //{

      //   for(k = 0; k < m_f2aMax.get_size(); k++)
      //   {
      //      for(j = m_iMin; j <= m_iMax; j++)
      //      {
      //         m_f2aMax[k][j - m_iMin] = 0.0;
      //         m_i2aMax[k][j - m_iMin] = (int)j;
      //         for(i = 0; i < m_iGroupCount; i++)
      //         {
      //            iGroup = i + m_iOutputGroup;
      //            iGroup %= m_groupa.get_size();
      //            m_f2aMax[k][j - m_iMin] += m_groupa[i]->m_channela[k]->m_faMax[j - m_iMin];
      //         }
      //      }
      //      m_f2aMax[k].quick_sort();
      //   }



      //   i32 n = m_iDivisionSampleCount * m_iChannelCount * m_iOutDivision;

      //   m_groupa[m_iOutputGroup]->Output1(&m_chunkaOut[m_iOutChunk].m_sha[n]);

      //   i32 iOutDiv2 = m_iOutDivision;
      //   i32 iOutChk2 = m_iOutChunk;

      //   iOutDiv2++;
      //   if(iOutDiv2 >= m_iDivisionCount)
      //   {
      //      iOutDiv2 = 0;
      //      iOutChk2++;
      //      if(iOutChk2 >= m_chunkaOut.get_size())
      //         iOutChk2 = 0;
      //   }
      //   n = m_iDivisionSampleCount * m_iChannelCount * iOutDiv2;
      //   if(m_iGroupCount > 1)
      //   {
      //      m_groupa[m_iOutputGroup]->Output2(&m_chunkaOut[iOutChk2].m_sha[n]);
      //   }

      //   m_iOutputGroup = (m_iOutputGroup + 1) % m_groupa.get_size();

      //   m_iOutDivision++;
      //   if(m_iOutDivision >= m_iDivisionCount)
      //   {
      //      m_iOutDivision = 0;
      //      m_iOutChunk++;
      //      if(m_iOutChunk >= m_chunkaOut.get_size())
      //         m_iOutChunk = 0;
      //   }

      //   m_iOutputCount++;

      //   m_iInputGroupCount--;

      //   /*   m_iFirstOutputGroup++;
      //   if(m_iFirstOutputGroup >= m_groupa.get_size())
      //   m_iFirstOutputGroup = 0;
      //   m_iOutputGroupCount--;
      //   m_iFirstInputDivision++;
      //   if(m_iFirstInputDivision >= m_chunka.get_size() * m_iDivisionCount)
      //   m_iFirstInputDivision = 0;
      //   m_iInputDivisionCount--;*/
      //}

      return true;
   }


   bool effect_devocalizer::Output(i16 * psh)
   {
      if(m_iOutputCount < m_iDivisionCount)
      {
         return false;
      }

      ::memory_copy(psh, m_chunkaOut[m_iFirstOutput].m_sha.get_data(), m_iSampleCount * sizeof(i16) * m_iChannelCount);

      m_iFirstOutput++;
      if(m_iFirstOutput >= m_chunkaOut.get_size())
         m_iFirstOutput = 0;

      m_iOutputCount -= m_iDivisionCount;

      return true;
   }

   bool effect_devocalizer::Chunk::Input(i16 * pshStream)
   {
      ::memory_copy(m_sha.get_data(), pshStream, m_pparent->m_iSampleCount * 2 * m_pparent->m_iChannelCount);
      return true;
   }


   effect_devocalizer::Group::Channel::Channel()
   {
   }


   void effect_devocalizer::Group::Channel::Input(bool bFilter)
   {
      i32 i; //  k;
      i32 iSampleCount = m_pgroup->m_pparent->m_iSampleCount;
      //   i32 iBinCount = iSampleCount / 2 + 1;
      //double wDiv = m_pgroup->m_pparent->m_wDiv;

//         if(false)
//         {
//            m_pgroup->m_dDivisor += 1.9;
//
//            double fMod;
//            //      const i32 iMaxCount = 3;
//
//            m_pgroup->m_pparent->m_spfftd->fft(m_da1.get_data(), m_cpxa.get_data());
//            double fMean;
//            double fArea = 0.0;
//            double fDiv;
//            double fTonic;
//            double wHalf;
//            i32 iBinCount = iSampleCount / 2 + 1;
//            for(i = 0; i < iBinCount; i++)
//            {
//               m_cpxa[i].r /= 16384.0 / 2.0;
//               m_cpxa[i].i /= 16384.0 / 2.0;
//               m_pgroup->m_daMod[i] = (double) ::sqrt(m_cpxa[i].r * m_cpxa[i].r + m_cpxa[i].i * m_cpxa[i].i);
//               fArea += m_pgroup->m_daMod[i];
//            }
//            fMean = fArea / iBinCount;
//            i32 j;
//            i32 iBin;
//            for(i = m_pgroup->m_pparent->m_iMin; i <= m_pgroup->m_pparent->m_iMax; i++)
//            {
//               fMod = 0.0f;
//               for(j = 1; j < 5; j++)
//               {
//                  iBin = i * j;
//                  if(iBin > iBinCount)
//                     break;
//
//                  fTonic = (double) (maximum(11.0f - i, 1.0) * 45.0);
//                  wHalf = iBin / wDiv;
//                  for(k = (i32) -wHalf; k <= (i32) wHalf; k++)
//                  {
//                     fDiv = (double) fabs(fTonic * (wHalf - abs(k) + 1));
//                     if((iBin + k)> iBinCount)
//                        break;
//                     fMod += m_pgroup->m_daMod[iBin + k] / fDiv;
//                  }
//                  //fMod += m_pgroup->m_pfMod[iBin];
//               }
//               /*         for(j = 2;;j++)
//               {
//               iBin = i / j;
//               if(iBin < 82)
//               break;
//               fMod += m_pfMod[iBin];
//               }*/
//
//               m_faMax[i - m_pgroup->m_pparent->m_iMin] = fMod;
//               m_iaMax[i - m_pgroup->m_pparent->m_iMin] = i;
//               if(i == 91)
//               {
//                  //information("Input iaMax = %d fMod = %f\n", i, fMod);
//               }
//            }
//            //      i32 wDiv = 10;
//
//
//
//
//         }
      if(bFilter)
      {
         m_pgroup->m_dDivisor += 1.5 ;

         double fDivisor = iSampleCount / 4.0f;
         if(m_pgroup->m_pparent->m_iGroupCount > 1)
         {
            fDivisor = iSampleCount * 2.0f;
         }

         //      const i32 iMaxCount = 3;

         m_pgroup->m_pparent->m_pfft->fft(m_da1.get_data(), m_complexa.get_data());
         //      double fArea = 0.0;
         i32 iBinCount = iSampleCount / 2 + 1;
         i32 iLBin = m_pgroup->m_pparent->GetFrequencyIndex(220.0);
         i32 iUBin = m_pgroup->m_pparent->GetFrequencyIndex(4000.0);

         for(i = 0; i < iLBin; i++)
         {
            m_complexa[i].r /= fDivisor;
            m_complexa[i].i /= fDivisor;
         }
         for(; i < iUBin; i++)
         {
            m_complexa[i].r = 0.0f;
            m_complexa[i].i = 0.0f;
         }
         for(; i < iBinCount; i++)
         {
            m_complexa[i].r /= fDivisor;
            m_complexa[i].i /= fDivisor;
         }




      }
      else
      {
         double * pf2 = m_da2.get_data();
         m_pgroup->m_dDivisor += 1;
         for(i = 0; i < iSampleCount; i++)
         {
            *pf2++ = 0;
         }
      }
   }

   bool effect_devocalizer::Group::Input(i16 * pshStream)
   {
      bool bDiff     = true;
      bool bFilter   = true;

      double * pfL = m_channela[0]->m_da1.get_data();
      double * pfR = m_channela[1]->m_da1.get_data();
      i16 * psh = pshStream;
      double * pfL2;
      double * pfR2;
      double * pfL3_;
      double * pfR3_;

      i32 iSampleCount = m_pparent->m_iSampleCount;

      i32 i;
      for(i = 0; i < iSampleCount; i++)
      {
         *pfL++ = *psh++;
         *pfR++ = *psh++;
      }


      pfL   = m_channela[0]->m_da1.get_data();
      pfR   = m_channela[1]->m_da1.get_data();
      pfL3_ = m_channela[0]->m_da3.get_data();
      pfR3_ = m_channela[1]->m_da3.get_data();

      m_dDivisor = 0;

      if(bDiff)
      {
         m_dDivisor += 1.0;
         for(i = 0; i < iSampleCount; i++)
         {
            *pfL3_ = (double) ((*pfL - *pfR) / 1.0);
            *pfR3_ = *pfL3_;
            pfL3_++;
            pfR3_++;
            pfL++;
            pfR++;
         }
      }
      else
      {
         m_dDivisor += 1.0;
         for(i = 0; i < iSampleCount; i++)
         {
            *pfL3_++ = 0.0f;
            *pfR3_++ = 0.0f;
         }
      }

      m_channela[0]->Input(bFilter);
      m_channela[1]->Input(bFilter);


      if(!bDiff && !bFilter)
      {
         pfL   = m_channela[0]->m_da1.get_data();
         pfR   = m_channela[1]->m_da1.get_data();
         pfL2  = m_channela[0]->m_da2.get_data();
         pfR2  = m_channela[1]->m_da2.get_data();
         m_dDivisor += 1.0;
         for(i = 0; i < iSampleCount; i++)
         {
            *pfL2++ = *pfL++;
            *pfR2++ = *pfR++;
         }
      }

      return true;

   }

   void effect_devocalizer::Group::Channel::Output(
      sort_array < double > & faMax,
      int_array & iaMax)
   {

      //   double * pfL = m_pf1;
      //double wHalf;

      //i32 iSampleCount = m_pgroup->m_pparent->m_iSampleCount;
      //i32 iBinCount = iSampleCount / 2 + 1;

//         i32 iMaxVoiceBin = m_pgroup->m_pparent->GetFrequencyIndex(8000.0);
//         i32 i;
//         i32 iBin;
//         double wDiv = m_pgroup->m_pparent->m_wDiv;
//         i32 j;
      //if(false)
//         i32 k;
//         i32 iMax;
//         double fMax;
      //   double fFirstMax = faMax[m_iaMax.get_size() - 1];
      //      double fRate = fMean * 5.0f / fFirstMax;
//         double fDiv;
//         double fTonic;
      i32 iCount = m_pgroup->m_pparent->m_iSampleCount / 2 + 1;
      int_array ia;
      ia.set_size(iCount);
//         if(false)
//         {
//            for(k = 0; k < m_pgroup->m_pparent->m_iCancelNoteCount; k++)
//            {
//               fMax = faMax[m_iaMax.get_size() - k - 1];
//               iMax = iaMax[m_iaMax.get_size() - k - 1];
//               information("Output iMax = %d fMax = %f\n", iMax, fMax);
//
//               //         double dFreq = iMax * (m_pgroup->m_pparent->m_iSamplesPerSecond)/ (iBinCount);
//               for(i = 1;; i++)
//               {
//                  iBin = iMax * i;
//                  if(iBin > iMaxVoiceBin)
//                     break;
//                  if(iBin > iBinCount)
//                     break;
//                  fTonic = (double) (maximum(6.0f - i, 1.0) * 90.0);
//                  wHalf = iBin / (wDiv + i);
//                  for(j = (i32) (-wHalf + 1.0f); j < (i32) wHalf; j++)
//                  {
//                     fDiv = fTonic * (wHalf - abs(j));
//                     if(iBin + j> iMaxVoiceBin)
//                        break;
//                     m_cpxa[iBin + j].r /= fDiv;
//                     m_cpxa[iBin + j].i /= fDiv;
//                     ia[iBin + j] = 1;
//                  }
//               }
//            }
//         }
      /*
      for(j = 0; j < iCount; j++)
      {
      if(ia[j] <= 0)
      {
      m_pcpx[j].r = 0.0;
      m_pcpx[j].i = 0.0;
      }
      }
      */
      m_pgroup->m_pparent->m_pifft->ifft(m_complexa.get_data(), m_da2.get_data());
   }

   bool effect_devocalizer::Group::Output1(i16 * pshStream)
   {

      index i;

      //for(i = 0; i < m_pparent->m_iChannelCount; i++)
      //{

      //   m_channela[i]->Output(m_pparent->m_f2aMax[i], m_pparent->m_i2aMax[i]);

      //}

      double * pfL = m_channela[0]->m_da1.get_data();
      double * pfR = m_channela[1]->m_da1.get_data();
      i16 * psh = pshStream;
      double * pfL2;
      double * pfR2;
      double * pfL3_;
      double * pfR3_;


      pfL  = m_channela[0]->m_da1.get_data();
      pfR  = m_channela[1]->m_da1.get_data();
      pfL2 = m_channela[0]->m_da2.get_data();
      pfR2 = m_channela[1]->m_da2.get_data();
      pfL3_ = m_channela[0]->m_da3.get_data();
      pfR3_ = m_channela[1]->m_da3.get_data();

      i32 iCount = m_pparent->m_iDivisionSampleCount * 2;

      for(i = 0; i < iCount; i++)
      {
         *pfL++ = *pfL2++ + *pfL3_++;
         *pfR++ = *pfR2++ + *pfR3_++;
      }

      pfL  = m_channela[0]->m_da1.get_data();
      pfR  = m_channela[1]->m_da1.get_data();
      psh = pshStream;

      m_dDivisor *= 1.2f;

      if(m_pparent->m_iGroupCount > 1)
      {
         m_dDivisor /= 3.2f;
      }

      //iDivisor = 1;

      iCount /= 2;

      double f;

      if(m_pparent->m_iGroupCount > 1)
      {
         for(i = 0; i < iCount; i++)
         {
            f = ((double)*psh + *pfL++) / m_dDivisor;

            if(f >= 32767.0f)
               *psh = 32767;
            else if(f <= -32768.0f)
               *psh = -32768;
            else
               *psh = (i16) f;
            psh++;

            f = ((double)*psh + *pfR++) / m_dDivisor;
            if(f >= 32767.0f)
               *psh = 32767;
            else if(f <= -32768.0f)
               *psh = -32768;
            else
               *psh = (i16) f;
            psh++;
         }
      }
      else
      {
         for(i = 0; i < iCount; i++)
         {
            f = *pfL++ / m_dDivisor;
            if(f >= 32767.0f)
               *psh = 32767;
            else if(f <= -32768.0f)
               *psh = -32768;
            else
               *psh = (i16) f;
            psh++;

            f = *pfR++ / m_dDivisor;
            if(f >= 32767.0f)
               *psh = 32767;
            else if(f <= -32768.0f)
               *psh = -32768;
            else
               *psh = (i16) f;
            psh++;
         }
      }

      return true;
   }

   bool effect_devocalizer::Group::Output2(i16 * pshStream)
   {

      i32 iCount = m_pparent->m_iDivisionSampleCount;
      double * pfL = &m_channela[0]->m_da1[iCount];
      double * pfR = &m_channela[1]->m_da1[iCount];

      i16 * psh = pshStream;



      for(i32 i = 0; i < iCount; i++)
      {
         *psh++ = (i16) *pfL++;
         *psh++ = (i16) *pfR++;
      }

      return true;
   }


   bool effect_devocalizer::IsEnabled()
   {
      return m_bEnable;
   }

   void effect_devocalizer::Enable(bool bSet)
   {
      m_bEnable = bSet;
   }

   void effect_devocalizer::PrepareChunk(i32 iDivision)
   {
      i32 i;
      i32 n;
      i32 s;
      i32 iLChunk = iDivision / m_iDivisionCount;
      i32 iLDivision = iDivision % m_iDivisionCount;
      i32 iUChunk = ((iDivision + m_iDivisionCount - 1) / m_iDivisionCount) % m_chunka.get_size();
      i32 iUDivision = (iDivision + m_iDivisionCount - 1) % m_iDivisionCount;

      s = m_iSampleCount * m_iChannelCount;

      i = s * iLDivision / m_iDivisionCount;
      n = s - i;
      ::memory_copy(m_chunk.m_sha.get_data(), &m_chunka[iLChunk].m_sha[i], n * 2);

      i32 j = n;

      if(iUChunk != iLChunk)
      {
         n = s * (iUDivision + 1) / m_iDivisionCount;
         ::memory_copy(&m_chunk.m_sha[j], m_chunka[iUChunk].m_sha.get_data(), n * 2);
      }
   }

   void effect_devocalizer::InputChunk()
   {
      m_iInputGroupCount++;
      m_iFirstInputGroup = (m_iFirstInputGroup + 1) % m_groupa.get_size();

      m_groupa[m_iFirstInputGroup]->Input(m_chunk.m_sha.get_data());


   }

   void effect_devocalizer::ChunkToGroup()
   {
      while(m_iInputDivisionCount >= m_iDivisionCount)
      {
         PrepareChunk(m_iFirstInputDivision);
         InputChunk();
         m_iFirstInputDivision++;
         if(m_iFirstInputDivision >= m_groupa.get_size())
            m_iFirstInputDivision = 0;
         m_iInputDivisionCount--;
      }

   }

   i32 effect_devocalizer::GetFrequencyIndex(double dFrequency)
   {
      return (i32) (dFrequency * (m_iSampleCount / 2) / (m_iSamplesPerSecond / 2));
   }


} // namespace wave



