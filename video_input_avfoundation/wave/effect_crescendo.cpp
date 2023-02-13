#include "framework.h"



namespace wave
{


   effect_crescendo::effect_crescendo()
   {
      m_bSustain     = true;
      m_bTriggerEnd  = true;
   }

   effect_crescendo::~effect_crescendo()
   {

   }

   void effect_crescendo::SetLengthMillis(u32 dwMillis, u32 dwSamplesPerSec)
   {
      m_iLength = dwSamplesPerSec * dwMillis / 1000;
   }

   //void effect_crescendo::SetFinalScale(i16 shMul, i16 shDiv)
   //{
   //   m_shFinalScaleDiv = shMul;
   //   m_shFinalScaleMul = shDiv;
   //}


   memsize effect_crescendo::Process16bits(i16 * pshStream, ::count iCountParam)
   {

      ::count iCount = (count) minimum(iCountParam, m_iLength - m_iStep);

      i16 * psh = pshStream;
      i32 i;
      for(i = 0; i < iCount; i++)
      {
         m_dCurrentRate = 1.0 - ((double)m_iStep / (double) m_iLength - 1.0) * ((double)m_iStep / (double)m_iLength - 1.0);
         psh[0] = (i16) (psh[0] * m_dCurrentRate);
         psh[1] = (i16) (psh[1] * m_dCurrentRate);
         psh += 2;
         m_iStep++;
      }
      if(m_bSustain)
      {
         for(; i < iCountParam; i++)
         {
            psh[0] = (i16) (psh[0] * m_dCurrentRate);
            psh[1] = (i16) (psh[1] * m_dCurrentRate);
            psh += 2;
            m_iStep++;
         }
      }
      return (i32) iCount;
   }

   void effect_crescendo::Initialize()
   {

      if (m_bWaitFirstNonZeroToStart)
      {

         m_lpfnaProcess.add(&wave_stream_effect::WaitNonZero);

      }

      m_lpfnaProcess.add((LPFN_PROCESS) &effect_crescendo::Process16bits);
      m_iStep = 0;
      m_dRate = 1.0 - (7.0 / (double) m_iLength);
      m_dCurrentRate = 0.0;
   }

   bool effect_crescendo::IsEndOfEffect()
   {
      if(m_bEnd || m_bDeleteOnEnd)
      {
         if(m_iStep >= (i32) (m_iLength - 1))
            return true;
      }
      return false;
   }


   effect_diminuendo::effect_diminuendo()
   {
      m_bSustain     = true;
      m_bTriggerEnd  = true;
      m_bEnd         = true;
   }

   effect_diminuendo::~effect_diminuendo()
   {

   }

   void effect_diminuendo::SetLengthMillis(u32 dwMillis,u32 dwSamplesPerSec)
   {
      m_iLength = dwSamplesPerSec * dwMillis / 1000;
   }

   //void effect_diminuendo::SetFinalScale(i16 shMul, i16 shDiv)
   //{
   //   m_shFinalScaleDiv = shMul;
   //   m_shFinalScaleMul = shDiv;
   //}


   memsize effect_diminuendo::Process16bits(i16 * pshStream, ::count iSampleCountParam)
   {

      //ASSERT(iSampleCountParam % 2 == 0);

      ::count iCount = (count)minimum(iSampleCountParam,m_iLength - m_iStep);

      i16 * psh = pshStream;
      i32 i;
      for(i = 0; i < iCount; i++)
      {
         m_dCurrentRate *= m_dRate;
         psh[0] = (i16)(psh[0] * m_dCurrentRate);
         psh[1] = (i16)(psh[1] * m_dCurrentRate);
         psh += 2;
         m_iStep++;
      }
      if(m_bSustain)
      {
         for(; i < iSampleCountParam; i++)
         {
            psh[0] = (i16)(psh[0] * m_dCurrentRate);
            psh[1] = (i16)(psh[1] * m_dCurrentRate);
            psh += 2;
            m_iStep++;
         }
      }
      return (i32)iCount;
   }

   void effect_diminuendo::Initialize()
   {
      m_lpfnaProcess.add((LPFN_PROCESS) &effect_diminuendo::Process16bits);
      m_iStep = 0;
      m_dRate = 1.0 - (7.0 / (double)m_iLength);
      m_dCurrentRate = 1.0;
   }

   bool effect_diminuendo::IsEndOfEffect()
   {
      if(m_bEnd)
      {
         if(m_iStep >= (i32)(m_iLength - 1))
            return true;
      }
      return false;
   }


} // namespace wave



