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
      class control_data;


      class CLASS_DECL_APP_CORE_AUDIO control_impact :
         public ::user::impact
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

         ::pointer<control_data>    m_pdata;
         color32_t                      m_colorForeground;
         color32_t                      m_colorBackground;
         ::draw2d::brush_pointer       m_pbrushBackground;
         unsigned int                           m_uiUpdateTimer;
         unsigned int                           m_uiUpdateState;
         //HANDLE                        m_hThreadContextMenu;
         //unsigned int                           m_dwThreadIdContextMenu;
         bool                          m_bInitialized;
         unsigned int                           m_uiNextSliderID;
         unsigned int                           m_dwUpdateTime;
         string                        m_strSearch;

         static const int              cnListCount;

         
         pointer_array < ::audio_mixer::control >     m_controla;
         atom_map < ::pointer<simple_static >>               m_labelmap;


         control_impact();
         ~control_impact();


         // void assert_ok() const override;
         // void dump(dump_context & dumpcontext) const override;

         ::audio_mixer::destination * get_destination();
         ::audio_mixer::audio_mixer * get_mixer();
         ::user::document * get_document();

         control_data * get_data();
         void LayoutLine(int iSource, ::audio_mixer::source * pSource, int iStartX, int iStartY, int * iEndX, int *iEndY);
         void set_title();
         void on_layout(::draw2d::graphics_pointer & pgraphics) override;
         bool create_control(::audio_mixer::control * pControl);
         bool CreateMuteControl(::audio_mixer::control * pControl);
         bool CreateVolumeControl(::audio_mixer::control * pControl);
         void delete_contents();
         bool CreateControls(::audio_mixer::source *pSource);
         bool CreateControls();
         //      enum_impact GetCurrentImpactIndex();



         void install_message_routing(::channel * pchannel) override;

         virtual void pre_translate_message(::message::message * pmessage) override;
         virtual void OnInitialUpdate();
         virtual bool pre_create_window(::user::system * pusersystem) override;
         virtual void handle(::topic * ptopic, ::context * pcontext) override;
         virtual void OnDraw(::image::image *pimage);
         virtual bool OnNotify(::user::message * pusermessage) override;
         virtual bool OnCommand(::user::message * pusermessage) override;
         DECLARE_MESSAGE_HANDLER(_001OnColumnclickList);
         DECLARE_MESSAGE_HANDLER(on_message_size);
         DECLARE_MESSAGE_HANDLER(on_message_destroy);
         DECLARE_MESSAGE_HANDLER(_001OnGetdispinfoList);
         DECLARE_MESSAGE_HANDLER(_001OnDblclkList);
         DECLARE_MESSAGE_HANDLER(_001OnButtonReserve);
         DECLARE_MESSAGE_HANDLER(on_message_create);
         DECLARE_MESSAGE_HANDLER(_001OnUpdateImpactUpdate);
         DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
         DECLARE_MESSAGE_HANDLER(_001OnCtlColor);
         DECLARE_MESSAGE_HANDLER(on_message_scroll_x);

         //void _OnUpdate(::pointer<::user::impact>pimpact, LPARAM lhint, ::object * pupdate);

      };


   } // namespace audio_mixer_user_base


} // namespace multimedia





