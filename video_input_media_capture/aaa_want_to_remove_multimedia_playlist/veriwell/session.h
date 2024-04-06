#pragma once


namespace multimedia_playlist
{

   namespace veriwell
   {

      class CLASS_DECL_APP_CORE_AUDIO session :
         virtual public ::multimedia_playlist::session
      {
      public:


         int                                                m_iDebug1;
         bool                                               m_bGettingCredentials;
         ::pointer < ::mutex >                                            m_pmutex2;
         //thread *                                         m_pthread;
         ::memory_file                                      m_memfile;
         pointer_array < ::image >                                m_imagea;
         string                                             m_strListName;
         pointer_array < ::multimedia_playlist::playlist >        m_pla;
         manual_reset_event                                 m_ev;
         ::pointer < ::mutex >                                            m_pmutexFile;


         ::pointer<::audio_decode::decoder>    m_pdecoderHold;


         session();
         virtual ~session();


         virtual void     run() override;


         virtual void on_update_playlist_set() override;


         ::memory_file & GetMemoryFile();

         void logged_in(bool bLogInOk);

         void container_loaded();


         virtual void run_spotify_step() override;

         virtual void load_image() override;

         virtual void on_load_image(::image * pimage) override;


         virtual ::multimedia_playlist::playlist * open_playlist(::payload payloadFile) override;
         virtual void update() override;

         virtual void on_play(::multimedia_playlist::track * ptrack) override;


//      virtual void start_new_thread();

         virtual ::pointer<::multimedia_playlist::playlist>new_playlist() override;
         virtual ::pointer<::multimedia_playlist::track>new_track() override;


      };

   } // namespace namespace veriwell

} // namespace multimedia_playlist













