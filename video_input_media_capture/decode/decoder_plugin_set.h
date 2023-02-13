#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO decoder_plugin_set :
      virtual public ::object
   {
   public:


      ::file::path_array                    m_patha;
      pointer_array < decoder_plugin >       m_plugina;


      decoder_plugin_set();
      virtual ~decoder_plugin_set();


      virtual void initialize(::particle * pparticle) override;


      decoder_plugin * FindPlugin(const ::string & lpcszTitle);
      decoder_plugin * LoadPlugin(const ::string & lpcszTitle);

      ::pointer<decoder>GetNewDecoder(::file::file * pfile = nullptr, bool bSeekable = true, i32 iReadBlockSize = -1);
      ::pointer<decoder>GetNewDecoder(::file::file * pfile, const ::string & pszModule, bool bSeekable = true, i32 iReadBlockSize = -1);

      virtual string get_error_message(decoder * pdecoder, ::file::file * preader);

   };


} // namespace audio



