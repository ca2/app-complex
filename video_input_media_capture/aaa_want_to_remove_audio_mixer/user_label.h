#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      namespace user
      {


         class CLASS_DECL_APP_CORE_AUDIO label :
            virtual public control
         {
         public:


            label();
            virtual ~label();


            virtual void SetText(const ::string & lpcszText) = 0;


         };


      } // namespace user


   } // namespace audio_mixer


} // namespace multimedia





