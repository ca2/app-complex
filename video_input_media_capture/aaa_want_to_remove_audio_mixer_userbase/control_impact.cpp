#include "framework.h"

#include "acme/constant/id.h"


#define IDC_MIXER_SLIDER 1000
//#define IDC_LIST 1001
#define IDC_BUTTON_RESERVE 1002
#define ID_VIEW_UPDATE 1003
#define IDI_ALBUM 1004
#define IDS_MIXER_DIALOG_TITLEFORMAT 1006

namespace multimedia
{

   namespace audio_mixer_user_base
   {


      const int control_impact::cnListCount = 9;

      control_impact::control_impact() :
         m_pbrushBackground(e_create)
      {

         //m_pdata = ___new control_data(this);

         m_bInitialized = false;
         //   m_iCacheNextIndex = 0;
         m_uiNextSliderID = IDC_MIXER_SLIDER;

         //m_colorForeground = psession->get_default_color(COLOR_BTNTEXT);
         //m_colorForeground = rgb(255, 255, 255);
         //m_colorForeground = rgb(255, 255, 255)
         //m_colorBackground = rgb(58,80,110);
         //m_colorBackground = psession->get_default_color(COLOR_3DFACE);
         m_colorBackground = rgb(74, 70, 64);

         //m_pbrushBackground.create_solid(m_colorBackground);
         //m_colorForeground = rgb(255, 255, 255);

         //m_pbrushBackground->CreateStockObject(NULL_BRUSH);
         m_colorForeground = rgb(0, 0, 0);


         m_dwUpdateTime = 0;
         informationf("AlbumFormImpact this = %x \n", this);
      }

      
      control_impact::~control_impact()
      {

      }


      void control_impact::install_message_routing(::channel * pchannel)
      {
         ::user::impact::install_message_routing(pchannel);
         MESSAGE_LINK(e_message_size, pchannel, this, &control_impact::on_message_size);
         MESSAGE_LINK(e_message_destroy, pchannel, this, &control_impact::on_message_destroy);
         MESSAGE_LINK(e_message_create, pchannel, this, &control_impact::on_message_create);
         //   //MESSAGE_LINK(e_message_timer, pchannel, this, &control_impact::on_timer);
         //   MESSAGE_LINK(e_message_context_menu, pchannel, this, &control_impact::on_message_context_menu);
         MESSAGE_LINK(e_message_scroll_y, pchannel, this, &control_impact::on_message_scroll_y);
#ifdef WINDOWS
         MESSAGE_LINK(WM_CTLCOLOR, pchannel, this, &control_impact::_001OnCtlColor);
#endif
         MESSAGE_LINK(e_message_scroll_x, pchannel, this, &control_impact::on_message_scroll_x);

         add_command_handler(IDC_BUTTON_RESERVE, &control_impact::_001OnButtonReserve);
         connect_command_probe(ID_VIEW_UPDATE, &control_impact::_001OnUpdateImpactUpdate);

         //   IGUI_WIN_ON_NOTIFY(LVN_COLUMNCLICK  , IDC_LIST  , this, this, &control_impact::_001OnColumnclickList);
         //IGUI_WIN_ON_NOTIFY(LVN_GETDISPINFO  , IDC_LIST  , this, this, &control_impact::_001OnGetdispinfoList);
         //IGUI_WIN_ON_NOTIFY(NM_DBLCLK        , IDC_LIST  , this, this, &control_impact::_001OnDblclkList);
      }


      void control_impact::assert_ok() const
      {
         ::user::impact::assert_ok();
      }

      void control_impact::dump(dump_context & dumpcontext) const
      {
         ::user::impact::dump(dumpcontext);
      }


      ::user::document * control_impact::get_document()
      {

         return ::user::impact::get_document();

      }


      void control_impact::on_message_size(::message::message * pmessage)
      {
         if(!m_bInitialized)
            return;
         pmessage->previous();

      }

      void control_impact::OnInitialUpdate()
      {
         //wait_cursor cwc(this);

      }

      void control_impact::_001OnGetdispinfoList(::message::message * pmessage)
      {
#ifdef WINDOWS_DESKTOP
         ::pointer<::message::notify>pnotify(pmessage);

         pnotify->m_lresult = 0;
#endif
      }

