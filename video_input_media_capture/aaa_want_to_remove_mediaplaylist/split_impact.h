#pragma once


namespace mediaplaylist
{


   class document;


   class CLASS_DECL_APP_CORE_AUDIO main_impact :
      virtual public ::user::split_impact,
      virtual public ::database::client
   {
   public:


      main_impact();
      virtual ~main_impact();


      void install_message_routing(::channel * pchannel) override;

      ::mediaplaylist::document * get_document();

      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

#ifdef _DEBUG
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
#endif


      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void on_create_split_impact() override;

   };


   class CLASS_DECL_APP_CORE_AUDIO body_impact :
      virtual public ::user::split_impact,
      virtual public ::database::client
   {
   public:


      body_impact();
      virtual ~body_impact();

      void install_message_routing(::channel * pchannel) override;

      ::mediaplaylist::document * get_document();

      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

#ifdef _DEBUG
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
#endif


      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void on_create_split_impact() override;

   };

   class CLASS_DECL_APP_CORE_AUDIO right_impact :
      virtual public ::user::split_impact,
      virtual public ::database::client
   {
   public:


      


      right_impact();
      virtual ~right_impact();


      void install_message_routing(::channel * pchannel) override;

      ::mediaplaylist::document * get_document();

      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

#ifdef _DEBUG
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
#endif


      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void on_create_split_impact() override;

   };


} // namespace mediaplaylist



