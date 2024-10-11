#include "framework.h"

#include "aura/update.h"
#include "acme/constant/id.h"


inline bool is_id_used(::u64 * pinteraction, ::u64 uId)
{
   
   while(*pinteraction != INVALID_ID)
   {
      
      if(*pinteraction == uId)
      {
         
         return true;
         
      }
      
      pinteraction++;
      
   }
   
   return false;
   
}

#define IS_ID_USED(id_suffix) is_id_used(usedid(), id_##id_suffix)

namespace mediaplaylist
{


   media_playlist::media_playlist()
   {

      defer_create_synchronization();

      m_puiOwner = nullptr;

      m_bProcessingQueue = false;

      m_psessionVeriwell = nullptr;

      m_psessionSpotify = nullptr;

      m_bSimulatePlaybackEnd = false;

      m_bPendingCheckForRestartOnWasPlaying = true;

      m_bRestartFadeIn = true;

      m_bOpenPlaylist = false;

      m_bBeforeOpenPlaylist = false;

      m_pimpactsystem = nullptr;

      m_pplaylistdoc = nullptr;

      m_plistview = nullptr;

      m_typeatomFrameWnd = ::type < ::mediaplaylist::frame >();

      m_typeatomImpact = ::type < ::mediaplaylist::main_impact >();

   }


   media_playlist::~media_playlist()
   {

   }


   void media_playlist::initialize(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      __construct(m_pstartup);

      if (IS_ID_USED(songs_changed))
      {

         informationf("id_songs_changed used");

      }

      if (IS_ID_USED(invalid))
      {

         informationf("id_invalid used");

      }

      if (IS_ID_USED(filter))
      {

         informationf("id_filter used");

      }

      m_pstartup->m_bFirstLoad = false;

      return ::success;

   }


   ::multimedia_playlist::session * media_playlist::spotify()
   {

      return m_psessionSpotify;

   }


   ::mediaplaylist::document * media_playlist::OpenPlaylist(::payload payloadFile, bool bMakeVisible, ::user::interaction* puiParent, e_window_flag ewindowflag, ::atom atom)
   {

      if (m_bOpenPlaylist)
      {

         return nullptr;

      }

      ::pointer<::mediaplaylist::document>pdocument;

      KEEP(m_bOpenPlaylist);

      if (payloadFile.is_empty())
      {

         if (GetDefaultPlaylist() == nullptr)
         {

            OpenDefaultPlaylist(true);

         }

         pdocument = GetDefaultPlaylist();

         pdocument->on_open_document(payloadFile);

      }
      else
      {

         m_pimpactsystem->m_puiOwner = m_puiOwner;

         pdocument = dynamic_cast <::mediaplaylist::document *> (m_pimpactsystem->open_document_file(get_app(), payloadFile, bMakeVisible, puiParent, ewindowflag, atom));

      }

      return pdocument;

   }


   void media_playlist::OnCloseDefaultPlaylist()
   {

   }


   ::mediaplaylist::document * media_playlist::OpenDiscardPlaylist(bool bMakeVisible, ::user::interaction* puiParent, e_window_flag ewindowflag, ::atom atom)
   {

      defer_initialize();

      ::file::path path;

      if (!GetDiscardPath(path))
      {

         return nullptr;

      }

      if (!file()->exists(path))
      {

         file()->put_contents(path, "<playlist></playlist>");

      }

      ::payload v;

      v["url"] = path;
      v["discard"] = true;

      m_pimpactsystem->m_puiOwner = m_puiOwner;

      ::mediaplaylist::document * pdocument = dynamic_cast <::mediaplaylist::document *> (m_pimpactsystem->open_document_file(get_app(), v, bMakeVisible, puiParent, ewindowflag, atom));

      if (pdocument == nullptr)
      {

         return nullptr;

      }

      return pdocument;

   }


   ::mediaplaylist::document * media_playlist::OpenDefaultPlaylist(bool bMakeVisible, ::user::interaction* puiParent, e_window_flag ewindowflag, ::atom atom)
   {

      defer_initialize();

      ::file::path path;

      if (!papp->mediaplaylist()->GetDefaultPath(path))
      {

         return nullptr;

      }

      m_pimpactsystem->m_puiOwner = m_puiOwner;

      ::mediaplaylist::document * pdocument = dynamic_cast <::mediaplaylist::document *> (m_pimpactsystem->open_document_file(get_app(), path, bMakeVisible, puiParent, ewindowflag, atom));

      if (pdocument != nullptr)
      {

         return pdocument;

      }

      m_pimpactsystem->m_puiOwner = m_puiOwner;

      pdocument = dynamic_cast <::mediaplaylist::document *> (m_pimpactsystem->open_document_file(get_app(), nullptr, bMakeVisible, puiParent, ewindowflag, atom));


      if (pdocument != nullptr)
      {

         return pdocument;

      }

      return nullptr;

   }


