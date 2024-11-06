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
      virtual void _001OnTimer(::timer * ptimer);

      void handle(::topic * ptopic, ::context * pcontext);

      void install_message_routing(::channel * pchannel) override;

      ::mediaplaylist::document * get_document();


      DECLARE_MESSAGE_HANDLER(on_message_create);
      //bool keyboard_focus_is_focusable();

      //virtual huge_integer increment_reference_count();

      //virtual huge_integer decrement_reference_count();

      //bool is_window_visible() override;

   };


} // namespace mediaplaylist





