#include "framework.h"

// #include "aqua/xml.h"
// #include "app-core/multimedia/audio_plugin/track.h"


// #ifdef WINDOWS_DESKTOP
// //#include "windows/tts_speaker.h"
// void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
// #endif


// namespace multimedia
// {


//    department::department()
//    {

//       m_bFadeOutAndStopOnExit = true;


//       defer_create_synchronization();

//    }


//    department::~department()
//    {

//    }


//    void department::init_multimedia()
//    {

//       //auto estatus = __construct_new(m_psoundtrackplayer);

//       //if (!estatus)
//       //{

//       //   return estatus;

//       //}

//       return ::success;

//    }


//    void department::term_multimedia()
//    {

//    }


//    void department::defer_initialize_audio_playback(::audio::e_purpose epurpose)
//    {

//       synchronous_lock synchronouslock(this->synchronization());

//       if (::is_set(m_psoundtrackplayer))
//       {

//          return ::success_none;

//       }

//       auto estatus = __construct_new(m_psoundtrackplayer);

//       if (!estatus)
//       {

//          return estatus;

//       }

//       synchronouslock.unlock();

//       estatus = m_psoundtrackplayer->defer_start(epurpose);

//       if (!estatus)
//       {

//          return estatus;

//       }

//       return estatus;

//    }

   
//    sound_track_player * department::sound_track()
//    {

//       return m_psoundtrackplayer;

//    }


//    ::pointer<::audio_plugin::plugin>department::prepare_plugin(::audio_plugin::plugin * ppluginParam)
//    {

//       if (ppluginParam == nullptr)
//       {

//          return nullptr;

//       }

//       ::pointer<::audio_plugin::plugin>pplugin(ppluginParam);

//       defer_initialize_audio_playback();

//       if (!pplugin->audio_plugin_matches(sound_track()->m_paudiomixer))
//       {

//          auto presampler = __allocate ::audio_plugin::resampler();

//          presampler->m_pplugin = pplugin;

//          pplugin = presampler;

//       }

//       sound_track()->m_paudiomixer->init_child(pplugin);

//       return pplugin;

//    }


//    void department::OnWavePlayerEvent(wave::player * pplayer, wave::player::e_happening happening, wave::player_command * pcommand)
//    {


//    }


//    ::pointer<audio_plugin::plugin>department::play_plugin(::audio_plugin::plugin * ppluginSource, bool bSynch)
//    {

//       if (ppluginSource == nullptr)
//       {

//          return nullptr;

//       }

//       ::pointer<::audio_plugin::plugin>pplugin = prepare_plugin(ppluginSource);

//       if (pplugin.is_null())
//       {

//          return nullptr;

//       }

//       return play_prepared_plugin(pplugin, bSynch);

//    }

//    ::pointer<audio_plugin::plugin>department::play_prepared_plugin(::audio_plugin::plugin* pplugin, bool bSynch)
//    {

//       {

//          synchronous_lock synchronouslock(sound_track()->m_paudiomixer->mutex());

//          sound_track()->m_paudiomixer->m_plugina.add(pplugin);

//       }

//       if (bSynch)
//       {

//          int iCountDown = 300;

//          try
//          {

//             while (!pplugin->audio_plugin_eof() && ::task_get_run())
//             {

//                sleep(100_ms);

//                iCountDown--;

//                if (iCountDown == 0)
//                {

//                   // Isn't it taking too much time to play this audio?
//                   //debug_break();

//                }

//             }

//          }
//          catch (...)
//          {

//          }

//       }

//       return pplugin;

//    }

//    ::pointer<::audio_plugin::plugin>department::prepare_audio(::file::file * pfile)
//    {

//       defer_initialize_audio_playback();

//       auto pdecoder = pmultimedia->audiowave()->m_pdecoderset->GetNewDecoder(pfile);

//       if (!pdecoder)
//       {

//          return nullptr;

//       }

//       return pdecoder;

