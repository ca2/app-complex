#include "framework.h"



namespace audio
{


   decoder_plugin_set::decoder_plugin_set()
   {

   }


   decoder_plugin_set::~decoder_plugin_set()
   {

   }


   void decoder_plugin_set::initialize(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      ::file::listing listing;

#if defined(APPLE_IOS)

      listing.add("audio_decode_libmpg123");
      listing.add("audio_decode_wave");
      listing.add("audio_decode_spotify");

      ::file::path_array straPreferred;
      straPreferred.add(library_file_name("audio_decode_mpg123"));
      listing.preferred_name(straPreferred);

#elif defined(UNIVERSAL_WINDOWS)

      listing.add("audio_decode_libmpg123.dll");
      listing.add("audio_decode_wave.dll");
      listing.add("audio_decode_spotify.dll");

      ::file::path_array straPreferred;
      straPreferred.add(library_file_name("audio_decode_mpg123"));
      listing.preferred_name(straPreferred);

#elif defined(ANDROID)

      listing.add("audio_decode_libmpg123.so");

      ::file::path_array straPreferred;
      straPreferred.add(library_file_name("audio_decode_mpg123"));
      listing.preferred_name(straPreferred);

#else

      ::file::path pathModule = dir()->ca2module();

      string strPattern = library_file_name("audio_decode_*");

      dir()->ls_file_pattern(listing, pathModule, { strPattern });

      ::file::path_array straPreferred;

      straPreferred.add(library_file_name("audio_decode_wave"));

      straPreferred.add(library_file_name("audio_decode_libmpg123"));

      listing.preferred_name(straPreferred);

#endif

      m_patha.add(listing);

      return ::success;

   }


   decoder_plugin * decoder_plugin_set::FindPlugin(const ::string & pszTitle)
   {

      synchronous_lock synchronouslock(this->synchronization());

      for(i32 i = 0; i < m_plugina.get_size(); i++)
      {

         if (m_plugina[i]->GetPluginTitle().case_insensitive_order(pszTitle) == 0)
         {

            return m_plugina.ptr_at(i);

         }

      }

      return nullptr;

   }


   decoder_plugin * decoder_plugin_set::LoadPlugin(const ::string & lpcszDll)
   {

      synchronous_lock synchronouslock(this->synchronization());

      ::pointer<decoder_plugin>pplugin = FindPlugin(lpcszDll);

      if (pplugin != nullptr)
      {

         return pplugin;

      }

      __construct_new(pplugin);

      if(!pplugin->Load(lpcszDll))
      {

         return nullptr;

      }

      m_plugina.add(pplugin);

      return pplugin;

   }


   ::pointer<decoder>decoder_plugin_set::GetNewDecoder(::file::file * pfile, bool bSeekable, i32 iReadBlockSize)
   {

      if(::is_null(pfile))
      {

         return nullptr;

      }

      ::file::path_array patha;

      string strPath = pfile->get_file_path();

      string_array stra;

      stra.explode(":", strPath);

      string strServer = purl->get_server(strPath);

      if ((stra.get_count() == 3 && stra[0] == "spotify_track")
         || string_begins_ci(strPath, "spotify:track:"))
      {

         patha.add("audio_spotify");

      }
      else if (::str::find_wwci("youtube.com", strServer) >= 0
         || ::str::find_wwci("youtu.be", strServer) >= 0)
      {

         patha.add("audio_youtube_player_api_for_iframe");

      }
      else
      {

         patha = m_patha;

      }

      // preferences

      ::count iCount = patha.get_count();

      for(::index i = 0; i < iCount; i++)
      {

         ::pointer<decoder>pdecoder = GetNewDecoder(pfile, patha[i].name(), bSeekable, iReadBlockSize);

         if (pdecoder.is_set())
         {

            return pdecoder;

         }

      }

      return nullptr;

   }


   string decoder_plugin_set::get_error_message(decoder * pdecoder, ::file::file* preader)
   {

      string strMessage("<h1>Unknown Error</h1>");

      if (!pdecoder)
      {

         strMessage = "<h2>Failed to load decoder plugin</h2>";

         if (preader)
         {

            strMessage += "Couldn't open decoder plugin for file \"" + preader->m_path + "\"<br><br>";

            strMessage += "Is plugin that can open \"" + preader->m_path.extension() + "\" files installed?";

         }

      }

      return strMessage;

   }


   ::pointer<decoder>decoder_plugin_set::GetNewDecoder(::file::file * pfile, const ::string & pszModule, bool bSeekable, i32 iReadBlockSize)
   {

      try
      {

         informationf("AudioDecoderPlugin Loading Plugin: " + string(pszModule));

         decoder_plugin * pplugin = LoadPlugin(pszModule);

         if(pplugin != nullptr)
         {

            informationf("AudioDecoderPlugin Plugin Loaded: " + string(pszModule));

            ::pointer<::multimedia::decoder>pdecoderBase = pplugin->NewDecoder();

            if(pdecoderBase.is_null())
            {

               informationf("AudioDecoderPlugin NewDecoder Failed: " + string(pszModule));

               return nullptr;

            }

            ::pointer<decoder>pdecoder = pdecoderBase;

            if(pdecoder.is_null())
            {

               return nullptr;

            }

            pdecoder->audio_set_seekable(bSeekable);

            if(iReadBlockSize > 0)
            {

               pdecoder->audio_set_read_block_size(iReadBlockSize);

            }

            if(::succeeded(pdecoder->multimedia_open(pfile)))
            {

               informationf("AudioDecoderPlugin multimedia_open Succeeded: " + string(pszModule) + " (" + pfile->get_file_path() + ")");

               return pdecoder;

            }

            informationf("AudioDecoderPlugin multimedia_open Failed: " + string(pszModule) + " (" + pfile->get_file_path() + ")");

         }

      }
      catch(...)
      {

      }

      return nullptr;

   }


} // namespace audio




