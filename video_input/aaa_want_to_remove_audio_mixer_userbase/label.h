#pragma once


namespace multimedia
{


   namespace audio_mixer_user_base
   {


      class CLASS_DECL_APP_CORE_AUDIO label : 
         virtual public ::simple_static,
         virtual public ::audio_mixer_user::label
      {
      public:


         label();
         virtual ~label();

         using ::simple_static::create_window;
         virtual bool create_window(::user::interaction * puiParent, const ::atom & atom) override;

         virtual void SetText(const ::string & pcsz) override;

      };


   } // namespace audio_mixer_user_base


} // namespace multimedia








