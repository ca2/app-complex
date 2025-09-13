#include "framework.h"

#include "aura/update.h"
#include "acme/constant/id.h"


namespace mediaplaylist
{


   player::player()
   {

      m_pplPlaying = nullptr;
      m_pplaylistdoc = nullptr;

   }

   player::~player()
   {

   }


   void player::initialize(::particle * pparticle)
   {

      auto estatus = ::mediaplaylist::listener::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      if (::is_null(papp->mediaplay()->m_pmediaplaylistplayer))
      {

         papp->mediaplay()->m_pmediaplaylistplayer = this;

      }

      return estatus;

   }


   e_play player::PlaylistPlay(info * pinfo)
   {
      __UNREFERENCED_PARAMETER(pinfo);
      return play_error_cancel;
   }

   bool player::DoesImplementSongNumber()
   {
      return false;
   }

   int player::GetSongNumber(const wchar_t * lpcwsz)
   {
      __UNREFERENCED_PARAMETER(lpcwsz);
      return -1;
   }

   void player::PlaylistPlayByIndex(::collection::index iIndex)
   {

      if (m_pplaylistdoc != nullptr)
      {

         if (m_pplaylistdoc->impact_playlist()->get_count() > 0 && iIndex < 0)
         {

            iIndex = iIndex % m_pplaylistdoc->impact_playlist()->get_count() + m_pplaylistdoc->impact_playlist()->get_count();

         }

         info info;
         info.m_iCurrentSong = iIndex;
         info.m_uHint = id_do_play;
         info.m_bMakeVisible = true;
         m_pplaylistdoc->play(&info);

      }

   }


   bool player::PlaylistPlay(::collection::index iOffset)
   {

      if (iOffset < 0)
      {

         papp->mediaplaylist()->m_bProcessingQueue = false;

      }

      if(m_pplaylistdoc != nullptr)
      {

         // going to play next song while on last song,
         // then should check for last queue
         if (iOffset == 1
               && m_pplaylistdoc->play_playlist() != nullptr
               && m_pplaylistdoc->play_playlist()->m_iCurrentSong + iOffset >= m_pplaylistdoc->play_playlist()->get_count()
               && papp->mediaplaylist()->m_straPlaylistQueue.has_elements())
         {

            papp->mediaplaylist()->m_bProcessingQueue = false;

            m_pplaylistdoc->on_open_document(papp->mediaplaylist()->m_straPlaylistQueue.pop());

            info info;
            info.m_iCurrentSong = m_pplaylistdoc->play_playlist()->m_iCurrentSong + 1;
            info.m_uHint = id_do_play;
            info.m_bMakeVisible = true;
            return m_pplaylistdoc->play(&info);

         }

         info info;
         info.m_iCurrentSong = m_pplaylistdoc->play_playlist() == nullptr ? 0 : m_pplaylistdoc->play_playlist()->m_iCurrentSong + iOffset;
         info.m_uHint = id_do_play;
         info.m_bMakeVisible = true;
         return m_pplaylistdoc->play(&info);

      }
      return false;

   }


   bool player::PlaylistPlayRandomItem()
   {

      if(m_pplaylistdoc != nullptr)
      {

         info info;
         info.m_bRandom = true;
         info.m_uHint = id_do_play;
         info.m_bMakeVisible = true;

         return m_pplaylistdoc->play(&info);

      }

      return false;

   }


   void player::OnClosePlayer()
   {

      ///if(m_pplaylistdoc != nullptr)
      //m_pplaylistdoc->set_callback(nullptr);

   }


   void player::PlaylistOnBeforeOpen()
   {
   }


   void player::playlist_on_playback_end()
   {
      PlaylistPlay(1);
   }


   bool player::is_playing()
   {
      return false;
   }


   void player::_ExecuteStop()
   {


   }


   void player::set_album_art(pointer_array < ::image::image > & imagea)
   {

      synchronous_lock sl2(mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::papaya::array::copy(m_imageaAlbum, imagea);

      m_imageaAlbum128.set_size(m_imageaAlbum.get_size());

      ::collection::index i = 0;

      for (; i < m_imageaAlbum.get_size(); i++)
      {

         if (m_imageaAlbum128[i]->is_null())
         {

            __øconstruct(m_imageaAlbum128.element_at(i));

            m_imageaAlbum128[i]->create({ 84, 90 });

         }

         m_imageaAlbum128[i]->g()->StretchBlt(
         0, 0, 90, 90,
         m_imageaAlbum[i]->g(), 0, 0,
         m_imageaAlbum[i]->width(),
         m_imageaAlbum[i]->height());

      }

   }


} // namespace mediaplaylist






