#include "framework.h"



namespace mediaplay
{


   document_container::document_container() 
   {

   }

   document_container::~document_container()
   {

   }


   void document_container::set_mediaplay_document(::mediaplay::document * pdocument)
   {

      //if (!m_pmediaplaydocument)
      //{

      //   __refer(m_pmediaplaydocument, papp->mediaplay()->get_document_template()->get_document())

      //}

      __refer(m_pmediaplaydocument, pdocument);

   }



   //::mediaplay::document * document_container::get_mediaplay_document()
   //{

   //   return m_pmediaplaydocument;

   //}


} //namespace mediaplay




