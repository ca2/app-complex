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
      virtual bool on_open_document(const var & varFile) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif


   };


} // namespace simple_os_drag_and_drop















