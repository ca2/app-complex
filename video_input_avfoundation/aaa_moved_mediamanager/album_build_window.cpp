#include "framework.h"



namespace  mediamanager
{


   album_build_window::album_build_window()
   {
      m_b1123 = false;
      m_iFieldIndexTitle = -1;
      m_iFieldIndexArtist = -1;
      m_iFieldIndexFileName = -1;
      m_iPreBuildStep = -1;
   }

   album_build_window::~album_build_window()
   {
   }

   bool album_build_window::create()
   {
      return create_message_queue("_vmsgenAlbumBuildWnd");
   }

   void album_build_window::start_build()
   {
      KillTimer(1123);
      KillTimer(1124);
      m_iPreBuildStep = -1;
      SetTimer(1122, 30, nullptr);
   }

   void album_build_window::stop_build()
   {
      m_b1123 = false;
      KillTimer(1123);
      KillTimer(1124);
   }

   void album_build_window::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      auto uEvent = ptimer->m_uEvent;

      if(uEvent == 1122)
      {

         if(!m_palbumbuild->PreBuild(m_iPreBuildStep, true, true))
         {

            KillTimer(1122);

         }

         m_oswindowCallback->post_message(WM_USER + 1217, 0, -1);
         if(m_iPreBuildStep == -1)
         {
            KillTimer(1122);
            m_b1123 = true;
            SetTimer(1123, 30, nullptr);
         }
      }
      else if(uEvent == 1123)
      {
         //::pointer<::mediamanager::album_build>palbumbuild = album_build();
         //if(palbumbuild->m_bBuilt == true)
         //{
         //   KillTimer(1123);
         //   m_b1123 = false;
         //}
         //else
         //{

         //   KillTimer(1124);

         //   cslock slRead1(&palbumbuild->m_csRead1);

         //   ::pointer<::sqlite::dataset>pds = palbumbuild->m_pdatasetRead1;

         //   if(m_iFieldIndexTitle < 0)
         //   {
         //      m_iFieldIndexTitle      = pds->field_index("title");
         //      m_iFieldIndexArtist     = pds->field_index("artist");
         //      //m_iFieldIndexFileName   = pds->field_index("filename");
         //   }


         //   ::int_array & ia = palbumbuild->GetPriorityArray();

         //   if(ia.get_size() <= 0)
         //   {
         //      if(palbumbuild->m_pdatabase->in_transaction())
         //      {
         //         palbumbuild->m_pdatabase->commit_transaction();
         //      }
         //      KillTimer(1123);
         //      m_b1123 = false;
         //      SetTimer(1124, 50, nullptr);
         //   }

         //   if(!palbumbuild->m_pdatabase->in_transaction())
         //   {
         //      m_iTransactionTrigger = 0;
         //      palbumbuild->m_pdatabase->start_transaction();
         //   }

         //   int iUpdatedId;

         //   ::get_task()->set_thread_priority(::e_priority_highest);


         //   ::collection::count iRemove = maximum(30, ia.get_size());

         //   ::int_array iaRemove;
         //   ::payload fv;
         //   int iId;
         //   int iAdded = 0;
         //   int iUpdated = 0;
         //   int iRemoved = 0;
         //   while(ia.get_size() > 0)
         //   {
         //      iId = ia.element_at(0);
         //      ia.erase_at(0);
         //      fv = iId;
         //      if(!pds->find_first("id", fv))
         //         continue;

         //      string wstrPath;
         //      wstrPath = pds->fv("filepath");

         //      index iFind;
         //      if((iFind = palbumbuild->m_fileinfo.m_wstraAdd.find_first(wstrPath)) >= 0)
         //      {
         //         iAdded++;
         //         palbumbuild->add(wstrPath, palbumbuild->m_fileinfo.m_timeaAdd[iFind]);
         //         palbumbuild->m_fileinfo.m_wstraAdd.erase_at(iFind);
         //         palbumbuild->m_fileinfo.m_timeaAdd.erase_at(iFind);
         //         break;
         //      }
         //      else if((iFind = palbumbuild->m_fileinfo.m_wstraUpdate.find_first(wstrPath)) >= 0)
         //      {
         //         iUpdated++;
         //         iUpdatedId = palbumbuild->m_fileinfo.m_iaUpdate[iFind];
         //         palbumbuild->Update(
         //         wstrPath,
         //         palbumbuild->m_fileinfo.m_timeaUpdate[iFind],
         //         palbumbuild->m_fileinfo.m_iaUpdate[iFind]);
         //         pds->FieldValueAt(m_iFieldIndexTitle)     = palbumbuild->record().m_wstrTitle;
         //         pds->FieldValueAt(m_iFieldIndexArtist)    = palbumbuild->record().m_wstrArtist;
         //         // pds->FieldValueAt(m_iFieldIndexFileName)  = palbumbuild->album_record().m_wstrFileName;
         //         palbumbuild->m_fileinfo.m_iaUpdate.erase_at(iFind);
         //         palbumbuild->m_fileinfo.m_wstraUpdate.erase_at(iFind);
         //         palbumbuild->m_fileinfo.m_timeaUpdate.erase_at(iFind);
         //         break;
         //      }
         //      else if((iFind = palbumbuild->m_fileinfo.m_wstraRemove.find_first(wstrPath)) >= 0)
         //      {
         //         iRemoved++;
         //         iaRemove.add(palbumbuild->m_fileinfo.m_iaRemove[iFind]);
         //         palbumbuild->m_fileinfo.m_iaRemove.erase_at(iFind);
         //         palbumbuild->m_fileinfo.m_wstraRemove.erase_at(iFind);
         //         pds->erase_row();
         //         iRemove--;
         //         if(iRemove < 0)
         //            break;
         //      }
         //   }
         //   palbumbuild->erase(iaRemove);
         //   if(ia.get_size() <= 0)
         //   {
         //      if(palbumbuild->m_pdatabase->in_transaction())
         //      {
         //         palbumbuild->m_pdatabase->commit_transaction();
         //      }
         //      KillTimer(1123);
         //      m_b1123 = false;
         //      SetTimer(1124, 50, nullptr);
         //   }
         //   if(iRemoved > 0 || iAdded > 0)
         //   {
         //      m_oswindowCallback->post_message(WM_USER + 1217, 0, -1);
         //   }
         //   else if(iUpdated > 0)
         //   {
         //      m_oswindowCallback->post_message(WM_USER + 1217, 1, iUpdated == 1 ? iUpdatedId : -1);
         //   }
         //}

      }
      else if(uEvent == 1124)
      {
         //::pointer<::mediamanager::album_build>palbumbuild = album_build();
         //cslock slRead1(&palbumbuild->m_csRead1);
         //::pointer<::sqlite::dataset>pds = palbumbuild->m_pdatasetRead1;

         //if(m_iFieldIndexTitle < 0)
         //{
         //   m_iFieldIndexTitle      = pds->field_index("title");
         //   m_iFieldIndexArtist     = pds->field_index("artist");
         //   //m_iFieldIndexFileName   = pds->field_index("filename");
         //}

         //::get_task()->set_thread_priority(::e_priority_below_normal);

         //int iRemove = 30;
         //if(!palbumbuild->m_pdatabase->in_transaction())
         //{
         //   m_iTransactionTrigger = 0;
         //   palbumbuild->m_pdatabase->start_transaction();
         //}

         //::int_array iaRemove;
         //auto pFind = 0;
         //::payload fv;
         //int iAdded = 0;
         //int iUpdated = 0;
         //int iRemoved = 0;
         //while(true)
         //{
         //   if(iFind < palbumbuild->m_fileinfo.m_iaUpdate.get_size())
         //   {
         //      iUpdated++;
         //      fv = palbumbuild->m_fileinfo.m_iaUpdate[iFind];
         //      if(pds->find_first("id", fv))
         //      {
         //         palbumbuild->Update(
         //         palbumbuild->m_fileinfo.m_wstraUpdate[iFind],
         //         palbumbuild->m_fileinfo.m_timeaUpdate[iFind],
         //         palbumbuild->m_fileinfo.m_iaUpdate[iFind]);
         //         pds->FieldValueAt(m_iFieldIndexTitle)     = palbumbuild->record().m_wstrTitle;
         //         pds->FieldValueAt(m_iFieldIndexArtist)    = palbumbuild->record().m_wstrArtist;
         //         //    pds->FieldValueAt(m_iFieldIndexFileName)  = palbumbuild->album_record().m_wstrFileName;
         //         palbumbuild->m_fileinfo.m_iaUpdate.erase_at(iFind);
         //         palbumbuild->m_fileinfo.m_wstraUpdate.erase_at(iFind);
         //         palbumbuild->m_fileinfo.m_timeaUpdate.erase_at(iFind);
         //         break;
         //      }
         //      else
         //      {
         //         //ASSERT(false);
         //      }

         //   }
         //   else if(iFind < palbumbuild->m_fileinfo.m_iaRemove.get_size())
         //   {
         //      iRemoved++;
         //      fv = palbumbuild->m_fileinfo.m_iaRemove[iFind];
         //      if(pds->find_first("id", fv))
         //      {
         //         iaRemove.add(palbumbuild->m_fileinfo.m_iaRemove[iFind]);
         //         palbumbuild->m_fileinfo.m_iaRemove.erase_at(iFind);
         //         palbumbuild->m_fileinfo.m_wstraRemove.erase_at(iFind);
         //         pds->erase_row();
         //         iRemove--;
         //         if(iRemove < 0)
         //            break;
         //      }
         //      else
         //      {
         //         iFind++;
         //      }
         //   }
         //   else
         //   {
         //      if(palbumbuild->m_pdatabase->in_transaction())
         //      {
         //         palbumbuild->m_pdatabase->commit_transaction();
         //      }

         //      KillTimer(1124);
         //      palbumbuild->m_bBuilt = true;
         //      break;
         //   }
         //}
         //m_iTransactionTrigger += iUpdated;
         //if(m_iTransactionTrigger > 240)
         //{
         //   if(palbumbuild->m_pdatabase->in_transaction())
         //   {
         //      palbumbuild->m_pdatabase->commit_transaction();
         //   }
         //   palbumbuild->m_pdatabase->start_transaction();
         //   m_iTransactionTrigger = 0;
         //}
         //palbumbuild->erase(iaRemove);
         //if(iRemoved > 0 || iAdded > 0)
         //{
         //   m_oswindowCallback->post_message(WM_USER + 1217, 2, -1);
         //}
         //else if(iUpdated > 0)
         //{
         //   m_oswindowCallback->post_message(WM_USER + 1217, 3, -1);
         //}
      }
   }

   ::pointer<::mediamanager::album_build>album_build_window::album_build()
   {
      return m_palbumbuild;
   }

   void album_build_window::Initialize(::pointer<::mediamanager::album_build>albumbuild)
   {
      m_palbumbuild = palbumbuild;
   }

}
