#include "framework.h"



namespace multimedia
{


   namespace audio_mixer_user_base
   {


      frame_window::frame_window()
      {

         m_pmainimpact          = nullptr;
         m_bSizeEnable        = false;
         m_bLayered           = true;

         set_translucent();

      }


      frame_window::~frame_window()
      {

      }


      //
     
      //ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
      //ON_COMMAND(ID_MIXER_EXIT, OnMixerExit)
      //

      void frame_window::install_message_routing(::channel * pchannel)
      {

         simple_frame_window::install_message_routing(pchannel);
         MESSAGE_LINK(e_message_create, pchannel, this, &frame_window::on_message_create);
         MESSAGE_LINK(e_message_destroy, pchannel, this, &frame_window::on_message_destroy);
         MESSAGE_LINK(e_message_measure_item, pchannel, this, &frame_window::_001OnMeasureItem);
         MESSAGE_LINK(e_message_close, pchannel, this, &frame_window::on_message_close);
         MESSAGE_LINK(WM_USER, pchannel, this, &frame_window::OnUserMessage);

      }


      bool frame_window::on_create_client(::user::system * lpcs, ::create * pContext)
      {
         return simple_frame_window::on_create_client(lpcs, pContext);
      }

      void frame_window::on_message_create(::message::message * pmessage)
      {


         pmessage->previous();



         ::double_rectangle rectangleWnd;
         m_wndToolBar.window_rectangle(rectangleWnd);
         ::size size;
         m_wndToolBar.set_window_position(zorder_none, 0, 0, size.cx(), size.cy(), SWP_NOMOVE | SWP_NOZORDER);
         m_wndToolBar.window_rectangle(rectangleWnd);
         m_wndToolBar.ModifyStyle(0, WS_VISIBLE);


         m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

         m_wndToolBarExport.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

         string_array straIndicator;
         straIndicator.add("IDS_APP_TITLE");
         straIndicator.add("IDS_APP_TITLE");

         m_bSizeEnable = true;


         //   TransparentFrameWndUpdateBars();
         InitializeBars();

         //pcreate->m_bRet = false;
      }


      void frame_window::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
      {

         simple_frame_window::route_command(pcommand);

      }


      ::pointer<main_impact>frame_window::GetMainImpact()
      {
         ASSERT(base_class <main_impact >::bases(m_pmainimpact));
         return  (m_pmainimpact);
      }


      void frame_window::on_message_destroy(::message::message * pmessage)
      {
      
         ::pointer<::user::message>pusermessage(pmessage);

         pusermessage->m_bRet = true;

      }


      void frame_window::OnUserMessage(::message::message * pmessage)
      {
         ::pointer<::user::message>pusermessage(pmessage);
         if(pusermessage->m_wparam == 54) // ::impact Changed
         {
            on_layout(pgraphics);
         }
         else if(pusermessage->m_wparam == 5678)
         {
            string str;
            m_wndStatusBar.SetPaneInfo(0, "1", SBPS_STRETCH | SBPS_NORMAL, 0);
            ///xxx        str.load_string(IDS_ALBUM_SEARCHINGINDICATOR);
            m_wndStatusBar.SetPaneText(0, str);
         }
         else if(pusermessage->m_wparam == 56789)
         {
            m_wndStatusBar.SetPaneInfo(0, /*ID_SEPARATOR*/ 0, SBPS_STRETCH | SBPS_NORMAL, 0);
         }
         else if(pusermessage->m_wparam == 51678)
         {
            string str((const ::string &) pusermessage->m_lparam.m_lparam);
            m_wndStatusBar.SetPaneInfo(0, "1", SBPS_STRETCH | SBPS_NORMAL, 0);
            m_wndStatusBar.SetPaneText(0, str);
         }
         pusermessage->m_lresult = 0;
         pusermessage->m_bRet = true;
      }

      void frame_window::_001OnMeasureItem(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
         //::pointer<::message::measure_item>pmeasureitem(pmessage);
      }

      /*bool frame_window::Initialize(db_server *pdbcentral)
      {
      m_pdbcentral = pdbcentral;

      m_pdbcentral->get_db_long_set()->LoadWindowCoordinates(
      "Janelas",
      "Album",
      this);
      return true;
      }*/

