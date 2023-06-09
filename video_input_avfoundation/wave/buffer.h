#pragma once


namespace wave
{


   class base;


   typedef i16 WAVEBUFFERDATA;
   typedef WAVEBUFFERDATA * LPWAVEBUFFERDATA;


   typedef array < WAVEBUFFERDATA > buffer_data_array;


   class CLASS_DECL_APP_CORE_AUDIO buffer :
      virtual public ::object
   {
   public:


      class CLASS_DECL_APP_CORE_AUDIO item :
         virtual public ::matter
      {
      public:


         bool           m_bShortCompress;
         bool           m_bFFT;
         index          m_iIndex;
         void *         m_pData;
         void *         m_posdata;
         memory         m_mem;

         bool FFTProcessed();
         bool OnMultimediaDone();

         virtual void * get_os_data();

      };


      using buffer_array = pointer_array < item >;


      memsize                 m_uiBufferSize;
      memsize                 m_uiAlign;
      memsize                 m_uiAnalysisSize;
      memsize                 m_uiAnalysisSizeOrder;
      memsize                 m_uiAllocationSize;
      memsize                 m_uiInterestSize;
      ::count                       m_iSkippedSamplesCount;

      index                         m_iCurrentBuffer;
      buffer_data_array        m_bdaData;
      buffer_data_array        m_bdaBuffer;
      array < byte >                m_baData;
      array < byte >                m_baBuffer;

      array < double >              m_daSetA;
      array < double >              m_daSetB;

      array < double >              m_daModuleSet;
      array < double >              m_daResultSet;

      critical_section              m_csResult;
      critical_section              m_csProcLevel1;
      critical_section              m_csProcLevel2;
      buffer_array                  m_buffera;
      //::pointer<kissfft::fftd>            m_pfft;
      //complexd_array                m_complexa;
      // *               m_pfft;
      //array < kiss_fft_cpx >        m_pcomplexa;

      double                        m_dNominalMaxLevel; // Divisor que faz o nivel maximo ser um.

      format                   m_waveformatIn;
      format                   m_waveformatOut;


      buffer();
      virtual ~buffer();


      double GetMaxLevel();
      void InterestCompressModuleSet();
      ::count GetBufferCount();
      double PeakValueFrequency(double dMin, double dMax, double dSampleFrequency, double * dAmplitude);
      double PeakValueFrequency(double dSampleFrequency, double * dAmplitude);
      double PeakValueFrequency(double * dAmplitude);
      void HighPassFilterData();
      void PeakValueFrequencies(double_array & daFreq, double_array & daAmp, ::count iCount);
//         void FFTProcess(LPWAVEHDR lpwavehdr);
      void FFTProcess(index iBuffer);
      //       void PCMOutProcessWAVEHDR(LPWAVEHDR lpwavehdr);
      void PCMOutProcess(index iBuffer);
      byte * PCMOutGetBuffer(index iIndex);
      void InterestCopyModuleToResult(double * lpdMax);
      void InterestCalcDoubleSetBModule();
      void InterestCalcSetBModule();
      void FFTOpen(memsize uiAllocationSize, memsize uiBufferSize, memsize uiAnalisysSize, memsize uiInterestSize, ::count uiSkippedSamplesCount);
      bool PCMOutOpen(base * pusermessage, memsize uiBufferSize, ::count uiBufferCount, memsize uiAlign, format * lpwfexIn, format * lpwfexOut);
      void Close(base * pusermessage);
      void ZeroDoubleSetAImaginary();
      void CopyDataToDoubleSetA(index iIndex);
      void CopyDataToSetA(index iIndex);
      void FFTDoubleSetADoubleSetB(bool bInverseTransform);
      void FFTSetASetB();
      item * get_buffer(index iIndex);
      void * get_buffer_data(index iIndex);
      void * get_buffer_os_data(index iIndex);
      double * FFTGetResult();
      void * PCMOutGetInBuffer();
      memsize  PCMOutGetInBufferSize();

   };


} // namespace wave



