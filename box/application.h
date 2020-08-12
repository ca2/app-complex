#pragma once



namespace simple_message_box
{


   class CLASS_DECL_APP_SIMPLE_BOX application :
      virtual public ::aura::application
   {
   public:


      var      m_varMessage;


      application();
      virtual ~application();

      virtual void on_request(::create * pcreate) override;


   };


} // namespace simple_message_box



