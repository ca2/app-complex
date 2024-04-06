#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class CLASS_DECL_APP_CORE_AUDIO control_data_switch :
         virtual public ::audio_mixer::control_data
      {
      public:


         control_data_switch();
         virtual ~control_data_switch();


         virtual i32 GetObjectType();


      };


   } // namespace audio_mixer


} // namespace multimedia



