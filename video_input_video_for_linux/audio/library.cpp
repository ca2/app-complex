#include "framework.h"



namespace audio
{


   library::library()
   {
   }


   //void library::get_create_impact_id_list(::array < ::atom > & ida)
   //{
   //
   //   ida.add("impact_audio_control");

   //}


   //void library::on_create_impact(::user::impact_data * pimpactdata)
   //{

   //   if(pimpactdata->m_atom == "impact_audio_control")
   //   {
   //      ::pointer<::create>cc(e_create);
   //      cc->m_puserinteractionParent = pimpactdata->m_pplaceholder;
   //      papp->audiomixeruserbase()->Initialize();

   //      ::pointer<audio_mixer_user_base::document>pdocument = ::user::__document(cc);

   //      if(pdocument != nullptr)
   //      {
   //         if(pdocument != nullptr)
   //         {
   //            ::pointer<::user::impact>pimpact = pdocument->get_impact();
   //            if(pimpact != nullptr)
   //            {
   //               ::pointer<::simple_frame_window>pframe =  (pimpact->get_parent_frame());
   //               if(pframe != nullptr)
   //               {
   //                  pimpactdata->m_pdocument = pdocument;
   //                  //pframe->m_bblur_Background = true;
   //               }
   //            }
   //         }
   //      }
   //   }

   //}


} // namespace audio

#ifdef CUBE

extern "C"
::acme::library * audio_get_new_library(::particle * pparticle)
{

   return new ::audio::library(pparticle);

}

#else

extern "C"
::acme::library * audio_get_new_library()
{

   return new ::audio::library();

}

extern "C"
CLASS_DECL_EXPORT ::aqua::audio * get_new_audio()
{

   return new ::audio::audio();

}

#endif




