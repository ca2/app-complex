#pragma once



namespace simple_message_box
{


   class CLASS_DECL_APP_SIMPLE_BOX application :
      virtual public ::aura::application
   {
   public:


      ::payload      m_varMessage;


      application();
      ~application() override;

      virtual void on_request(::request * prequest) override;


   };


} // namespace simple_message_box



