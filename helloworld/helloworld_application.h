#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_SIMPLE_HELLOWORLD application :
      public ::aura::application
   {
   public:
      
      
      ::user::impact_system *       m_pdocumenttemplate;


      application();
      ~application() override;


      virtual bool initialize_application();
      virtual int32_t exit_application() override;

      virtual void on_request(::create * pcreate);


   };



} // namespace helloworld





