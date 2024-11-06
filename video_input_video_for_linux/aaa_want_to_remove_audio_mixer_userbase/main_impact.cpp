#include "framework.h"


#define IDC_MIXER_SLIDER 1000
#define IDC_BUTTON_RESERVE 1002
#define ID_VIEW_UPDATE 1003
#define IDI_ALBUM 1004
#define IDS_MIXER_DIALOG_TITLEFORMAT 1006
#define IDS_MIXER_SPEAKERSCONTROLS 1007
#define IDS_MIXER_WAVEINCONTROLS 1008


namespace multimedia
{


   namespace audio_mixer_user_base
   {


      const int main_impact::cnListCount = 9;


      main_impact::main_impact() :
         m_pbrushBackground(e_create)
      {


         m_pcontrol = nullptr;



         m_bInitialized = false;
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

      main_impact::~main_impact()
      {

      }

      void main_impact::install_message_routing(::channel * pchannel)
      {
         ::userex::pane_tab_impact::install_message_routing(pchannel);
         //MESSAGE_LINK(e_message_size, pchannel, this, &main_impact::on_message_size);
         MESSAGE_LINK(e_message_destroy, pchannel, this, &main_impact::on_message_destroy);
         MESSAGE_LINK(e_message_create, pchannel, this, &main_impact::on_message_create);
         //   //MESSAGE_LINK(e_message_timer, pchannel, this, &main_impact::_001OnTimer);
         // MESSAGE_LINK(e_message_context_menu, pchannel, this, &main_impact::on_message_context_menu);
         //   MESSAGE_LINK(e_message_scroll_y, pchannel, this, &main_impact::on_message_scroll_y);
         //      MESSAGE_LINK(WM_CTLCOLOR, pchannel, this, &main_impact::_001OnCtlColor);

         //   IGUI_WIN_ON_NOTIFY(LVN_COLUMNCLICK  , IDC_LIST, this, this, &main_impact::_001OnColumnclickList);
         // IGUI_WIN_ON_NOTIFY(NM_DBLCLK        , IDC_LIST, this, this, &main_impact::_001OnDblclkList);
         //IGUI_WIN_ON_NOTIFY(LVN_GETDISPINFO  , IDC_LIST, this, this, &main_impact::_001OnGetdispinfoList);

         //      IGUI_WIN_ON_CONTROL(BN_CLICKED, IDC_BUTTON_RESERVE     , this, this, &main_impact::_001OnButtonReserve);

         connect_command_probe(ID_VIEW_UPDATE, &main_impact::_001OnUpdateImpactUpdate);
      }



      void main_impact::assert_ok() const
      {
         ::user::impact::assert_ok();
      }

      void main_impact::dump(dump_context & dumpcontext) const
      {
         ::user::impact::dump(dumpcontext);
      }


      ::user::document * main_impact::get_document()
      {

         return ::user::impact::get_document();

      }


      void main_impact::on_message_size(::message::message * pmessage)
      {
         if(!m_bInitialized)
            return;
         if(pmessage->previous())
            return;

         LayoutControl();
      }


      void main_impact::handle(::topic * ptopic, ::context * pcontext)
      {

      }


      void main_impact::_001OnGetdispinfoList(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
         //      ::pointer<::message::notify>pnotify(pmessage);
      }

      void main_impact::on_message_destroy(::message::message * pmessage)
      {


         __UNREFERENCED_PARAMETER(pmessage);

      }

      void main_impact::_001OnColumnclickList(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
      }



      void main_impact::_001OnDblclkList(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
         //      ::pointer<::message::notify>pnotify(pmessage);
      }

      void main_impact::_001OnButtonReserve(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
      }


      void main_impact::pre_translate_message(::message::message * pmessage)
      {

         ::pointer<::user::message>pusermessage(pmessage);

         return ::user::impact::pre_translate_message(pmessage);

      }
      

      void main_impact::on_message_create(::message::message * pmessage)
      {

         //wait_cursor cwc(this);

         if(pmessage->previous())
            return ;


#ifdef WINDOWS_DESKTOP

         m_enhmetafile = GetEnhMetaFileW(wstring(pcontext->directory()->matter("veriwell_vmsp/image/vector/vmp.emf")));


         GetEnhMetaFileHeader(m_enhmetafile, sizeof(m_emh), &m_emh);
#endif

         ::double_rectangle clientRect(0, 0, 0, 0);

         ::pointer<department>central = papp->audiomixeruserbase();

         add_image_tab(central->m_strPlaybackTitle, central->m_strPlaybackIcon, central->m_atomPlaybackPane);
         add_image_tab(central->m_strRecordingTitle, central->m_strRecordingIcon, central->m_atomRecordingPane);

         set_current_tab_by_id(central->m_atomPlaybackPane);

         //::user::impact::handle(ptopic, pcontext);

         m_bInitialized = true;

      }


      bool main_impact::pre_create_window(::user::system * pusersystem)
      {
         pusersystem->m_createstruct.style = pusersystem->m_createstruct.style;


         return ::user::impact::pre_create_window(pusersystem);
      }



      void main_impact::_001OnUpdateImpactUpdate(::message::message * pmessage)
      {
         ::pointer<::message::command>pcommand(pmessage);
         pcommand->enable();
         pcommand->m_bRet = true;
      }


      void main_impact::_001OnCtlColor(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);

      }


