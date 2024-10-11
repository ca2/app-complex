#include "framework.h"

//#include "aqua/xml.h"
//
//#ifdef WINDOWS_DESKTOP
////#include "windows/tts_speaker.h"
//void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//#endif
//
//#ifdef __APPLE__
//#include <dlfcn.h>
//#include <mach-o/dyld.h>
//#include <mach-o/nlist.h>
//#include <sys/types.h> // for jl_raise_debugger
//#endif
//
//
//CLASS_DECL_APP_CORE_AUDIO string_array det_l(::particle * pparticle, string str)
//{
//
//   //string strKey = acmefile()->as_string("C:\\sensitive\\sensitive\\seed\\google_translate_api.txt");
//
//   //   strKey.trim();
//
//   property_set set;
//
//   //set["raw_http"] = true;
//   //set["disable_common_name_cert_check"] = true;
//
//   set["interactive_user"] = true;
//
//   string strQuery = Sys(pparticle).url().url_encode(str);
//
//   //string strUrl = "https://www.googleapis.com/language/translate/v2/detect?q=" + strQuery + "&key=" + strKey;
//
//   string strUrl = "https://api.ca2.cc/translate/v1/detect?q=" + strQuery;
//
//   string strJson = App(pparticle).http()->get(strUrl, set);
//
//   const char * pszJson = strJson;
//   ::payload v;
//
//   try
//   {
//
//      v.parse_network_payload(pszJson);
//
//   }
//   catch (...)
//   {
//
//   }
//
//
//   string_array stra;
//
//   for (::collection::index i = 0; i < v["data"]["detections"][0].payloada().get_count(); i++)
//   {
//
//      string strLanguageCode = v["data"]["detections"][0][i]["language"];
//
//      stra.add(strLanguageCode);
//
//   }
//
//   return stra;
//
//
//}
//
////#ifdef CUBE
////
////DECL_MM_DEC_LIB(audio_decode_libmpg123);
////DECL_MM_DEC_LIB(audio_decode_wave);
////
////#endif
//
//
//namespace multimedia
//{
//
//
////   __IMPLEMENT_APPLICATION_RELEASE_TIME();


   application::application()