//    }


//    ::pointer<::audio_plugin::plugin>department::get_and_play_audio(::file::file * pfile, bool bSynch)
//    {

//       ::pointer<::audio_plugin::plugin>pplugin = prepare_audio(pfile);

//       if (pplugin.is_null())
//       {

//          return nullptr;

//       }

//       return play_plugin(pplugin, bSynch);

//    }


//    void department::play_audio(::payload payloadFile, bool bSynch)
//    {

//       predicate_run(bSynch, [=]()
//       {

//          auto pfile = file()->get_reader(payloadFile, ::file::e_open_share_deny_none);

//          if (pfile)
//          {

//             get_and_play_audio(pfile, bSynch);

//          }

//       });

//    }


//    //department::department()
//    //{

//    //   //m_bFadeOutAndStopOnExit = true;

//    //   //m_paudiomixeruserbase = nullptr;

//    //}


//    //department::~department()
//    //{
//    //}


//    void department::init_instance()
//    {

//       //if (!::acme::department::init_instance())
//       //{

//       //   ERROR(".1");

//       //   return false;

//       //}

//       return true;

//    }


//    string department::get_media_call_title(string str)
//    {

//       return str;

//    }

//    void department::init3()
//    {

//       INFORMATION("start");

//       //if (m_pmultimedia.is_null())
//       //{

//       //   __construct_new(m_pmultimedia);

//       //}



// #ifdef CUBE

//       void * l = dlopen(file()->module(), RTLD_LOCAL);

//       if (l != nullptr)
//       {

//          LPFN_NEW_MULTIMEDIA_DECODER pfn;

//          pfn = (LPFN_NEW_MULTIMEDIA_DECODER)dlsym(l, "audio_decode_libmpg123_NewDecoderInterface");

//          if (pfn == nullptr)
//          {

//             //message_box(nullptr, "Failed ld libmpg1234");

//          }
//          else
//          {

//             m_mapMultimediaDecoderFactory["audio_decode_libmpg123"] = pfn;

//          }

//          pfn = (LPFN_NEW_MULTIMEDIA_DECODER)dlsym(l, "audio_decode_wave_NewDecoderInterface");

//          if (pfn == nullptr)
//          {

//             //message_box(nullptr, "Failed ld libsurf");

//          }
//          else
//          {

//             m_mapMultimediaDecoderFactory["audio_decode_wave"] = pfn;

//          }

//       }

// #endif

//       m_pmultimediafile = __allocate ::multimedia::file_application();

// #ifdef WINDOWS_DESKTOP

//       ([a-z0-9_]+)_factory(::factory::factory * pfactory);

// #endif

//       if (factory_item < ::tts::speaker >() == nullptr)
//       {

//          add_factory_item < ms_translator_speaker, ::tts::speaker >();

//       }

//       add_factory_item <::wave::player_command >();
//       add_factory_item <::audio::wave_recorder_command >();

//       //add_factory_item <::multimedia::audio_mixer_user_base::document >();
//       //add_factory_item <::multimedia::audio_mixer_user_base::frame_window >();
//       //add_factory_item <::multimedia::audio_mixer_user_base::main_impact >();
//       //add_factory_item <::multimedia::audio_mixer_user_base::control_impact >();

//       //      add_factory_item <::duration_array > ();
//       // add_factory_item <duration_array >();

//       //if (!::acme::department::init3())
//       //{

//       //   ERROR(".1");

//       //   return false;

//       //}

//       //add_matter_locator("app-core/multimedia");

//       //INFORMATION(".1");

//       //if (!m_paudiomixer)
//       //{

//       //   auto estatus = __construct_new(m_paudiomixer);

//       //   if (!estatus)
//       //   {

//       //      warningf("Could not initialize Audio Mixer (1)");

//       //   }
//       //   else
//       //   {

//       //      if (!m_paudiomixer->init1())
//       //      {

//       //         warningf("Could not initialize Audio Mixer (2)");

