#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      namespace user
      {


         class CLASS_DECL_APP_CORE_AUDIO level_control :
            virtual public control
         {
         public:


            enum enum_orientation
            {
               e_orientation_vertical,
               e_orientation_horizontal,
            };


            level_control();
            virtual ~level_control();


            virtual void SetPos(int iPos);
            virtual int GetPos() const;


            virtual void SetOrientation(enum_orientation eorientation);
            virtual void SetRange(int iMin, int iMax);
            virtual void SetPageSize(int iPage);
            virtual void SetLineSize(int iSize);

            virtual ::audio_mixer::control_data_volume * get_data_volume();


         };


      } // namespace user


   } // namespace audio_mixer


} // namespace multimedia




