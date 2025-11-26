#pragma once


namespace user
{
   class multiple_document_template;
}


namespace mediaplaylist
{


   class document;
   class central_callback_interface;


   class CLASS_DECL_APP_CORE_AUDIO media_playlist : 
      virtual public pointer_array < listener >,
      virtual public ::database::client
   {
   public:


      ::pointer<user::single_document_template>          m_pimpactsystem;
      ::pointer<::mediaplaylist::document>               m_pplaylistdocDefault;
      ::pointer<::mediaplaylist::document>               m_pplaylistdocCurrent;
      ::type                                m_typeatomFrameWnd;
      ::type                                m_typeatomImpact;
      string                                       m_strMatter;
      bool                                         m_bOpenPlaylist;
      bool                                         m_bBeforeOpenPlaylist;


      media_playlist(::particle * pparticle);
      virtual ~media_playlist();

   
      bool initialize();


      ::pointer<::mediaplaylist::document>GetNewPlaylist(bool bMakeVisible = false);

      ::pointer<::mediaplaylist::document>GetDefaultPlaylist();
      ::pointer<::mediaplaylist::document>GetCurrentPlaylist(bool bOkEmpty, bool bMakeVisible = false, ::pointer<::user::interaction>uieParent = nullptr);

      ::pointer<::mediaplaylist::document>OpenDefaultPlaylist(bool bMakeVisible, ::pointer<::user::interaction>uieParent = nullptr);
      ::pointer<::mediaplaylist::document>OpenPlaylist(const ::string & lpcszPath, bool bMakeVisible, ::pointer<::user::interaction>uieParent = nullptr);


      void OnCloseDefaultPlaylist();
      bool GetDefaultPath(::file::path & str);
      bool GetPath(::file::listing & listing);
      bool GetFolder(::file::path & path);


      ::file::path get_new_playlist_path();

   };


} // namespace mediaplaylist

