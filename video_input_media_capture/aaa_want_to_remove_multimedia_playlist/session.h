#pragma once


namespace multimedia_playlist
{


   class CLASS_DECL_APP_CORE_AUDIO session :
      virtual public ::thread
   {
   public:


//      class CLASS_DECL_APP_CORE_AUDIO thread :
//         virtual public ::thread
//
//      {
//      public:
//
//         session *      m_psession;
//
//
//         thread(::particle * pparticle);
//         virtual ~thread();
//
//
//         virtual void     run() override;
//
//
//      };


      int                                       m_iDebug1;
      bool                                      m_bGettingCredentials;

      ::pointer < ::mutex >                                     m_pmutex2;

      pointer_array < playlist >                             m_plaDeferUpdate;
      pointer_array < playlist >                             m_plaDeferUpdateTracks;
      pointer_array < track >                                m_traDeferUpdate;

      manual_reset_happening                        m_evAudioFormat;

      ::memory_file                             m_memfile;

      ::pointer<::multimedia_playlist::track>         m_ptrackCurrent;

      ::pointer<::multimedia_playlist::track>         m_ptrackDiba;

      array < ::image::image_pointer >                m_pimagea;

      string                                    m_strListName;

      pointer_array < ::multimedia_playlist::playlist >      m_pla;

      manual_reset_happening                        m_ev;

      string                                    m_strUserAgent;

      ::pointer < ::mutex >                                     m_pmutexFile;


      ::pointer<::audio_decode::decoder>  m_pdecoderHold;


      session();
      virtual ~session();


      huge_integer increment_reference_count() override
      {

         return ::thread::increment_reference_count();

      }


      huge_integer decrement_reference_count() override
      {

         return ::thread::decrement_reference_count();

      }


      huge_integer release() override
      {

         return ::thread::release();

      }

      virtual void     run() override;


      virtual void defer_sleep();

      virtual void on_update_playlist_set();


      ::memory_file & GetMemoryFile();

      void logged_in(bool bLogInOk);

      void container_loaded();

      virtual ::multimedia_playlist::playlist * open_playlist(::payload payloadFile);
      virtual ::multimedia_playlist::playlist * open_search(::payload payloadFile);
      virtual void run_spotify_step();

      virtual void load_image();

      virtual void on_load_image(::image::image *pimage);

      virtual void on_play(::multimedia_playlist::track * ptrack);

      virtual void update();


//      virtual void start_new_thread();

      virtual ::pointer<::multimedia_playlist::playlist>new_playlist();
      virtual ::pointer<::multimedia_playlist::track>new_track();


   };


} // namespace multimedia_playlist



