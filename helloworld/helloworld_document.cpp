#include "framework.h"


namespace helloworld
{


   document::document(::object * pobject) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::document(papp)
   {


   }

   
   document::~document()
   {

   }


#ifdef _DEBUG
   
   void document::assert_valid() const
   {
	   
      ::user::document::assert_valid();

   }

   void document::dump(dump_context & dumpcontext) const
   {
	   
      ::user::document::dump(dumpcontext);

   }

#endif //_DEBUG


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(const var & varFile)
   {

      return true;

   }


} // namespace helloworld



