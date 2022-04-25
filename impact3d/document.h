#pragma once


namespace app_complex_impact3d
{


   class CLASS_DECL_APP_COMPLEX_IMPACT3D document :
      public ::user::document
   {
   public:


      document();
	   virtual ~document();


	   void assert_ok() const override;
	   void dump(dump_context & dumpcontext) const override;

      bool on_new_document() override;
      virtual bool on_open_document(const ::payload & payloadFile) override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

      virtual ::stream& write(::stream& stream) const override;


   };


} // namespace app_complex_impact3d















