#pragma once



namespace  mediamanager
{


   class album_build;
   class album_build_window;


   class CLASS_DECL_APP_CORE_AUDIO album_build_thread :
      public ::thread
   {
   public:

     
      album_build_window  *                  m_puserinteraction;
      ::pointer<::mediamanager::album_build>       m_palbumbuild;


      album_build_thread();

      void Initialize(::pointer<::mediamanager::album_build>palbumbuild);

      virtual void init_thread() override;
      virtual void term_thread() override;

      virtual ~album_build_thread();

   };


} // namespace mediamanager


