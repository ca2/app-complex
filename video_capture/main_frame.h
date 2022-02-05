#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE main_frame :
      virtual public simple_frame_window
   {
   public:


      bool                       m_bExplicitTranslucency;
      ::user::enum_translucency      m_etranslucency;
      impact *                     m_pimpact;

      main_frame();
      virtual ~main_frame();

      DECLARE_MESSAGE_HANDLER(_001OnCaptureEvent);

      void install_message_routing(::channel * pchannel) override;

      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;
      virtual ::experience::frame * frame_experience();

      virtual bool has_pending_graphical_update();

   };


} // namespace app_complex_video_capture












