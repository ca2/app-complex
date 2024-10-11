#include "framework.h"

#include "aura/update.h"
#include "acme/constant/id.h"


namespace multimedia
{


   namespace audio_mixer_user_base
   {


      control_data::control_data()
      {

      }


      control_data::~control_data()
      {

      }


      void control_data::initialize_audio_mixer_userbase_control(control_impact * pimpact)
      {

         auto estatus = ::object::initialize(pimpact);

         if (!estatus)
         {

            return estatus;

         }

         if(m_pmixer == nullptr)
         {
            
            auto estatus = __refer(m_pmixer, papp->audiomixer());

            if (!estatus)
            {

               return estatus;

            }

         }

         if (m_pmixer == nullptr)
         {

            return false;

         }

         m_pmixer->set_callback(this);

         return ::success;

      }


      void     control_data::set_new_device(u32 uiMixerID)
      {

         void     mmrc;

         ::audio_mixer::audio_mixer * pmixer = get_mixer();

         if(0 != (mmrc = pmixer->set_new_device(uiMixerID)))
         {
            output_error_message("Could not open audio_mixer device!");
            return mmrc;
         }

         //m_pdestination = nullptr;

         m_pmixer->m_pdevice->initialize_capabilities();

         return mmrc;

      }


      void     control_data::set_new_destination(::audio_mixer::e_destination edestination)
      {

         void     mmrc;

         if(m_pdestination != nullptr)
         {

            mmrc = set_new_device(m_pmixer->m_pdevice->m_uiMixerID);

            // Reset All Contents
            if(mmrc != 0)
            {
               return mmrc;
            }

            //m_pdestination = nullptr;

         }

         auto pdestination = m_pmixer->m_pdevice->get_destination(edestination);

         if(!pdestination)
         {

            return mmrc;

         }

         m_pdestination = pdestination;

         m_pdestination->initialize_source_info();

         m_pimpact->call_subject(id_new_destination);

         return mmrc;
      }


      ::audio_mixer_user::level_control * control_data::allocate_level_control()
      {

         auto pinteraction  = __allocate ::audio_mixer_user_base::slider();

         return pinteraction;

      }


      ::audio_mixer_user::toggle_control * control_data::allocate_toggle_control()
      {

         auto pinteraction  = __allocate ::audio_mixer_user_base::mute_control();

         return pinteraction;

      }


      ::audio_mixer_user::label * control_data::allocate_label()
      {

         auto pinteraction  = __allocate ::audio_mixer_user_base::label();

         return pinteraction;

      }


      ::audio_mixer::audio_mixer * control_data::get_mixer()
      {
         return m_pmixer;
      }

      ::audio_mixer::destination * control_data::get_destination()
      {
         return m_pdestination;
      }


   } // namespace audio_mixer_user_base


} // namespace multimedia




