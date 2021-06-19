#pragma once


namespace videocapture
{


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE edit_view:
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      top_view * m_ptopview;


      edit_view(::object * pobject);
      virtual ~edit_view();

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual void install_message_routing(::channel * pchannel);

      DECLARE_MESSAGE_HANDLER(on_message_create);

      bool keyboard_focus_is_focusable();

      //virtual i64 add_ref(OBJ_REF_DBG_PARAMS);

      //virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);

      bool is_window_visible() override;

   };


} // namespace videocapture




