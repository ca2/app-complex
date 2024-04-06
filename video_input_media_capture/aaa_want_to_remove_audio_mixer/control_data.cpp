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


      i32 control_data::GetObjectType()
      {

         return DataTypeBase;

      }


      i32 control_data::get_type()
      {

         return m_iType;

      }


   } // namespace audio_mixer


} // namespace multimedia



















