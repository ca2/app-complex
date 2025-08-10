#include "framework.h"



namespace multimedia_playlist
{


   track::track()
   {

      m_bLoading = false;
      m_bNew = true;
      m_pl = nullptr;

   }


   track::~track()
   {


   }


   void track::initialize_multimedia_playlist_playlist(::multimedia_playlist::session * psession)
   {

      auto estatus = ::object::initialize(psession);

      if (!estatus)
      {

         return estatus;

      }

      m_psession = psession;

      return estatus;

   }


   string track::get_name()
   {

//      if(m_strName.has_character() && (m_durationLastUpdate.elapsed() < 60 * 1000))
//      {
//
//         return m_strName;
//
//      }

      if(m_bNew)
      {

         m_bNew = false;

         on_update();

      }

      return m_strName;



   }



   string track::get_id()
   {

      return "spotify_track:" + as_string(m_pl->m_iIndex) + ":" + as_string(m_iIndex);

   }


   string track::get_artist()
   {

      if(m_bNew)
      {

         m_bNew = false;

         on_update();

      }

      return m_strArtist;


   }

   string_array_base track::get_artista()
   {

      if (m_bNew)
      {

         m_bNew = false;

         on_update();

      }

      return m_straArtist;


   }

   string track::get_album()
   {

      if(m_bNew)
      {

         m_bNew = false;

         on_update();

      }

      return m_strAlbum;


   }

   string    track::get_path()
   {

      return get_uri();

   }

   string track::get_uri()
   {


      if (m_bNew)
      {

         m_bNew = false;

         on_update();

      }

      return m_strUri;

   }


   bool track::update()
   {

      return true;

   }

   void track::on_update()
   {


   }


   bool track::load(::payload payloadFile)
   {

      return false;

   }


} // namespace multimedia_playlist










