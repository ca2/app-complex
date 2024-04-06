#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_SIMPLE_HELLOWORLD application :
      public ::aura::application
   {
   public:
      
      
      ::user::impact_system *       m_pimpactsystem;


      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



      virtual bool initialize_application();
      virtual int32_t exit_application() override;

      virtual void on_request(::request * prequest) override;


   };



} // namespace helloworld





