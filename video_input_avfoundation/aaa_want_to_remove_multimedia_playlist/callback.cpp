#include "framework.h"


//
//
////::multimedia_playlist::session * spotify_session(void * p)
////{
////
////   return (::multimedia_playlist::session *) p;
////
////}
////
////
////::multimedia_playlist::session * session_session(sp_session * session)
////{
////
////   return spotify_session(sp_session_userdata(session));
////
////}
////
////
////
//void SP_CALLCONV mediaplaylist_plspotify_image_loaded_cb(sp_image * pimage,void *session_session);
////
//////static void SP_CALLCONV  try_jukebox_start(sp_session * sess);
////
////
/////**
////* Callback from libplspotify, telling us the rootlist is fully synchronized
////* We just print an informational message
////*
////* @param  pc            The playlist container handle
////* @param  session_session      The opaque pointer
////*/
////void SP_CALLCONV container_loaded(sp_playlistcontainer *pc,void *session_session)
////{
////
////   spotify_session(session_session)->container_loaded(pc);
////
////}
////
////
////
/////* ---------------------------  SESSION CALLBACKS  ------------------------- */
/////**
////* This callback is called when an attempt to login has succeeded or failed.
////*
////* @sa sp_session_callbacks#logged_in
////*/
////void SP_CALLCONV  logged_in(sp_session *sess,sp_error error)
////{
////
////   sp_playlistcontainer *pc = sp_session_playlistcontainer(sess);
////
////   if(SP_ERROR_OK != error)
////   {
////
////      fprintf(stderr,"jukebox: Login failed: %s\n", sp_error_message(error));
////
////      session_session(sess)->logged_in(false);
////
////   }
////   else
////   {
////
////      session_session(sess)->logged_in(true);
////
////      sp_playlistcontainer_add_callbacks(
////         pc,
////         &session_session(sess)->pc_callbacks,
////         session_session(sess));
////
////   }
////
////}
////
////
/////**
////* Called on various events to start playback if it hasn't been started already.
////*
////* The function simply starts playing the first track of the playlist.
////*/
//////static void SP_CALLCONV  try_jukebox_start(sp_session * sess)
//////{
//////   sp_track *t;
//////
//////   if(!session_session(sess)->jukeboxlist)
//////      return;
//////
//////   if(!sp_playlist_num_tracks(session_session(sess)->jukeboxlist)) {
//////      fprintf(stderr,"jukebox: No tracks in playlist. Waiting\n");
//////      return;
//////   }
//////
//////   if(sp_playlist_num_tracks(session_session(sess)->jukeboxlist) < session_session(sess)->track_index) {
//////      fprintf(stderr,"jukebox: No more tracks in playlist. Waiting\n");
//////      return;
//////   }
//////
//////   t = sp_playlist_track(session_session(sess)->jukeboxlist,session_session(sess)->track_index);
//////
//////   if(session_session(sess)->currenttrack && t != session_session(sess)->currenttrack) {
//////      /* Someone changed the current track */
//////      //audio_fifo_flush(&g_audiofifo);
//////      sp_session_player_unload(sess);
//////      session_session(sess)->currenttrack = nullptr;
//////   }
//////
//////   if(!t)
//////      return;
//////
//////   if(sp_track_error(t) != SP_ERROR_OK)
//////      return;
//////
//////   if(session_session(sess)->currenttrack == t)
//////      return;
//////
//////   session_session(sess)->playback_done = 0;
//////
//////   session_session(sess)->currenttrack = t;
//////
//////   printf("jukebox: Now playing \"%s\"...\n",sp_track_name(t));
//////   //fflush(stdout);
//////
//////   sp_session_player_load(sess,t);
//////   sp_session_player_play(sess,1);
//////}
//////
////
/////**
////* This callback is called from an internal libplspotify thread to ask us to
////* reiterate the main loop.
////*
////* We notify the main thread using a condition variable and a protected variable.
////*
////* @sa sp_session_callbacks#notify_main_thread
////*/
////void SP_CALLCONV  notify_main_thread(sp_session *sess)
////{
////   //   pthread_mutex_lock(&g_notify_mutex);
////   session_session(sess)->notify_do = 1;
////   session_session(sess)->m_ev.set_happening();
////   //pthread_cond_signal(&g_notify_cond);
////   //pthread_mutex_unlock(&g_notify_mutex);
////}
////
/////**
////* This callback is used from libplspotify whenever there is PCM data available.
////*
////* @sa sp_session_callbacks#music_delivery
////*/
////int SP_CALLCONV music_delivery(sp_session *sess,const sp_audioformat *format, const void *frames,int num_frames)
////{
////
////   int & start = session_session(sess)->playback_start;
////
////   try
////   {
////
////      synchronous_lock synchronouslock(&session_session(sess)->m_pmutexFile);
////
////      if(session_session(sess)->m_af.sample_rate == 0 && session_session(sess)->m_af.channels == 0 && start >= 32)
////      {
////
////         if(format->sample_rate > 0 && format->channels > 0)
////         {
////
////            session_session(sess)->m_af = *format;
////
////            session_session(sess)->m_evAudioFormat.set_happening();
////
////         }
////
////      }
////
////
////      if(session_session(sess)->playback_done)
////      {
////
////         return 0;
////
////      }
////
////      start++;
////
////      session_session(sess)->GetMemoryFile().write(frames,num_frames * 2 * session_session(sess)->m_af.channels);
////
////      return num_frames;
////
////   }
////   catch (const const ::exception & e)
////   {
////
////      session_session(sess)->playback_done = 1;
////      session_session(sess)->notify_do = 1;
////
////   }
////   catch(...)
////   {
////
////   }
////
////   return 0;
////
////}
////
////
/////**
////* This callback is used from libplspotify when the current track has ended
////*
////* @sa sp_session_callbacks#end_of_track
////*/
////void SP_CALLCONV  end_of_track(sp_session *sess)
////{
////   session_session(sess)->playback_done = 1;
////   session_session(sess)->notify_do = 1;
////}
////
////
/////**
////* Callback called when libplspotify has ___new metadata available
////*
////* Not used in this example (but available to be able to reuse the session.c file
////* for other examples.)
////*
////* @sa sp_session_callbacks#metadata_updated
////*/
////void SP_CALLCONV  metadata_updated(sp_session *sess)
////{
////   //   try_jukebox_start(sess);
////}
////
/////**
////* Notification that some other connection has started playing on this account.
////* Playback has been stopped.
////*
////* @sa sp_session_callbacks#play_token_lost
////*/
////void SP_CALLCONV  play_token_lost(sp_session *sess)
////{
////   ///audio_fifo_flush(&g_audiofifo);
////
////   if(session_session(sess)->currenttrack != nullptr) {
////      sp_session_player_unload(sess);
////      session_session(sess)->currenttrack = nullptr;
////   }
////}
/////* --------------------  PLAYLIST CONTAINER CALLBACKS  --------------------- */
/////**
////* Callback from libplspotify, telling us a playlist was added to the playlist container.
////*
////* We add our playlist callbacks to the newly added playlist.
////*
////* @param  pc            The playlist container handle
////* @param  pl            The playlist handle
////* @param  position      Index of the added playlist
////* @param  session_session      The opaque pointer
////*/
////void SP_CALLCONV  SP_CALLCONV  playlist_added(sp_playlistcontainer *pc,sp_playlist *pl,int position,void *session_session)
////{
////
////   sp_playlist_add_callbacks(pl,&spotify_session(session_session)->pl_callbacks,session_session);
////
////   //spotify_session(session_session)->container_loaded(pc);
////
////}
////
////
/////**
////* Callback from libplspotify, telling us a playlist was erased from the playlist container.
////*
////* This is the place to erase our playlist callbacks.
////*
////* @param  pc            The playlist container handle
////* @param  pl            The playlist handle
////* @param  position      Index of the erased playlist
////* @param  session_session      The opaque pointer
////*/
////void SP_CALLCONV  playlist_erased(sp_playlistcontainer *pc,sp_playlist *pl, int position,void *session_session)
////{
////
////   sp_playlist_erase_callbacks(pl,&spotify_session(session_session)->pl_callbacks,session_session);
////
////   //spotify_session(session_session)->container_loaded(pc);
////
////}
////
/////**
////* Callback from libplspotify. Something renamed the playlist.
////*
////* @param  pl            The playlist handle
////* @param  session_session      The opaque pointer
////*/
////void SP_CALLCONV playlist_renamed(sp_playlist *pl,void *session_session)
////{
////
////   //spotify_session(session_session)->container_loaded(pc);
////   //sp_playlistcontainer * pc
////}
////
/////**
////* Callback from libplspotify, telling us the rootlist is fully synchronized
////* We just print an informational message
////*
////* @param  pc            The playlist container handle
////* @param  session_session      The opaque pointer
////*/
//////static void SP_CALLCONV  container_loaded(sp_playlistcontainer *pc,void *session_session)
//////{
//////   fprintf(stderr,"jukebox: Rootlist synchronized (%d playlists)\n",
//////      sp_playlistcontainer_num_playlists(pc));
//////}
////
////
/////**
////* The playlist container callbacks
////*/
////
////
/////* --------------------------  PLAYLIST CALLBACKS  ------------------------- */
/////**
////* Callback from libplspotify, saying that a track has been added to a playlist.
////*
////* @param  pl          The playlist handle
////* @param  tracks      An array of track handles
////* @param  num_tracks  The number of tracks in the \c tracks array
////* @param  position    Where the tracks were inserted
////* @param  session_session    The opaque pointer
////*/
////void SP_CALLCONV tracks_added(sp_playlist *pl,sp_track * const *tracks, int num_tracks,int position,void *session_session)
////{
////   if(pl != spotify_session(session_session)->jukeboxlist)
////      return;
////
////   printf("jukebox: %d tracks were added\n",num_tracks);
////   //fflush(stdout);
////   //try_jukebox_start(spotify_session(session_session)->sp);
////
////
////   spotify_session(session_session)->on_tracks_added(pl, tracks, num_tracks, position);
////
////}
////
/////**
////* Callback from libplspotify, saying that a track has been added to a playlist.
////*
////* @param  pl          The playlist handle
////* @param  tracks      An array of track indices
////* @param  num_tracks  The number of tracks in the \c tracks array
////* @param  session_session    The opaque pointer
////*/
////void SP_CALLCONV tracks_erased(sp_playlist *pl,const int *tracks, int num_tracks,void *session_session)
////{
////
////   int k = 0;
////
////   if(pl != spotify_session(session_session)->jukeboxlist)
////      return;
////
////   spotify_session(session_session)->on_tracks_erased(pl, tracks, num_tracks);
////
////   //for(i = 0; i < num_tracks; ++i)
////   //   if(tracks[i] < spotify_session(session_session)->track_index)
////   //      ++k;
////
////   //spotify_session(session_session)->track_index -= k;
////
////   //printf("jukebox: %d tracks were erased\n",num_tracks);
////   //fflush(stdout);
////   //try_jukebox_start(spotify_session(session_session)->sp);
////}
////
/////**
////* Callback from libplspotify, telling when tracks have been moved around in a playlist.
////*
////* @param  pl            The playlist handle
////* @param  tracks        An array of track indices
////* @param  num_tracks    The number of tracks in the \c tracks array
////* @param  new_position  To where the tracks were moved
////* @param  session_session      The opaque pointer
////*/
////void SP_CALLCONV tracks_moved(sp_playlist *pl,const int *tracks, int num_tracks,int new_position,void *session_session)
////{
////   if(pl != spotify_session(session_session)->jukeboxlist)
////      return;
////
////   //printf("jukebox: %d tracks were moved around\n",num_tracks);
////   ////fflush(stdout);
////   //try_jukebox_start(spotify_session(session_session)->sp);
////
////
////
////}
////
/////**
////* A track has ended. Remove it from the playlist.
////*
////* Called from the main loop when the music_delivery() callback has set g_playback_done.
////*/
////void track_ended(sp_session * sess)
////{
////   int tracks = 0;
////   if(session_session(sess)->currenttrack) {
////      session_session(sess)->m_evAudioFormat.set_happening();
////      session_session(sess)->currenttrack = nullptr;
////      sp_session_player_unload(sess);
////      session_session(sess)->track_loaded = 0;
////      //if(session_session(sess)->erase_tracks) {
////      //   sp_playlist_erase_tracks(session_session(sess)->jukeboxlist,&tracks,1);
////      //}
////      //else {
////      //   ++session_session(sess)->track_index;
////      //   try_jukebox_start(sess);
////      //}
////   }
////
////   //if(session_session(sess)->currenttrack) {
////   //   session_session(sess)->currenttrack = nullptr;
////   //   sp_session_player_unload(sess);
////   //   if(session_session(sess)->erase_tracks) {
////   //      sp_playlist_erase_tracks(session_session(sess)->jukeboxlist,&tracks,1);
////   //   }
////   //   else {
////   //      ++session_session(sess)->track_index;
////   //      try_jukebox_start(sess);
////   //   }
////   //}
////}
////
////
///*void SP_CALLCONV mediaplaylist_session_image_loaded_cb(sp_image * pimage,void *session_session)
////{
////
////   ::multimedia_playlist::session * psession = (::multimedia_playlist::session *) session_session;
////
///*   psession->defer_load_image(pimage);
////
////}
////
////
////
////
////
////
////
