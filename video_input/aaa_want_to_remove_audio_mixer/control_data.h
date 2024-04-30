#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class CLASS_DECL_APP_CORE_AUDIO control_data :
         virtual public ::object
      {
      public:


         enum
         {
            TypeDefault = 1,
            TypeStereoBalance = 2,
            TypeStereoVolume = 3,
            TypeStereoBalanceLabel = 4,
            TypeStereoVolumeLabel = 5,
            TypeUniformMute = 6
         };


         enum
         {
            DataTypeBase = 0,
            DataTypeVolume = 1,
            DataTypeMute = 2
         };


         i32                  m_iType;
         u32                  m_uiMixerID;
         u32                  m_uiLineID;
         u32                  m_uiControlID;
         ::raw::index                m_iIndex;


         control_data();
         virtual ~control_data();


         virtual i32 GetObjectType();
         virtual i32 get_type();



      };


   } // namespace audio_mixer


} // namespace multimedia

