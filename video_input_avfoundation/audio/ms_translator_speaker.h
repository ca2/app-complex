#pragma once


class CLASS_DECL_APP_CORE_AUDIO ms_translator_speaker :
   virtual public ::tts::speaker
{
public:


   ::collection::index       m_iTranslatorFile;
   string      m_strTranslatorToken;


   ms_translator_speaker();
   virtual ~ms_translator_speaker();


   virtual bool speak(const ::scoped_string & scopedstrText);

   virtual bool speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSynch = false);

   virtual bool stop(string strLang);

   virtual bool is_speaking(string strLang);


};




