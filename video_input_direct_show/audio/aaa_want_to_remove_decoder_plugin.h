#pragma once


namespace multimedia
{


   class CLASS_DECL_APP_CORE_AUDIO decoder_plugin:
      virtual public ::object
   {
   public:


      string                           m_strNewDecoder;
      string                           m_strTitle;
      ::pointer<::acme::library>      m_plibrary;
      decoder * (*                     m_lpfnNewDecoder)();


      decoder_plugin();
      virtual ~decoder_plugin();


      virtual bool Load(const ::scoped_string & scopedstrTitle);
      virtual ::multimedia::decoder * NewDecoder();

      virtual string GetPluginTitle();

   };


} // namespace multimedia




