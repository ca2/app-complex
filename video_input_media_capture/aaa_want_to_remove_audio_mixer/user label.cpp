#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      namespace user
      {


         label::label()
         {

            __construct(m_pdata, ::place(new ::audio_mixer::control_data()));

         }


         label::~label()
         {

         }


      } // namespace user


   } // namespace audio_mixer


} // namespace multimedia









