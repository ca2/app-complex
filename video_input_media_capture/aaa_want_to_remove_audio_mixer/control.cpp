#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      control::control()
      {

         m_pmixersource = nullptr;
      }


      control::~control()
      {

         ::audio_mixer::user_control * pinteraction;

         for(i32 i = 0; i < this->get_size(); i++)
         {

            if((pinteraction = this->element_at(i)) != nullptr)
            {

               delete pinteraction;

            }

         }

      }

      bool control::CreateWindows(::pointer<::user::interaction>pParent, i32 iStyle)
      {
         UNREFERENCED_PARAMETER(pParent);
         UNREFERENCED_PARAMETER(iStyle);
         return true;
      }



      bool control::CreateWindowsVolumeV001(::pointer<::user::interaction>pParent, u32 nStartID, u32 * nNextID)
      {

         return false;

      }


      bool control::_001CreateMuteControl(::pointer<::user::interaction>pParent, u32 nStartID, u32 * nNextID)
      {

         return false;

      }

      void control::Prepare()
      {

      }


      ::pointer<::audio_mixer::user_control>control::GetControl(i32 iType)
      {

         ::pointer<::audio_mixer::user_control>pusercontrol;

         for(i32 i = 0; i < this->get_size(); i++)
         {

            pusercontrol = this->element_at(i);

            if (pusercontrol == nullptr)
            {

               continue;

            }

            if(pusercontrol->get_data()->get_type() == iType)
            {

               return pusercontrol;

            }

         }

         return nullptr;

      }


      ::pointer<::audio_mixer::user_control>control::GetControlByIndex(::index iIndex)
      {

         return this->element_at(iIndex);

      }


      void control::OnMixerControlChange()
      {

         if(this->get_size() <= 0)
            return;
//         void                            mmrc;
         //   void                            mmrc;
         //    oswindow                            htxt;
         //    PMACONTROLINSTANCE_FADER        pmaci_fader;
         //    LPMACONTROLINSTANCE             pmaci;
         //    LPMIXERCONTROL                  pmxctrl;
//         i32                             nRange;
//         u32                            cChannels;
//         u32                            cMultipleItems;
         //       u32                            cChannels;
         //     u32                            cMultipleItems;
         //    u32                            u;
         //    u32                            uIndex;
         //    u32                            v;
         //    MIXERCONTROLDETAILS             mxcd;
         //   oswindow                            hsbFocus;
         //    oswindow                            hsb;


         //    hsbFocus = GetFocus();
         //    if (nullptr == hsbFocus)
         //    {
         //        hsbFocus = get_child_by_id(oswindow, IDD_MACONTROL_MULTICHANNEL_BASE);
         //    }
         //    else
         //    {
         //        uIndex = GetDlgCtrlId(hsbFocus);
         //        if (uIndex < IDD_MACONTROL_MULTICHANNEL_BASE)
         //        {
         //            hsbFocus = get_child_by_id(oswindow, IDD_MACONTROL_MULTICHANNEL_BASE);
         //        }
         //    }


         //
         //
         //
         //    pmaci_fader = (PMACONTROLINSTANCE_FADER)(u32)GetWindowLong(oswindow, DWL_USER);
         //    pmaci       = pmaci_fader->pmaci;
         //    pmxl        = pmaci->pmxl;
         //    pmxctrl     = pmaci->pmxctrl;
         //    pmxcd_u     = &pmaci_fader->pmxcd_u[0];
         //    nRange      = pmaci_fader->nRange;
      }


      ::pointer<::audio_mixer::control_data>control::GetWindowData(i32 iType)
      {

         ::pointer<::audio_mixer::user_control>pusercontrol;

         for(i32 i = 0; i < this->get_size(); i++)
         {

            pusercontrol = this->element_at(i);

            if (pusercontrol == nullptr)
            {

               continue;

            }

            if(pusercontrol->get_data()->get_type() == iType)
            {

               return pusercontrol->get_data();

            }

         }

         return nullptr;

      }


      ::pointer<::audio_mixer::user_control>ontrol::GetControlByDlgCtrlID(u32 nID)
      {

         ::pointer<::audio_mixer::user_control>pusercontrol;

         for(i32 i = 0; i < this->get_size(); i++)
         {

            pusercontrol = this->element_at(i);

            if (pusercontrol == nullptr)
            {

               continue;

            }

            if((u32) pusercontrol->GetDlgCtrlId() == nID)
            {

               return pusercontrol;

            }

         }

         return nullptr;

      }


      ::pointer<::audio_mixer::control_data>control::GetWindowDataByDlgCtrlID(u32 nID)
      {

         ::pointer<::audio_mixer::user_control>pusercontrol;

         for(i32 i = 0; i < this->get_size(); i++)
         {

            pusercontrol = this->element_at(i);

            if(pusercontrol == nullptr)
               continue;

            if((u32) pusercontrol->GetDlgCtrlId() == nID)
            {

               return pusercontrol->get_data();

            }

         }

         return nullptr;

      }


      void control::OnVHScroll(u32 nSBCode, u32 nPos, ::pointer<::user::interaction>pScrollBar)
      {

      }


      bool control::OnCommand(WPARAM wParam, LPARAM lParam)
      {

         return false;

      }



      bool control::control_type(e_control econtrol) const
      {

         UNREFERENCED_PARAMETER(econtrol);

         return false;

      }


      iptr control::add(::audio_mixer::user_control * pinteraction)
      {

         pinteraction->get_data()->m_iIndex = this->get_size();

         control_ptr_array::add(pinteraction);

         return get_upper_bound();

      }


   } // namespace audio_mixer


} // namespace multimedia




