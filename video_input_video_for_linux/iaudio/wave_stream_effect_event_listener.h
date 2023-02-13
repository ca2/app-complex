#pragma once


namespace iaudio
{


   class wave_stream_effect;


   class wave_stream_effect_event_listener
   {
   public:



      wave_stream_effect_event_listener();
      virtual ~wave_stream_effect_event_listener();


      void OnWaveStreamEffectEvent(wave_stream_effect * peffect, i32 iEvent);


   };


} // namespace iaudio



