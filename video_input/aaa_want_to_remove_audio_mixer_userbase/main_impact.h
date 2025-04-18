#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class audio_mixer;
      class control;
      class destination;
      class source;


   } // namespace audio_mixer


   namespace audio_mixer_user_base
   {


      class document;
      class control_impact;


      class CLASS_DECL_APP_CORE_AUDIO main_impact :
         public ::userex::pane_tab_impact
      {
      public:


                  enum Timers
         {
            UpdateTimer = 1
         };
         enum UpdateEvents
         {
            UpdateEventTimer = 1,
            UpdateEventUpdated = 2
         };
         enum UpdateStates
         {
            UpdateStateTiming = 1,
            UpdateStateUpdating = 2
         };

         unsigned int                       m_uiUpdateTimer;
         unsigned int                       m_uiUpdateState;
         //HANDLE                     m_hThreadContextMenu;
         //unsigned int                      m_dwThreadIdContextMenu;
         bool                       m_bInitialized;
         unsigned int                       m_uiNextSliderID;
         unsigned int                      m_dwUpdateTime;
         string                     m_strSearch;
         color32_t                   m_colorForeground;
         color32_t                   m_colorBackground;
         ::draw2d::brush_pointer             m_pbrushBackground;
         ::pointer<control_impact>            m_pcontrol;

         HENHMETAFILE               m_enhmetafile;
         ENHMETAHEADER              m_emh;

         static const int cnListCount;

         main_impact();
         virtual ~main_impact();

         // void assert_ok() const override;
         // void dump(dump_context & dumpcontext) const override;

         virtual void on_create_impact(::user::impact_data * pimpactdata) override;
         void LayoutControl();


         void install_message_routing(::channel * pchannel) override;


         ::user::document * get_document();

         using ::userex::pane_tab_impact::set_title;
         void set_title();
         void delete_contents();
         //      enum_impact GetCurrentImpactIndex();


         virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
         //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);



         virtual void pre_translate_message(::message::message * pmessage) override;
         virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
         virtual bool pre_create_window(::user::system * pusersystem) override;
         virtual bool OnNotify(::user::message * pusermessage) override;

         DECLARE_MESSAGE_HANDLER(_001OnColumnclickList);
         DECLARE_MESSAGE_HANDLER(on_message_size);
         DECLARE_MESSAGE_HANDLER(on_message_destroy);
         DECLARE_MESSAGE_HANDLER(_001OnGetdispinfoList);
         DECLARE_MESSAGE_HANDLER(_001OnDblclkList);
         DECLARE_MESSAGE_HANDLER(_001OnButtonReserve);
         DECLARE_MESSAGE_HANDLER(on_message_create);
         DECLARE_MESSAGE_HANDLER(_001OnUpdateImpactUpdate);
         DECLARE_MESSAGE_HANDLER(_001OnCtlColor);
         DECLARE_MESSAGE_HANDLER(_001OnMixerSpeakerscontrols);
         DECLARE_MESSAGE_HANDLER(_001OnUpdateMixerSpeakerscontrols);
         DECLARE_MESSAGE_HANDLER(_001OnMixerWaveincontrols);
         DECLARE_MESSAGE_HANDLER(_001OnUpdateMixerWaveincontrols);
      };


   } // namespace audio_mixer_user_base


} // namespace multimedia




