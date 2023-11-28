#include "framework.h"



namespace  mediamanager
{


   album_build_thread::album_build_thread()
   {

      m_puserinteraction = nullptr;

   }


   album_build_thread::~album_build_thread()
   {

   }


   void album_build_thread::init_thread()
   {

      m_puserinteraction = __new< album_build_window >();

      m_puserinteraction->create();

      return true;

   }


   void album_build_thread::term_thread()
   {

      thread::term_thread();

   }


   void album_build_thread::Initialize(::pointer<::mediamanager::album_build>albumbuild)
   {

      ASSERT(m_puserinteraction != nullptr);

      m_puserinteraction->Initialize(palbumbuild);

      m_palbumbuild = palbumbuild;

   }


}

