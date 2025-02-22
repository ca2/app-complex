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


         int                  m_iType;
         unsigned int                  m_uiMixerID;
         unsigned int                  m_uiLineID;
         unsigned int                  m_uiControlID;
         ::collection::index                m_iIndex;


         control_data();
         virtual ~control_data();


         virtual int GetObjectType();
         virtual int get_type();



      };


   } // namespace audio_mixer


} // namespace multimedia

