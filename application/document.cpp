#include "framework.h"


namespace simple_application
{


   document::document()
   {

   }


   document::~document()
   {

   }


   void document::assert_ok() const
   {

      ::user::document::assert_ok();

   }


   void document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

      impact * pimpact = get_typed_impact < impact >();

      if(pimpact == NULL)
      {

         return true;

      }

      return true;

   }


   long long document::increment_reference_count()
   {

      return  ::user::document::increment_reference_count();

   }


   long long document::decrement_reference_count()
   {

      return  ::user::document::decrement_reference_count();

   }


   stream& document::write(::stream& stream) const
   {

      return stream;

   }


} // namespace simple_application



