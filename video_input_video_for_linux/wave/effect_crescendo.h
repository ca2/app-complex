#pragma once


namespace wave
{


   class effect_diminuendo :
      public ::iaudio::wave_stream_effect
   {
   public:


      i32            m_iLength;
      bool           m_bSustain;
      bool           m_bTriggerEnd;
      i32            m_iStep;
      double         m_dRate;
      double         m_dCurrentRate;
      bool           m_bCrescendo;


      effect_diminuendo();
      virtual ~effect_diminuendo();


      virtual bool IsEndOfEffect() override;
      virtual memsize Process16bits(i16 * pshStream, ::count iCount) override;

      void SetLengthMillis(u32 dwMillis, u32 dwSamplesPerSec);
      void Initialize();


   };


   class effect_crescendo:
      public ::iaudio::wave_stream_effect
   {
   public:


      i32         m_iLength; // in samples
      bool        m_bSustain;
      bool        m_bTriggerEnd;
      i32         m_iStep;
      double      m_dRate;
      double      m_dCurrentRate;
      bool        m_bCrescendo;


      effect_crescendo();
      virtual ~effect_crescendo();


      virtual bool IsEndOfEffect() override;
      virtual memsize Process16bits(i16 * pshStream, ::count iCount) override;

      //void SetFinalScale(i16 shMul, i16 shDiv);

      void SetLengthMillis(u32 dwMillis,u32 dwSamplesPerSec);
      void Initialize();


   };


} // namespace wave



