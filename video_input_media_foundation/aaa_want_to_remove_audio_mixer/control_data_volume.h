#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class CLASS_DECL_APP_CORE_AUDIO control_data_volume :
         virtual public ::audio_mixer::control_data
      {
      public:


         i32                             nRange;
         i32                             nPageInc;


         control_data_volume();
         virtual ~control_data_volume();

         virtual i32 GetObjectType();

      };


   } // namespace audio_mixer


} // namespace multimedia

