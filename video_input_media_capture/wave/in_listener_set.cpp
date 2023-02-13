#include "framework.h"



namespace wave
{


   in_listener_set::in_listener_set()
   {

   }


   in_listener_set::~in_listener_set()
   {

   }


   void in_listener_set::in_data_proc(in *pwavein, u32 dwSampleTime, int iBuffer)
   {

      for(i32 i = 0; i < this->get_size(); i++)
      {

         element_at(i)->in_data_proc(pwavein, dwSampleTime, iBuffer);

      }

   }


} // namespace wave



