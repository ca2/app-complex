#pragma once


namespace audio
{


   class decoder_plugin_set;


   class CLASS_DECL_APP_CORE_AUDIO decoder_plugin :
      virtual public ::multimedia::decoder_plugin
   {
   public:


      //string                     m_strTitle;
      //::acme::library              m_library;
      //::audio::decoder * (* m_lpfnNewDecoder)(::particle * pparticle);
      //void                    (* m_lpfnDeleteDecoder)(::audio::decoder * pdecoder);


      decoder_plugin();
      ~decoder_plugin();


      //virtual bool Load(const ::string & pszTitle) override;
      //virtual ::multimedia::decoder * NewDecoder() override;
      //virtual void DeleteDecoder(::multimedia::decoder * pdecoder) override;

      //string GetPluginTitle() override;

   };


} // namespace audio



