#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE edit_impact:
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      top_impact * m_ptopimpact;


      edit_impact();
      virtual ~edit_impact();

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void handle(::topic * ptopic, ::context * pcontext) override;

      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

      bool keyboard_focus_is_focusable();

      //virtual long long increment_reference_count();

      //virtual long long decrement_reference_count();

      //bool is_this_visible(::user::enum_layout elayout = ::user::e_layout_design) override;

   };


} // namespace app_complex_video_capture