   ::mediaplaylist::document * media_playlist::GetDiscardPlaylist()
   {

      ::mediaplaylist::document * pdocument = OpenDiscardPlaylist(true, nullptr);

      m_pplaylistdoc = pdocument;

      return m_pplaylistdoc;


   }


   ::mediaplaylist::document * media_playlist::GetDefaultPlaylist()
   {

      ::mediaplaylist::document * pdocument = OpenDefaultPlaylist(true, nullptr);

      m_pplaylistdoc = pdocument;

      return m_pplaylistdoc;

   }


   ::mediaplaylist::document * media_playlist::GetNewPlaylist(bool bMakeVisible)
   {

      m_pimpactsystem->m_puiOwner = m_puiOwner;

      ::pointer<::mediaplaylist::document>pdocument = m_pimpactsystem->open_new_document(get_app());

      m_pplaylistdoc = pdocument;

      m_pplaylistdoc->on_new_playlist();

      return m_pplaylistdoc;

   }


   ::mediaplaylist::document * media_playlist::GetCurrentPlaylist(bool bEmptyOk, bool bMakeVisible, ::user::interaction* puiParent, e_window_flag ewindowflag, ::atom atom)
   {

      ::mediaplaylist::document * pdocument = m_pplaylistdoc;

      if (pdocument != nullptr && pdocument->impact_playlist() != nullptr && (bEmptyOk || pdocument->impact_playlist()->get_count() > 0))
      {

         m_pplaylistdoc = pdocument;

         return pdocument;

      }

      pdocument = OpenDiscardPlaylist(bMakeVisible, puiParent, ewindowflag, atom);

      if (pdocument != nullptr && pdocument->impact_playlist() != nullptr && (bEmptyOk || pdocument->impact_playlist()->get_count() > 0))
      {

         m_pplaylistdoc = pdocument;

         return pdocument;

      }

      pdocument = OpenDefaultPlaylist(bMakeVisible, puiParent, ewindowflag, atom);

      m_pplaylistdoc = pdocument;

      return pdocument;

   }


   string media_playlist::calc_default_object_id()
   {

      return "mediaplaylist::media_playlist";

   }


   ::file::path media_playlist::get_new_playlist_path()
   {

      ::file::path path;

      ::file::path pathFolder;

      if (!GetFolder(pathFolder))
      {

         throw ::exception(::exception("could not retrieve default media play list folder path"));

      }

      for (::collection::index i = 1; i <= 10000; i++)
      {

         path = pathFolder / "Playlist " + as_string(i) + ".playlist";

         if (!file()->exists(path))
            break;

      }

      return path;

   }


   bool media_playlist::GetFolder(::file::path & pathDir)
   {

      pathDir = pcontext->m_papexcontext->dir()->music() / "Music/Playlists";

      pcontext->m_papexcontext->dir()->create(pathDir);

      return true;

   }


   bool media_playlist::GetDiscardPath(::file::path & path)
   {

      path = pcontext->m_papexcontext->dir()->music() / "Music/Playlists/ca2" / "discard.playlist";

      pcontext->m_papexcontext->dir()->create(path.folder());

      return true;

   }


   bool media_playlist::GetDefaultPath(::file::path & path, bool bLocal)
   {

      path = pcontext->m_papexcontext->dir()->music() / "Music/Playlists/ca2" / "default.playlist";

      pcontext->m_papexcontext->dir()->create(path.folder());

      return true;

   }



   bool media_playlist::GetPath(::file::listing & listing)
   {

      ::file::path pathDefault;

      GetDefaultPath(pathDefault);

      listing.add(pathDefault);

      ::file::path pathDiscard;

      GetDiscardPath(pathDiscard);

      listing.add(pathDiscard);

      ::file::path pathFolder;

      GetFolder(pathFolder);

      ::file::listing l2(get_app());

      l2.ls_pattern_file(pathFolder, { "*.playlist" });

      listing.add(l2);

      return true;

   }


