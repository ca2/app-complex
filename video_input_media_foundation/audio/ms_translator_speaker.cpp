#include "framework.h"

//#include "aqua/xml.h"


CLASS_DECL_ACME string file_friendly_transform(const ::scoped_string & scopedstr, bool bTransformSlashes = true);


ms_translator_speaker::ms_translator_speaker()
{

   m_iTranslatorFile = 1;

}


ms_translator_speaker::~ms_translator_speaker()
{

}


bool ms_translator_speaker::speak(const ::scoped_string & scopedstrText)
{

   bool bOk = speak("en", strText);

   return bOk;

}


bool ms_translator_speaker::speak(const ::scoped_string & scopedstrLangParam, const ::scoped_string & scopedstrTextParam, bool bSynch)
{

   string strLang(strLangParam);

   string strText(strTextParam);

// ::xml::document d;

// d.load("<root>" + strText + "</root>");

// strText = d.get_text();

   strText.trim();

   //throw ::exception(todo("html"));

   //strText = puser->html()->resolve_entities(strText);

   bool bRetry = false;

   if (strLang == "cn")
   {

      strLang = "zh-cn";

   }
   else if (strLang == "se")
   {

      strLang = "sv";

   }
   else if (strLang == "en-uk")
   {

      strLang = "en";

   }
   else if (strLang == "uk-ua")
   {

      strLang = "uk";

   }
   else if (strLang == "tr")
   {

      // TRICKY : Phantom exists: BOO... it is mee-eee!
      strLang = "en";

   }
   else if(strLang.is_empty())
   {

      strLang = "en";

   }

   int i1, i2;

   i1 = (int) (random(1, 2));

   i2 = (int) (random(1, 2));

   string strGender = i1 == 1 ? "male" : "female";

   string strQuality = i2 == 1 ? "MaxQuality" : "MinSize";

   string strFileRel = file_friendly_transform(strText);

   string strMd5 = psystem->crypto().md5(strText);

   if (strFileRel.length() > 30)
   {

      strFileRel = strFileRel.substr(24) + "_-_-_-";

   }
   else
   {

      while (strFileRel.length() < 30)
      {

         strFileRel += "_";

      }

   }

   strFileRel += strMd5;

   ::file::path pathMp3;

   ::file::path pathTxt;

   ::file::path pathFolder =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "speech";

   pathMp3 = pathFolder / strLang / strQuality / strGender / strFileRel + ".mp3";

   pathTxt = pathFolder / strLang / strQuality / strGender / strFileRel + ".txt";

   // todo... fastly check if file is mp3 file...
   if (file()->as_string(pathTxt) == strText && file()->length(pathMp3) > 100)
   {

      goto play;

   }

retry:

   if (m_strTranslatorToken.is_empty() || bRetry)
   {

      string strUrl = "https://api.cognitive.microsoft.com/sts/v1.0/issueToken";

      string strResponse;

      {

         ::property_set set;

         set["raw_http"] = true;
         set["disable_common_name_cert_check"] = true;

#include "sensitive/azure_resident.txt"

         set["headers"]["accept"] = "application/network_payload";
         //         set["headers"]["content-type"] = "application/x-www-form-urlencoded";
         set["headers"]["Ocp-Apim-Subscription-Key"] = string(scopedstrKey1);

         //set["post"]["code"]= "# code=\"" + strCode + "\"";
         set["post"]["network_payload"] = "{body}";

         strResponse = http()->get(strUrl, set);

      }

      //const_char_pointer psz = strResponse;

      //::payload v;

      //v.parse_network_payload(scopedstr);

      //m_strTranslatorToken = v["access_token"];

      m_strTranslatorToken = strResponse.trimmed();

      file()->put_text_utf8(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators" / "token.txt", m_strTranslatorToken);

   }

   if (m_strTranslatorToken.is_empty())
   {

      if (!bRetry)
      {

         bRetry = true;

         goto retry;

      }

      return false;

   }

   {

      ::property_set set;

      set["raw_http"] = true;
      set["disable_common_name_cert_check"] = true;

      set["headers"]["Authorization"] = "Bearer " + m_strTranslatorToken;


      if (string_begins_ci(strText, "ca2 ") || string_begins_ci(strText, "ca2\n"))
      {
         strText = "c a 2" + strText.substr(3);
      }
      if (string_ends_ci(strText, " ca2") || string_ends_ci(strText, "\nca2"))
      {
         strText = strText.left(strText.length() - 3) + "c a 2";
      }
      //strText.utf8_replace(" ca2 ", " c a 2 ");
      //strText.utf8_replace(" ca2\n", " c a 2\n");
      //strText.utf8_replace("\nca2 ", "\nc a 2 ");
      //strText.utf8_replace("\nca2\n", "\nc a 2\n");

      string strEncode = ::url::encode(strText);

      string strDecode = ::url::decode(strEncode);




      string strUrl = "http://api.microsofttranslator.com/V2/Http.svc/Speak?text=" + strEncode + "&language=" + strLang + "&format=audio/mp3&options=" + strQuality + "|" + strGender;

      http()->download(strUrl, pathMp3, set);

      int iStatusCode = set["http_status_code"];

      if (iStatusCode >= 400 && iStatusCode < 500)
      {
         string str = file()->as_string(pathMp3);
         if (str.case_insensitive_find("The incoming token has expired") >= 0)
         {


            m_strTranslatorToken.empty();
            if (!bRetry)
            {

               bRetry = true;

               goto retry;

            }

            return false;

         }
         else if (str.case_insensitive_find("'language' must be a valid language") >= 0)
         {
            str = file()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing.txt");
            str += strLang + "\n";
            file()->put_contents(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing.txt", str);
            return false;
         }
         else if (str.case_insensitive_find("Language name is not supported") >= 0)
         {
            str = file()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing2.txt");
            str += strLang + "\n";
            file()->put_contents(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing2.txt", str);
            return false;
         }
         else
         {

            return false;
         }

      }

      file()->put_contents(pathTxt, strText);

   }

play:

   informationf("speak: %s", pathMp3.c_str());

   paudio->play_audio(pathMp3, bSynch);

   return true;

}


bool ms_translator_speaker::stop(const ::scoped_string & scopedstrLang)
{

   return true;

}


bool ms_translator_speaker::is_speaking(const ::scoped_string & scopedstrLang)
{

   return false;

}



