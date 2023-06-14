#include "framework.h"


#ifdef WINDOWS
#include <mmsystem.h>
#endif

#ifndef WINDOWS_DESKTOP

#define MAPPER 0

#endif

#ifdef CUBE

extern "C"
void ([a-z0-9_]+)_factory(::factory::factory * pfactory);

#endif



namespace wave
{


   wave::wave()
   {


#ifdef WINDOWS_DESKTOP

      m_uiWaveInDevice  = WAVE_MAPPER;
      m_uiWaveOutDevice = WAVE_MAPPER;

#else

      m_uiWaveInDevice  = 0;
      m_uiWaveOutDevice = 0;

#endif


   }


   wave::~wave()
   {

   }


   void wave::initialize(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      __construct_new(m_pdecoderset);

      //add_factory_item <::audio::effect_devocalizer::Group >();
      //add_factory_item <::audio::effect_devocalizer::Group::Channel >();

      if (!([a-z0-9_]+)_factory(::factory::factory * pfactory))
      {

         return ::error_failed;

      }

      return estatus;

   }

   ::pointer<in>wave::get_in()
   {

      return m_pwavein;

   }



   bool wave::([a-z0-9_]+)_factory(::factory::factory * pfactory)
   {

      PFN_factory ([a-z0-9_]+)_factory = nullptr;

#ifdef APPLE_IOS

      ([a-z0-9_]+)_factory = &([a-z0-9_]+)_factory;

#else

      __construct_new(m_plibrary);

      ::acme::library & library = *m_plibrary;

      if(library.is_opened())
         return true;

      string strLibrary = ::audio::get_default_library_name();

      if(strLibrary.is_empty())
      {

         return false;

      }

      if(!library.open(strLibrary, false))
      {

#ifdef WINDOWS_DESKTOP

         if(strLibrary == "audio_xaudio" && is_windows_7_or_lower())
         {

            strLibrary = "audio_xaudio7";

            if(library.open(strLibrary, false))
            {
               goto cont1;
            }


         }
         else if(strLibrary != "audio_mmsystem")
         {

            strLibrary = "audio_mmsystem";

            if(library.open(strLibrary, false))
            {
               goto cont1;
            }


         }

         output_error_message("Failed to open specified audio library : \"" + strLibrary + "\". Going to use fallback audio library.");

         information("Failed to do multimedia audio factory_exchange. Could not load library(1)");

         strLibrary = "audio_directsound";

         if(!library.open(strLibrary, false))
         {

            information("Failed to do multimedia audio factory_exchange. Could not load library(2)");

            strLibrary = "audio_mmsystem";

            if(!library.open(strLibrary, false))
            {

               output_error_message("Failed to open specified audio library : \"" + strLibrary + "\" and fallbacks (\"audio_mmsystem\"\"audio_directsound\". No audio library available. No audio.");

               information("Failed to do multimedia audio factory_exchange. Could not load library(3)");

               return false;

            }

         }

#else // WINDOWS_DESKTOP


         output_error_message("Failed to open '" + strLibrary + "' audio library. No audio output and possible other functionality unavailability.\n\nSome reasons:\n   - No audio plugin library present;\n   - Present audio plugin library(ies) didn't open.\n\n" + library.m_strMessage);

         return false;

#endif // !WINDOWS_DESKTOP

      }

      ([a-z0-9_]+)_factory = library.get < PFN_factory > (strLibrary + "_factory");

#ifdef WINDOWS_DESKTOP
cont1:
#endif

#endif

      if(([a-z0-9_]+)_factory == nullptr)
      {

         ([a-z0-9_]+)_factory = library.get < PFN_factory > ("factory_exchange");

         if(([a-z0-9_]+)_factory == nullptr)
         {
            information("failed to do multimedia audio factory_exchange. Could not ca2 factory_item exchange entry point_i32 function");

            return false;

         }

      }

      ([a-z0-9_]+)_factory(::factory::factory * pfactory);

      return true;

   }


   bool wave::create_in()
   {

      if (m_pwavein.is_set())
      {

         return true;

      }

      __construct(m_pwavein);

      if (m_pwavein)
      {

         m_pwavein->begin_synch();

         //m_pwavein->m_evInitialized.wait(::time((5000) * 2));

      }

      return true;

   }




   void wave::destroy()
   {

   }


   void wave::close()
   {
   }


} // namespace wave


