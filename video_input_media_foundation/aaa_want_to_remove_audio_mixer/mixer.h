#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class device;
      class callback;


      class CLASS_DECL_APP_CORE_AUDIO audio_mixer :
         virtual public ::object
      {
      public:


         ::pointer<::audio_mixer::device>       m_pdevice;
         ::pointer<::audio_mixer::callback>     m_pcallback;


      protected:


         audio_mixer();
         virtual ~audio_mixer();


      public:

         
         virtual void initialize(::particle * pparticle) override;


         virtual ::audio_mixer::callback * get_callback();
         virtual void set_callback(::audio_mixer::callback * pcallback);


         virtual void     set_new_device(unsigned int uiMixerId);


         virtual bool OnCommand(::user::message * pusermessage);


      };


   } // namespace audio_mixer


} // namespace multimedia





