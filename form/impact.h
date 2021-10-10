#pragma once


namespace simple_form
{


   class CLASS_DECL_APP_SIMPLE_FORM impact :
      virtual public ::user::impact
   {
   public:


      impact();
      virtual ~impact();

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace simple_form


