#include "framework.h"


namespace video_capture
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


   bool document::on_open_document(const ::payload & varFile)
   {

      view * pview = get_typed_view < view >();

      if(pview == nullptr)
      {

         return true;

      }


      return true;

   }


   i64 document::add_ref()
   {

      return  ::user::document::add_ref(OBJ_REF_DBG_ARGS);

   }

   i64 document::dec_ref()
   {

      return  ::user::document::dec_ref(OBJ_REF_DBG_ARGS);

   }



} // namespace video_capture

















