#include "framework.h"


namespace simple_application
{


   document::document()
   {

   }


   document::~document()
   {

   }


   void document::assert_valid() const
   {

      ::user::document::assert_valid();

   }


   void document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(const payload & varFile)
   {

      view * pview = get_typed_view < view >();

      if(pview == NULL)
      {

         return true;

      }

      return true;

   }


   int64_t document::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return  ::user::document::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t document::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return  ::user::document::dec_ref(OBJ_REF_DBG_ARGS);

   }


   stream& document::write(::stream& stream) const
   {

      return stream;

   }


} // namespace simple_application