      void control_impact::on_message_destroy(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
      }

      void control_impact::_001OnColumnclickList(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
      }



      void control_impact::_001OnDblclkList(::message::message * pmessage)
      {
#ifdef WINDOWS_DESKTOP
         ::pointer<::message::notify>pnotify(pmessage);
         // TODO: add your control notification handler code here
         //   LPNMLISTVIEW lpnmlv = (LPNMLISTVIEW) pnotify->get_lpnmhdr();
         //   CListCtrl * pList = (CListCtrl *) get_child_by_id(lpnmlv->hdr.idFrom);
         pnotify->m_lresult = 0;
#endif
      }

      void control_impact::_001OnButtonReserve(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
         // TODO: add your control notification handler code here
      }


      void control_impact::pre_translate_message(::message::message * pmessage)
      {

         ::pointer<::user::message>pusermessage(pmessage);

         return ::user::impact::pre_translate_message(pmessage);
         
      }


      void control_impact::on_message_create(::message::message * pmessage)
      {
         
         if (pmessage->previous())
         {

            return;

         }

         m_bInitialized = true;

      }


      bool control_impact::pre_create_window(::user::system * pusersystem)
      {
         pusersystem->m_createstruct.style = pusersystem->m_createstruct.style;
         //   int i = WS_POPUP;

#ifdef WINDOWS_DESKTOP




#endif

         return ::user::impact::pre_create_window(pusersystem);
      }


      /*void control_impact::SetImageLists()
      {
      ::draw2d::graphics_pointer spgraphics(e_create);
      spgraphics->CreateDC(
      "DISPLAY",
      nullptr,
      nullptr,
      nullptr);
      //CTabCtrl * pTab = (CTabCtrl *) get_child_by_id(IDC_TAB);
      if(m_SmallImageList.GetSafeHandle() != nullptr)
      {
      //  pTab->SetImageList(nullptr);
      }
      int iBitCount = spgraphics->GetDeviceCaps(BITSPIXEL);
      if(iBitCount > 8)
      {
      m_SmallImageListBitmap.delete_object();
      m_SmallImageListBitmap.LoadBitmap(IDB_ALBUM_SMALL_256);
      m_SmallImageListBitmapV001.delete_object();
      m_SmallImageListBitmapV001.LoadBitmap(IDB_ALBUM_SMALL_256);
      m_SmallImageList.create(
      16, 16,
      ILC_COLOR32 |
      ILC_MASK,
      2,
      1);
      m_SmallImageListV001.create(
      16, 16,
      ILC_COLOR32 |
      ILC_MASK,
      2,
      1);
      //m_SmallImageList.SetBkColor(CLR_NONE);
      m_SmallImageList.SetBkColor(psession->get_default_color(COLOR_WINDOW));
      m_SmallImageList.add(&m_SmallImageListBitmap, rgb(255, 0, 255));
      m_SmallImageListV001.SetBkColor(crButtonFace);
      m_SmallImageListV001.add(&m_SmallImageListBitmapV001, rgb(255, 0, 255));

      }
      else
      {
      m_SmallImageListBitmap.delete_object();
      m_SmallImageListBitmap.LoadBitmap(IDB_ALBUM_SMALL_16);
      m_SmallImageListBitmapV001.delete_object();
      m_SmallImageListBitmapV001.LoadBitmap(IDB_ALBUM_SMALL_16);
      m_SmallImageList.create(
      16, 16,
      ILC_COLOR32 |
      ILC_MASK,
      2,
      1);
      m_SmallImageListV001.create(
      16, 16,
      ILC_COLOR32 |
      ILC_MASK,
      2,
      1);
      m_SmallImageList.SetBkColor(CLR_NONE);
      m_SmallImageList.add(&m_SmallImageListBitmap, rgb(255, 0, 255));
      m_SmallImageListV001.SetBkColor(CLR_NONE);
      m_SmallImageListV001.add(&m_SmallImageListBitmapV001, rgb(255, 0, 255));

      }
      if(m_SmallImageList.GetSafeHandle() != nullptr)
      {
      }
      if(m_SmallImageListV001.GetSafeHandle() != nullptr)
      {
      //        pTab->SetImageList(&m_SmallImageListV001);

      }


      spgraphics->DeleteDC();
      }
      */

