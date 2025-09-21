#include "framework.h"



namespace multimedia
{

   namespace audio_mixer
   {


      namespace user
      {


         level_control::level_control()
         {

            øconstruct(m_pdata, øallocate ::audio_mixer::control_data_volume());

         }


         level_control::~level_control()
         {

         }


         void level_control::SetOrientation(enum_orientation eorientation)
         {

            __UNREFERENCED_PARAMETER(eorientation);

            throw ::interface_only();

         }


         void level_control::SetRange(int iMin, int iMax)
         {

            __UNREFERENCED_PARAMETER(iMin);
            __UNREFERENCED_PARAMETER(iMax);

            throw ::interface_only();

         }


         void level_control::SetLineSize(int iSize)
         {

            __UNREFERENCED_PARAMETER(iSize);

            throw ::interface_only();

         }


         void level_control::SetPageSize(int iPage)
         {

            __UNREFERENCED_PARAMETER(iPage);

            throw ::interface_only();

         }


         int level_control::GetPos() const
         {

            throw ::interface_only();

         }


         void level_control::SetPos(int iPos)
         {

            __UNREFERENCED_PARAMETER(iPos);

            throw ::interface_only();

         }


         ::audio_mixer::control_data_volume * level_control::get_data_volume()
         {

            return m_pdata.cast < ::audio_mixer::control_data_volume >();

         }


      } // namespace user


   } // namespace audio_mixer


} // namespace multimedia











