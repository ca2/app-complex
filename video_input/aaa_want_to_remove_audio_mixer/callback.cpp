#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      callback::callback()
      {

      }


      callback::~callback()
      {

      }


      ::audio_mixer::user::level_control * callback::allocate_level_control()
      {

         return nullptr;

      }


      ::audio_mixer::user::toggle_control * callback::allocate_toggle_control()
      {

         return nullptr;

      }


      ::audio_mixer::user::label * callback::allocate_label()
      {

         return nullptr;

      }


   } // namespace audio_mixer


} // namespace multimedia