   bool media_playlist::initialize()
   {

      //::database::client::initialize_data_client(papp->dataserver());

      add_factory_item <::mediaplaylist::document >();
      add_factory_item <::mediaplaylist::frame >();
      add_factory_item <::mediaplaylist::list_impact >();
      add_factory_item <::mediaplaylist::playlist_list_impact >();
      add_factory_item <::mediaplaylist::impact >();
      add_factory_item <::mediaplaylist::right_impact >();
      add_factory_item <::mediaplaylist::main_impact >();
      add_factory_item <::mediaplaylist::body_impact >();
      add_factory_item <::mediaplaylist::edit_impact >();

      m_strMatter = "mediaplaylist";

      m_pimpactsystem = ::as(__new user::single_document_template(
                            m_strMatter,
                            ::type < ::mediaplaylist::document >(),
                            m_typeatomFrameWnd, // custom MDI child frame
                            m_typeatomImpact)));

      if (m_pimpactsystem == nullptr)
      {

         return false;

      }

      papp->add_document_template(m_pimpactsystem);

      return true;

   }


   ::multimedia_playlist::playlist * media_playlist::open_playlist(::payload payloadFile)
   {

      string strName = payloadFile.get_file_path();

      if (strName.case_insensitive_find("api.spotify.com/v1/search") >= 0)
      {

         if (m_plibrarySpotify.is_null() || !m_plibrarySpotify->is_opened())
         {

            return nullptr;

         }

         if (m_psessionSpotify == nullptr)
         {

            return nullptr;

         }

         string strPlaylist;

         strPlaylist = strName;

         string strName = payloadFile;

         return m_psessionSpotify->open_search(strName);

      }
      else if (strName.case_insensitive_begins_eat("spotify_playlist:"))
      {

         if (m_plibrarySpotify.is_null() || !m_plibrarySpotify->is_opened())
         {

            return nullptr;

         }

         if (m_psessionSpotify == nullptr)
         {

            return nullptr;

         }

         string strPlaylist;

         strPlaylist = string("spotify_playlist:") + strName;

         string strName = payloadFile;

         return m_psessionSpotify->open_playlist(strPlaylist);

      }

      return m_psessionVeriwell->open_playlist(payloadFile);

   }


   startup::startup() :
      m_bWasPlaying(operator[]("bWasPlaying")),
      m_strPlaylist(operator[]("strPlaylist")),
      m_strPlaylistPlaying(operator[]("strPlaylistPlaying")),
      m_pathDefault(operator[]("pathDefault"))
   {

      m_bFirstLoad = false;

   }


   //startup::~startup()
   //{

   //}


   //void startup::io(::stream & stream)
   //{

   //   stream(m_bWasPlaying);

   //   stream(m_strPlaylist);
   //   stream(m_strPlaylistPlaying);
   //   stream(propset());

   //   if (!stream.is_storing() && !stream.fail())
   //   {

   //      m_bFirstLoad = true;

   //   }

   //}


   void media_playlist::load_startup()
   {

      if (!m_pstartup->m_bFirstLoad)
      {

         if (papp->datastream()->get("mediaplaylist_startup", m_pstartup))
         {

            m_pstartup->m_bFirstLoad = true;

         }

      }

   }


   void media_playlist::save_startup()
   {

      papp->datastream()->set("mediaplaylist_startup", m_pstartup);

   }


   void media_playlist::defer_initialize()
   {

      if (m_psessionVeriwell == nullptr)
      {

         m_psessionVeriwell = __new ::multimedia_playlist::veriwell::session();

         if (m_psessionVeriwell == nullptr)
         {

            informationf("failed to allocated veriwell multimedia playlist session");

         }

      }

      if (acmefile()->exists(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->config() / "system/spotify.txt"))
      {
         if (
         (m_psessionSpotify == nullptr
          || m_pspotifywebapi == nullptr)
         &&
         (m_plibrarySpotify.is_null() || !m_plibrarySpotify->is_opened() || !m_plibrarySpotify->open_ca2_library()))
         {

            m_plibrarySpotify.create(this);

            m_plibrarySpotify->open("multimedia_playlist_spotify", false);

            if (!m_plibrarySpotify->is_opened() || !m_plibrarySpotify->open_ca2_library())
            {

               informationf("spotify multimedia playlist library could not be loaded or is not present");

            }
            else
            {

               if (m_psessionSpotify == nullptr)
               {

                  m_psessionSpotify = m_plibrarySpotify->alloc(get_app(), "session", nullptr).cast<::multimedia_playlist::session>();

                  if (m_psessionSpotify == nullptr)
                  {

                     informationf("failed to allocated spotify multimedia playlist session");

                  }

               }

               if (m_pspotifywebapi == nullptr)
               {

                  m_pspotifywebapi = m_plibrarySpotify->alloc(get_app(), "web_api", nullptr).cast<::multimedia_playlist::web_api>();

                  if (m_pspotifywebapi == nullptr)
                  {

                     informationf("failed to allocated spotify multimedia playlist session");

                  }

               }

            }

         }

      }

   }



} // namespace mediaplaylist


