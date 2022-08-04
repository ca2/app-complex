#pragma once


namespace helloworld
{


   class document;


   class CLASS_DECL_APP_SIMPLE_HELLOWORLD impact :
      public ::user::impact
   {
   public:


      impact(::object * pobject);
      virtual ~impact();

      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void on_update(::user::impact * pimpact, ::user::e_update eupdate, ::object * pobject) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace helloworld




