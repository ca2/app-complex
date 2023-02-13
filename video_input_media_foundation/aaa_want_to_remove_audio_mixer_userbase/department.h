#pragma once


namespace multimedia
{


   namespace audio_mixer_userbase
   {


      class CLASS_DECL_APP_CORE_AUDIO department :
         virtual public ::audio_mixer::department,
         virtual public ::user::interaction
      {
      public:


         atom                                                 m_atomPlaybackPane;
         string                                             m_strPlaybackTitle;
         string                                             m_strPlaybackIcon;


         atom                                                 m_atomRecordingPane;
         string                                             m_strRecordingTitle;
         string                                             m_strRecordingIcon;

         ::pointer<thread>                               m_pthread;
         ::pointer<::user::multiple_document_template>     m_pimpactsystem;


         department();
         virtual ~department();


         virtual void init1() override;
         virtual void init() override;

         virtual void term_instance() override;

         void install_message_routing(::channel * pchannel) override;
         ::pointer<::user::multiple_document_template>get_document_template();

         ::pointer<::user::multiple_document_template>CreateDocTemplate(::particle * pparticle);
         void DisplayAMixer();
         bool Initialize();
         static void SetMIXERVISUALCENTRAL(::pointer<department>pMIXERVISUALCENTRAL);

         DECLARE_MESSAGE_HANDLER(on_message_close);



      };


   } // namespace audio_mixer_userbase


} // namespace multimedia





