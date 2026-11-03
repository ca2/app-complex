#pragma once


namespace multimedia
{


   namespace audio_mixer_user_base
   {


      class CLASS_DECL_APP_CORE_AUDIO mute_control :
         virtual public ::user::button,
         virtual public ::audio_mixer_user::toggle_control
      {
      public:


         mute_control();
         virtual ~mute_control();


         using ::user::button::create_window;
         virtual bool create_window(::user::interaction * puiParent, const ::atom & atom) override;

         //virtual ::enum_check get_check() override;
         virtual void set_check(::enum_check echeck, const ::action_context & action_context) override;
         virtual void set_label(const ::string & pcsz) override;



      };


   } // namespace audio_mixer_user_base


} // namespace multimedia





