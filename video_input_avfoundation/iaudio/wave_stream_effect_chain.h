#pragma once


namespace iaudio
{


   class wave_stream_effect;
   class wave_stream_effect_order;


   enum EWaveEffectInsert
   {


      WaveEffectInsertBeforeFirst,
      WaveEffectInsertAfterLast,


   };


   class CLASS_DECL_APP_CORE_AUDIO wave_stream_effect_chain :
      public wave_stream_effect
   {
      public:


         array < wave_stream_effect *, wave_stream_effect * > m_effectptra;


         wave_stream_effect_chain();
         virtual ~wave_stream_effect_chain();

         bool InsertEffect(EWaveEffectInsert einsert, wave_stream_effect * peffect);

         virtual memsize Process16bits(i16 * pshStream, ::count iCount) override;

         void SortEffectChain();

   };


} // namespace iaudio



