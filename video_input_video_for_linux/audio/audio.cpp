#include "framework.h"

#include "audio/audio/plugin/track.h"



#ifdef WINDOWS_DESKTOP
//#include "windows/tts_speaker.h"
void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
#endif


namespace audio
{


   audio::audio()
   {

      m_bLocalFileSystemSynch = false;

      m_bFadeOutAndStopOnExit = true;

      m_timePreBuffer = 1_s;

      defer_create_synchronization();

      add_factory_item < ::audio::track >();

      add_factory_item < ::audio::sound_track_player, ::aura::sound_track_player >();

      add_factory_item < ::wave::player_command >();

   }


   audio::~audio()
   {

   }


   void audio::init_multimedia()
   {

      //auto estatus = __construct_new(m_psoundtrackplayer);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return ::success;

   }


   void audio::term_multimedia()
   {

   }



   ::pointer<::audio::plugin>audio::prepare_plugin(::audio::plugin * ppluginParam)
   {

      if (ppluginParam == nullptr)
      {

         return nullptr;

      }

      ::pointer<::audio::plugin>pplugin(ppluginParam);

      defer_initialize_audio_playback();

      if (!pplugin->audio_matches(sound_track()->m_paudiomixer))
      {

         auto presampler = __allocate ::audio::resampler();

         presampler->m_pplugin = pplugin;

         pplugin = presampler;

      }

      auto psoundtrack = sound_track();

      if(!psoundtrack)
      {

         output_error_message("Sound track object is not present.", papp->get_app_user_friendly_task_bar_name(), e_message_box_icon_exclamation, nullptr);

         return nullptr;

      }

      auto paudiomixer = psoundtrack->m_paudiomixer;

      if(!paudiomixer)
      {

         output_error_message("Audio mixer object is not present.", papp->get_app_user_friendly_task_bar_name(), e_message_box_icon_exclamation, nullptr);

         return nullptr;

      }

      paudiomixer->init_child(pplugin);

      return pplugin;

   }


   void audio::OnWavePlayerEvent(::wave::player * pplayer, ::wave::player::enum_player_happening happening, ::wave::player_command * pcommand)
   {


   }


   ::pointer<::audio::plugin>audio::play_plugin(::audio::plugin * ppluginSource, bool bSynch)
   {

      if (ppluginSource == nullptr)
      {

         return nullptr;

      }

      ::pointer<::audio::plugin>pplugin = prepare_plugin(ppluginSource);

      if (pplugin.is_null())
      {

         return nullptr;

      }

      return play_prepared_plugin(pplugin, bSynch);

   }

   ::pointer<::audio::plugin>audio::play_prepared_plugin(::audio::plugin* pplugin, bool bSynch)
   {

      //{

      //   synchronous_lock synchronouslock(sound_track()->m_paudiomixer->synchronization());

      //   sound_track()->m_paudiomixer->m_plugina.add(pplugin);

      //}

      sound_track()->mix(pplugin);

      if (bSynch)
      {

         int iCountDown = 300;

         try
         {

            while (!pplugin->audio_eof() && ::task_get_run())
            {

               sleep(100_ms);

               iCountDown--;

               if (iCountDown == 0)
               {

                  // Isn't it taking too much time to play this audio?
                  //debug_break();

               }

            }

         }
         catch (...)
         {

         }

      }

      return pplugin;

   }

   ::pointer<::audio::plugin>audio::prepare_audio(::file::file * pfile)
   {

      defer_initialize_audio_playback();

      auto pdecoder = audiowave()->m_pdecoderset->GetNewDecoder(pfile);

      if (!pdecoder)
      {

         return nullptr;

      }

      return pdecoder;

   }


   ::pointer<::audio::plugin>audio::get_and_play_audio(::file::file * pfile, bool bSynch)
   {

      ::pointer<::audio::plugin>pplugin = prepare_audio(pfile);

      if (pplugin.is_null())
      {

         return nullptr;

      }

      return play_plugin(pplugin, bSynch);

   }


   void audio::play_audio(const ::payload & payloadFile, bool bSynch)
   {

      predicate_run(bSynch, [=]()
      {

         auto pfile = __context(payloadFile).file()->get_reader(__context_value(payloadFile), ::file::e_open_share_deny_none);

         if (pfile)
         {

            get_and_play_audio(pfile, bSynch);

         }

      });

   }


   //audio::audio()
   //{

   //   //m_bFadeOutAndStopOnExit = true;