      void control_impact::_001OnUpdateImpactUpdate(::message::message * pmessage)
      {
         ::pointer<::message::command>pcommand(pmessage);
         pcommand->enable();
         pcommand->m_bRet = true;
      }







      void control_impact::handle(::topic * ptopic, ::context * pcontext)
      {
         
         ::user::impact::handle(ptopic, pcontext);
         
         if(ptopic->m_atom == id_new_destination)
         {

            //New destination set
            set_title();

            ::audio_mixer::destination * pdestination = get_destination();
            pdestination->initialize_all_controls();

            ::audio_mixer::audio_mixer * pmixer = get_mixer();

            pmixer->m_pdevice->map_lines();
            pmixer->m_pdevice->map_controls();

            CreateControls();
            pmixer->m_pdevice->MapDlgCtrlIDToControls();
            pdestination->update_all_controls();

            set_need_layout();

         }

      }


      void control_impact::OnDraw(::image::image *pimage)
      {

         __UNREFERENCED_PARAMETER(pimage);

      }


      bool control_impact::CreateControls()
      {
         delete_contents();

         CreateControls(get_destination());

         ::audio_mixer::source_array & sourcea = get_destination()->get_source_info();

         for(int i = 0; i < sourcea.get_size(); i++)
         {
            CreateControls(sourcea[i]);
         }

         return true;
      }

      bool control_impact::CreateControls(::audio_mixer::source *pSource)
      {

         bool bHasControls = false;

         ::audio_mixer::control * pinteraction;

         ::audio_mixer::control_array & controla = pSource->m_mixercontrola;

         for(int iControl = 0; iControl < controla.get_size(); iControl++)
         {
            pinteraction = controla[iControl];

            if(create_control(pinteraction))
            {
               bHasControls = true;
            }

         }

         if(bHasControls)
         {
            
            ::double_rectangle rectangle(0, 0, 0, 0);
            
            auto pst = __allocate simple_static();

            pst->create_window(this, pSource->get_source_name());

            pst->set_window_text(pSource->get_source_name());

            pst->ModifyStyleEx(0, WS_EX_TRANSPARENT, SWP_SHOWWINDOW);

            m_labelmap.set_at(pSource->GetLineID(), pst);

         }

         return true;

      }


      void control_impact::delete_contents()
      {

         m_labelmap.erase_all();

         //unsigned int dwKey;

         //simple_static * pst;

         //POSITION pos = m_staticsLines.get_start_position();

         //while(pos != nullptr)
         //{

         //   m_staticsLines.get_next_assoc(pos, dwKey, pst);

         //   delete pst;

         //}

         //m_staticsLines.erase_all();

      }


      bool control_impact::create_control(::audio_mixer::control * pinteraction)
      {

         if(pinteraction->control_type(::audio_mixer::control_volume))
         {

            return CreateVolumeControl(pinteraction);

         }
         else if(pinteraction->control_type(::audio_mixer::control_boolean))
         {

            return CreateMuteControl(pinteraction);

         }
         else
         {

            return false;

         }


      }


      bool control_impact::CreateVolumeControl(::audio_mixer::control * pinteraction)
      {

         if(!pinteraction->CreateWindowsVolumeV001(this, m_uiNextSliderID, &m_uiNextSliderID))
            return false;

         return true;

      }


      bool control_impact::CreateMuteControl(::audio_mixer::control *pinteraction)
      {

         if(!pinteraction->_001CreateMuteControl(this, m_uiNextSliderID, &m_uiNextSliderID))
            return false;

         return true;

      }


