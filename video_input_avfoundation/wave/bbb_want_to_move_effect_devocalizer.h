#pragma once


#include "axis/math/kissfft/kissfft.h"


namespace wave
{


   class effect_devocalizer  :
      virtual public ::iaudio::stream_effect
   {
   public:


      class Chunk
      {
      public:


         effect_devocalizer *       m_pparent;
         array < i16 >              m_sha;


         void Initialize(effect_devocalizer * pparent);
         bool Input(i16 * pshStream);
      };

      class Group :
         virtual public ::object
      {
      public:


            
         class Channel :
            virtual public ::object
         {
         public:


               

            Group *                          m_pgroup;

            f64_array                     m_da1;
            f64_array                     m_da2;
            f64_array                     m_da3;
            complexd_array                   m_complexa;
            sort_array < double >            m_faMax;
            ::i32_array                        m_iaMax;


            Channel();

            void Initialize(Group * pgroup);
            void Input(bool bFilter);
            void Output(sort_array < double > & faMax, ::i32_array & iaMax);

         };

         effect_devocalizer *                 m_pparent;
         pointer_array < Channel >                              m_channela;
         complexd_array                            m_complexa;
         f64_array                              m_daMod;
         double                                    m_dDivisor;

         Group();
         void Initialize(effect_devocalizer * pparent);
         bool Input(i16 * pshStream);
         bool Output1(i16 * pshStream);
         bool Output2(i16 * pshStream);


      };

      ::pointer<kissfft::fftd>                     m_pfft;
      ::pointer<kissfft::ifftd>                    m_pifft;

      //sort_array < sort_array < double >,const sort_array < double > &,array < sort_array < double > >, &BaseNullCompare < const sort_array < double > & >  > m_f2aMax;

      int2a                                  m_i2aMax;

      // Tuning Parameters
      i32                                   m_iCancelNoteCount;
      i32                                   m_iMin;
      i32                                   m_iMax;
      double                                    m_wDiv;

      bool                                      m_bEnable;

      i32                                   m_iDivisionCount;
      i32                                   m_iFirstOutput;
      i32                                   m_iOutputCount;
      i32                                   m_iOutDivision;
      i32                                   m_iOutChunk;


      i32                                   m_iSamplesPerSecond;
      i32                                   m_iSampleCount;
      i32                                   m_iChannelCount;
      i32                                   m_iGroupCount;

      i32                                   m_iInputDivisionCount;
      i32                                   m_iFirstInputDivision;
      i32                                   m_iFirstChunk;
      i32                                   m_iChunkCount;
      i32                                   m_iFirstInputGroup;
      i32                                   m_iInputGroupCount;
      i32                                   m_iOutputGroup;

      i32                                   m_iDivisionSampleCount;

      pointer_array < Group >                                m_groupa;
      array < Chunk, Chunk & >             m_chunka;
      array < Chunk, Chunk & >             m_chunkaOut;
      Chunk                                     m_chunk;

      effect_devocalizer(bool bEnable, i32 iSampleCount, i32 iSamplesPerSecond, i32 iDivisionCount, i32 iGroupCount);
      virtual ~effect_devocalizer();


      i32 GetFrequencyIndex(double dFrequency);
      void ChunkToGroup();
      void InputChunk();
      void PrepareChunk(i32 iDivision);
      void Enable(bool bSet = true);
      bool IsEnabled();
      bool GroupToOutput();
      bool Output(i16 * pshIn);
      virtual memsize Process16bits(i16 * pshStream, ::count iCount);
      virtual bool Process(i16 * pshIn, i16 * pshOut);


   };


} // namespace wave



