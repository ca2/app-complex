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

      i32                  m_iTransactionTrigger;
      i32                  m_iFieldIndexTitle;
      i32                  m_iFieldIndexArtist;
      i32                  m_iFieldIndexFileName;

      i32                  m_iPreBuildStep;

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