//       //      }
//       //      else
//       //      {

//       //         if (!m_paudiomixer->init())
//       //         {

//       //            warningf("Could not initialize Audio Mixer (3)");

//       //         }

//       //      }

//       //   }

//       //}

//       //if (!m_paudiomixeruserbase)
//       //{

//       //   auto estatus = __construct_new(m_paudiomixeruserbase);

//       //   if (!estatus)
//       //   {

//       //      warningf("Could not initialize Audio Mixer User Base (1)");

//       //   }
//       //   else
//       //   {

//       //      //m_paudiomixeruserbase->construct(this);

//       //      if (!m_paudiomixeruserbase->init1())
//       //      {

//       //         warningf("Could not initialize Audio Mixer User Base (2)");

//       //      }
//       //      else
//       //      {

//       //         if (!m_paudiomixeruserbase->init())
//       //         {

//       //            warningf("Could not initialize Audio Mixer User Base (3)");

//       //         }

//       //      }

//       //   }

//       //}

//       if (!m_paudiowave)
//       {

//          auto estatus = __construct_new(m_paudiowave);

//          if (!estatus)
//          {

//             warningf("Could not initialize Audio Wave (1)");

//          }

//       }

//       //if (m_pmediamanager.is_null())
//       //{

//       //   auto estatus = __construct_new(m_pmediamanager);

//       //   if (!estatus)
//       //   {

//       //      FATAL("Could not create Multimedia Media Manager (5)");

//       //      return false;

//       //   }


//       //}

//       //// xxx TODO
//       ////add_library(__allocate ::multimedia::library());

//       //m_pmediaplay = __allocate ::mediaplay::mediaplay();

//       //if (m_pmediaplay == nullptr)
//       //   return false;

//       //m_pmediaplaylist = __allocate ::mediaplaylist::media_playlist();


//       //if (m_pmediaplaylist.is_null())
//       //{

//       //   FATAL("Could not create Multimedia Media Playlist");

//       //   return false;

//       //}

//       /*if(!m_pmediaplaylist->initialize())
//       {
//          informationf("Could not initialize Multimedia Media Playlist");
//          return false;
//       }*/

//       if (!init_multimedia())
//       {

//          FATAL("Could not initialize Multimedia department");

//          return false;

//       }

//       return true;

//    }


//    LPFN_NEW_MULTIMEDIA_DECODER department::get_multimedia_decoder_factory(const ::string & pszTitle)
//    {

//       return m_mapMultimediaDecoderFactory[pszTitle];

//    }


//    void department::term_instance()
//    {

//       try
//       {

//          audiowave()->close();

//       }
//       catch (...)
//       {

//       }

//       //audiowave().release();

//       //try
//       //{

//       //   mediamanager()->destroy();

//       //}
//       //catch (...)
//       //{

//       //}

//       //m_pmediamanager.release();

//       //try
//       //{

//       //   m_pmediaplaylist.release();

//       //}
//       //catch (...)
//       //{

//       //}

//       //try
//       //{

//       //   if (m_paudiomixeruserbase.is_set())
//       //   {

//       //      m_paudiomixeruserbase->term();

//       //   }

//       //}
//       //catch (...)
//       //{

//       //}

//       //m_paudiomixeruserbase.release();

//       //try
//       //{

//       //   if (m_paudiomixer.is_set())
//       //   {

//       //      m_paudiomixer->term();

//       //   }

//       //}
//       //catch (...)
//       //{

//       //}

//       //m_paudiomixer.release();

//       //try
//       //{

//       //   if (m_pmultimedia.is_set())
//       //   {

//       //      m_pmultimedia->term_multimedia();

//       //      m_pmultimedia.release();

//       //   }

//       //}
//       //catch (...)
//       //{

//       //}

//       //try
//       //{

//       //   ::acme::department::term_application();

//       //}
//       //catch (...)
//       //{

//       //}


//    }




