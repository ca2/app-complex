#pragma once


namespace multimedia
{


   namespace audio_mixer_user_base
   {


      class department;

      enum e_wparam
      {

         wparam_display_a_mixer,

      };



      class CLASS_DECL_APP_CORE_AUDIO thread :
         public ::thread
      {
      public:





         //department *         m_pdepartment;


         thread();
         virtual ~thread();


         //virtual department * get_section();
         virtual void initialize(::particle * pparticle) override;

         virtual void init_thread() override;
         virtual void term_thread() override;

         void install_message_routing(::channel * pchannel) override;

         DECLARE_MESSAGE_HANDLER(_001OnThreadMessage);


      };


   } // namespace audio_mixer_user_base


} // namespace multimedia