   //   //m_paudiomixeruserbase = nullptr;

   //}


   //audio::~audio()
   //{
   //}


   void audio::init_instance()
   {

      //if (!::aura::audio::init_instance())
      //{

      //   error() <<".1";

      //   return false;

      //}

      return true;

   }


   void audio::init3()
   {

      information() << "video_input_video_for_linux audio::init3 start";

#ifdef CUBE

      void * l = dlopen(file()->module(), RTLD_LOCAL);

      if (l != nullptr)
      {

         LPFN_NEW_MULTIMEDIA_DECODER pfn;

         pfn = (LPFN_NEW_MULTIMEDIA_DECODER)dlsym(l, "audio_libmpg123_NewDecoderInterface");

         if (pfn == nullptr)
         {

            //message_box(nullptr, "Failed ld libmpg1234");

         }
         else
         {

            m_mapMultimediaDecoderFactory["audio_libmpg123"] = pfn;

         }

         pfn = (LPFN_NEW_MULTIMEDIA_DECODER)dlsym(l, "audio_wave_NewDecoderInterface");

         if (pfn == nullptr)
         {

            //message_box(nullptr, "Failed ld libsurf");

         }
         else
         {

            m_mapMultimediaDecoderFactory["audio_wave"] = pfn;

         }

      }

#endif

      __øconstruct(m_pmultimediafile, __allocate ::multimedia::file_application());

#ifdef WINDOWS_DESKTOP

      ([a-z0-9_]+)_factory(::factory::factory * pfactory);

#endif

      if (factory_item < ::tts::speaker >() == nullptr)
      {

         add_factory_item < ms_translator_speaker, ::tts::speaker >();

      }

      add_factory_item <::wave::player_command >();
      add_factory_item <::wave::recorder_command >();

      if (!m_pwave)
      {

         auto estatus = __construct_new(m_pwave);

         if (!estatus)
         {

            warning() <<"Could not initialize Audio Wave (1)";

         }

      }

      if (!init_multimedia())
      {

         fatal() <<"Could not initialize Multimedia audio";

         return false;

      }

      return true;

   }


   LPFN_NEW_MULTIMEDIA_DECODER audio::get_multimedia_decoder_factory(const ::string & pszTitle)
   {

      return m_mapMultimediaDecoderFactory[pszTitle];

   }


   void audio::term_instance()
   {

      try
      {

         audiowave()->close();

      }
      catch (...)
      {

      }

      //audiowave().release();

      //try
      //{

      //   mediamanager()->destroy();

      //}
      //catch (...)
      //{

      //}

      //m_pmediamanager.release();

      //try
      //{

      //   m_pmediaplaylist.release();

      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   if (m_paudiomixeruserbase.is_set())
      //   {

      //      m_paudiomixeruserbase->term();

      //   }

      //}
      //catch (...)
      //{

      //}

      //m_paudiomixeruserbase.release();

      //try
      //{

      //   if (m_paudiomixer.is_set())
      //   {

      //      m_paudiomixer->term();

      //   }

      //}
      //catch (...)
      //{

      //}

      //m_paudiomixer.release();

      //try
      //{

      //   if (m_pmultimedia.is_set())
      //   {

      //      m_pmultimedia->term_multimedia();

      //      m_pmultimedia.release();

      //   }

      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   ::aura::audio::term_application();

      //}
      //catch (...)
      //{

      //}


   }




   //void audio::play_audio(::payload strFile, bool bSynch)
   //{

   //   multimedia().play_audio(strFile, bSynch);

   //}



   //void audio::on_song_added(string strId)
   //{


   //}


   ::pointer<::tts::speaker>audio::tts_speaker()
   {

      if (m_pspeaker.is_null())
      {

         m_pspeaker = create_tts_speaker();

      }

      return m_pspeaker;

   }


   ::pointer<::tts::speaker>audio::trans_speaker()
   {

      if (m_ptransspeaker.is_null())
      {

         m_ptransspeaker = create_trans_speaker();

      }

      return m_ptransspeaker;

   }


   ::pointer<::tts::speaker>audio::create_tts_speaker()
   {

      auto pspeaker = __øcreate < ::tts::speaker >();

      if (pspeaker.is_set())
      {

         pspeaker->m_pspeakerFallback = create_trans_speaker();

      }
      else
      {

         pspeaker = create_trans_speaker();

      }

      return ::transfer(pspeaker);

   }


   ::pointer<::tts::speaker>audio::create_trans_speaker()
   {

      auto pspeaker = __create_new < ms_translator_speaker >();

      return ::transfer(pspeaker);

   }


