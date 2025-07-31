#include "framework.h"



namespace mediaplay
{


   single_document_template::single_document_template(const ::scoped_string & scopedstrMatter,   ::type pDocClass,   ::type pFrameClass,   ::type pimpactClass ) :
      m_pActivePlaylistDoc(nullptr),
      ::user::impact_system(scopedstrMatter, pDocClass, pFrameClass, pimpactClass),
      ::user::single_document_template(scopedstrMatter, pDocClass, pFrameClass, pimpactClass)
   {

      load_template();

   }


   single_document_template::~single_document_template()
   {
#ifdef _DEBUG
      if(m_pdocument != nullptr)
         informationf("Warning: destroying single_document_template with live document.");
#endif
   }



   void single_document_template::request(::request * prequest)
   {
      pcreate->payload("document") = (::object *) nullptr;
      bool bMakeVisible = pcreate->payload("make_visible_boolean");
//      ::pointer<::user::interaction>puiParent = pcreate->payload("parent_user_interaction").cast < ::user::interaction > ();
//      ::pointer<::user::impact>pviewAlloc = pcreate->payload("allocation_impact").cast < ::impact > ();
      if(pcreate->m_payloadFile.is_empty())
      {
         pcreate->payload("document") = OpenDocumentFileNoReserve(nullptr, pcreate);
      }
      else
      {
         OpenDocumentFileNoReserve(nullptr, pcreate);
         ReserveSong(pcreate->m_payloadFile, true, bMakeVisible != 0);
         pcreate->payload("document") = m_pdocument;
      }
   }

   ::pointer<::user::document>single_document_template::OpenDocumentFileNoReserve(::payload payloadFile, ::request * prequest)
   {

      ::pointer<::user::document>pdocument;

      ::pointer<::user::frame_window>pFrame;

      bool bCreated = false;      // => doc and frame created

      bool bWasModified = false;

      if (m_pdocument.is_set())
      {

         // already have a document - reinit it
         pdocument = m_pdocument;

         if (!pdocument->save_modified())
         {

            return nullptr;        // leave the original one

         }

         ::pointer<::user::impact>pimpact = pdocument->get_impact(0);

         if(pimpact != nullptr)
         {

            pFrame = pimpact->get_parent_frame();

         }

         //      pFrame = (m_pdocument)->GetLyricWindow()->get_parent_frame();
         //      ASSERT(pFrame != nullptr);
         //      ASSERT_KINDOF(user::frame_window, pFrame);
         //      ASSERT_VALID(pFrame);

      }
      else
      {

         pdocument = create_new_document(pcreate);

         ASSERT(pFrame == nullptr);     // will be created below

         bCreated = true;

      }

      if (pdocument == nullptr)
      {

         // linux message_box(WINDOWS_DEFINITION_IDP_FAILED_TO_CREATE_DOC);
         output_error_message("Failed to create document");

         return nullptr;

      }

      ASSERT(pdocument == m_pdocument);

      bool bCreatedNewFrame = false;

      if (pFrame == nullptr && bCreated)
      {

         ASSERT(bCreated);

         // create frame - set as document frame
         bool bAutoDelete = pdocument->m_bAutoDelete;

         pdocument->m_bAutoDelete = false;

         // don't destroy if something goes wrong
         pFrame = create_new_frame(pdocument, nullptr, pcreate);

         pdocument->m_bAutoDelete = bAutoDelete;

         if (pFrame == nullptr)
         {

            // linux message_box(WINDOWS_DEFINITION_IDP_FAILED_TO_CREATE_DOC);

            output_error_message("Failed to create document");

            pdocument.release();       // explicit delete on error

            return nullptr;

         }

         bCreatedNewFrame = true;

      }

      if(payloadFile.is_empty())
      {

         set_default_title(pdocument);

         // avoid creating temporary compound file when starting up invisible
         if (!pcreate->m_bMakeVisible)
         {

            pdocument->m_bEmbedded = true;

         }

         if (!pdocument->on_new_document())
         {

            // user has been alerted to what failed in on_new_document
            informationf("::user::document::on_new_document returned false.");

            if (bCreated)
            {

               pFrame->DestroyWindow();    // will destroy document

            }

            return nullptr;

         }

      }
      else
      {

         //wait_cursor wait;

         // open an existing document
         bWasModified = pdocument->is_modified();

         pdocument->set_modified_flag(false);  // not dirty for open

         if (!pdocument->on_open_document(payloadFile))
            //if(VMS_FAILED(ReserveSong(lpszPathName, true)))
         {

            // user has been alerted to what failed in on_open_document
            informationf("::user::document::on_open_document returned false.");

            if (bCreated)
            {

               pFrame->DestroyWindow();    // will destroy document

            }
            else if (!pdocument->is_modified())
            {

               // original document is untouched
               pdocument->set_modified_flag(bWasModified);

            }
            else
            {

               // we corrupted the original document
               set_default_title(pdocument);

               if (!pdocument->on_new_document())
               {

                  informationf("Error: on_new_document failed after trying to open a document - trying to continue.");
                  // assume we can continue

               }

            }

            return nullptr;        // open failed

         }

         pdocument->set_path_name(payloadFile);

      }

      //::thread * pthread = ::get_task();

      if (bCreated)
      {

         if(papp->m_puiMain == nullptr)
         {

            papp->m_puiMain = pFrame;

         }

      }
      if(bCreatedNewFrame)
      {
         InitialUpdateFrame(pFrame, pdocument, pcreate->m_bMakeVisible);
      }

      return pdocument;
   }

