#pragma once


namespace simple_os_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_OS_DRAG_AND_DROP document :
      public ::user::document
   {
   public:


      document();
	   virtual ~document();


	   virtual void assert_valid() const override;
	   virtual void dump(dump_context & dumpcontext) const override;

      virtual bool on_new_document() override;
      virtual bool on_open_document(const ::payload & varFile) override;

#ifdef DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


   };


} // namespace simple_os_drag_and_drop















