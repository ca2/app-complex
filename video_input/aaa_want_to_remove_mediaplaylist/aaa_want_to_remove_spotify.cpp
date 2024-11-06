

::mediaplaylist::plspotify * spotifypl(void * p)
{

   return (::mediaplaylist::plspotify *) p;

}


::mediaplaylist::plspotify * userdata(sp_session * session)
{

   return spotifypl(sp_session_userdata(session));

}



void SP_CALLCONV mediaplaylist_plspotify_image_loaded_cb(sp_image * pimage,void *userdata);

//static void SP_CALLCONV  try_jukebox_start(sp_session * sess);


/**
* Callback from libplspotify, telling us the rootlist is fully synchronized
* We just print an informational message
*
* @param  pc            The playlist container handle
* @param  userdata      The opaque pointer
*/
static void SP_CALLCONV container_loaded(sp_playlistcontainer *pc,void *userdata)
{

   spotifypl(userdata)->container_loaded(pc);

}



/* ---------------------------  SESSION CALLBACKS  ------------------------- */
/**
* This callback is called when an attempt to login has succeeded or failed.
*
* @sa sp_session_callbacks#logged_in
*/
static void SP_CALLCONV  logged_in(sp_session *sess,sp_error error)
{
   sp_playlistcontainer *pc = sp_session_playlistcontainer(sess);
   int i;

   if(SP_ERROR_OK != error)
   {
      fprintf(stderr,"jukebox: Login failed: %s\n",
              sp_error_message(error));

      userdata(sess)->logged_in(false);

   }
   else
   {

      userdata(sess)->logged_in(true);

      sp_playlistcontainer_add_callbacks(
      pc,
      &userdata(sess)->pc_callbacks,
      userdata(sess));

   }


}


/**
* Called on various events to start playback if it hasn't been started already.
*
* The function simply starts playing the first track of the playlist.
*/
//static void SP_CALLCONV  try_jukebox_start(sp_session * sess)
//{
//   sp_track *t;
//
//   if(!userdata(sess)->jukeboxlist)
//      return;
//
//   if(!sp_playlist_num_tracks(userdata(sess)->jukeboxlist)) {
//      fprintf(stderr,"jukebox: No tracks in playlist. Waiting\n");
//      return;
//   }
//
//   if(sp_playlist_num_tracks(userdata(sess)->jukeboxlist) < userdata(sess)->track_index) {
//      fprintf(stderr,"jukebox: No more tracks in playlist. Waiting\n");
//      return;
//   }
//
//   t = sp_playlist_track(userdata(sess)->jukeboxlist,userdata(sess)->track_index);
//
//   if(userdata(sess)->currenttrack && t != userdata(sess)->currenttrack) {
//      /* Someone changed the current track */
//      //audio_fifo_flush(&g_audiofifo);
//      sp_session_player_unload(sess);
//      userdata(sess)->currenttrack = NULL;
//   }
//
//   if(!t)
//      return;
//
//   if(sp_track_error(t) != SP_ERROR_OK)
//      return;
//
//   if(userdata(sess)->currenttrack == t)
//      return;
//
//   userdata(sess)->playback_done = 0;
//
//   userdata(sess)->currenttrack = t;
//
//   printf("jukebox: Now playing \"%s\"...\n",sp_track_name(t));
//   //fflush(stdout);
//
//   sp_session_player_load(sess,t);
//   sp_session_player_play(sess,1);
//}
//

/**
* This callback is called from an internal libplspotify thread to ask us to
* reiterate the main loop.
*
* We notify the main thread using a condition variable and a protected variable.
*
* @sa sp_session_callbacks#notify_main_thread
*/
static void SP_CALLCONV  notify_main_thread(sp_session *sess)
{
   //   pthread_mutex_lock(&g_notify_mutex);
   userdata(sess)->notify_do = 1;
   userdata(sess)->m_ev.SetEvent();
   //pthread_cond_signal(&g_notify_cond);
   //pthread_mutex_unlock(&g_notify_mutex);
}

/**
* This callback is used from libplspotify whenever there is PCM data available.
*
* @sa sp_session_callbacks#music_delivery
*/
static int SP_CALLCONV music_delivery(sp_session *sess,const sp_audioformat *format,
                                      const void *frames,int num_frames)
{

   int & start = userdata(sess)->playback_start;

   try
   {

      synchronous_lock synchronouslock(&userdata(sess)->m_pmutexFile);

      if(userdata(sess)->m_af.sample_rate == 0 && userdata(sess)->m_af.channels == 0 && start >= 32)
      {

         if(format->sample_rate > 0 && format->channels > 0)
         {

            userdata(sess)->m_af = *format;

            userdata(sess)->m_evAudioFormat.SetEvent();

         }

      }


      if(userdata(sess)->playback_done)
      {

         return 0;

      }

      start++;

      userdata(sess)->GetMemoryFile().write(frames,num_frames * 2 * userdata(sess)->m_af.channels);


      return num_frames;

   }
   catch(...)
   {

   }

   return 0;

}


