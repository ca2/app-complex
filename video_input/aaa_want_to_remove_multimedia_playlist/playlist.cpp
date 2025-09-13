#include "framework.h"



namespace multimedia_playlist
{



   playlist::playlist()
   {

      defer_create_synchronization();

      m_c               = 0;

      m_bNew            = true;

      m_bNewTracks      = true;

      m_bDiscard        = false;

      m_bSearch         = false;

      m_iCurrentVScroll = -1;

   }


   playlist::~playlist()
   {

      if(papp->mediaplaylist() != nullptr)
      {

         try
         {

            if (papp->mediaplaylist()->m_pplaylistdoc != nullptr)
            {

               if (papp->mediaplaylist()->m_pplaylistdoc->impact_playlist() == this)
               {

                  papp->mediaplaylist()->m_pplaylistdoc->set_impact_playlist(nullptr);

               }

               if (papp->mediaplaylist()->m_pplaylistdoc->play_playlist() == this)
               {

                  papp->mediaplaylist()->m_pplaylistdoc->set_play_playlist(nullptr);

               }

            }

         }
         catch (...)
         {


         }

      }

   }


   void playlist::initialize_multimedia_playlist_playlist(session * psession)
   {

      auto estatus = ::object::initialize(psession);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   string playlist::get_name()
   {

      if(m_bNew)
      {

         m_bNew = false;

         on_update();

      }

      return m_strName;


   }


   bool playlist::update()
   {

      //synchronous_lock synchronouslock(papp->mediaplaylist()->spotify()->mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ////m_durationLastUpdate= ::duration::now();

      ////m_strName = sp_playlist_name(m_pl);
      //if (!sp_playlist_is_loaded(m_pl))
      //{

      //   return false;

      //}

      //m_strName = sp_playlist_name(m_pl);

      //if(m_strName.is_empty())
      //{

      //   informationf("playlist with empty name");

      //}

      return true;

   }


   void playlist::on_update()
   {

      //synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex2);

      //papp->mediaplaylist()->spotify()->m_plaDeferUpdate.add_unique(this);


   }

   //void playlist::on_tracks_added(sp_track * const * tracks, int num_tracks, int position)
   //{

   //   if(m_bNewTracks)
   //   {

   //      return;

   //   }

   //   on_update_tracks();

   //}

   void playlist::on_tracks_erased(const int * tracks, int num_tracks)
   {

      if(m_bNewTracks)
      {

         return;

      }

      on_update_tracks();

   }


   bool playlist::update_tracks()
   {

      //{

      //   synchronous_lock synchronouslock(papp->mediaplaylist()->spotify()->mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //   m_tra.erase_all();

      //   array < sp_track * > a;

      //   //m_durationLastUpdateTracks= ::duration::now();

      //   count c = sp_playlist_num_tracks(m_pl);

      //   m_c = c;

      //   for(::collection::index i = 0; i < m_c; i++)
      //   {

      //      sp_track * tr = sp_playlist_track(m_pl,i);

      //      if(tr == nullptr)
      //      {

      //         return false;

      //      }

      //      sp_track_add_ref(tr);

      //      a.add(tr);

      //   }

      //   m_tra.set_size(a.get_size());

      //   for(::collection::index i = 0; i < a.get_size(); i++)
      //   {

      //      sp_track * tr = a[i];

      auto ptr  = __allocate track();

      //      m_tra.element_at(i) = ptr;

      //      ptr->m_tr = tr;

      //      ptr->m_iIndex = i;

      //      ptr->m_pl = this;

      //   }

      //}

      //{

      //   synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //   string_array_base stra;

      //   for (auto & tr : m_tra)
      //   {

      //      stra.add(tr->get_id());

      //   }


      //   m_stra =  stra;



      //}


      //if(papp->mediaplaylist()->m_pplaylistdoc != nullptr)
      //{

      //   if(papp->mediaplaylist()->m_pplaylistdoc->m_ppl == this)
      //   {

      //      papp->mediaplaylist()->m_pplaylistdoc->defer_update_songs();

      //   }

      //}

      return true;

   }


   void playlist::on_update_tracks()
   {

      /*      if(m_c == 0 && m_durationLastUpdateTracks.elapsed()  < 30 * 1000)
               return;
            else if(m_c < 100 && m_durationLastUpdateTracks.elapsed() < 90 * 1000)
               return;
            else if(m_durationLastUpdateTracks.elapsed() < 180 * 1000)
               return;*/

      //synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex2);

      //papp->mediaplaylist()->spotify()->m_plaDeferUpdateTracks.add_unique(this);


   }


   string_array_base playlist::get_stra()
   {

      if(m_bNewTracks)
      {

         m_bNewTracks = false;

         on_update_tracks();

      }

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      return m_stra;

   }

   void playlist::ensure_playlist()
   {


   }


   bool playlist::save()
   {

      return true;

   }


   bool playlist::load(string strFile)
   {

      return true;

   }

   void playlist::set_int(const ::scoped_string & scopedstr, long long iValue)
   {

      synchronous_lock synchronouslock(papp->mediaplaylist()->mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_setPlaylist[m_path + "." + string(scopedstr)] = iValue;

   }


   long long playlist::get_int(const ::scoped_string & scopedstr, long long iDefault)
   {

      synchronous_lock synchronouslock(papp->mediaplaylist()->mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      long long iValue = iDefault;

      m_setPlaylist[m_path + "." + string(scopedstr)] = iValue;

      return iValue;

   }


   void playlist::set_string(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrValue)
   {

      synchronous_lock synchronouslock(papp->mediaplaylist()->mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      string strValue(scopedstrValue);

      m_setPlaylist[m_path + "." + string(scopedstr)] = strValue;

   }


   string playlist::get_string(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrDefault)
   {

      synchronous_lock synchronouslock(papp->mediaplaylist()->mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      string strValue(scopedstrDefault);

      m_setPlaylist[m_path + "." + string(scopedstr)] = strValue;

      return strValue;

   }



   ::collection::count playlist::get_count()
   {

      return 0;

   }


   bool playlist::is_shuffle()
   {

      return false;

   }


   bool playlist::is_recursive()
   {

      return false;

   }


   bool playlist::is_loop()
   {

      return false;

   }


   string playlist::add_song(::payload payloadFile, bool bAddDuplicate)
   {

      return "";

   }


   bool playlist::erase_song(::collection::index iSong, bool bUpdate)
   {

      return true;

   }


   string playlist::get_title()
   {

      if (m_strTitle.has_character())
      {

         return m_strTitle;

      }

      return m_strName;

   }


} // namespace multimedia_playlist








