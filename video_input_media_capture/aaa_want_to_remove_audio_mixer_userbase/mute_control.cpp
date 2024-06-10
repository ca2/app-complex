#include "framework.h"



namespace multimedia
{


   namespace audio_mixer_user_base
   {


      mute_control::mute_control()
      {

         set_button_style(::user::button::style_push);

      }

      mute_control::~mute_control()
      {
      }

//      enum_check mute_control::get_check()
//      {
//         return ::user::button::get_check();
//      }


      void mute_control::set_check(::enum_check echeck, const ::action_context & context)
      {

         ::user::button::set_check(echeck, context);

      }


      void mute_control::set_label(const ::string & lpcsz)
      {
         set_window_text(lpcsz);
      }

      bool mute_control::create_window(::user::interaction * puiParent, const ::atom & atom)
      {

         return ::user::button::create_window(
            nullptr,
            "",
            BS_AUTOCHECKBOX |
            WS_CHILD |
            WS_VISIBLE,
            puiParent,
            atom) != false;
      }



   } // namespace audio_mixer_user_base


} // namespace multimedia




