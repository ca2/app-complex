#include "framework.h"


namespace simple_os_drag_and_drop
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

      string strPath = payloadFile.get_file_path();


      return true;

   }


   int64_t document::increment_reference_count()
   {

      return  ::user::document::increment_reference_count();

   }

   int64_t document::decrement_reference_count()
   {

      return  ::user::document::decrement_reference_count();

   }



} // namespace simple_os_drag_and_drop

















