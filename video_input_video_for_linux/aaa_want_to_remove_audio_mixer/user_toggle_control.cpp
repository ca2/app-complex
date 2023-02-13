#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      namespace user
      {


         toggle_control::toggle_control()
         {

            __construct(m_pdata, __new(::audio_mixer::control_data_switch));

         }


         toggle_control::~toggle_control()
         {

         }

         //virtual void initialize(::particle * pparticle) override;


         ::pointer<::audio_mixer::control_data_switch>toggle_control::get_data_switch()
         {

            return  m_pdata;

         }


      } // namespace user


   } // namespace audio_mixer


} // namespace multimedia