   /////////////////////////////////////////////////////////////////////////////
   // single_document_template diagnostics

#ifdef _DEBUG
   void single_document_template::dump(dump_context & dumpcontext) const
   {
      ::user::impact_system::dump(dumpcontext);

      if (m_pdocument)
         dumpcontext << "with document: " << (void *)m_pdocument;
      else
         dumpcontext << "with no document";

      dumpcontext << "\n";
   }

   void single_document_template::assert_ok() const
   {
      ::user::impact_system::assert_ok();
      if (m_pdocument)
         ASSERT_VALID( (m_pdocument));
   }
#endif //_DEBUG



   bool single_document_template::ReserveSong(LPINT lpiaSongs, int iSongCount, bool bDoPlay, bool bMakeVisible)
   {

      ::pointer<::mediaplaylist::media_playlist>mediaplaylist = papp->mediaplaylist();

      ::pointer<::mediaplaylist::document>pdocument = mediaplaylist->GetCurrentPlaylist(true, bMakeVisible);

      if(!pdocument->AddSong(lpiaSongs, iSongCount, bDoPlay, bMakeVisible))
         return false;

      return true;

   }


   bool single_document_template::ReserveSong(int iSongCode, bool bDoPlay, bool bMakeVisible)
   {

      ::pointer<::mediaplaylist::media_playlist>mediaplaylist = papp->mediaplaylist();

      ::pointer<::mediaplaylist::document>pdocument = mediaplaylist->GetCurrentPlaylist(true, bMakeVisible);

      if(!pdocument->AddSong(iSongCode, bDoPlay, bMakeVisible, true))
         return false;

      return true;

   }


   bool single_document_template::ReserveSong(::payload payloadFile, bool bDoPlay, bool bMakeVisible)
   {

      ::pointer<::mediaplaylist::media_playlist>mediaplaylist = papp->mediaplaylist();

      ::pointer<::mediaplaylist::document>pdocument = mediaplaylist->GetCurrentPlaylist(true, bMakeVisible);

      if(!pdocument->AddSong(payloadFile, bDoPlay ? ::mediaplaylist::document::AddSongAndPlay : ::mediaplaylist::document::AddSongAndPlayIfNotPlaying, bMakeVisible, true))
         return false;

      return true;

   }


   bool single_document_template::ReserveSong(string_array & stra, bool bDoPlay, bool bMakeVisible)
   {

      ::pointer<::mediaplaylist::media_playlist>mediaplaylist = papp->mediaplaylist();

      ::pointer<::mediaplaylist::document>pdocument = mediaplaylist->GetCurrentPlaylist(true, bMakeVisible);

      if(!pdocument->AddSong(stra, bDoPlay, bMakeVisible))
         return false;

      return true;

   }


} // namespace mediaplay




