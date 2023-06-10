#include "framework.h"



namespace multimedia
{

   namespace audio_mixer
   {


      namespace user
      {


         level_control::level_control()
         {

            __construct(m_pdata, __new(::audio_mixer::control_data_volume));

         }


         level_control::~level_control()
         {

         }


         void level_control::SetOrientation(enum_orientation eorientation)
         {

            UNREFERENCED_PARAMETER(eorientation);

            throw ::interface_only();

         }


         void level_control::SetRange(i32 iMin, i32 iMax)
         {

            UNREFERENCED_PARAMETER(iMin);
            UNREFERENCED_PARAMETER(iMax);

            throw ::interface_only();

         }


         void level_control::SetLineSize(i32 iSize)
         {

            UNREFERENCED_PARAMETER(iSize);

            throw ::interface_only();

         }


         void level_control::SetPageSize(i32 iPage)
         {

            UNREFERENCED_PARAMETER(iPage);

            throw ::interface_only();

         }


         i32 level_control::GetPos() const
         {

            throw ::interface_only();

         }


         void level_control::SetPos(i32 iPos)
         {

            UNREFERENCED_PARAMETER(iPos);

            throw ::interface_only();

         }


         ::audio_mixer::control_data_volume * level_control::get_data_volume()
         {

            return m_pdata.cast < ::audio_mixer::control_data_volume >();

         }


      } // namespace user


   } // namespace audio_mixer


} // namespace multimedia











