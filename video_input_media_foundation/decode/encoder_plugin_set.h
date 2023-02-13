#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO encoder_plugin_set :
      virtual public ::object
   {
   public:


      pointer_array < encoder_plugin >       m_plugina;


      encoder_plugin_set();
      virtual ~encoder_plugin_set();


      encoder_plugin * FindPlugin(i32 iId);
      encoder_plugin * LoadPlugin(i32 iId, const ::string & lpcszDll);

      encoder * GetNewEncoder(const ::string & lpcszFileName, file_pointer * pfile = nullptr);


   };


} // namespace audio




