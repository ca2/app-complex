#pragma once


namespace mediaplay
{

   
   class document;


   class CLASS_DECL_APP_CORE_AUDIO document_container :
      virtual public ::object
   {
   public:


      ::pointer<::mediaplay::document>       m_pmediaplaydocument;


      document_container();
      virtual ~document_container();


      virtual void set_mediaplay_document(::mediaplay::document * pdocument);


      inline ::mediaplay::document * get_mediaplay_document() { return m_pmediaplaydocument; }
          


   };


} //namespace mediaplay



