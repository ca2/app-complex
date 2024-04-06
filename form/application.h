#pragma once


#include "app-simple/form/application.h"
#include "core/platform/application.h"


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM application :
      virtual public ::app_simple_form::application,
      virtual public ::core::application
   {
   public:


      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


      string preferred_experience() override;
      void init_instance() override;
      void term_application() override;

      void on_request(::request * prequest) override;


#ifdef _DEBUG
      int64_t increment_reference_count() override;
      int64_t decrement_reference_count() override;
#endif


   };


} // namespace simple_form