      void control_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
      {
         int iStartX = 0;
         int iEndX = 0;
         int iStartY = 0;
         int iEndY = 0;

         if(get_destination() == nullptr)
            return;

         LayoutLine(-1, get_destination(), iStartX, iStartY, &iEndX, &iEndY);
         iStartX = iEndX;

         ::audio_mixer::source_array & sourcea = get_destination()->get_source_info();

         for(int i = 0; i < sourcea.get_size(); i++)
         {

            LayoutLine(i, sourcea[i], iStartX, iStartY, &iEndX, &iEndY);

            iStartX = iEndX;

         }

         //::double_rectangle rectangle(0, 0, iEndX, iEndY);
         //::AdjustWindowRectEx(&rectangle, GetStyle(), false,
         //      GetExStyle());
         //set_window_position(0, 0, 0, rectangle.width(), rectangle.height(), SWP_NOMOVE | SWP_NOACTIVATE);
         //::double_rectangle rectangleX;
         //this->rectangle(rectangleX);

         set_need_redraw();

      }

      void control_impact::set_title()
      {
         string strFormat;
         //strFormat.load_string(IDS_MIXER_DIALOG_TITLEFORMAT);
         strFormat = "%s - %s - %s";

         string strAppTitle;
         //strAppTitle.load_string(WINDOWS_DEFINITION_IDS_APP_TITLE);
         strAppTitle = papp->m_strAppName;

         string strTitle;
         ASSERT(get_destination() != nullptr);
         strTitle.formatf(
         strFormat,
         strAppTitle.c_str(),
         get_mixer()->m_pdevice->get_product_name().c_str(),
         get_destination()->get_source_name().c_str());

         set_window_text(strTitle);

      }

      void control_impact::LayoutLine(int iSource, ::audio_mixer::source *pSource, int iStartX, int iStartY, int *piEndX, int *piEndY)
      {
         ::audio_mixer::control_array & controla = pSource->m_mixercontrola;
         ::audio_mixer::control * pinteraction;
         ::audio_mixer::user_control * pusercontrol;
         bool bHasAtLeastOneControl = false;
         int y = iStartY;
         int y2;
         y += 2;

         auto & pst = m_labelmap[pSource->GetLineID()];

         pst->set_window_position(
            zorder_none,
            iStartX, y,
            70, 30,
            SWP_SHOWWINDOW);

         y += 30;

         for(int iControl = 0; iControl < controla.get_size(); iControl++)
         {

            pinteraction = controla[iControl];

            if(pinteraction->control_type(::audio_mixer::control_volume))
            {
               if(pinteraction->get_size() >= 2)
               {
                  pusercontrol = pinteraction->GetControl(::audio_mixer::control_data::TypeStereoBalanceLabel);
                  y2 = y;
                  if(pusercontrol != nullptr)
                  {
                     bHasAtLeastOneControl = true;
                     pusercontrol->set_window_position(zorder_none, iStartX, y2, 80, 15, SWP_SHOWWINDOW);
                     y2 += 15;
                     pusercontrol = pinteraction->GetControl(::audio_mixer::control_data::TypeStereoBalance);
                     if(pusercontrol != nullptr)
                     {
                        pusercontrol->set_window_position(zorder_none, iStartX, y2, 70, 30, SWP_SHOWWINDOW);
                     }
                     y += 45;
                  }
                  y2 = y;
                  pusercontrol = pinteraction->GetControl(::audio_mixer::control_data::TypeStereoVolumeLabel);
                  if(pusercontrol != nullptr)
                  {
                     bHasAtLeastOneControl = true;
                     pusercontrol->set_window_position(zorder_none, iStartX, y2, 80, 15, SWP_SHOWWINDOW);
                     y2 += 15;
                     pusercontrol = pinteraction->GetControl(::audio_mixer::control_data::TypeStereoVolume);
                     if(pusercontrol != nullptr)
                     {
                        bHasAtLeastOneControl = true;
                        pusercontrol->set_window_position(zorder_none, iStartX, y2, 50, 120, SWP_SHOWWINDOW);
                     }
                  }
                  y += 135;
               }

            }
         }

         for(::collection::index iControl = 0; iControl < controla.get_size(); iControl++)
         {

            pinteraction = controla[iControl];

            if(pinteraction->control_type(::audio_mixer::control_mux))
            {

               m_controla.add_unique(pinteraction);

            }

            if(pinteraction->control_type(::audio_mixer::control_boolean))
            {
               ::collection::count iSize = pinteraction->get_size();
               for(::collection::index i = 0; i < iSize; i++)
               {
                  pusercontrol = pinteraction->GetControlByIndex(i);
                  bHasAtLeastOneControl = true;
                  pusercontrol->set_window_position(zorder_none, iStartX, y, 80, 30, SWP_SHOWWINDOW);
                  y += 30;
               }
            }
         }
         if(iSource >= 0)
         {
            for(int iControl = 0; iControl < m_controla.get_size(); iControl++)
            {
               pinteraction = m_controla[iControl];
               if(pinteraction->control_type(::audio_mixer::control_boolean))
               {
                  pusercontrol = pinteraction->GetControlByIndex(iSource);
                  bHasAtLeastOneControl = true;
                  pusercontrol->set_window_position(zorder_none, iStartX, y, 80, 30, SWP_SHOWWINDOW);
                  y += 30;
               }
            }
         }
         if(iSource >= 0)
         {
            for(int iControl = 0; iControl < m_controla.get_size(); iControl++)
            {
               pinteraction = m_controla[iControl];
            }
         }
         if( bHasAtLeastOneControl)
         {
            *piEndX = iStartX + 184;
            *piEndY = 300;
         }
      }


