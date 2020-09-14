#pragma once

namespace helloworld
{

   class CLASS_DECL_APP_SIMPLE_HELLOWORLD document :
      public ::user::document
   {
   public:


      document(::layered * pobjectContext);
	   virtual ~document();

      
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual bool on_new_document();
      virtual bool on_open_document(const var & varFile) override;

   };

} // namespace helloworld