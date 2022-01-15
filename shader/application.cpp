#include "framework.h"
#include "aura/application.h"
#include "aura/update.h"


namespace simple_shader
{


   application::application() :
      m_echeckSimple(topic(id_simple_checkbox)),
      m_echeckNoClientFrame(topic(id_no_client_frame)),
      m_strSimple(topic(id_simple_text))
   {
      
      auto pproperty1 = find_property(id_simple_checkbox);
      
      bool bCheckOk = false;
      
      if(pproperty1->m_etype == type_enum_check)
      {
         
         auto pproperty = pproperty1;
         
         if(pproperty->m_etype == type_enum_check)
         {
            
            auto & echeck = pproperty->m_echeck;
            
            if(echeck == check_undefined)
            {
               
               bCheckOk = true;
               
            }
            
         }
         
      }
      
      if(!bCheckOk)
      {
       
         output_error_message("simple_check_box is not ok");
         
      }
      
      m_ptemplateSimpleDrawingMain = nullptr;

      m_ppaneview = nullptr;

      m_strAppId = "app-simple/shader";

      m_strAppName = "app-simple/shader";

      m_strBaseSupportId = "ca2_flag";

      m_bLicense = false;

      m_bMultiverseChat = true;

      m_strMainTitle = "Simple Drawing";

   }


   application::~application()
   {

   }




   string application::get_hover_font() const
   {

      return "Helvetica";

   }


   void application::init_instance()
   {

      set_local_data();

      puser->will_use_view_hint(FONTSEL_IMPACT);

      add_factory_item <::simple_shader::document >();
      add_factory_item <::simple_shader::frame >();
      add_factory_item <::simple_shader::main_frame >();
      add_factory_item <::user::button_view >();
      add_factory_item <::simple_shader::impact >();
      add_factory_item <::simple_shader::tab_view >();

      default_toggle_check_handling(id_simple_checkbox);

      default_toggle_check_handling(id_no_client_frame);

      if (!::aura::application::init_instance())
      {

         return false;

      }

      auto pdoctemplate = __new(::user::single_document_template(
                               "main",
                               __type(document),
                               __type(main_frame),
                               __type(tab_view)));

      m_ptemplateSimpleDrawingMain = pdoctemplate;

      add_document_template(pdoctemplate);

      default_data_save_handling(id_simple_checkbox);

      default_data_save_handling(id_no_client_frame);

      default_data_save_handling(id_simple_text);

      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(false);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      m_bMultiverseChat = !is_true("no_hello_edit");

      if (m_ptemplateSimpleDrawingMain->get_document_count() == 0)
      {

         if(pcreate->m_bMakeVisible)
         {

            INFORMATION("pcreate->m_bMakeVisible");

         }
         else
         {

            INFORMATION("NOT pcreate->m_bMakeVisible");

         }

         m_ptemplateSimpleDrawingMain->do_request(pcreate);

      }

      if (is_true("wfi_maximize"))
      {

         pcreate->m_pcommandline->m_varQuery["document"].cast < document >()->get_typed_view < ::user::tab_view >()->top_level_frame()->prodevian_prepare_window_maximize();

      }

      output_debug_string("\nfinished simple_shader::on_request");

   }


   string application::preferred_experience()
   {

      return ::aura::application::preferred_experience();

   }


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   __pointer(impact) application::create_simple_shader_view(::user::impact* pimpactParent, ::user::impact_data * pimpactdata)
   {

      return pimpactParent->create_view < impact >(pimpactdata);

   }


   ::id application::translate_property_id(const ::id & id)
   {

      if(id == "simple_checkbox")
      {

         return id_simple_checkbox;

      }
      else if(id == "simple_text")
      {

         return id_simple_text;

      }

      return id;

   }


   __namespace_application_factory("app-simple/shader");


} // namespace simple_shader



