#pragma once


namespace simple_application
{


   class CLASS_DECL_APP_SIMPLE_APPLICATION document :
      public ::user::document
   {
   public:


      document();
	   virtual ~document();


	   virtual void assert_valid() const override;
	   virtual void dump(dump_context & dumpcontext) const override;

      virtual bool on_new_document() override;
      virtual bool on_open_document(const payload & varFile) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif

      virtual ::stream& write(::stream& stream) const override;


   };


} // namespace simple_application















