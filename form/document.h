#pragma once


namespace app_complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM document :
      public ::user::document
   {
   public:


      document();
	   ~document() override;

      
	   void assert_valid() const override;
	   void dump(dump_context & dumpcontext) const override;

      bool on_new_document() override;
      bool on_open_document(const ::payload & payloadFile) override;


#ifdef _DEBUG
      int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


   };


} // namespace app_complex_form



