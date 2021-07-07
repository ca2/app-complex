#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE toggle_view:
      virtual public ::user::impact,
      virtual public ::user::button
   {
   public:


      top_view *           m_ptopview;


      toggle_view();
      virtual ~toggle_view();


      virtual void install_message_routing(::channel * pchannel);


      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


      virtual bool keyboard_focus_is_focusable();


   };


} // namespace video_capture




