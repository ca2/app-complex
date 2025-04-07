#pragma once


namespace mediaplaylist
{


   class document;


   class CLASS_DECL_APP_CORE_AUDIO impact :
      virtual public ::user::split_impact,
      virtual public ::database::client
   {
   public:


      impact(::particle * pparticle);
      virtual ~impact();


      void install_message_routing(::channel * pchannel) override;

      ::pointer<::mediaplaylist::document>get_document();

      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

#ifdef _DEBUG
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
#endif


      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void on_create_split_impact();

   };


} // namespace mediaplaylist
