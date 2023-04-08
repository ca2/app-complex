#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class CLASS_DECL_APP_CORE_AUDIO callback :
         virtual public ::object
      {
      public:


         callback();
         virtual ~callback();


         virtual ::audio_mixer_user::level_control * allocate_level_control();
         virtual ::audio_mixer_user::toggle_control * allocate_toggle_control();
         virtual ::audio_mixer_user::label * allocate_label();

      };


   } // namespace audio_mixer


} // namespace multimedia







