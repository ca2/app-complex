#pragma once


namespace iaudio
{


   class wave_stream_effect_chain;


   class CLASS_DECL_APP_CORE_AUDIO wave_stream_effect :
      virtual public ::object
   {
      public:


         typedef memsize (wave_stream_effect:: * LPFN_PROCESS) (i16 * pshStream, ::count iCount);

         bool                    m_bEnd;
         bool                    m_bDeleteOnEnd;
         bool                    m_bWaitFirstNonZeroToStart;
         array < LPFN_PROCESS >  m_lpfnaProcess;



         wave_stream_effect();
         virtual ~wave_stream_effect();

         virtual bool IsEndOfEffect();
         virtual memsize CallProcess16bits(i16 * pshStream, ::count iCount);
         virtual memsize Process16bits(i16 * pshStream, ::count iCount);
         virtual memsize WaitNonZero(i16 * pshStream, ::count iCount);

   };


} // namespace iaudio



