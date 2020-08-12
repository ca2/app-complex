#pragma once


namespace simple_app
{


   class CLASS_DECL_APP_SIMPLE_APP window :
      virtual public ::user::interaction
   {
   public:


      window();
      virtual ~window();


      virtual void install_message_routing(::channel* pchannel) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnDisplayChange);


   };


} // namespace simple_app












