#pragma once


namespace multimedia
{


   namespace audio_mixer_userbase
   {


      class control_impact;


      class CLASS_DECL_APP_CORE_AUDIO control_data :
         public ::audio_mixer::callback,
         virtual public ::object
      {
      public:


         ::pointer<::audio_mixer::audio_mixer>     m_pmixer;
         ::pointer<::audio_mixer::destination>     m_pdestination;
         ::pointer<control_impact>                               m_pimpact;


         control_data();
         virtual ~control_data();


         virtual void initialize_audio_mixer_userbase_control(control_impact * pimpact);


         void     set_new_destination(::audio_mixer::e_destination edestination);
         void     set_new_device(u32 uiMixerID);

         ::audio_mixer::destination * get_destination();
         ::audio_mixer::audio_mixer * get_mixer();

         ::audio_mixer::user::level_control * allocate_level_control();
         ::audio_mixer::user::toggle_control * allocate_toggle_control();
         ::audio_mixer::user::label * allocate_label();

      };


   } // namespace audio_mixer_userbase


} // namespace multimedia




