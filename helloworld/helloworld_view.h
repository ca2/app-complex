#pragma once


namespace helloworld
{


   class document;


   class CLASS_DECL_APP_SIMPLE_HELLOWORLD view :
      public ::user::impact
   {
   public:


      view(::layered * pobjectContext);
      virtual ~view();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void on_update(::user::impact * pimpact, ::user::e_update eupdate, ::object * pobject) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace helloworld




