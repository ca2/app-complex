#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class department;


      class CLASS_DECL_APP_CORE_AUDIO thread :
         public ::thread,
         public ::database::client
      {
      public:


         


         enum e_message
         {
            MessageMixerThread = WM_USER + 113,
         };

         bool                                m_bPendingShowCommand;

         ::pointer<::audio_mixer::department>m_psection;


         thread();
         virtual ~thread();


         void install_message_routing(::channel * pchannel) override;

         virtual void init_thread() override;
         virtual void term_thread() override;

         virtual void pre_translate_message(::message::message * pmessage) override;


         DECLARE_MESSAGE_HANDLER(OnMixerMessage);
         DECLARE_MESSAGE_HANDLER(OnVmsmException);
         DECLARE_MESSAGE_HANDLER(OnUserMessage);


      };


   } // namespace audio_mixer


} // namespace multimedia