//    //void department::play_audio(::payload strFile, bool bSynch)
//    //{

//    //   multimedia().play_audio(strFile, bSynch);

//    //}



//    void department::on_song_added(string strId)
//    {


//    }


//    ::pointer<::tts::speaker>department::tts_speaker()
//    {

//       if (m_pspeaker.is_null())
//       {

//          m_pspeaker = create_tts_speaker();

//       }

//       return m_pspeaker;

//    }


//    ::pointer<::tts::speaker>department::trans_speaker()
//    {

//       if (m_ptransspeaker.is_null())
//       {

//          m_ptransspeaker = create_trans_speaker();

//       }

//       return m_ptransspeaker;

//    }


//    ::pointer<::tts::speaker>department::create_tts_speaker()
//    {

//       auto pspeaker = __øcreate < ::tts::speaker >();

//       if (pspeaker.is_set())
//       {

//          pspeaker->m_pspeakerFallback = create_trans_speaker();

//       }
//       else
//       {

//          pspeaker = create_trans_speaker();

//       }

//       return pspeaker;

//    }


//    ::pointer<::tts::speaker>department::create_trans_speaker()
//    {

//       ::pointer<::tts::speaker>pspeaker;

//       pspeaker = __allocate ms_translator_speaker();

//       return pspeaker;

//    }


//    void department::speak(string lang, string text, bool bSynch)
//    {

//       ::pointer<::tts::speaker>pspeaker = tts_speaker();

//       if (pspeaker.is_set())
//       {

//          pspeaker->speak(lang, text, bSynch);

//       }

//    }

//    void department::trans_speak(string strLang, string strText, bool bSynch)
//    {


//       ::pointer<::tts::speaker>pspeaker = trans_speaker();

//       if (pspeaker.is_set())
//       {
//          pspeaker->speak(strLang, strText, bSynch);
//       }

