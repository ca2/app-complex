#pragma once


namespace simple_form
{


   class CLASS_DECL_APP_SIMPLE_FORM simple_form_002 :
      virtual public simple_form
   {
   public:


      __composite(::user::still)                m_pstill;
      __composite(::user::plain_edit)           m_pedit;
      __composite(::user::combo_box)            m_pcombobox;
      __composite(::user::button)               m_pbutton;


      simple_form_002();
      virtual ~simple_form_002();

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


#ifdef DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

      virtual void install_message_routing(::channel * psender) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_control_event(::user::control_event * pevent) override;


   };


} // namespace simple_form


