#pragma once


namespace simple_application
{


   class CLASS_DECL_APP_SIMPLE_APPLICATION document :
      public ::user::document
   {
   public:


      document();
	   virtual ~document();


	   // void assert_ok() const override;
	   // void dump(dump_context & dumpcontext) const override;

      bool on_new_document() override;
      virtual bool on_open_document(const ::payload & payloadFile) override;

#ifdef _DEBUG
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
#endif

      virtual ::stream& write(::stream& stream) const override;


   };


} // namespace simple_application















