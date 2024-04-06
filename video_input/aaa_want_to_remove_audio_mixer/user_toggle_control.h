#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class control_data_switch;


      namespace user
      {


         class CLASS_DECL_APP_CORE_AUDIO toggle_control :
            virtual public control
         {
         public:


            toggle_control();
            virtual ~toggle_control();

//            virtual void initialize(::particle * pparticle) override;

            virtual void _001SetCheck(::enum_check echeck, const ::action_context & action_context) = 0;
            virtual void set_label(const ::string & lpcszLabel) = 0;

            virtual ::pointer<::audio_mixer::control_data_switch>get_data_switch();


         };


      } // namespace user


   } // namespace audio_mixer


} // namespace multimedia


