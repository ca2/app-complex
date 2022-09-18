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

      string preferred_experience() override;
      void init_instance() override;
      void term_application() override;

      void on_request(::create * pcreate) override;


#ifdef _DEBUG
      int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


   };


} // namespace simple_form



