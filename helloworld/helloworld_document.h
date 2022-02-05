#pragma once

namespace helloworld
{

   class CLASS_DECL_APP_SIMPLE_HELLOWORLD document :
      public ::user::document
   {
   public:


      document(::object * pobject);
	   virtual ~document();

      
   #ifdef _DEBUG
	   void assert_ok() const override;
	   void dump(dump_context & dumpcontext) const override;
   #endif

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile) override;

   };

} // namespace helloworld