      void frame_window::on_message_close(::message::message * pmessage)
      {
         pmessage->m_bRet = false;
      }

      bool frame_window::OnToolsOptions()
      {
         //   if(m_poptionsimpact == nullptr)
         //   {
         //      m_poptionsimpact = ___new CAlbumOptionsDialog();
         //      m_poptionsimpact->create(&m_poptionsimpact);
         //      m_poptionsimpact->show_window(SW_SHOWNORMAL);
         //   }
         return true;
      }

      void frame_window::_001OnAppLanguage(::message::message * pmessage)
      {
         //__UNREFERENCED_PARAMETER(lParam);
         //if(wParam == ::aura::application::WPARAM_LANGUAGE_UPDATE)
         {
            //      TransparentFrameWndUpdateBars();
            InitializeBars();
         }
         //return 0;

      }

      /*CCommandIdToTextIdMapRow maprowToolBar[] =
      {
      CCommandIdToTextIdMapRow(
      ID_MIXER_SPEAKERSCONTROLS,
      IDS_MIXER_PLAYBACKCONTROL),
      CCommandIdToTextIdMapRow(
      ID_MIXER_WAVEINCONTROLS,
      IDS_MIXER_RECORDINGCONTROL),
      CCommandIdToTextIdMapRow::endRow
      };
      */

      bool frame_window::InitializeBars()
      {
         bool bResult = true;

         string str;
         ::double_rectangle rectangleWnd;
         m_wndToolBar.window_rectangle(rectangleWnd);
         ::size size;

         //   while(m_wndToolBar.DeleteButton(0));
         /*    if (!m_wndToolBar.LoadToolBar(IDR_MIXER))
         {
         TRACE0("Failed to create toolbar\n");
         bResult = false;      // fail to create
         }
         else
         {
               CVmsGuiUtil::UpdateToolBarText(
         m_wndToolBar,
         maprowToolBar);
         CVmsGuiUtil::OptimizeToolBarStyleForText(
         m_wndToolBar);*/

         //      CMenuBarV033::CalcSize(m_wndToolBar.GetToolBarCtrl(), size);
         /*      m_wndToolBar.set_window_position(0, 0, 0, size.cx(), size.cy(), SWP_NOMOVE | SWP_NOZORDER);
         //m_wndToolBar.GetToolBarCtrl().AutoSize();
         m_wndToolBar.window_rectangle(rectangleWnd);
         m_wndToolBar.ModifyStyle(0, WS_VISIBLE);
         m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
         CBRS_TOOLTIPS | CBRS_FLYBY);

         m_wndToolBarExport.SetBarStyle(m_wndToolBar.GetBarStyle() |
         CBRS_TOOLTIPS | CBRS_FLYBY);
         }

         */



         string_array straIndicator;
         straIndicator.add("IDS_APP_TITLE");
         straIndicator.add("IDS_APP_TITLE");
         /*    if (!m_wndStatusBar.SetIndicators(straIndicator))
         {
         TRACE0("Failed to create status bar\n");
         return false;      // fail to create
         }
         m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_STRETCH | SBPS_NORMAL, 0);
         m_wndStatusBar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_NORMAL, 0);*/


         return bResult;
      }

      void frame_window::pre_translate_message(::message::message * pmessage)
      {
         return simple_frame_window::pre_translate_message(pmessage);
      }


      void frame_window::OnFrameworkV033Command(::message::message * pmessage)
      {
         ::pointer<::user::message>pusermessage(pmessage);
         //   return simple_frame_window::OnFrameworkV033Command(wParam, lParam);
         pusermessage->m_lresult = 0;
         pusermessage->m_bRet = true;
      }

      bool frame_window::OnMixerExit()
      {
         post_message(e_message_close);
         return true;
      }

      void frame_window::post_non_client_destroy()
      {
         simple_frame_window::post_non_client_destroy();
      }


      void frame_window::UpdateToolBarText(simple_toolbar & toolbar)
      {
         __UNREFERENCED_PARAMETER(toolbar);

      }

      bool frame_window::GetToolButtonText(string & str, unsigned int uiCmd)
      {
         __UNREFERENCED_PARAMETER(str);
         __UNREFERENCED_PARAMETER(uiCmd);

         return false;

      }


   } // namespace audio_mixer_user_base


} // namespace multimedia