      void main_impact::_001OnMixerSpeakerscontrols(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
         ::pointer<department>user = papp->audiomixeruserbase();
         if(get_current_tab_id() != user->m_atomPlaybackPane)
         {
            set_current_tab_by_id(user->m_atomPlaybackPane);
         }
      }

      void main_impact::_001OnUpdateMixerSpeakerscontrols(::message::message * pmessage)
      {
         ::pointer<::message::command>pcommand(pmessage);
         ::pointer<department>user = papp->audiomixeruserbase();
         if(get_current_tab_id() == user->m_atomPlaybackPane)
         {
            pcommand->set_check(true);
            pcommand->enable(true);
         }
         else
         {
            pcommand->set_check(false);
            pcommand->enable(true);
         }
         pcommand->m_bRet = true;
      }

      void main_impact::_001OnMixerWaveincontrols(::message::message * pmessage)
      {
         __UNREFERENCED_PARAMETER(pmessage);
         ::pointer<department>user = papp->audiomixeruserbase();
         if(get_current_tab_id() != user->m_atomRecordingPane)
         {
            set_current_tab_by_id(user->m_atomRecordingPane);
         }
      }

      void main_impact::_001OnUpdateMixerWaveincontrols(::message::message * pmessage)
      {
         ::pointer<::message::command>pcommand(pmessage);
         ::pointer<department>user = papp->audiomixeruserbase();
         if(get_current_tab_id() == user->m_atomRecordingPane)
         {
            pcommand->set_check(true);
            pcommand->enable(true);
         }
         else
         {
            pcommand->set_check(false);
            pcommand->enable(true);
         }

         pcommand->m_bRet = true;

      }


      bool main_impact::OnNotify(::user::message * pusermessage)
      {

         __UNREFERENCED_PARAMETER(pusermessage);

         return false;

      }


      void main_impact::on_create_impact(::user::impact_data * pimpactdata)
      {
         //      void     mmrc;
         ::pointer<control_impact>pinteraction = create_impact < control_impact > (pimpactdata);
         ::pointer<department>user = papp->audiomixeruserbase();
         if(pimpactdata->m_atom == user->m_atomPlaybackPane)
         {
            pinteraction->get_data()->initialize(this);
            pinteraction->get_data()->set_new_device(0);
            pinteraction->get_data()->set_new_destination(::audio_mixer::destination_speakers);
         }
         else if(pimpactdata->m_atom == user->m_atomRecordingPane)
         {
            pinteraction->get_data()->initialize(this);
            pinteraction->get_data()->set_new_device(0);
         }
      }

      void main_impact::LayoutControl()
      {
         if(m_pcontrol != nullptr)
         {
            ::double_rectangle rectangleX;

            ::double_rectangle rectangleHosting;
            this->rectangle(rectangleX);
            m_pcontrol->set_window_position(zorder_none, rectangleX.left(), rectangleX.top(), rectangleX.width(), rectangleX.height(), SWP_SHOWWINDOW);
            m_pcontrol->on_layout(pgraphics);
         }
      }

      void main_impact::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
      {



         ::double_rectangle rectangleMeta;
         ::double_rectangle rectangleDib;

         ::double_rectangle rectangleX;

         this->rectangle(rectangleX);

         if(session()->savings()->is_trying_to_save(::e_resource_processing))
         {
            pgraphics->fill_rectangle(rectangleX, rgb(255,255,255));
         }
         else
         {
            pgraphics->color_blend(rectangleX, rgb(255,255,255), 32);
         }

         ::double_rectangle rectangle;

         rectangle = rectangleX;
         rectangle.ScaleHeightAspect(minimum(rectangleX.height(), rectangleX.height() - 333), rectangleX.right(), rectangleX.bottom());

         if(m_enhmetafile != nullptr)
         {
            rectangleMeta.left() = 0;
            rectangleMeta.top() = 0;
            rectangleMeta.right() = m_emh.rclBounds.right() - m_emh.rclBounds.left();
            rectangleMeta.bottom() = m_emh.rclBounds.bottom() - m_emh.rclBounds.top();
            //rectangleMeta.FitOnCenter(rectangleX);
            rectangleMeta.FitOnCenterOf(rectangleX);
            //rectangleMeta.Align(::ca2::AlignBottom | ::ca2::AlignRight, rectangleX);

            rectangleDib = rectangleMeta;
            rectangleDib -= rectangleMeta.top_left();

            ::image::image_pointer pimage;

            pimage = create_image(rectangleDib.size());

            if(pimage->get_graphics() != nullptr)
            {

               pimage->get_graphics()->fill_rectangle(rectangleDib, rgb(0, 0, 0));

#ifdef WINDOWS

               pimage->get_graphics()->PlayMetaFile(m_enhmetafile, rectangleDib);

#endif
               pimage->channel_copy(::color::e_channel_opacity, ::color::e_channel_green);

               pimage->channel_multiply(0.23, ::color::e_channel_opacity);

               pgraphics->draw(rectangleMeta, pimage->get_graphics());

            }

         }

         ::userex::pane_tab_impact::_000OnDraw(pgraphics);

      }

      /*void main_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {
      __UNREFERENCED_PARAMETER(pgraphics);



      }*/


   } // namespace audio_mixer_user_base


} // namespace multimedia




