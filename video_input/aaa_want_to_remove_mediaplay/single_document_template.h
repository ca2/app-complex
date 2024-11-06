#pragma once


class playlist_document;


namespace mediaplay
{


   class CLASS_DECL_APP_CORE_AUDIO single_document_template :
      virtual public user::single_document_template
   {
   public:


      playlist_document * m_pActivePlaylistDoc;


      single_document_template(const ::string & pszMatter, ::type pDocClass, ::type pFrameClass, ::type pimpactClass );
      virtual ~single_document_template();

      

      // payloadFile, bMakeVisible = true, u * puiParent = nullptr, u * puiAlloc)
      void request(::request * prequest);
      ::pointer<::user::document>OpenDocumentFileNoReserve(::payload varPathName, ::request * prequest);
      bool ReserveSong(string_array & stra, bool bDoPlay, bool bMakeVisible);
      bool ReserveSong(int iSongCode, bool bDoPlay, bool bMakeVisible);
      bool ReserveSong(::payload varPath, bool bDoPlay, bool bMakeVisible);
      bool ReserveSong(LPINT lpiaSongs, int iSongCount, bool bDoPlay, bool bMakeVisible);


   #ifdef _DEBUG
      virtual void dump(dump_context&) const;
      // void assert_ok() const override;
   #endif //_DEBUG


   };


} // namespace mediaplay



