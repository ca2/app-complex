#pragma once

namespace  mediamanager
{

   class album_build;

   class album_build_window :
      virtual public ::user::interaction
   {
   public:
      ::pointer<::mediamanager::album_build>        m_palbumbuild;
      ::pointer<::user::interaction>    m_oswindowCallback;
      bool                 m_b1123;

      int                  m_iTransactionTrigger;
      int                  m_iFieldIndexTitle;
      int                  m_iFieldIndexArtist;
      int                  m_iFieldIndexFileName;

      int                  m_iPreBuildStep;

      album_build_window();
      virtual ~album_build_window();

      void stop_build();
      void Initialize(::pointer<::mediamanager::album_build>palbumbuild);
      ::pointer<::mediamanager::album_build>album_build();
      void start_build();

      bool create();

      virtual void _001OnTimer(::timer * ptimer);
   };

} // namespace mediamanager
