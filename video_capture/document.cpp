#include "framework.h"
#include "document.h"
#include "impact.h"
#include "application.h"


namespace app_complex_video_capture
{


   document::document()
   {

   }


   document::~document()
   {

   }


   //void document::assert_ok() const
   //{

   //   ::user::document::assert_ok();

   //}


   //void document::dump(dump_context & dumpcontext) const
   //{

   //   ::user::document::dump(dumpcontext);

   //}


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

      impact * pimpact = get_typed_impact < impact >();

      if(pimpact == nullptr)
      {

         return true;

      }


      return true;

   }


#ifdef _DEBUG


   i64 document::increment_reference_count()
   {

      return  ::user::document::increment_reference_count(REFERENCING_DEBUGGING_ARGS);

   }

   i64 document::decrement_reference_count()
   {

      return  ::user::document::decrement_reference_count(REFERENCING_DEBUGGING_ARGS);

   }


#endif


   impact * document::get_impact()
   {

      return get_typed_impact < impact >();

   }


} // namespace app_complex_video_capture

















