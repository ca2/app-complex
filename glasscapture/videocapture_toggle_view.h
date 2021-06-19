#pragma once


namespace videocapture
{


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE toggle_view:
      virtual public ::user::impact,
      virtual public ::user::button
   {
   public:


      top_view *           m_ptopview;


      toggle_view(::object * pobject);
      virtual ~toggle_view();


      virtual void install_message_routing(::channel * pchannel);


      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


      virtual bool keyboard_focus_is_focusable();


   };


} // namespace videocapture




