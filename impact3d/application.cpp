#include "framework.h"


namespace app_complex_impact3d
{


   application::application()
   {
      
      m_ptemplateMain = nullptr;

      m_ptemplateImpact = nullptr;

      m_ppaneimpact = nullptr;

      m_strAppId = "app-complex/impact3d";

      m_strAppName = "Complex Impact 3D";

      m_strBaseSupportId = "app-complex/impact3d";

      m_bLicense = false;

      m_bMultiverseChat = true;

      m_strMainTitle = "Complex Impact 3D";

   }


   application::~application()
   {


   }


   void application::init_instance()
   {

      set_local_data();

      ::factory::add_factory_item<::app_complex_impact3d::document >();
      ::factory::add_factory_item<::app_complex_impact3d::frame >();
      ::factory::add_factory_item<::app_complex_impact3d::main_frame >();
      ::factory::add_factory_item<::user::button_view >();
      ::factory::add_factory_item<::app_complex_impact3d::impact >();
      ::factory::add_factory_item<::app_complex_impact3d::pane_impact >();

      ::core::application::init_instance();

      auto pdoctemplate = __new(::user::single_document_template(
                               "main",
                               __type(::user::document),
                               __type(main_frame),
                               __type(pane_impact)));

      m_ptemplateMain = pdoctemplate;

      add_document_template(pdoctemplate);

      pdoctemplate = __new(::user::single_document_template(
         "main",
         __type(document),
         __type(frame),
         __type(impact)));

      m_ptemplateImpact = pdoctemplate;

      add_document_template(pdoctemplate);

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

      if (m_ptemplateMain->get_document_count() == 0)
      {

         if(pcreate->m_bMakeVisible)
         {

            INFORMATION("pcreate->m_bMakeVisible");

         }
         else
         {

            INFORMATION("NOT pcreate->m_bMakeVisible");

         }

         m_ptemplateMain->do_request(pcreate);

      }

      if (is_true("wfi_maximize"))
      {

         pcreate->m_pcommandline->payload("document").cast < document >()->get_type_impact < ::user::tab_view >()->top_level_frame()->design_window_maximize();

      }

      output_debug_string("\nfinished app_complex_impact3d::on_request");

   }


   string application::preferred_experience()
   {

      return ::core::application::preferred_experience();

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


} // namespace app_complex_impact3d