   void audio::speak(const string & lang, const string & text, bool bSynch)
   {

      auto pspeaker = tts_speaker();

      if (pspeaker.is_set())
      {

         pspeaker->speak(lang, text, bSynch);

      }

   }


   void audio::trans_speak(const ::string & strLang, const ::string & strText, bool bSynch)
   {

      auto pspeaker = trans_speaker();

      if (pspeaker.is_set())
      {

         pspeaker->speak(strLang, strText, bSynch);

      }

      //      ::xml::document d(this);
      //
      //      d.load("<root>" + strText + "</root>");
      //
      //      strText = d.get_text();
      //
      //      strText.trim();
      //
      //      strText = psystem->html()->resolve_entities(strText);
      //
      //      bool bRetry = false;
      //
      //   retry:
      //
      //      if (m_strTranslatorToken.is_empty() || bRetry)
      //      {
      //
      //         string strUrl = "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13";
      //
      //         string strResponse;
      //
      //         {
      //
      //            ::property_set set;
      //
      //            set["raw_http"] = true;
      //            set["disable_common_name_cert_check"] = true;
      //
      //#include "sensitive/azure_resident.txt"
      //
      //            set["headers"]["accept"] = "audio/network_payload";
      //            set["headers"]["content-type"] = "audio/x-www-form-urlencoded";
      //
      //            //set["post"]["code"]= "# code=\"" + strCode + "\"";
      //            set["post"]["grant_type"] = "client_credentials";
      //            set["post"]["client_id"] = "ca2_resident";
      //            set["post"]["client_secret"] = pszKey1;
      //            set["post"]["scope"] = "http://api.microsofttranslator.com";
      //
      //            strResponse = http()->get(strUrl, set);
      //
      //         }
      //
      //         const char * psz = strResponse;
      //
      //         ::payload v;
      //
      //         v.parse_network_payload(psz);
      //
      //         m_strTranslatorToken = v["access_token"];
      //
      //         file()->put_text_utf8(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators" / "token.txt", m_strTranslatorToken);
      //
      //      }
      //
      //      if (m_strTranslatorToken.has_character())
      //      {
      //
      //         string strFile;
      //
      //         while (file()->exists(strFile =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators" / as_string(m_iTranslatorFile) + ".mp3"))
      //         {
      //
      //            m_iTranslatorFile++;
      //
      //         }
      //
      //
      //         ::property_set set;
      //
      //         set["raw_http"] = true;
      //         set["disable_common_name_cert_check"] = true;
      //
      //         set["headers"]["Authorization"] = "Bearer " + m_strTranslatorToken;
      //
      //
      //         if (string_begins_ci(strText, "ca2 ") || string_begins_ci(strText, "ca2\n"))
      //         {
      //            strText = "c a 2" + strText.substr(3);
      //         }
      //         if (string_ends_ci(strText, " ca2") || string_ends_ci(strText, "\nca2"))
      //         {
      //            strText = strText.left(strText.length() - 3) + "c a 2";
      //         }
      //         strText.utf8_replace(" ca2 ", " c a 2 ");
      //         strText.utf8_replace(" ca2\n", " c a 2\n");
      //         strText.utf8_replace("\nca2 ", "\nc a 2 ");
      //         strText.utf8_replace("\nca2\n", "\nc a 2\n");
      //
      //         string strEncode = ::url::encode(strText);
      //
      //         string strDecode = ::url::decode(strEncode);
      //
      //         string strUrl = "http://api.microsofttranslator.com/V2/Http.svc/Speak?text=" + strEncode + "&language=" + strLang + "&format=audio/mp3&options=MaxQuality";
      //
      //         http()->download(strUrl, strFile, set);
      //
      //         int iStatusCode = set["http_status_code"];
      //
      //         if (iStatusCode >= 400 && iStatusCode < 500)
      //         {
      //            string str = file()->as_string(strFile);
      //            if (str.case_insensitive_find("The incoming token has expired") >= 0)
      //            {
      //
      //
      //               m_strTranslatorToken.empty();
      //
      //            }
      //            else if (str.case_insensitive_find("'language' must be a valid language") >= 0)
      //            {
      //               str = file()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing.txt");
      //               str += strLang + "\n";
      //               file()->put_contents(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing.txt", str);
      //               return;
      //            }
      //            else if (str.case_insensitive_find("Language name is not supported") >= 0)
      //            {
      //               str = file()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing2.txt");
      //               str += strLang + "\n";
      //               file()->put_contents(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing2.txt", str);
      //               return;
      //            }
      //            else
      //            {
      //
      //               return;
      //            }
      //
      //         }
      //         else
      //         {
      //
      //            papp->play_audio(strFile, bSynch);
      //
      //         }
      //
      //      }
      //
      //      if (m_strTranslatorToken.is_empty())
      //      {
      //
      //         if (!bRetry)
      //         {
      //
      //            bRetry = true;
      //
      //            goto retry;
      //
      //         }
      //
      //      }

   }


