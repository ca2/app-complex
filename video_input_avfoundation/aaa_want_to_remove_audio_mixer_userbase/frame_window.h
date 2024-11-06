#pragma once


namespace multimedia
{


   namespace audio_mixer_user_base
   {


      class main_impact;


      class CLASS_DECL_APP_CORE_AUDIO frame_window :
         public simple_frame_window
      {
      public:


         ::pointer<main_impact>         m_pmainimpact;
         simple_toolbar                m_wndToolBar;
         simple_toolbar                m_wndToolBarExport;
         simple_toolbar                m_wndToolBarHtmlImpact;
         simple_status_bar             m_wndStatusBar;
         bool                          m_bSizeEnable;


         frame_window();
         virtual ~frame_window();


         bool GetToolButtonText(string &str, unsigned int uiCmd);
         void UpdateToolBarText(simple_toolbar &toolbar);
         ::pointer<main_impact>GetMainImpact();

         void install_message_routing(::channel * pchannel) override;
         bool InitializeBars();





         virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant);
         virtual void pre_translate_message(::message::message * pmessage);
         virtual bool on_create_client(::user::system * lpcs, ::create * pContext);
         virtual void post_non_client_destroy();

         DECLARE_MESSAGE_HANDLER(_001OnAppLanguage);
         DECLARE_MESSAGE_HANDLER(on_message_create);
         DECLARE_MESSAGE_HANDLER(on_message_destroy);
         DECLARE_MESSAGE_HANDLER(_001OnMeasureItem);
         DECLARE_MESSAGE_HANDLER(on_message_close);
         DECLARE_MESSAGE_HANDLER(OnUserMessage);
         DECLARE_MESSAGE_HANDLER(OnFrameworkV033Command);
         bool OnMixerExit();
         bool OnToolsOptions();


      };


   } // namespace audio_mixer_user_base


} // namespace multimedia




