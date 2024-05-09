#pragma once


class CLASS_DECL_APP_CORE_AUDIO ms_translator_speaker :
   virtual public ::tts::speaker
{
public:


   ::collection::index       m_iTranslatorFile;
   string      m_strTranslatorToken;


   ms_translator_speaker();
   virtual ~ms_translator_speaker();


   virtual bool speak(const ::string & strText);

   virtual bool speak(const ::string & strLang, const ::string & strText, bool bSynch = false);

   virtual bool stop(string strLang);

   virtual bool is_speaking(string strLang);


};




