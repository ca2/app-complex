#pragma once


namespace simple_os_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_OS_DRAG_AND_DROP document :
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
      virtual int64_t increment_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override;
      virtual int64_t decrement_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override;
#endif


   };


} // namespace simple_os_drag_and_drop















