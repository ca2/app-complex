#include "framework.h"

#include "aura/update.h"
//#include "app-core/multimedia/multimedia/id3.h"
#include "aqua/xml.h"
#include "xml_playlist.h"


#ifdef WINDOWS_DESKTOP

//#include <windows.h>
#include <wmsdk.h>


// http://nogeekhere.blogspot.com.br/2009/05/how-to-extracting-embedded-album-art.html

string extract_mccdi(string str)
{

   wstring wszAudioFile(str);

   bool bOK = false;

   WM_PICTURE * pPicture = nullptr;
   memory mem;

   do
   {

      comptr<IWMSyncReader> pIWMSyncReader;
      if (FAILED(WMCreateSyncReader(nullptr, 0, &pIWMSyncReader))) break;

      if (FAILED(pIWMSyncReader->Open(wszAudioFile))) break;

      comptr<IWMHeaderInfo3> pIWMHeaderInfo3;
      if (FAILED(pIWMSyncReader->QueryInterface(&pIWMHeaderInfo3))) break;

      WMT_ATTR_DATATYPE wmtDataType = WMT_TYPE_STRING;
      ::u16 wStreamNum = 0;
      ::u16 wLength = 0;
      if (FAILED(pIWMHeaderInfo3->GetAttributeByName(
                 &wStreamNum, g_wszWMMCDI, &wmtDataType, nullptr, &wLength))) break;
      if (FAILED(pIWMHeaderInfo3->GetAttributeByName(
                 &wStreamNum, g_wszWMWMContentID, &wmtDataType, nullptr, &wLength))) break;



      // pPicture = (WM_PICTURE*)::heap::management::memory(::heap::e_memory_main)->allocate(wLength);
      mem.set_size(wLength);

      if (FAILED(pIWMHeaderInfo3->GetAttributeByName(
                 &wStreamNum, g_wszWMMCDI, &wmtDataType, (::u8*)mem.get_data(), &wLength))) break;

      bOK = true;

   }
   while (false);
   wstring wstr((wchar_t *) mem.get_data(), mem.get_size() / 2);
   return wstr;

}

#endif


namespace multimedia_playlist
{


   namespace veriwell
   {


      track::track()
      {

         m_bNew = true;

      }


      track::~track()
      {

      }


      void track::initialize_multimedia_playlist_veriwell_track(::multimedia_playlist::veriwell::session * psession)
      {

         auto estatus = ::multimedia_playlist::track::initialize_multimedia_playlist_playlist(psession);

         if (!estatus)
         {

            return estatus;

         }

         return estatus;

      }


      string track::get_name()
      {

         //      if(m_strName.has_char() && (m_durationLastUpdate.elapsed() < 60 * 1000))
         //      {
         //
         //         return m_strName;
         //
         //      }

         if (m_bNew)
         {

            m_bNew = false;

            on_update();

         }

         return m_strName;



      }



      string track::get_id()
      {

         return "veriwell_track:" + as_string(m_pl->m_iIndex) + ":" + as_string(m_iIndex);

      }


      string track::get_artist()
      {

         if (m_bNew)
         {

            m_bNew = false;

            on_update();

         }

         return m_strArtist;


      }



      string track::get_album()
      {

         if (m_bNew)
         {

            m_bNew = false;

            on_update();

         }

         return m_strAlbum;


      }


      bool track::update()
      {

         string strName;

         string strAlbum;

         string strArtist;

         ::pointer<playlist>ppl = m_pl;

         if (ppl.is_set())
         {

            synchronous_lock synchronouslock(ppl->mutex());

            ::xml::node * pnode = ppl->m_pxmlplaylist->m_pnodeCurrent->get_child_at("song", m_iIndex, 1);

            if (pnode != nullptr)
            {

               pnode->find_attribute("name", strName);

               pnode->find_attribute("album", strAlbum);

               pnode->find_attribute("artist", strArtist);

            }

         }

         if (strName.has_char())
         {

            m_strName = strName;

            m_strAlbum = strAlbum;

            m_strArtist = strArtist;

         }
         else
         {

            bool bParsed = false;

            if (string_begins_ci(m_path, "http://")
                  || string_begins_ci(m_path, "https://"))
            {

               string strServer = purl->get_server(m_path);

               if (::str::find_wwci("youtube.com", strServer) >= 0
                     || ::str::find_wwci("youtu.be", strServer) >= 0)
               {

                  auto pfile = file()->get_reader(m_path);

                  auto pdecoder = papp->audiowave()->m_pdecoderset->GetNewDecoder(pfile);

                  if (pdecoder)
                  {

                     ::payload payload;

                     pdecoder->multimedia_get_attribute(id_title, payload);

                     m_strName = payload;

                  }

                  bParsed = true;

               }

            }

            if(!bParsed)
            {

               file_pointer file = file()->get_file(m_path, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none);

               if (file.is_null())
               {

                  return false;

               }

               /*

               property_set set = id3_set(file);

               m_strName = set["name"];

               m_strAlbum = set["album"];

               m_strArtist = set["artist"];

               */

            }

            if (ppl.is_set())
            {

               synchronous_lock synchronouslock(ppl->mutex());

               ::xml::node * pnode = ppl->m_pxmlplaylist->m_pnodeCurrent->get_child_at("song", m_iIndex, 1);

               if (pnode != nullptr
                  && strName != m_strName
                  && strAlbum != m_strAlbum
                  && strArtist != m_strArtist)
               {

                  pnode->set_attribute("name", m_strName);

                  pnode->set_attribute("album", m_strAlbum);

                  pnode->set_attribute("artist", m_strArtist);

                  m_pl->save();

               }

            }

         }

         if (m_strName.is_empty())
         {

            m_strName = m_path.title();

         }

         return true;

      }


      void track::on_update()
      {

         update();

      }

      bool track::load(::payload payloadFile)
      {

         m_path = payloadFile.get_file_path();

         m_strName = payloadFile.get_file_path().title();

         update();

         return true;

      }


      string track::get_path()
      {

         return m_path;

      }


   } // namespace veriwell;


} // namespace multimedia_playlist










