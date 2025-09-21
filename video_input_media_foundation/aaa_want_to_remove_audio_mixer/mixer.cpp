#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      audio_mixer::audio_mixer()
      {

      }


      audio_mixer::~audio_mixer()
      {


      }


      void audio_mixer::initialize(::particle * pparticle)
      {

         auto estatus = øconstruct(m_pdevice);

         if (!estatus)
         {

            throw ::exception(::exception("audio mixer device initialization exception"));

            return estatus;

         }

         return ::success;

      }


      void     audio_mixer::set_new_device(unsigned int uiMixerId)
      {

         return error_failed;

      }


      bool audio_mixer::OnCommand(::user::message * pusermessage)
      {

         if(m_pdevice != nullptr && m_pdevice->OnCommand(pusermessage))
            return true;

         return false;

      }


      ::audio_mixer::callback * audio_mixer::get_callback()
      {

         return m_pcallback;

      }


      void audio_mixer::set_callback(::audio_mixer::callback * pcallback)
      {

         m_pcallback = pcallback;

      }


   } // namespace audio_mixer


} // namespace multimedia





