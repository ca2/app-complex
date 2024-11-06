#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      control_data::control_data()
      {

      }


      control_data::~control_data()
      {

      }


      int control_data::GetObjectType()
      {

         return DataTypeBase;

      }


      int control_data::get_type()
      {

         return m_iType;

      }


   } // namespace audio_mixer


} // namespace multimedia



