   void audio::google_speak(const ::string & strLang, const ::string & strTextParam, bool bSynch)
   {

      string strText(strTextParam);

      if (strText.case_insensitive_find("<h1>") >= 0 || strText.case_insensitive_find("<h2>") >= 0)
      {

         strText.replace_ci("<h1>", "");
         strText.replace_ci("<h2>", "");

      }
      else
      {

         //throw ::exception(todo("xml"))

         //::xml::document d;

         //d.load("<root>" + strText + "</root>");

         //strText = d.get_text();

         strText.trim();

      }

      string strFile;

      while (file()->exists(strFile =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "gtranslators" / as_string(m_iGTranslatorFile) + ".mp3"))
      {

         m_iGTranslatorFile++;

      }

      //bool bRetry = false;

      string strKey = file_system()->as_string("C:\\sensitive\\sensitive\\seed\\google_translate_api.txt");

      strKey.trim();

      property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      string strQuery = ::url::encode(strText);

      string strUrl = "http://translate.google.com/translate_tts?ie=UTF-8&q=" + strQuery + "&tl=" + strLang + "&key=" + strKey;

      http()->download(strUrl, strFile, set);

      paudio->play_audio(strFile, bSynch);

   }


   void audio::speak(const string & text)
   {

      synchronous_lock synchronouslock(this->synchronization());

      ::pointer<::tts::speaker>& pspeaker = m_pspeaker;

      if (pspeaker.is_null())
      {

         pspeaker = create_tts_speaker();

      }

      if (pspeaker.is_set())
      {

         synchronouslock.unlock();

         if (!pspeaker->speak(text))
         {

            //informationf("test");

         }

      }

   }


   //void audio::france_exit()
   //{

   //   if (m_pmediaplayview != nullptr)
   //   {

   //      m_pmediaplayview->m_bFranceExit = true;



   //      if (m_bFadeOutAndStopOnExit)
   //      {

   //         if (m_pmediaplayview->get_wave_player() != nullptr && m_pmediaplayview->get_wave_player()->IsPlaying())
   //         {

   //            m_pmediaplayview->StartFadeOut(mediaplay::ExecuteStop, mediaplay::ExecuteNone);

   //            ::time tickStart = ::time::now();

   //            while (::time::now() - tickStart < 15000 && m_pmediaplayview->get_wave_player()->IsPlaying())
   //            {

   //               sleep(100_ms);

   //            }

   //            informationf("not playing or timeout");

   //         }

   //      }

   //   }

   //   ::aura::audio::france_exit();

   //}
   //void audio::on_decoder_fill_title_info(::multimedia::decoder * pdecoder, string_array & straTitle, string_array_array & straaTitle)
   //{

   //}


   LPWAVEOUT audio::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   {

      auto pplugin = __allocate ::audio::source();

      if (pplugin.is_null())
      {

         return nullptr;

      }

      return pplugin->waveout_open(iChannel, pformat, pcallback);

   }


   ::file_pointer audio::get_rtp_file(const ::payload & payloadFile)
   {

#ifdef UNIVERSAL_WINDOWS

      return nullptr;

#else

      throw ::exception(todo);

      //::file::path path = payloadFile.get_file_path();

      //auto pfile = __allocate rtp::file();

      //if (!pfile->rx_open(purl->get_server(path), purl->get_port(path)))
      //{

      //   pfile.release();

      //   return nullptr;

      //}

      //try
      //{

      //   ::property_set setQuery;

      //   setQuery.parse_network_arguments(purl->get_query(path));

      //   if (setQuery["payload_type"] == "mp3" || setQuery["payload_type"].get_string().is_empty())
      //   {

      //      pfile->set_payload("mp3", &payload_type_mp3_128);

      //   }

      //}
      //catch (...)
      //{

      //   return nullptr;

      //}

      //return pfile;

#endif

   }


} // namespace multimedia