////   {
////
////      m_bFadeOutAndStopOnExit = true;
////
////      //m_paudiomixeruserbase = nullptr;
////
////   }
////
////
////   application::~application()
////   {
////   }
////
////   
////   void application::init_instance()
////   {
////
////      if (!::aura::application::init_instance())
////      {
////
////         ERROR(".1");
////
////         return false;
////
////      }
////
////      return true;
////
////   }
////
////
////   void application::init3()
////   {
////
////      INFORMATION("start");
////
////      if (m_pmultimedia.is_null())
////      {
////
////         __construct_new(m_pmultimedia);
////
////      }
////
////
////
////#ifdef CUBE
////
////      void *l = dlopen(file()->module(), RTLD_LOCAL);
////
////      if (l != nullptr)
////      {
////
////         LPFN_NEW_MULTIMEDIA_DECODER pfn;
////
////         pfn = (LPFN_NEW_MULTIMEDIA_DECODER)dlsym(l, "audio_decode_libmpg123_NewDecoderInterface");
////
////         if (pfn == nullptr)
////         {
////
////            //message_box(nullptr, "Failed ld libmpg1234");
////
////         }
////         else
////         {
////
////            m_mapMultimediaDecoderFactory["audio_decode_libmpg123"] = pfn;
////
////         }
////
////         pfn = (LPFN_NEW_MULTIMEDIA_DECODER)dlsym(l, "audio_decode_wave_NewDecoderInterface");
////
////         if (pfn == nullptr)
////         {
////
////            //message_box(nullptr, "Failed ld libsurf");
////
////         }
////         else
////         {
////
////            m_mapMultimediaDecoderFactory["audio_decode_wave"] = pfn;
////
////         }
////
////      }
////
////#endif
////
////      m_pmultimediafile = __allocate ::multimedia::file_application();
////
////#ifdef WINDOWS_DESKTOP
////
////      ([a-z0-9_]+)_factory(::factory::factory * pfactory);
////
////#endif
////
////      if(factory_item < ::tts::speaker >() == nullptr)
////      {
////
////         add_factory_item < ms_translator_speaker, ::tts::speaker > ();
////
////      }
////
////      add_factory_item <::wave::player_command >();
////      add_factory_item <::wave::recorder_command >();
////
////      add_factory_item <::audio_mixer_user_base::document >();
////      add_factory_item <::audio_mixer_user_base::frame_window >();
////      add_factory_item <::audio_mixer_user_base::main_impact >();
////      add_factory_item <::audio_mixer_user_base::control_impact >();
////
////      //      add_factory_item <::duration_array > ();
////      // add_factory_item <duration_array >();
////
////      if (!::aura::application::init3())
////      {
////
////         ERROR(".1");
////
////         return false;
////
////      }
////
////      add_matter_locator("app-core/multimedia");
////
////      INFORMATION(".1");
////
////      if (!m_paudiomixer)
////      {
////
////         auto estatus = __construct_new(m_paudiomixer);
////
////         if (!estatus)
////         {
////
////            warningf("Could not initialize Audio Mixer (1)");
////
////         }
////         else
////         {
////
////            if (!m_paudiomixer->init1())
////            {
////
////               warningf("Could not initialize Audio Mixer (2)");
////
////            }
////            else
////            {
////
////               if (!m_paudiomixer->init())
////               {
////
////                  warningf("Could not initialize Audio Mixer (3)");
////
////               }
////
////            }
////
////         }
////
////      }
////
////      if (!m_paudiomixeruserbase)
////      {
////
////         auto estatus = __construct_new(m_paudiomixeruserbase);
////
////         if (!estatus)
////         {
////
////            warningf("Could not initialize Audio Mixer User Base (1)");
////
////         }
////         else
////         {
////
////            //m_paudiomixeruserbase->construct(this);
////
////            if (!m_paudiomixeruserbase->init1())
////            {
////
////               warningf("Could not initialize Audio Mixer User Base (2)");
////
////            }
////            else
////            {
////
////               if (!m_paudiomixeruserbase->init())
////               {
////
////                  warningf("Could not initialize Audio Mixer User Base (3)");
////
////               }
////
////            }
////
////         }
////
////      }
////
////      if (!m_paudiowave)
////      {
////
////         auto estatus = __construct_new(m_paudiowave);
////
////         if (!estatus)
////         {
////
////            warningf("Could not initialize Audio Wave (1)");
////
////         }
////
////      }
////
////      if (m_pmediamanager.is_null())
////      {
////
////         auto estatus = __construct_new(m_pmediamanager);
////
////         if (!estatus)
////         {
////
////            FATAL("Could not create Multimedia Media Manager (5)");
////
////            return false;
////
////         }
////
////
////      }
////
////      // xxx TODO
////      //add_library(__allocate ::multimedia::library());
////
////      m_pmediaplay = __allocate ::mediaplay::mediaplay();
////
////      if (m_pmediaplay == nullptr)
////         return false;
////
////      m_pmediaplaylist = __allocate ::mediaplaylist::media_playlist();
////
////
////      if (m_pmediaplaylist.is_null())
////      {
////
////         FATAL("Could not create Multimedia Media Playlist");
////
////         return false;
////
////      }
////
////      /*if(!m_pmediaplaylist->initialize())
////      {
////         informationf("Could not initialize Multimedia Media Playlist");
////         return false;
////      }*/
////
////      if (!m_pmultimedia->init_multimedia())
////      {
////
////         FATAL("Could not initialize Multimedia department");
////
////         return false;
////
////      }
////
////      return true;
////
////   }
////
////
////   LPFN_NEW_MULTIMEDIA_DECODER application::get_multimedia_decoder_factory(const ::string & pszTitle)
////   {
////
////      return m_mapMultimediaDecoderFactory[pszTitle];
////
////   }
////
////
////   void application::term_instance()
////   {
////
////      try
////      {
////
////         audiowave()->close();
////
////      }
////      catch (...)
////      {
////
////      }
////
////      //audiowave().release();
////
////      //try
////      //{
////
////      //   mediamanager()->destroy();
////
////      //}
////      //catch (...)
////      //{
////
////      //}
////
////      //m_pmediamanager.release();
////
////      //try
////      //{
////
////      //   m_pmediaplaylist.release();
////
////      //}
////      //catch (...)
////      //{
////
////      //}
////
////      //try
////      //{
////
////      //   if (m_paudiomixeruserbase.is_set())
////      //   {
////
////      //      m_paudiomixeruserbase->term();
////
////      //   }
////
////      //}
////      //catch (...)
////      //{
////
////      //}
////
////      //m_paudiomixeruserbase.release();
////
////      //try
////      //{
////
////      //   if (m_paudiomixer.is_set())
////      //   {
////
////      //      m_paudiomixer->term();
////
////      //   }
////
////      //}
////      //catch (...)
////      //{
////
////      //}
////
////      //m_paudiomixer.release();
////
////      //try
////      //{
////
////      //   if (m_pmultimedia.is_set())
////      //   {
////
////      //      m_pmultimedia->term_multimedia();
////
////      //      m_pmultimedia.release();
////
////      //   }
////
////      //}
////      //catch (...)
////      //{
////
////      //}
////
////      try
////      {
////
////         ::aura::application::term_application();
////
////      }
////      catch (...)
////      {
////
////      }
////
////
////   }
////
////
////
////
////   void application::play_audio(::payload strFile, bool bSynch)
////   {
////
////      multimedia().play_audio(strFile, bSynch);
////
////   }
////
////
////
////   void application::on_song_added(string strId)
////   {
////
////
////   }
////
////
////   ::pointer<::tts::speaker>application::tts_speaker()
////   {
////
////      if (m_pspeaker.is_null())
////      {
////
////         m_pspeaker = create_tts_speaker();
////
////      }
////
////      return m_pspeaker;
////
////   }
////
////
////   ::pointer<::tts::speaker>application::trans_speaker()
////   {
////
////      if (m_ptransspeaker.is_null())
////      {
////
////         m_ptransspeaker = create_trans_speaker();
////
////      }
////
////      return m_ptransspeaker;
////
////   }
////
////
////   ::pointer<::tts::speaker>application::create_tts_speaker()
////   {
////
////      auto pspeaker = __create < ::tts::speaker > ();
////
////      if (pspeaker.is_set())
////      {
////
////         pspeaker->m_pspeakerFallback = create_trans_speaker();
////
////      }
////      else
////      {
////
////         pspeaker = create_trans_speaker();
////
////      }
////
////      return pspeaker;
////
////   }
////
////
////   ::pointer<::tts::speaker>application::create_trans_speaker()
////   {
////
////      ::pointer<::tts::speaker>pspeaker;
////
////      pspeaker = __allocate ms_translator_speaker();
////
////      return pspeaker;
////
////   }
////
////
////   void application::speak(string lang, string text, bool bSynch)
////   {
////
////      ::pointer<::tts::speaker>pspeaker = tts_speaker();
////
////      if (pspeaker.is_set())
////      {
////
////         pspeaker->speak(lang, text, bSynch);
////
////      }
////
////   }
////
////   void application::trans_speak(string strLang, string strText, bool bSynch)
////   {
////
////
////      ::pointer<::tts::speaker>pspeaker = trans_speaker();
////
////      if (pspeaker.is_set())
////      {
////         pspeaker->speak(strLang, strText, bSynch);
////      }
////
////      //      ::xml::document d(this);
////      //
////      //      d.load("<root>" + strText + "</root>");
////      //
////      //      strText = d.get_text();
////      //
////      //      strText.trim();
////      //
////      //      strText = psystem->html()->resolve_entities(strText);
////      //
////      //      bool bRetry = false;
////      //
////      //   retry:
////      //
////      //      if (m_strTranslatorToken.is_empty() || bRetry)
////      //      {
////      //
////      //         string strUrl = "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13";
////      //
////      //         string strResponse;
////      //
////      //         {
////      //
////      //            ::property_set set;
////      //
////      //            set["raw_http"] = true;
////      //            set["disable_common_name_cert_check"] = true;
////      //
////      //#include "sensitive/azure_resident.txt"
////      //
////      //            set["headers"]["accept"] = "application/network_payload";
////      //            set["headers"]["content-type"] = "application/x-www-form-urlencoded";
////      //
////      //            //set["post"]["code"]= "# code=\"" + strCode + "\"";
////      //            set["post"]["grant_type"] = "client_credentials";
////      //            set["post"]["client_id"] = "ca2_resident";
////      //            set["post"]["client_secret"] = pszKey1;
////      //            set["post"]["scope"] = "http://api.microsofttranslator.com";
////      //
////      //            strResponse = http()->get(strUrl, set);
////      //
////      //         }
////      //
////      //         const char * psz = strResponse;
////      //
////      //         ::payload v;
////      //
////      //         v.parse_network_payload(psz);
////      //
////      //         m_strTranslatorToken = v["access_token"];
////      //
////      //         file()->put_text_utf8(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "translators" / "token.txt", m_strTranslatorToken);
////      //
////      //      }
////      //
////      //      if (m_strTranslatorToken.has_char())
////      //      {
////      //
////      //         string strFile;
////      //
////      //         while (file()->exists(strFile =          auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "translators" / as_string(m_iTranslatorFile) + ".mp3"))
////      //         {
////      //
////      //            m_iTranslatorFile++;
////      //
////      //         }
////      //
////      //
////      //         ::property_set set;
////      //
////      //         set["raw_http"] = true;
////      //         set["disable_common_name_cert_check"] = true;
////      //
////      //         set["headers"]["Authorization"] = "Bearer " + m_strTranslatorToken;
////      //
////      //
////      //         if (string_begins_ci(strText, "ca2 ") || string_begins_ci(strText, "ca2\n"))
////      //         {
////      //            strText = "c a 2" + strText.substr(3);
////      //         }
////      //         if (string_ends_ci(strText, " ca2") || string_ends_ci(strText, "\nca2"))
////      //         {
////      //            strText = strText.left(strText.length() - 3) + "c a 2";
////      //         }
////      //         strText.utf8_replace(" ca2 ", " c a 2 ");
////      //         strText.utf8_replace(" ca2\n", " c a 2\n");
////      //         strText.utf8_replace("\nca2 ", "\nc a 2 ");
////      //         strText.utf8_replace("\nca2\n", "\nc a 2\n");
////      //
////      //         string strEncode = purl->url_encode(strText);
////      //
////      //         string strDecode = purl->url_decode(strEncode);
////      //
////      //         string strUrl = "http://api.microsofttranslator.com/V2/Http.svc/Speak?text=" + strEncode + "&language=" + strLang + "&format=audio/mp3&options=MaxQuality";
////      //
////      //         http()->download(strUrl, strFile, set);
////      //
////      //         int iStatusCode = set["http_status_code"];
////      //
////      //         if (iStatusCode >= 400 && iStatusCode < 500)
////      //         {
////      //            string str = file()->as_string(strFile);
////      //            if (str.case_insensitive_find("The incoming token has expired") >= 0)
////      //            {
////      //
////      //
////      //               m_strTranslatorToken.empty();
////      //
////      //            }
////      //            else if (str.case_insensitive_find("'language' must be a valid language") >= 0)
////      //            {
////      //               str = file()->as_string(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "translators/missing.txt");
////      //               str += strLang + "\n";
////      //               file()->put_contents(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "translators/missing.txt", str);
////      //               return;
////      //            }
////      //            else if (str.case_insensitive_find("Language name is not supported") >= 0)
////      //            {
////      //               str = file()->as_string(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "translators/missing2.txt");
////      //               str += strLang + "\n";
////      //               file()->put_contents(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "translators/missing2.txt", str);
////      //               return;
////      //            }
////      //            else
////      //            {
////      //
////      //               return;
////      //            }
////      //
////      //         }
////      //         else
////      //         {
////      //
////      //            papp->play_audio(strFile, bSynch);
////      //
////      //         }
////      //
////      //      }
////      //
////      //      if (m_strTranslatorToken.is_empty())
////      //      {
////      //
////      //         if (!bRetry)
////      //         {
////      //
////      //            bRetry = true;
////      //
////      //            goto retry;
////      //
////      //         }
////      //
////      //      }
////
////   }
////
////#define DEBUG_MEDIAPLAYLIST_OPEN_COUNT 0
////
////   ::pointer<::user::document>application::defer_create_impact(string strImpact, ::user::interaction * puiParent, e_window_flag ewindowflag, const ::atom & atom)
////   {
////
////      if (strImpact == "mediaplaylist")
////      {
////
////         ::pointer<::mediaplaylist::document>pplaylistdoc = papp->mediaplaylist()->m_pplaylistdoc;
////
////         if (pplaylistdoc.is_null())
////         {
////
////            ::pointer<::mediaplaylist::media_playlist>mediaplaylist = papp->mediaplaylist();
////
////            pplaylistdoc = mediaplaylist->GetCurrentPlaylist(true, true, puiParent, ewindowflag, atom);
////
////            if (DEBUG_MEDIAPLAYLIST_OPEN_COUNT > 0)
////            {
////
////               for (int i = 0; i < DEBUG_MEDIAPLAYLIST_OPEN_COUNT; i++)
////               {
////
////                  pplaylistdoc->close_document();
////
////                  pplaylistdoc = mediaplaylist->OpenDiscardPlaylist(true, puiParent, ewindowflag, atom);
////
////               }
////
////            }
////
////         }
////
////         if (::is_set(pplaylistdoc)
////               && ::is_set(mediaplay()->m_pmediaplaylistplayer))
////         {
////
////            pplaylistdoc->set_player(mediaplay()->m_pmediaplaylistplayer);
////
////
////            mediaplay()->m_pmediaplaylistplayer->m_pplaylistdoc = pplaylistdoc;
////
////
////
////         }
////
////         return pplaylistdoc;
////
////      }
////
////      return nullptr;
////
////   }
////
////
////   void application::google_speak(string strLang, string strText, bool bSynch)
////   {
////
////      if (strText.case_insensitive_find("<h1>") >= 0 || strText.case_insensitive_find("<h2>") >= 0)
////      {
////
////         strText.replace_ci("<h1>", "");
////         strText.replace_ci("<h2>", "");
////
////      }
////      else
////      {
////         ::xml::document d;
////
////         d.load("<root>" + strText + "</root>");
////
////         strText = d.get_text();
////
////         strText.trim();
////
////      }
////
////      string strFile;
////
////      while (file()->exists(strFile =          auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "gtranslators" / as_string(m_iGTranslatorFile) + ".mp3"))
////      {
////
////         m_iGTranslatorFile++;
////
////      }
////
////      //bool bRetry = false;
////
////      string strKey = acmefile()->as_string("C:\\sensitive\\sensitive\\seed\\google_translate_api.txt");
////
////      strKey.trim();
////
////      property_set set;
////
////      set["raw_http"] = true;
////
////      set["disable_common_name_cert_check"] = true;
////
////      string strQuery = purl->url_encode(strText);
////
////      string strUrl = "http://translate.google.com/translate_tts?ie=UTF-8&q=" + strQuery + "&tl=" + strLang + "&key=" + strKey;
////
////      http()->download(strUrl, strFile, set);
////
////      papp->play_audio(strFile, bSynch);
////
////   }
////
////
////   void application::speak(string text)
////   {
////
////      synchronous_lock synchronouslock(this->synchronization());
////
////      ::pointer<::tts::speaker>& pspeaker = m_pspeaker;
////
////      if (pspeaker.is_null())
////      {
////
////         pspeaker = create_tts_speaker();
////
////      }
////
////      if (pspeaker.is_set())
////      {
////
////         synchronouslock.unlock();
////
////         if (!pspeaker->speak(text))
////         {
////
////            informationf("test");
////
////         }
////
////      }
////
////   }
////
////
////   void application::france_exit()
////   {
////
////      if (m_pmediaplayview != nullptr)
////      {
////
////         m_pmediaplayview->m_bFranceExit = true;
////
////
////
////         if (m_bFadeOutAndStopOnExit)
////         {
////
////            if (m_pmediaplayview->get_wave_player() != nullptr && m_pmediaplayview->get_wave_player()->IsPlaying())
////            {
////
////               m_pmediaplayview->StartFadeOut(mediaplay::ExecuteStop, mediaplay::ExecuteNone);
////
////               ::duration tickStart = ::duration::now();
////
////               while (::duration::now() - tickStart < 15000 && m_pmediaplayview->get_wave_player()->IsPlaying())
////               {
////
////                  sleep(100_ms);
////
////               }
////
////               informationf("not playing or timeout");
////
////            }
////
////         }
////
////      }
////
////      ::aura::application::france_exit();
////
////   }
////
////
////   LPWAVEOUT application::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
////   {
////
////      auto pplugin = __allocate ::audio_plugin::source();
////
////      if (pplugin.is_null())
////      {
////
////         return nullptr;
////
////      }
////
////      return pplugin->waveout_open(iChannel, pformat, pcallback);
////
////   }
//
//} // namespace multimedia




