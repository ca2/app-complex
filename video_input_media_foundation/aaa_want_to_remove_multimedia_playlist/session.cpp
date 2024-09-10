#include "framework.h"



namespace multimedia_playlist
{


   session::session()
   {

      defer_create_synchronization();

   }


   session::~session()
   {


   }


   ::pointer<::multimedia_playlist::playlist>session::new_playlist()
   {

      return nullptr;

   }


   ::pointer<::multimedia_playlist::track>session::new_track()
   {

      return nullptr;

   }



//   void session::start_new_thread()
//   {
//
//      if (m_pthread != nullptr)
//      {
//
//         try
//         {
//
//            m_pthread->set_finish();
//
//         }
//         catch (...)
//         {
//
//         }
//
//         try
//         {
//
//            m_pthread = nullptr;
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//      m_ev.ResetEvent();
//
//      m_pthread = nullptr;
//
//      m_bGettingCredentials = false;
//
//
//
//   }


   void     session::run()
   {

      return ::success;

   }


   void session::defer_sleep()
   {


   }


   void session::run_spotify_step()
   {

   }


   void session::load_image()
   {


   }


   void session::on_load_image(::image::image *pimage)
   {

   }


   void session::on_play(::multimedia_playlist::track * ptrack)
   {

      m_ptrackCurrent = ptrack;

   }


   ::memory_file & session::GetMemoryFile()
   {

      if (m_pdecoderHold.is_null())
         throw ::exception(error_not_expected);

      return m_pdecoderHold->audio_plugin_memory_file();

   }


   void session::logged_in(bool bLogInOn)
   {

      if(!bLogInOn)
      {

         ///::account::set_cred_ok(get_app(), "spotify_login",false);

         return;

      }

      //::account::set_cred_ok(get_app(), "spotify_login",true);


   }


   void session::update()
   {



   }


//   session::thread::thread(::particle * pparticle) :
//      ::object(pparticle),
//      ::thread(pparticle)
//   {
//
//      m_psession = nullptr;
//
//   }
//
//
//   session::thread::~thread()
//   {
//
//
//   }
//
//
//   i32 session::thread::run()
//   {
//
//      return m_psession->run();
//
//   }

   void session::on_update_playlist_set()
   {

      if (papp->mediaplaylist()->m_pplaylistlistview != nullptr)
      {

         papp->mediaplaylist()->m_pplaylistlistview->_001OnUpdateItemCount();

      }

   }


   void session::container_loaded()
   {

   }


   ::multimedia_playlist::playlist * session::open_playlist(::payload payloadFile)
   {

      return nullptr;

   }


   ::multimedia_playlist::playlist * session::open_search(::payload payloadFile)
   {

      return nullptr;

   }



} // namespace multimedia_playlist




