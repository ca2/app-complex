#include "framework.h"



namespace audio
{


   interprocess_handler::interprocess_handler(const ::string & strApp) :
      ::interprocess::handler(strApp)
   {

      m_straCallbackApp.add_unique("app-core/resident");

   }


   void interprocess_handler::on_interprocess_call(::payload & payload, const ::string & strObject, const ::string & strMember, payload_array & payloada)
   {

      if(strMember == "register_callback" && payloada.has_elements())
      {

         m_straCallbackApp.add_unique(payloada[0].get_string());

      }
      else
      {

         ::interprocess::handler::on_interprocess_call(payload, strObject,strMember, payloada);

      }

   }


   void interprocess_handler::on_media_playback_start(::file::path pathOrigin, string strTitle,string_array straArtist, string strAlbum, memory & memoryImage, string strUrl)
   {

#ifdef UNIVERSAL_WINDOWS

      return;

#endif

      payload_array va;

      va.add(pathOrigin);

      va.add(strTitle);

      va.add_item(straArtist);

      va.add(strAlbum);

      va.add(pbase64->encode(memoryImage));

      va.add(strUrl);

      for(auto strApp : m_straCallbackApp)
      {

         auto pcall = create_call(strApp, "application", "on_media_playback_start");

         pcall->add_args(va);

         pcall->announce();

      }

   }


   void interprocess_handler::on_media_playback_end(::file::path pathOrigin, string strTitle,string_array straArtist, string strAlbum)
   {

#ifdef UNIVERSAL_WINDOWS

      return;

#endif

      if (!task_get_run())
      {

         return;

      }

      payload_array va;

      va.add(pathOrigin);

      va.add(strTitle);

      va.add_item(straArtist);

      va.add(strAlbum);

      for(auto & strApp : m_straCallbackApp)
      {

         string strCallApp = strApp;

         auto pcall = create_call(strCallApp, "application", "on_media_playback_end");

         pcall->add_args(va);

         pcall->announce();

      }

   }


} // namespace audio