      void control_impact::on_message_scroll_y(::message::message * pmessage)
      {

         SCAST_MSG(scroll);

         ::pointer<::user::interaction>pusercontrol = pscroll->m_pScrollBar;
         ::audio_mixer::control * pControl;
         if(get_mixer()->m_pdevice->m_mapDlgItemIDToControl.lookup(pusercontrol->GetDlgCtrlId(), pControl))
         {
            pControl->OnVHScroll(pscroll->m_nSBCode, (unsigned int) pscroll->m_nPos, pscroll->m_pScrollBar);
         }
      }

      void control_impact::_001OnCtlColor(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
         //   ::pointer<::message::ctl_color>pctlcolor(pmessage);
         throw ::not_implemented();
         //   HBRUSH hbr = ::user::impact::OnCtlColor(pgraphics, pusercontrol, nCtlColor);
         /*HBRUSH hbr;
         if(pctlcolor->m_nCtlType == CTLCOLOR_EDIT)
         {
         pctlcolor->m_pdc->SetTextColor(m_colorForeground);
         hbr = m_pbrushBackground;
         pctlcolor->m_pdc->SetBkColor(m_colorBackground);
         }
         else if(pctlcolor->m_nCtlType == CTLCOLOR_MSGBOX)
         {
         hbr = m_pbrushBackground;
         }
         else if(pctlcolor->m_nCtlType == CTLCOLOR_STATIC)
         {
         pctlcolor->m_pdc->SetTextColor(m_colorForeground);
         hbr = m_pbrushBackground;
         pctlcolor->m_pdc->SetBkColor(m_colorBackground);
         pctlcolor->m_pdc->SetBkMode(TRANSPARENT);
         }
         else if(pctlcolor->m_nCtlType == CTLCOLOR_DLG)
         {
         //      pgraphics->SetTextColor(rgb(255, 255, 255));
         //      hbr = m_pbrushBackground;
         //      pgraphics->SetBkColor(rgb(0, 0, 0));
         }
         else
         {
         // trans      pctlcolor->m_hbrush = ::user::impact::OnCtlColor(pctlcolor->m_pdc, pctlcolor->m_puserinteraction, pctlcolor->m_nCtlType);
         }*/
      }

      void control_impact::on_message_scroll_x(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
         //::pointer<::message::scroll>pscroll(pmessage);
      }


      ::audio_mixer::audio_mixer * control_impact::get_mixer()
      {
         return get_data()->get_mixer();
      }

      ::audio_mixer::destination * control_impact::get_destination()
      {
         return get_data()->get_destination();
      }


      bool control_impact::OnNotify(::user::message * pusermessage)
      {

         __UNREFERENCED_PARAMETER(pusermessage);

         return false;

      }


      bool control_impact::OnCommand(::user::message * pusermessage)
      {

         if(get_mixer()->OnCommand(pusermessage))
            return true;

         return false;

      }


      control_data * control_impact::get_data()
      {

         return m_pdata;

      }


   } // namespace audio_mixer_user_base


} // namespace multimedia



