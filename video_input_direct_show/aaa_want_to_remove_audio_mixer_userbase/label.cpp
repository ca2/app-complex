#include "framework.h"



namespace multimedia
{


   namespace audio_mixer_user_base
   {



      label::label()
      {

      }


      label::~label()
      {

      }


      void label::SetText(const ::string & lpcsz)
      {

         set_window_text(lpcsz);

      }


      bool label::create_window(::user::interaction * puiParent, const ::atom & atom)
      {
         
         ::user::system createstruct(WS_EX_TRANSPARENT, nullptr, nullptr, WS_CHILD | WS_VISIBLE);
         
         if(!create_window_ex(createstruct, puiParent, atom))
         {
            return false;
         }

         return true;

      }


   } // namespace audio_mixer_user_base


} // namespace multimedia





