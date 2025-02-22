#include "framework.h"



namespace mediaplaylist
{


   media_playlist::media_playlist(::particle * pparticle) :
      ::object(pparticle)
   {

      m_bOpenPlaylist               = false;
      m_bBeforeOpenPlaylist         = false;
      m_pimpactsystem                = nullptr;
      m_pplaylistdocDefault         = nullptr;
      m_pplaylistdocCurrent         = nullptr;



   }

   media_playlist::~media_playlist()
   {

   }


   ::pointer<::mediaplaylist::document>media_playlist::OpenPlaylist(const ::string & lpszPathName, bool bMakeVisible, ::pointer<::user::interaction>uieParent)
   {

      if(m_bOpenPlaylist)
         return nullptr;

      ::pointer<::mediaplaylist::document>pdocument = nullptr;

      /*if(m_listenerspa.get_count() > 0 && !m_bBeforeOpenPlaylist)
      {

         keep <bool> keepBeforeOpenPlaylist(&m_bBeforeOpenPlaylist, true, false, true);

         for(::collection::index i = m_listenerspa.get_count() - 1; i >= 0; i--)
         {

            pdocument = m_listenerspa(i)->_001OnBeforeOpenPlaylist();

            if(pdocument != nullptr)
               return pdocument;

         }

      }*/

      keep <bool> keepOpenPlaylist(&m_bOpenPlaylist, true, false, true);

      //::pointer<::create>cc(e_create);

      //cc->m_pcommandline->m_payloadFile = lpszPathName;

      //cc->m_bMakeVisible  = bMakeVisible;

      //cc->m_puserinteractionParent = puieParent;

      if(GetDefaultPlaylist() == nullptr)
      {

         OpenDefaultPlaylist(true);

      }

      pdocument = GetDefaultPlaylist();

      pdocument->on_open_document(lpszPathName);

      // (m_pimpactsystem->request(cc));

      //if(pdocument != nullptr)
      //{

      //   //add(pdocument);

      //   auto pupdate = new_update();

      //   update = ::update::HintInitial;

      //   pdocument->update_all_impacts(ptopic);

      //}

      return pdocument;

   }


   void media_playlist::OnCloseDefaultPlaylist()
   {

   }

   ::pointer<::mediaplaylist::document>media_playlist::OpenDefaultPlaylist(bool bMakeVisible, ::pointer<::user::interaction>uieParent)
   {

      if(m_pplaylistdocDefault != nullptr)
      {

         return m_pplaylistdocDefault;

      }

      m_pplaylistdocDefault = m_pimpactsystem->open_document_file(get_app(), nullptr,bMakeVisible, puieParent);

      return m_pplaylistdocDefault;

   }


   ::pointer<::mediaplaylist::document>media_playlist::GetDefaultPlaylist()
   {
      if(m_pplaylistdocDefault != nullptr)
         return m_pplaylistdocDefault;
      return m_pplaylistdocDefault;
   }

   ::pointer<::mediaplaylist::document>media_playlist::GetNewPlaylist(bool bMakeVisible)
   {
      if(m_pplaylistdocCurrent == nullptr)
      {
         m_pplaylistdocCurrent = OpenDefaultPlaylist(bMakeVisible);
      }
      m_pplaylistdocCurrent->on_new_playlist();
      return m_pplaylistdocCurrent;
   }


   ::pointer<::mediaplaylist::document>media_playlist::GetCurrentPlaylist(bool bEmptyOk, bool bMakeVisible, ::pointer<::user::interaction>uieParent)
   {
      if(m_pplaylistdocCurrent == nullptr)
      {
         m_pplaylistdocCurrent = OpenDefaultPlaylist(bEmptyOk, bMakeVisible, puieParent);
      }
      return m_pplaylistdocCurrent;
   }

   bool media_playlist::GetDefaultPath(::file::path & str)
   {
      string strFile;

      if(datastream()->get("default_playlist",strFile) && file()->exists(strFile))
      {

         str = strFile;

         return strFile;

      }


      if(string(papp->m_dataid.id().m_psz).find("&data_source=local&") >= 0)
      {

         str = pcontext->directory()->userdata() / papp->m_strRelativeFolder / "default.playlist";

      }
      else
      {

         str = ::file::path("uifs://Music/") / papp->m_strRelativeFolder / "default_playlist.playlist";

      }

      return true;

   }


   ::file::path media_playlist::get_new_playlist_path()
   {

      ::file::path path;

      ::file::path pathFolder;

      if(!GetFolder(pathFolder))
      {

         throw ::exception(::exception("could not retrieve default media play list folder path"));

      }

      for(::collection::index i = 1; i <= (5000); i++)
      {

         path = pathFolder / "Playlist " + as_string(i) + ".playlist";

         if(!file()->exists(path))
            break;

      }

      return path;

   }
   bool media_playlist::GetFolder(::file::path & path)
   {

      if(string(papp->m_dataid.id().m_psz).find("&data_source=local&") >= 0)
      {

         path = pcontext->directory()->userdata() / papp->m_strRelativeFolder;

      }
      else
      {

         path = ::file::path("uifs://Music") / papp->m_strRelativeFolder;

      }

      return true;

   }

   bool media_playlist::GetPath(::file::listing & listing)
   {

      ::file::path pathFolder;

      if(!GetFolder(pathFolder))
      {

         return false;

      }

      listing.ls_pattern(pathFolder, "*.playlist");

      if(listing.get_count() <= 0)
      {

         ::file::path path;

         GetDefaultPath(path);

         listing.add(path);

      }

      return true;
   }

   bool media_playlist::initialize()
   {

      m_dataid = papp->m_dataid + ".multimedia.mediaplaylist";

      ::database::client::initialize_data_client(&papp->simpledb().db());

      add_factory_item <::mediaplaylist::document >();
      add_factory_item <::mediaplaylist::frame >();
      add_factory_item <::mediaplaylist::list_impact >();
      add_factory_item <::mediaplaylist::playlist_list_impact >();
      add_factory_item <::mediaplaylist::impact >();

      m_pimpactsystem = ___new user::single_document_template(
      get_app()->m_pcoreapp,
      m_strMatter,
      ::type < ::mediaplaylist::document >(),
      m_typeatomFrameWnd, // custom MDI child frame
      m_typeatomImpact);

      m_pimpactsystem->m_bQueueDocumentOpening = false;

      if(m_pimpactsystem == nullptr)
         return false;

      return true;
   }






} // namespace mediaplaylist


