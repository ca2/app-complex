#pragma once


namespace mediaplay
{


   class single_document_template;


   class CLASS_DECL_APP_CORE_AUDIO mediaplay:
      virtual public ::acme::department
   {
   public:


      ::type                                 m_typeDocument;
      ::type                                 m_typeFrameWnd;
      ::type                                 m_typeImpact;
      ::type                                 m_typeIPFrame;

      string                                 m_strMatter;
      ::pointer<single_document_template>   m_pimpactsystem;


      ::mediaplaylist::player *              m_pmediaplaylistplayer;


      mediaplay();
      virtual ~mediaplay();


      single_document_template * get_document_template();
      single_document_template * create_document_template();

      impact *              get_impact();


   };


} // namespace mediaplay


