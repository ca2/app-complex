#pragma once


namespace mediaplaylist
{


   class CLASS_DECL_APP_CORE_AUDIO edit_impact :
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      edit_impact();
      virtual ~edit_impact();

      virtual void _001OnAfterChangeText(const ::action_context & action_context);
      virtual void on_timer(::timer * ptimer);

      void handle(::topic * ptopic, ::handler_context * pcontext);

      void install_message_routing(::channel * pchannel) override;

      ::mediaplaylist::document * get_document();


      DECLARE_MESSAGE_HANDLER(on_message_create);
      //bool keyboard_focus_is_focusable();

      //virtual long long increment_reference_count();

      //virtual long long decrement_reference_count();

      //bool is_window_visible() override;

   };


} // namespace mediaplaylist





