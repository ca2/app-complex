#pragma once


#include "base/user/user/document.h"


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM document :
      public ::user::document
   {
   public:


      document();
	   ~document() override;

      
	   // void assert_ok() const override;
	   // void dump(dump_context & dumpcontext) const override;

      bool on_new_document() override;
      bool on_open_document(const ::payload & payloadFile) override;


#ifdef _DEBUG
      long long increment_reference_count() override;
      long long decrement_reference_count() override;
#endif


   };


} // namespace app_complex_form



