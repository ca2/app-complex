#pragma once


namespace multimedia_playlist
{


   namespace veriwell
   {


      class CLASS_DECL_APP_CORE_AUDIO xml_playlist :
         virtual public ::object
      {
      public:


         xml::document                          m_xmldoc;
         ::pointer<::xml::node>                 m_pnodePlaylist;
         ::pointer<::xml::node>                 m_pnodeCurrent;
         ::pointer<::xml::edit>                 m_pxmledit;


         xml_playlist()
         {


         }


         virtual ~xml_playlist()
         {

         }

      };


   } // namespace veriwell


} // namespace multimedia_playlist



