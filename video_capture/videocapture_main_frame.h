#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE main_frame :
      virtual public simple_frame_window
   {
   public:


      bool                       m_bExplicitTranslucency;
      ::user::enum_translucency      m_etranslucency;
      view *                     m_pview;

      main_frame();
      virtual ~main_frame();

      DECLARE_MESSAGE_HANDLER(_001OnCaptureEvent);

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;
      virtual ::experience::frame * experience_get_frame();

      virtual bool has_pending_graphical_update();

   };


} // namespace video_capture