/**
* This callback is used from libplspotify when the current track has ended
*
* @sa sp_session_callbacks#end_of_track
*/
static void SP_CALLCONV  end_of_track(sp_session *sess)
{
   userdata(sess)->playback_done = 1;
   userdata(sess)->notify_do = 1;
}


/**
* Callback called when libplspotify has aaa_primitive_new metadata available
*
* Not used in this example (but available to be able to reuse the session.c file
* for other examples.)
*
* @sa sp_session_callbacks#metadata_updated
*/
static void SP_CALLCONV  metadata_updated(sp_session *sess)
{
   //   try_jukebox_start(sess);
}

/**
* Notification that some other connection has started playing on this account.
* Playback has been stopped.
*
* @sa sp_session_callbacks#play_token_lost
*/
static void SP_CALLCONV  play_token_lost(sp_session *sess)
{
   ///audio_fifo_flush(&g_audiofifo);

   if(userdata(sess)->currenttrack != NULL)
   {
      sp_session_player_unload(sess);
      userdata(sess)->currenttrack = NULL;
   }
}
/* --------------------  PLAYLIST CONTAINER CALLBACKS  --------------------- */
/**
* Callback from libplspotify, telling us a playlist was added to the playlist container.
*
* We add our playlist callbacks to the newly added playlist.
*
* @param  pc            The playlist container handle
* @param  pl            The playlist handle
* @param  position      Index of the added playlist
* @param  userdata      The opaque pointer
*/
static void SP_CALLCONV  SP_CALLCONV  playlist_added(sp_playlistcontainer *pc,sp_playlist *pl,int position,void *userdata)
{

   sp_playlist_add_callbacks(pl,&spotifypl(userdata)->pl_callbacks,userdata);

   //spotifypl(userdata)->container_loaded(pc);

}


/**
* Callback from libplspotify, telling us a playlist was erased from the playlist container.
*
* This is the place to erase our playlist callbacks.
*
* @param  pc            The playlist container handle
* @param  pl            The playlist handle
* @param  position      Index of the erased playlist
* @param  userdata      The opaque pointer
*/
static void SP_CALLCONV  playlist_erased(sp_playlistcontainer *pc,sp_playlist *pl, int position,void *userdata)
{

   sp_playlist_erase_callbacks(pl,&spotifypl(userdata)->pl_callbacks,userdata);

   //spotifypl(userdata)->container_loaded(pc);

}

/**
* Callback from libplspotify. Something renamed the playlist.
*
* @param  pl            The playlist handle
* @param  userdata      The opaque pointer
*/
static void SP_CALLCONV playlist_renamed(sp_playlist *pl,void *userdata)
{

   //spotifypl(userdata)->container_loaded(pc);
   //sp_playlistcontainer * pc
}

/**
* Callback from libplspotify, telling us the rootlist is fully synchronized
* We just print an informational message
*
* @param  pc            The playlist container handle
* @param  userdata      The opaque pointer
*/
//static void SP_CALLCONV  container_loaded(sp_playlistcontainer *pc,void *userdata)
//{
//   fprintf(stderr,"jukebox: Rootlist synchronized (%d playlists)\n",
//      sp_playlistcontainer_num_playlists(pc));
//}


/**
* The playlist container callbacks
*/


/* --------------------------  PLAYLIST CALLBACKS  ------------------------- */
/**
* Callback from libplspotify, saying that a track has been added to a playlist.
*
* @param  pl          The playlist handle
* @param  tracks      An array of track handles
* @param  num_tracks  The number of tracks in the \c tracks array
* @param  position    Where the tracks were inserted
* @param  userdata    The opaque pointer
*/
static void SP_CALLCONV tracks_added(sp_playlist *pl,sp_track * const *tracks,
                                     int num_tracks,int position,void *userdata)
{
   if(pl != spotifypl(userdata)->jukeboxlist)
      return;

   printf("jukebox: %d tracks were added\n",num_tracks);
   //fflush(stdout);
   //try_jukebox_start(spotifypl(userdata)->sp);
}

