#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      department::department()
      {

      }


      department::~department()
      {

      }


      bool department::([a-z0-9_]+)_factory(::factory::factory * pfactory)
      {

         if (m_plibrary.is_null())
         {

            m_plibrary.create(this);

         }

         ::acme::library & library = *m_plibrary;

         if (library.is_opened())
         {

            return true;

         }

         string strLibrary = papp->multimedia_audio_mixer_get_default_library_name();

         if (strLibrary.is_empty())
         {

            return false;

         }

         if(!library.open(strLibrary, false))
         {

            TRACE("Failed to do multimedia audio mixer factory_item exchange. Could not load library");

            return false;

         }

         PFN_factory ([a-z0-9_]+)_factory = library.get < PFN_factory > ("factory_exchange");

         if(([a-z0-9_]+)_factory == nullptr)
         {

            TRACE("Failed to do multimedia audio mixer factory_item exchange. Could not get factory_item exchange entry point function");

            return false;

         }

         ([a-z0-9_]+)_factory(::factory::factory * pfactory);

         return true;

      }


      void department::init1()
      {

         if(!([a-z0-9_]+)_factory(::factory::factory * pfactory))
         {

            TRACE("Failed to do multimedia audio mixer factory_item exchange");

         }

         return true;

      }


      void department::term()
      {

         DestroyWindow();

      }


      void department::init()
      {

         return ::success;

      }


   } // namespace audio_mixer


} // namespace multimedia





