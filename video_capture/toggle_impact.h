#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE toggle_view:
      virtual public ::user::impact,
      virtual public ::user::button
   {
   public:


      top_view *           m_ptopview;


      toggle_view();
      virtual ~toggle_view();


      void install_message_routing(::channel * pchannel) override;


      virtual void handle(::topic * ptopic, ::context * pcontext) override;


      virtual bool keyboard_focus_is_focusable();


   };


} // namespace app_complex_video_capture