/**
* Callback from libplspotify, saying that a track has been added to a playlist.
*
* @param  pl          The playlist handle
* @param  tracks      An array of track indices
* @param  num_tracks  The number of tracks in the \c tracks array
* @param  userdata    The opaque pointer
*/
static void SP_CALLCONV tracks_erased(sp_playlist *pl,const int *tracks,
                                       int num_tracks,void *userdata)
{
   int i,k = 0;

   if(pl != spotifypl(userdata)->jukeboxlist)
      return;

   //for(i = 0; i < num_tracks; ++i)
   //   if(tracks[i] < spotifypl(userdata)->track_index)
   //      ++k;

   //spotifypl(userdata)->track_index -= k;

   //printf("jukebox: %d tracks were erased\n",num_tracks);
   //fflush(stdout);
   //try_jukebox_start(spotifypl(userdata)->sp);
}

/**
* Callback from libplspotify, telling when tracks have been moved around in a playlist.
*
* @param  pl            The playlist handle
* @param  tracks        An array of track indices
* @param  num_tracks    The number of tracks in the \c tracks array
* @param  new_position  To where the tracks were moved
* @param  userdata      The opaque pointer
*/
static void SP_CALLCONV tracks_moved(sp_playlist *pl,const int *tracks,
                                     int num_tracks,int new_position,void *userdata)
{
   if(pl != spotifypl(userdata)->jukeboxlist)
      return;

   //printf("jukebox: %d tracks were moved around\n",num_tracks);
   ////fflush(stdout);
   //try_jukebox_start(spotifypl(userdata)->sp);
}

/**
* A track has ended. Remove it from the playlist.
*
* Called from the main loop when the music_delivery() callback has set g_playback_done.
*/
static void track_ended(sp_session * sess)
{
   int tracks = 0;
   if(userdata(sess)->currenttrack)
   {
      userdata(sess)->m_evAudioFormat.SetEvent();
      userdata(sess)->currenttrack = NULL;
      sp_session_player_unload(sess);
      userdata(sess)->track_loaded = 0;
      //if(userdata(sess)->erase_tracks) {
      //   sp_playlist_erase_tracks(userdata(sess)->jukeboxlist,&tracks,1);
      //}
      //else {
      //   ++userdata(sess)->track_index;
      //   try_jukebox_start(sess);
      //}
   }

   //if(userdata(sess)->currenttrack) {
   //   userdata(sess)->currenttrack = NULL;
   //   sp_session_player_unload(sess);
   //   if(userdata(sess)->erase_tracks) {
   //      sp_playlist_erase_tracks(userdata(sess)->jukeboxlist,&tracks,1);
   //   }
   //   else {
   //      ++userdata(sess)->track_index;
   //      try_jukebox_start(sess);
   //   }
   //}
}






namespace mediaplaylist
{


   plspotify::plspotify(::particle * pparticle)  :
      object(pparticle),
      thread(pparticle),
      
      m_memfile(pparticle),
      
      m_pmutexFile(pparticle)
   {

      m_session               = NULL;
      erase_tracks = 0;
      notify_do = 0;
      playback_done = 0;
      jukeboxlist = NULL;
      currenttrack = NULL;
      track_index = -1;

      notify_do = 0;
      playback_done = 0;

      ZERO(pc_callbacks);

      pc_callbacks.playlist_added = &playlist_added;
      pc_callbacks.playlist_erased = &playlist_erased;
      pc_callbacks.container_loaded = &::container_loaded;


      /**
      * The callbacks we are interested in for individual playlists.
      */

      ZERO(pl_callbacks);

      pl_callbacks.tracks_added = &tracks_added;
      pl_callbacks.tracks_erased = &tracks_erased;
      pl_callbacks.tracks_moved = &tracks_moved;
      pl_callbacks.playlist_renamed = &playlist_renamed;


      ZERO(session_callbacks);

      session_callbacks.logged_in = &::logged_in;
      session_callbacks.notify_main_thread = &notify_main_thread;
      session_callbacks.music_delivery = &music_delivery;
      session_callbacks.metadata_updated = &metadata_updated;
      session_callbacks.play_token_lost = &play_token_lost;
      session_callbacks.log_message = NULL;
      session_callbacks.end_of_track = &end_of_track;

      m_strLocationCache      =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "spotify\\cache";
      m_strLocationSettings   =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "spotify\\settings";

               auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create(m_strLocationCache);
               auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create(m_strLocationSettings);

      m_strUserAgent          = "waven";

      m_strListName = "waven";
      track_loaded = false;

      ZERO(spconfig);

      spconfig.api_version             = SPOTIFY_API_VERSION;
      spconfig.cache_location          = m_strLocationCache;
      spconfig.settings_location       = m_strLocationSettings;
      spconfig.application_key         = g_appkey;
      spconfig.application_key_size    = g_appkey_size;
      spconfig.user_agent              = m_strUserAgent;
      spconfig.callbacks               = &session_callbacks;

      spconfig.userdata                = this;

      m_evAudioFormat.ResetEvent();

      begin();

   }


