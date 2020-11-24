#include "framework.h"


namespace simple_form
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


   int64_t document::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t document::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

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

      string strPath = varFile.get_file_path();


      return true;

   }




} // namespace simple_form

















