#include "framework.h"



namespace mediaplay
{


   mediaplay::mediaplay()
   {

      m_pmediaplaylistplayer = nullptr;

   }


   mediaplay::~mediaplay()
   {

   }


   single_document_template * mediaplay::get_document_template()
   {

      return m_pimpactsystem;

   }


   single_document_template * mediaplay::create_document_template()
   {

      if (m_pimpactsystem != nullptr)
      {

         return m_pimpactsystem;

      }

      auto psingledocumenttemplate = __new(single_document_template(
                                          m_strMatter,
                                          m_typeDocument,
                                          m_typeFrameWnd,
                                          m_typeImpact));

      papp->add_document_template(psingledocumenttemplate);

      m_pimpactsystem = psingledocumenttemplate;

      return psingledocumenttemplate;

   }


   impact * mediaplay::get_impact()
   {

      single_document_template * ptemplate = get_document_template();

      if(ptemplate == nullptr)
      {

         return nullptr;

      }

      ::user::document * pdocument = ptemplate->get_document();

      if(pdocument == nullptr)
      {

         return nullptr;

      }

      impact * pimpact = pdocument->get_typed_impact < impact >();

      if(pimpact == nullptr)
      {

         return nullptr;

      }

      return pimpact;

   }


} // namespace mediaplay





