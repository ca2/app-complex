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

         for(int i = 0; i < this->get_size(); i++)
         {

            if((pinteraction = this->element_at(i)) != nullptr)
            {

               delete pinteraction;

            }

         }

      }

      bool control::CreateWindows(::pointer<::user::interaction>pParent, int iStyle)
      {
         __UNREFERENCED_PARAMETER(pParent);
         __UNREFERENCED_PARAMETER(iStyle);
         return true;
      }



      bool control::CreateWindowsVolumeV001(::pointer<::user::interaction>pParent, unsigned int nStartID, unsigned int * nNextID)
      {

         return false;

      }


      bool control::_001CreateMuteControl(::pointer<::user::interaction>pParent, unsigned int nStartID, unsigned int * nNextID)
      {

         return false;

      }

      void control::Prepare()
      {

      }


      ::pointer<::audio_mixer::user_control>control::GetControl(int iType)
      {

         ::pointer<::audio_mixer::user_control>pusercontrol;

         for(int i = 0; i < this->get_size(); i++)
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


      ::pointer<::audio_mixer::user_control>control::GetControlByIndex(::collection::index iIndex)
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
//         int                             nRange;
//         unsigned int                            cChannels;
//         unsigned int                            cMultipleItems;
         //       unsigned int                            cChannels;
         //     unsigned int                            cMultipleItems;
         //    unsigned int                            u;
         //    unsigned int                            uIndex;
         //    unsigned int                            v;
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
         //    pmaci_fader = (PMACONTROLINSTANCE_FADER)(unsigned int)GetWindowLong(oswindow, DWL_USER);
         //    pmaci       = pmaci_fader->pmaci;
         //    pmxl        = pmaci->pmxl;
         //    pmxctrl     = pmaci->pmxctrl;
         //    pmxcd_u     = &pmaci_fader->pmxcd_u[0];
         //    nRange      = pmaci_fader->nRange;
      }


      ::pointer<::audio_mixer::control_data>control::GetWindowData(int iType)
      {

         ::pointer<::audio_mixer::user_control>pusercontrol;

         for(int i = 0; i < this->get_size(); i++)
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


      ::pointer<::audio_mixer::user_control>ontrol::GetControlByDlgCtrlID(unsigned int nID)
      {

         ::pointer<::audio_mixer::user_control>pusercontrol;

         for(int i = 0; i < this->get_size(); i++)
         {

            pusercontrol = this->element_at(i);

            if (pusercontrol == nullptr)
            {

               continue;

            }

            if((unsigned int) pusercontrol->GetDlgCtrlId() == nID)
            {

               return pusercontrol;

            }

         }

         return nullptr;

      }


      ::pointer<::audio_mixer::control_data>control::GetWindowDataByDlgCtrlID(unsigned int nID)
      {

         ::pointer<::audio_mixer::user_control>pusercontrol;

         for(int i = 0; i < this->get_size(); i++)
         {

            pusercontrol = this->element_at(i);

            if(pusercontrol == nullptr)
               continue;

            if((unsigned int) pusercontrol->GetDlgCtrlId() == nID)
            {

               return pusercontrol->get_data();

            }

         }

         return nullptr;

      }


      void control::OnVHScroll(unsigned int nSBCode, unsigned int nPos, ::pointer<::user::interaction>pScrollBar)
      {

      }


      bool control::OnCommand(WPARAM wParam, LPARAM lParam)
      {

         return false;

      }



      bool control::control_type(e_control econtrol) const
      {

         __UNREFERENCED_PARAMETER(econtrol);

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




