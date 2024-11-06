#include "framework.h"



namespace multimedia_playlist
{


   namespace veriwell
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

         return __allocate playlist();

      }

      ::pointer<::multimedia_playlist::track>session::new_track()
      {

         return __allocate track();

      }


//      void session::start_new_thread()
//      {
//
//         if (m_pthread != nullptr)
//         {
//
//            try
//            {
//
//               m_pthread->set_finish();
//
//            }
//            catch (...)
//            {
//
//            }
//
//            try
//            {
//
//               m_pthread = nullptr;
//
//            }
//            catch (...)
//            {
//
//            }
//
//         }
//
//

      //m_pthread = ___new thread(this);

      //m_pthread->m_psession = this;

      //m_pthread->begin();

//      }


      void     session::run()
      {

         m_ev.ResetEvent();

         m_bGettingCredentials = false;

         m_strUserAgent = "waven";

         m_strListName = "waven";

         m_evAudioFormat.ResetEvent();

         m_iDebug1 = 0;

         try
         {

            if (mutex() == nullptr)
            {

               informationf("no ::pointer < ::mutex > for spotify session!!\n");

            }

         }
         catch (...)
         {

         }

         return ::success;

      }


      void session::run_spotify_step()
      {

      }


      ::memory_file & session::GetMemoryFile()
      {

         if (m_pdecoderHold.is_null())
         {

            throw ::exception(error_not_expected);

         }

         return m_pdecoderHold->audio_plugin_memory_file();

      }


      void session::logged_in(bool bLogInOn)
      {

         if (!bLogInOn)
         {

            //::account::set_cred_ok(get_app(), "spotify_login", false);

            return;

         }

         //::account::set_cred_ok(get_app(), "spotify_login", true);

      }


      void session::update()
      {

      }


      void session::on_load_image(::image::image *pimage)
      {

      }


      ::multimedia_playlist::playlist * session::open_playlist(::payload payloadFile)
      {
         synchronous_lock synchronouslock(this->synchronization());
         auto pFind = -1;
         for (::collection::index i = 0; i < m_pla.get_count(); i++)
         {
            try
            {
               if (m_pla[i]->m_path.case_insensitive_order(payloadFile.get_file_path()) == 0)
               {
                  iFind = i;
                  break;
               }
            }
            catch (...)
            {
            }
         }
         if (::is_null(pFind))
         {

            auto ppl = __allocate ::multimedia_playlist::veriwell::playlist();

            ppl->load(payloadFile);

            ppl->m_iIndex = m_pla.get_size();

            m_pla.add(ppl);

            return ppl;

         }
         else
         {
            return m_pla[iFind];
         }
      }

//      session::thread::thread(::particle * pparticle) :
//         ::object(pparticle),
//         ::thread(pparticle)
//      {
//
//         m_psession = nullptr;
//
//      }
//
//
//      session::thread::~thread()
//      {
//
//
//      }
//
//
//      int session::thread::run()
//      {
//
//         return m_psession->run();
//
//      }

      void session::on_update_playlist_set()
      {

      }


      void session::container_loaded()
      {

      }


      void session::load_image()
      {

         m_ptrackDiba = nullptr;

         m_imagea.erase_all();

         ::multimedia_playlist::track * ptrack = m_ptrackCurrent;

         if (ptrack == nullptr)
         {

            return;

         }

         ::pointer<multimedia_playlist::veriwell::track>ptr = ptrack;

         if (ptr.is_null())
         {

            return;

         }

         ::image::image_pointer pimage = ::object::load_image(ptr->m_path.folder() / "Folder.jpg");

         if (!pimage)
         {

            return;

         }

         m_imagea.add(pimage);

         m_ptrackDiba = m_ptrackCurrent;

      }


      void session::on_play(::multimedia_playlist::track * ptrack)
      {

         m_ptrackCurrent = ptrack;

         load_image();

      }


   } // veriwell


} // namespace multimedia_playlist