//       //      ::xml::document d(this);
//       //
//       //      d.load("<root>" + strText + "</root>");
//       //
//       //      strText = d.get_text();
//       //
//       //      strText.trim();
//       //
//       //      strText = psystem->html()->resolve_entities(strText);
//       //
//       //      bool bRetry = false;
//       //
//       //   retry:
//       //
//       //      if (m_strTranslatorToken.is_empty() || bRetry)
//       //      {
//       //
//       //         string strUrl = "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13";
//       //
//       //         string strResponse;
//       //
//       //         {
//       //
//       //            ::property_set set;
//       //
//       //            set["raw_http"] = true;
//       //            set["disable_common_name_cert_check"] = true;
//       //
//       //#include "sensitive/azure_resident.txt"
//       //
//       //            set["headers"]["accept"] = "department/network_payload";
//       //            set["headers"]["content-type"] = "department/x-www-form-urlencoded";
//       //
//       //            //set["post"]["code"]= "# code=\"" + strCode + "\"";
//       //            set["post"]["grant_type"] = "client_credentials";
//       //            set["post"]["client_id"] = "ca2_resident";
//       //            set["post"]["client_secret"] = pszKey1;
//       //            set["post"]["scope"] = "http://api.microsofttranslator.com";
//       //
//       //            strResponse = http()->get(strUrl, set);
//       //
//       //         }
//       //
//       //         const char * psz = strResponse;
//       //
//       //         ::payload v;
//       //
//       //         v.parse_network_payload(psz);
//       //
//       //         m_strTranslatorToken = v["access_token"];
//       //
//       //         file()->put_text_utf8(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators" / "token.txt", m_strTranslatorToken);
//       //
//       //      }
//       //
//       //      if (m_strTranslatorToken.has_character())
//       //      {
//       //
//       //         string strFile;
//       //
//       //         while (file()->exists(strFile =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators" / as_string(m_iTranslatorFile) + ".mp3"))
//       //         {
//       //
//       //            m_iTranslatorFile++;
//       //
//       //         }
//       //
//       //
//       //         ::property_set set;
//       //
//       //         set["raw_http"] = true;
//       //         set["disable_common_name_cert_check"] = true;
//       //
//       //         set["headers"]["Authorization"] = "Bearer " + m_strTranslatorToken;
//       //
//       //
//       //         if (string_begins_ci(strText, "ca2 ") || string_begins_ci(strText, "ca2\n"))
//       //         {
//       //            strText = "c a 2" + strText.substr(3);
//       //         }
//       //         if (string_ends_ci(strText, " ca2") || string_ends_ci(strText, "\nca2"))
//       //         {
//       //            strText = strText.left(strText.length() - 3) + "c a 2";
//       //         }
//       //         strText.utf8_replace(" ca2 ", " c a 2 ");
//       //         strText.utf8_replace(" ca2\n", " c a 2\n");
//       //         strText.utf8_replace("\nca2 ", "\nc a 2 ");
//       //         strText.utf8_replace("\nca2\n", "\nc a 2\n");
//       //
//       //         string strEncode = purl->url_encode(strText);
//       //
//       //         string strDecode = purl->url_decode(strEncode);
//       //
//       //         string strUrl = "http://api.microsofttranslator.com/V2/Http.svc/Speak?text=" + strEncode + "&language=" + strLang + "&format=audio/mp3&options=MaxQuality";
//       //
//       //         http()->download(strUrl, strFile, set);
//       //
//       //         int iStatusCode = set["http_status_code"];
//       //
//       //         if (iStatusCode >= 400 && iStatusCode < 500)
//       //         {
//       //            string str = file()->as_string(strFile);
//       //            if (str.case_insensitive_find("The incoming token has expired") >= 0)
//       //            {
//       //
//       //
//       //               m_strTranslatorToken.empty();
//       //
//       //            }
//       //            else if (str.case_insensitive_find("'language' must be a valid language") >= 0)
//       //            {
//       //               str = file()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing.txt");
//       //               str += strLang + "\n";
//       //               file()->put_contents(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing.txt", str);
//       //               return;
//       //            }
//       //            else if (str.case_insensitive_find("Language name is not supported") >= 0)
//       //            {
//       //               str = file()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing2.txt");
//       //               str += strLang + "\n";
//       //               file()->put_contents(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "translators/missing2.txt", str);
//       //               return;
//       //            }
//       //            else
//       //            {
//       //
//       //               return;
//       //            }
//       //
//       //         }
//       //         else
//       //         {
//       //
//       //            papp->play_audio(strFile, bSynch);
//       //
//       //         }
//       //
//       //      }
//       //
//       //      if (m_strTranslatorToken.is_empty())
//       //      {
//       //
//       //         if (!bRetry)
//       //         {
//       //
//       //            bRetry = true;
//       //
//       //            goto retry;
//       //
//       //         }
//       //
//       //      }

//    }

// //#define DEBUG_MEDIAPLAYLIST_OPEN_COUNT 0
// //
// //   ::pointer<::user::document>department::defer_create_impact(string strImpact, ::user::interaction * puiParent, e_window_flag ewindowflag, const ::atom & atom)
// //   {
// //
// //      if (strImpact == "mediaplaylist")
// //      {
// //
// //         ::pointer<::mediaplaylist::document>pplaylistdoc = papp->mediaplaylist()->m_pplaylistdoc;
// //
// //         if (pplaylistdoc.is_null())
// //         {
// //
// //            ::pointer<::mediaplaylist::media_playlist>mediaplaylist = papp->mediaplaylist();
// //
// //            pplaylistdoc = mediaplaylist->GetCurrentPlaylist(true, true, puiParent, ewindowflag, atom);
// //
// //            if (DEBUG_MEDIAPLAYLIST_OPEN_COUNT > 0)
// //            {
// //
// //               for (int i = 0; i < DEBUG_MEDIAPLAYLIST_OPEN_COUNT; i++)
// //               {
// //
// //                  pplaylistdoc->close_document();
// //
// //                  pplaylistdoc = mediaplaylist->OpenDiscardPlaylist(true, puiParent, ewindowflag, atom);
// //
// //               }
// //
// //            }
// //
// //         }
// //
// //         if (::is_set(pplaylistdoc)
// //            && ::is_set(mediaplay()->m_pmediaplaylistplayer))
// //         {
// //
// //            pplaylistdoc->set_player(mediaplay()->m_pmediaplaylistplayer);
// //
// //
// //            mediaplay()->m_pmediaplaylistplayer->m_pplaylistdoc = pplaylistdoc;
// //
// //
// //
// //         }
// //
// //         return pplaylistdoc;
// //
// //      }
// //
// //      return nullptr;
// //
// //   }
// //