   plspotify::~plspotify()
   {


   }


   int plspotify::run()
   {

      m_ev.ResetEvent();

      int err = sp_session_create(&spconfig,&m_session);

      m_ev.wait(minutes(1));

      string username = "camiloveriwell";

      string password = file_system()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "config\\spotify\\pas.txt");

      m_ev.ResetEvent();

      sp_session_login(m_session,username,password,0,NULL);

      next_timeout = 0;

      while(m_bRun)
      {

         run_spotify_step();

      }

      if(papp->mediaplaylist()->m_bPendingCheckForRestartOnWasPlaying)
      {

         papp->mediaplaylist()->m_bPendingCheckForRestartOnWasPlaying = false;

         papp->mediaplaylist()->GetCurrentPlaylist(false)->defer_restart_on_was_playing();

      }


      return 0;

   }

   void plspotify::run_spotify_step()
   {

      synchronous_lock synchronouslock(m_pmutex);

      if(next_timeout == 0)
      {

         synchronouslock.unlock();

         while(!notify_do && m_bRun)
         {

            m_ev.wait(::duration(84));

         }

         synchronouslock.lock();

      }

      if(!m_bRun)
         return;

      notify_do = 0;

      m_ev.ResetEvent();

      if(playback_done && track_loaded)
      {

         track_ended(m_session);

      }

      do
      {

         sp_session_process_events(m_session,&next_timeout);

      }
      while(next_timeout == 0 && m_bRun);

   }


   void plspotify::load_image()
   {

      synchronous_lock sl2(papp->mediaplaylist()->m_pplaylistdocCurrent->m_spplayer->mutex());

      synchronous_lock synchronouslock(m_pmutex);

      sp_album * a = sp_track_album(currenttrack);

      if(a == NULL)
         return;

      const unsigned char * imageid = sp_album_cover(a,SP_IMAGE_SIZE_LARGE);

      if(imageid == NULL)
         return;

      sp_image * pimage = sp_image = create_image({m_session, imageid});

      if(pimage->is_null())
         return;

      sp_image_add_load_callback(pimage,&mediaplaylist_plspotify_image_loaded_cb, this);

      synchronouslock.unlock();

      defer_load_image(pimage);


   }


   void plspotify::defer_load_image(sp_image * pimage)
   {

      synchronous_lock sl2(papp->mediaplaylist()->m_pplaylistdocCurrent->m_spplayer->mutex());

      synchronous_lock synchronouslock(m_pmutex);

      if(pimage->is_null())
      {

         return;

      }

      if(!sp_image_is_loaded(pimage))
      {

         return;

      }

      size_t s;

      const void * p= sp_image_data(pimage,&s);

      if(p != NULL)
      {



         ::memory_file m(get_app(),(void *)p,s);

         m_pimagea->set_size(1);

         m_pimagea[0]->create(this);

         if(!m_pimagea[0]->load_image(&m))
         {

            informationf("image_loaded_failed");

         }

         //->multimedia_get_attribute(id_AlbumArt,v);

         ::papaya::array::copy(papp->mediaplaylist()->m_pplaylistdocCurrent->m_spplayer->m_pimageaAlbum,m_pimagea);




      }

      sp_image_erase_load_callback(pimage,&mediaplaylist_plspotify_image_loaded_cb,this);

      sp_image_release(pimage);

   }


   void plspotify::on_update_playlist_set(sp_playlistcontainer * pc)
   {

      synchronous_lock synchronouslock(m_pmutex);

      m_pla.erase_all();

      int num_playlists = sp_playlistcontainer_num_playlists(pc);

      for(int i = 0; i < num_playlists; ++i)
      {
         sp_playlist *pl = sp_playlistcontainer_playlist(pc,i);

         sp_playlist_add_ref(pl);

         sp_playlist_add_callbacks(pl,&pl_callbacks,m_session);

         plspotify::pl * p = __alloc(aaa_primitive_new plspotify::pl(this));

         p->m_pl = pl;

         p->m_iIndex = i;

         m_pla.add(p);

      }

      synchronouslock.unlock();

      papp->mediaplaylist()->m_pplaylistlistview->_001OnUpdateItemCount();

   }


   ::memory_file & plspotify::GetMemoryFile()
   {
      return m_memfile;
   }


   void plspotify::logged_in(bool bLogInOn)
   {

      if(!bLogInOn)
      {

         m_bRun = false;

         return;

      }

   }

   void plspotify::container_loaded(sp_playlistcontainer * pc)
   {

      synchronous_lock synchronouslock(m_pmutex);

      on_update_playlist_set(pc);

      ::fork(get_app(),[this]()
      {

         if(papp->mediaplaylist()->m_bPendingCheckForRestartOnWasPlaying)
         {

            papp->mediaplaylist()->m_bPendingCheckForRestartOnWasPlaying = false;

            papp->mediaplaylist()->GetCurrentPlaylist(false)->defer_restart_on_was_playing();

         }

      });

   }

   plspotify::pl::pl(::particle * pparticle):
      object(pparticle)
   {

   }

   plspotify::pl::~pl()
   {
      synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex);

      sp_playlist_release(m_pl);

   }


   string plspotify::pl::get_name()
   {

      if(m_strName.has_char() && (m_durationLastUpdate.elapsed() < 30 * 1000))
      {

         return m_strName;

      }

      defer_update();

      if(m_strName.has_char())
      {

         return m_strName;

      }

      return "";


   }


   void plspotify::pl::defer_update()
   {

      synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex);

      m_durationLastUpdate= ::duration::now();

      m_strName = sp_playlist_name(m_pl);

   }

   void plspotify::pl::defer_update_tracks()
   {

      synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex);

      if(m_tra.get_count() == 0 && m_durationLastUpdateTracks.elapsed()  < 5 * 1000)
         return;
      else if(m_tra.get_count() > 0 && m_durationLastUpdateTracks.elapsed() < 30 * 1000)
         return;

      m_durationLastUpdateTracks= ::duration::now();

      int c = sp_playlist_num_tracks(m_pl);

      m_tra.set_size(c);

      for(::collection::index i = 0; i < c; i++)
      {

         tr * ptr = __alloc(aaa_primitive_new tr(this));

         m_tra[i] = ptr;

         ptr->m_tr = sp_playlist_track(m_pl,i);

         sp_track_add_ref(ptr->m_tr);

         ptr->m_iIndex = i;

         ptr->m_pl = this;

      }

   }


   void plspotify::pl::get_stra(string_array & stra)
   {

      defer_update_tracks();

      for(auto & tr : m_tra)
      {

         stra.add(tr->get_id());

      }

   }

   plspotify::tr::tr(::particle * pparticle):
      object(pparticle)
   {

   }

   plspotify::tr::~tr()
   {
      sp_track_release(m_tr);
   }


   string plspotify::tr::get_name()
   {

      if(m_strName.has_char() && (m_durationLastUpdate.elapsed() < 60 * 1000))
      {

         return m_strName;

      }

      defer_update();

      if(m_strName.has_char())
      {

         return m_strName;

      }

      return "";


   }



   string plspotify::tr::get_id()
   {

      return "spotify_track:" + as_string(m_pl->m_iIndex) + ":" + as_string(m_iIndex);

   }


   string plspotify::tr::get_artist()
   {

      if(m_strArtist.has_char() && (m_durationLastUpdate.elapsed() < 60 * 1000))
      {

         return m_strArtist;

      }

      defer_update();

      if(m_strArtist.has_char())
      {

         return m_strArtist;

      }

      return "";


   }



   string plspotify::tr::get_album()
   {

      if(m_strAlbum.has_char() && (m_durationLastUpdate.elapsed() < 60 * 1000))
      {

         return m_strAlbum;

      }

      defer_update();

      if(m_strAlbum.has_char())
      {

         return m_strAlbum;

      }

      return "";


   }

   void plspotify::tr::defer_update()
   {

      synchronous_lock synchronouslock(&papp->mediaplaylist()->spotify()->m_pmutex);

      m_durationLastUpdate= ::duration::now();

      m_strName = sp_track_name(m_tr);

      m_straArtist.erase_all();

      int cA = sp_track_num_artists(m_tr);

      for(::collection::index i = 0; i < cA; i++)
      {

         sp_artist * a = sp_track_artist(m_tr,i);

         m_straArtist.add(sp_artist_name(a));

      }

      m_strArtist = m_straArtist.implode(",");

      sp_album * a = sp_track_album(m_tr);

      if(a != NULL)
      {

         m_strAlbum = sp_album_name(a);

      }



   }

} // namespace mediaplaylist




void SP_CALLCONV mediaplaylist_plspotify_image_loaded_cb(sp_image * pimage,void *userdata)
{

   ::mediaplaylist::plspotify * pplspotify = (::mediaplaylist::plspotify *) userdata;

   pplspotify->defer_load_image(pimage);

}
