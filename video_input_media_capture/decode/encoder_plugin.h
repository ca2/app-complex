#pragma once


extern "C"
typedef ::audio::encoder * AUDIO_NEW_ENCODER();

extern "C"
typedef AUDIO_NEW_ENCODER * LPFN_AUDIO_NEW_ENCODER;


namespace audio
{


   class encoder_plugin_set;


   class CLASS_DECL_APP_CORE_AUDIO encoder_plugin :
      virtual public ::object
   {
   public:


      i32                                   m_iId;
      ::pointer<::acme::library>           m_plibrary;
      LPFN_AUDIO_NEW_ENCODER                m_lpfnNewEncoder;


      encoder_plugin();
      ~encoder_plugin();


      void SetPluginId(i32 iId);
      bool LoadModule(const ::string &);
      ::audio::encoder * NewEncoder();
      //void DeleteEncoder(::audio::encoder * pdecoder);

      i32 GetPluginId();

   };


} // namespace audio




