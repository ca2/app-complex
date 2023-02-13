#include "framework.h"



namespace iaudio
{


   wave_stream_effect_chain::wave_stream_effect_chain()
   {

   }

   wave_stream_effect_chain::~wave_stream_effect_chain()
   {

   }


   bool wave_stream_effect_chain::InsertEffect(EWaveEffectInsert einsert, ::iaudio::wave_stream_effect *peffect)
   {
      ASSERT(peffect != this);

      if(peffect == this)
         return false;

      switch(einsert)
      {
      case WaveEffectInsertBeforeFirst:
      {
         m_effectptra.insert_at(0, peffect);
      }
      break;
      case WaveEffectInsertAfterLast:
      {
         m_effectptra.add(peffect);
      }
      break;
      default:
         ASSERT(false);
         return false;
      }

      return true;

   }


   void wave_stream_effect_chain::SortEffectChain()
   {

   }


   memsize wave_stream_effect_chain::Process16bits(i16 *pshStream, ::count iCount)
   {

      for(i32 i = 0; i < m_effectptra.get_size(); i++)
      {

         iCount = m_effectptra[i]->Process16bits(pshStream, iCount);

      }

      return iCount;

   }


} // namespace iaudio



