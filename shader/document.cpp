#include "framework.h"


namespace simple_shader
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

      impact * pimpact = get_type_impact < impact >();

      if(pimpact == NULL)
      {

         return true;

      }

      string strPath = payloadFile.get_file_path();


      return true;

   }


   int64_t document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   int64_t document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   stream& document::write(::stream& stream) const
   {

      return stream;

   }


} // namespace simple_shader

















