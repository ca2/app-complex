#pragma once


namespace mediaplay
{


   class CLASS_DECL_APP_CORE_AUDIO impact :
      virtual public ::mediaplay::impact_interface
   {
   public:


      bool                          m_bPlaylistStartupLoaded;
      bool                          m_bFranceExit;


      impact();
      virtual ~impact();

      virtual void initialize(::particle * pparticle) override;


#ifdef _DEBUG
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
#endif

      virtual ::pointer<::user::interaction>KaraokeGetWnd();

      void install_message_routing(::channel * pchannel) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void handle(::topic * ptopic, ::context * pcontext) override;
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      DECLARE_MESSAGE_HANDLER(on_http_request_response);
      // DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      //DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateImpactEncoding);
      DECLARE_MESSAGE_HANDLER(_001OnShowEncoding);

      DECLARE_MESSAGE_HANDLER(_001OnPlaylistPrevious);
      DECLARE_MESSAGE_HANDLER(_001OnUpdatePlaylistPrevious);
      DECLARE_MESSAGE_HANDLER(_001OnPlaylistNext);
      DECLARE_MESSAGE_HANDLER(_001OnUpdatePlaylistNext);

      DECLARE_MESSAGE_HANDLER(_001OnExecutePlay);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateExecutePlay);
      DECLARE_MESSAGE_HANDLER(_001OnExecuteStop);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateExecuteStop);

      DECLARE_MESSAGE_HANDLER(_001OnExecutePrevious);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateExecutePrevious);
      DECLARE_MESSAGE_HANDLER(_001OnExecuteNext);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateExecuteNext);

      DECLARE_MESSAGE_HANDLER(_001OnExecuteFirst);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateExecuteFirst);
      DECLARE_MESSAGE_HANDLER(_001OnExecuteLast);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateExecuteLast);

      DECLARE_MESSAGE_HANDLER(_001OnExecuteRoulette);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateExecuteRoulette);

      virtual void OnWavePlayerEvent(::wave::player * pplayer, ::wave::player::e_event eevent, ::wave::player_command * pcommand) override;

      document * get_document();

      virtual void _001OnTabClick(i32 iTab);

      data * get_data();
   };


} // namespace mediaplay



