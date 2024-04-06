#include "framework.h"

//#include "aura/message.h"
#include "acme/constant/id.h"


namespace multimedia
{


   namespace audio_mixer_user_base
   {


      thread::thread()
      {
      }

      thread::~thread()
      {
      }


      void thread::init_thread()
      {

         auto estatus = ::thread::init_thread();

         if (!estatus)
         {

            return estatus;

         }

         return true;

      }


      void thread::term_thread()
      {

         ::thread::term_thread();

      }


      void thread::install_message_routing(::channel * pchannel)
      {

         MESSAGE_LINK(::message_thread, pchannel, this, &thread::_001OnThreadMessage);

      }


      void thread::_001OnThreadMessage(::message::message * pmessage)
      {

         ::pointer<::user::message>pusermessage(pmessage);

         switch(pusermessage->m_wparam)
         {
         case wparam_display_a_mixer:
         {

            //wait_cursor waitcursor(//this);

            //auto pdepartment = m_pdepartment;

            auto pdoctemplate = papp->audiomixeruserbase()->get_document_template();

            ASSERT(pdoctemplate != nullptr);

            if(pdoctemplate != nullptr)
            {

               ::pointer<::user::document>pdocument = pdoctemplate->open_new_document(get_app());

               if(pdocument != nullptr)
               {

                  pdocument->update_all_impacts(id_new_destination);

                  ::pointer<::user::impact>pimpact = pdocument->get_impact(0);

                  if(pimpact != nullptr)
                  {

                     ::pointer<::user::interaction>puserinteraction = pimpact->get_parent_frame();

                     if(puserinteraction != nullptr)
                     {

                        //puserinteraction->set_keyboard_focus();
                        //puserinteraction->set_foreground_window();
                        //puserinteraction->BringWindowToTop();
                        //puserinteraction->display(e_display_restore);
                        puserinteraction->display(e_display_restore, XXXe_activation_set_foreground);

                     }

                  }

               }

            }

         }
         break;

         }


         if(pusermessage->m_wparam ==  23)
         {
         }
         else if(pusermessage->m_wparam ==  21)
         {
         }
         else if(pusermessage->m_wparam == 19)
         {
            ASSERT(false);
            //        CDBCentral * pgraphics = (CDBCentral *) lParam;
            //      pgraphics->SongsCreateBuildAlbumThread(
            //        (CDataCentral::EBuildSongsAlbumOperation)
            //      (CDataCentral::eBuildSongsAlbumDeleteNotFound |
            //    CDataCentral::eBuildSongsAlbumAddNew |
            //  CDataCentral::eBuildSongsAlbumCreateSearchReferences),
            //false, this, this);
         }
         else if(pusermessage->m_wparam == 20)
         {
            ASSERT(false);
            //        CDBCentral * pgraphics = (CDBCentral *) lParam;
            //      pgraphics->SongsCreateBuildAlbumThread(
            //        (CDataCentral::EBuildSongsAlbumOperation)
            //      (CDataCentral::eBuildSongsAlbumAddNew |
            //    CDataCentral::eBuildSongsAlbumCreateSearchReferences),
            //  true, this, this);
         }
         else if(pusermessage->m_wparam == 810)
         {
            ASSERT(false);
            //        CDBCentral * pgraphics = (CDBCentral *) lParam;
            //      pgraphics->SongsCreateBuildAlbumThread(
            //        (CDataCentral::EBuildSongsAlbumOperation)
            //      CDataCentral::eBuildSongsAlbumDeleteNotFound,
            //    false, this, this);
         }
         else if(pusermessage->m_wparam == 20191817)
         {
            ASSERT(false);
         }
         else if(pusermessage->m_wparam == 67985)
         {
            ASSERT(false);
            //m_pMixerDocTemplate->close_all_documents(lParam != 0);
         }


         //    if(m_pMixerDocTemplate != nullptr)
         //  {
         //    m_pMixerDocTemplate->open_new_document();
         //  if(GetMainWnd() != nullptr)
         //{
         //  GetMainWnd()->set_foreground_window();
         //}
         //}

      }


      void thread::initialize(::particle * pparticle)
      {

         return ::success;

      }



      //::pointer<department>thread::get_section()
      //{
      //   return m_psection;
      //}


   } // namespace audio_mixer_user_base


} // namespace multimedia






