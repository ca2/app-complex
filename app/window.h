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


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      DECLARE_MESSAGE_HANDLER(on_message_close);
      DECLARE_MESSAGE_HANDLER(on_message_display_change);


   };


} // namespace simple_app












