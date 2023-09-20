#include "framework.h"

//#include "aura/message.h"


namespace multimedia
{

   namespace audio_mixer_user_base
   {


      department::department()
      {

      }


      department::~department()
      {

      }


      void department::init1()
      {

         if(papp->is_session())
         {

            add_factory_item <document >();
            add_factory_item <main_impact >();
            add_factory_item <control_impact >();
            add_factory_item <frame_window >();

         }

         return true;

      }


      void department::init()
      {

         return ::success;

      }


      void department::term_instance()
      {

         m_pimpactsystem->close_all_documents(false);

         if(m_pimpactsystem.is_set())
         {

            m_pimpactsystem.release();

         }

      }


      void department::install_message_routing(::channel * pchannel)
      {

         ::user::interaction::install_message_routing(pchannel);

         MESSAGE_LINK(e_message_close, pchannel, this, &department::on_message_close);

      }


      void department::on_message_close(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);

         DestroyWindow();

      }


      ::pointer<::user::multiple_document_template>department::CreateDocTemplate(::particle * pparticle)
      {

         if(m_pimpactsystem == nullptr)
         {

            m_pimpactsystem = __new(::user::multiple_document_template(
                                  "audio_mixer_user_base/audio_mixer",
                                  ::type < document >(),
                                  ::type < frame_window >(),
                                  ::type < main_impact >()));

            papp->add_document_template(m_pimpactsystem);

         }

         return m_pimpactsystem;

      }


      bool department::Initialize()
      {

         if (m_pthread != nullptr)
         {

            return true;

         }

         __construct(m_pthread, __new(thread));

         if (m_pthread == nullptr)
         {

            return false;

         }

         m_atomPlaybackPane        = "mixeruibase::playback_pane";
         m_strPlaybackIcon       = "matter://audio_mixer/icon_playback_16.png";
         m_strPlaybackTitle      = "<string atom='mplite:mixer_playback_tab'>Playback</string>";

         m_atomRecordingPane       = "mixeruibase::recording_pane";
         m_strRecordingIcon      = "matter://audio_mixer/icon_recording_16.png";
         m_strRecordingTitle     = "<string atom='mplite:mixer_recording_tab'>Recording</string>";


         //CreateDocTemplate(this);

         if (get_document_template() == nullptr)
         {

            return false;

         }

         if (!m_pthread->begin_synch())
         {

            return false;

         }

         return true;

      }


      void department::DisplayAMixer()
      {

         m_pthread->post_message(::message_thread, wparam_display_a_mixer);

      }


      ::pointer<::user::multiple_document_template>department::get_document_template()
      {

         return m_pimpactsystem;

      }


   } // namespace audio_mixer_user_base


} // namespace multimedia




