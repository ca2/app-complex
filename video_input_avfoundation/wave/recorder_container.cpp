#include "framework.h"



namespace wave
{


   recorder_container::recorder_container()
   {

   }


   recorder_container::~recorder_container()
   {

   }


   ::pointer<::wave::recorder>recorder_container::get_recorder()
   {

      return m_pwaverecorder;

   }


   bool recorder_container::initialize_recorder()
   {

      m_pwaverecorder = memory_new  ::wave::recorder ();

      if(m_pwaverecorder == nullptr)
         return false;

      if(!m_pwaverecorder->begin_synch())
         return false;

      return true;

   }

} // namespace wave



