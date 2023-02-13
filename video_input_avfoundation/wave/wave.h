#pragma once


namespace wave
{


   class in;


   class CLASS_DECL_APP_CORE_AUDIO wave :
      virtual public ::object
   {
   public:

      bool                                               m_bInitialized;
      ::pointer<in>                              m_pwavein;
      u32                                                m_uiWaveInDevice;
      u32                                                m_uiWaveOutDevice;
      ::pointer<::acme::library>                      m_plibrary;
      ::pointer<format>                          m_pwaveformat;
      ::pointer<buffer>                          m_pwavebuffer;
      ::pointer<audio::decoder_plugin_set>     m_pdecoderset;



      wave();
      virtual ~wave();


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;


      ::pointer<in>get_in();

      bool create_in();

      bool ([a-z0-9_]+)_factory(::factory::factory * pfactory);


      void close();


   };


} // namespace wave






