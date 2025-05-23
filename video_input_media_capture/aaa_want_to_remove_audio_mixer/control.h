#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class source;


      class CLASS_DECL_APP_CORE_AUDIO control :
         public ::audio_mixer_user::control_ptr_array
      {
      public:


         
         enum Styles
         {
            StyleV001 = 1
         };


         ::audio_mixer::source                * m_pmixersource;


         control();
         virtual ~control();


         using ::audio_mixer_user::control_ptr_array::add;
         virtual iptr add(::audio_mixer::user_control * pinteraction);

         virtual bool control_type(e_control econtrol) const;
         virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
         virtual ::pointer<::audio_mixer::control_data>GetWindowDataByDlgCtrlID(unsigned int nID);
         virtual ::pointer<::audio_mixer::user_control>GetControlByDlgCtrlID(unsigned int nID);
         virtual void OnVHScroll(unsigned int nSBCode, unsigned int nPos, ::pointer<::user::interaction>pScrollBar);
         virtual ::pointer<::audio_mixer::control_data>GetWindowData(int iType);
         virtual void OnMixerControlChange();
         virtual ::pointer<::audio_mixer::user_control>GetControl(int iType);
         virtual ::pointer<::audio_mixer::user_control>GetControlByIndex(::collection::index iIndex);
         virtual void Prepare();
         virtual bool CreateWindowsVolumeV001(::pointer<::user::interaction>pParent, unsigned int nStartID, unsigned int * nNextID);

         virtual bool _001CreateMuteControl(::pointer<::user::interaction>pParent, unsigned int nStartID, unsigned int * nNextID);

         virtual bool CreateWindows(::pointer<::user::interaction>pParent, int iStyle);


      };



      class control_array :
         public pointer_array < control >
      {
      public:

         control_array()
         {


         }
      };

      //typedef CLASS_DECL_APP_CORE_AUDIO pointer_array < control > control_array;


   } // namespace audio_mixer


} // namespace multimedia