//    void department::google_speak(string strLang, string strText, bool bSynch)
//    {

//       if (strText.case_insensitive_find("<h1>") >= 0 || strText.case_insensitive_find("<h2>") >= 0)
//       {

//          strText.replace_ci("<h1>", "");
//          strText.replace_ci("<h2>", "");

//       }
//       else
//       {
//          ::xml::document d;

//          d.load("<root>" + strText + "</root>");

//          strText = d.get_text();

//          strText.trim();

//       }

//       string strFile;

//       while (file()->exists(strFile =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "gtranslators" / as_string(m_iGTranslatorFile) + ".mp3"))
//       {

//          m_iGTranslatorFile++;

//       }

//       //bool bRetry = false;

//       string strKey = file_system()->as_string("C:\\sensitive\\sensitive\\seed\\google_translate_api.txt");

//       strKey.trim();

//       property_set set;

//       set["raw_http"] = true;

//       set["disable_common_name_cert_check"] = true;

//       string strQuery = purl->url_encode(strText);

//       string strUrl = "http://translate.google.com/translate_tts?ie=UTF-8&q=" + strQuery + "&tl=" + strLang + "&key=" + strKey;

//       http()->download(strUrl, strFile, set);

//       pmultimedia->play_audio(strFile, bSynch);

//    }


//    void department::speak(string text)
//    {

//       synchronous_lock synchronouslock(this->synchronization());

//       ::pointer<::tts::speaker>& pspeaker = m_pspeaker;

//       if (pspeaker.is_null())
//       {

//          pspeaker = create_tts_speaker();

//       }

//       if (pspeaker.is_set())
//       {

//          synchronouslock.unlock();

//          if (!pspeaker->speak(text))
//          {

//             informationf("test");

//          }

//       }

//    }


//    //void department::france_exit()
//    //{

//    //   if (m_pmediaplayview != nullptr)
//    //   {

//    //      m_pmediaplayview->m_bFranceExit = true;



//    //      if (m_bFadeOutAndStopOnExit)
//    //      {

//    //         if (m_pmediaplayview->get_wave_player() != nullptr && m_pmediaplayview->get_wave_player()->IsPlaying())
//    //         {

//    //            m_pmediaplayview->StartFadeOut(mediaplay::ExecuteStop, mediaplay::ExecuteNone);

//    //            ::duration tickStart = ::duration::now();

//    //            while (::duration::now() - tickStart < 15000 && m_pmediaplayview->get_wave_player()->IsPlaying())
//    //            {

//    //               sleep(100_ms);

//    //            }

//    //            informationf("not playing or timeout");

//    //         }

//    //      }

//    //   }

//    //   ::acme::department::france_exit();

//    //}
//    void department::on_decoder_fill_title_info(::multimedia::decoder * pdecoder, string_array & straTitle, string_array_array & straaTitle)
//    {

//    }

//    LPWAVEOUT department::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
//    {

//       auto pplugin = __allocate ::audio_plugin::source();

//       if (pplugin.is_null())
//       {

//          return nullptr;

//       }

//       return pplugin->waveout_open(iChannel, pformat, pcallback);

//    }

// } // namespace multimedia



