#pragma once


namespace simple_shader
{


   class CLASS_DECL_APP_SIMPLE_SHADER document :
      public ::user::document
   {
   public:


      document();
	   virtual ~document();


	   void assert_valid() const override;
	   void dump(dump_context & dumpcontext) const override;

      bool on_new_document() override;
      virtual bool on_open_document(const ::payload & varFile) override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

      virtual ::stream& write(::stream& stream) const override;


   };


} // namespace simple_shader















