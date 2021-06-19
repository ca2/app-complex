#include "framework.h"


namespace videocapture
{


   document::document(::object * pobject) :
      object(pobject),
      ::data::data_container_base(pobject),
      ::user::document(pobject)
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

      string strPath = varFile.get_string();

      varFile["url"] = strPath;

      varFile["http_set"]["raw_http"] = purl->get_server(varFile["url"]).find_wci("ca2") < 0 || purl->query_get_param( purl->get_query(varFile["url"]), "sessid") == "noauth";
      varFile["http_set"]["disable_common_name_cert_check"] = true;

      string str;

/*      if(pview->m_prender->m_pimageImage->load_image(varFile))
      {

         get_typed_view < view >()->m_strImage = varFile["url"];

         {

            synchronous_lock slText(get_typed_view < view >() != nullptr  ? &get_typed_view < view >()->m_mutexText : nullptr);

            get_typed_view < view >()->m_strHelloMultiverse = "image:" + get_typed_view < view >()->m_strImage + "," + get_typed_view < view >()->m_strHelloMultiverse;

         }

      }
      else if(get_typed_view < ::user::plain_edit_view >() != nullptr
              && pcontext->m_papexcontext->file().exists(varFile)
              && (str = pcontext->m_papexcontext->file().as_string(varFile)).has_char())
      {

         get_typed_view < ::user::plain_edit_view >()->_001SetText(str.Left(84),::e_source_user);

      }
      else if(get_typed_view < ::userex::pane_tab_view >() != nullptr)
      {

         get_typed_view < MAIN_IMPACT);

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



} // namespace videocapture

















