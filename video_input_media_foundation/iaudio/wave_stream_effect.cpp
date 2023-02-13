#include "framework.h"



namespace iaudio
{


   wave_stream_effect::wave_stream_effect()
   {
      m_bDeleteOnEnd = false;
      m_bEnd = false;
      m_bWaitFirstNonZeroToStart = false;
   }

   wave_stream_effect::~wave_stream_effect()
   {

   }

   bool wave_stream_effect::IsEndOfEffect()
   {

      return false;

   }


   memsize wave_stream_effect::CallProcess16bits(i16 * pshStream, ::count iCount)
   {

      return (this->*m_lpfnaProcess[0])(pshStream, iCount);

   }


   memsize wave_stream_effect::Process16bits(i16 * pshStream, ::count iCount)
   {

      ::zero(pshStream, iCount);

      return iCount;

   }


   memsize wave_stream_effect::WaitNonZero(i16 * pshStream, ::count iCount)
   {

      //ASSERT(iCount % 2 == 0);


      i16 * psh = pshStream;

      index i;

      for (i = 0; i < iCount; i++)
      {

         if (psh[0] != 0 || psh[1] != 0)
         {

            m_lpfnaProcess.erase_at(0);

            break;

         }

         psh += 2;

      }

      // Jee!! assuming stereo!!
      // Jee!! assuming 16 bits sample!!
      /*  i *= 2;
         i += 3;
         i &= ~0x3;*/

      if (i < iCount)
      {

         CallProcess16bits(pshStream, iCount - i);

      }

      return (i32)iCount;

   }


} // namespace iaudio



