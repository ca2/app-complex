#include "framework.h"

#include "aqua/xml.h"
#include "xml_playlist.h"


namespace multimedia_playlist
{


   namespace veriwell
   {


      playlist::playlist()
      {

         m_pxmlplaylist = ___new xml_playlist();

         defer_create_synchronization();

         m_c = 0;

         m_bNew = true;

         m_bNewTracks = true;

      }


      playlist::~playlist()
      {
         
         ::acme::del(m_pxmlplaylist);

      }


      void playlist::initialize_multimedia_playlist_veriwell_playlist(::multimedia_playlist::veriwell::session * psession)
      {

         auto estatus = ::multimedia_playlist::playlist::initialize_multimedia_playlist_playlist(psession);

         if (!estatus)
         {

            return estatus;

         }

         return estatus;

      }


      session * playlist::session()
      {

         return dynamic_cast < veriwell::session *> (m_psession);

      }


      string playlist::get_name()
      {

         if (m_bNew)
         {

            m_bNew = false;

            on_update();

         }

         return m_strName;


      }


      bool playlist::update()
      {


         m_strName = ::file::path(m_path).title();

         return true;

      }


      void playlist::on_update()
      {



      }


      void playlist::on_update_tracks()
      {

         synchronous_lock synchronouslock(this->synchronization());

         m_stra.erase_all();

         for (auto & ptrack : m_tracka)
         {

            string strId = ptrack->get_id();

            m_stra.add(strId);

         }


      }


      bool playlist::save()
      {

         if (!m_path.has_char())
         {

            return false;

         }

         string strPlay = m_pxmlplaylist->m_xmldoc.get_xml();

         file()->put_contents(m_path, strPlay);

         return true;

      }


      bool playlist::load(string strFile)
      {

         m_path = strFile;

         string strXml = file()->as_string(m_path);

         if (!m_pxmlplaylist->m_xmldoc.load(strXml))
         {

            return true;

         }

         string_array stra;

         stra = get_stra();

         m_tracka.erase_all();

         for (::collection::index i = 0; i < stra.get_size(); i++)
         {

            ::pointer<track>ptrack = m_psession->new_track();

            ptrack->m_pl = this;

            ptrack->m_iIndex = m_tracka.get_size();

            ptrack->load(stra[i]);

            m_tracka.add(ptrack);

         }

         m_strName = ::file::path(m_path).title();

         m_strTitle = ::file::path(m_path).title();

         return true;

      }

      string_array playlist::get_stra()
      {

         string_array stra;

         synchronous_lock synchronouslock(this->synchronization());

         ensure_playlist();

         if (m_pxmlplaylist->m_pnodePlaylist == nullptr)
            return stra;

         m_pxmlplaylist->m_pnodePlaylist->get_child_attr_value(stra, "song", "path", is_recursive() ? -1 : 1);

         return stra;

      }

      //stra.add(papp->mediaplaylist()->spotify()->m_straPlaylist);

      string playlist::add_song(::payload payloadFile, bool bAddDuplicate)
      {

         synchronous_lock synchronouslock(this->synchronization());

         if (!bAddDuplicate)
         {

            string_array stra;

            m_pxmlplaylist->m_pnodePlaylist->get_child_attr_value(stra, "song", "path", is_recursive() ? -1 : 1);

            auto pFind = stra.reverse_find_ci(payloadFile);

            if (::is_set(pFind))
            {

               string strId = m_tracka[iFind]->get_id();

               ::fork(get_app(), [=]()
               {

                  string_array straNew;

                  straNew.add(strId);

                  if (papp->mediaplaylist()->m_pplaylistdoc != nullptr)
                  {

                     papp->mediaplaylist()->m_pplaylistdoc->defer_update_songs(&straNew);

                  }

                  if (papp->mediaplaylist()->m_plistview != nullptr)
                  {

                     papp->mediaplaylist()->m_plistview->_001EnsureVisible(iFind);

                  }

               });

               return strId;

            }

         }

         m_setFile[payloadFile.get_file_path()] = payloadFile;

         ensure_playlist();

         ::pointer<::xml::node>pnodeSong = m_pxmlplaylist->m_pnodeCurrent->add_child("song");

         pnodeSong->set_attribute("path", payloadFile.get_file_path());

         ::pointer<track>ptrack = m_psession->new_track();

         ptrack->load(payloadFile);

         ptrack->m_pl = this;

         ptrack->m_iIndex = m_tracka.get_size();

         m_tracka.add(ptrack);

         m_bNewTracks = true;

         string strId = ptrack->get_id();

         ::fork(get_app(), [=]()
         {

            string_array straNew;

            straNew.add(strId);

            if (papp->mediaplaylist()->m_pplaylistdoc != nullptr)
            {

               papp->mediaplaylist()->m_pplaylistdoc->defer_update_songs(&straNew);

            }

            if (papp->mediaplaylist()->m_plistview != nullptr)
            {

               papp->mediaplaylist()->m_plistview->_001OnUpdateItemCount();
               papp->mediaplaylist()->m_plistview->_001EnsureVisible(ptrack->m_iIndex);

            }

         });

         return strId;


      }

      ::collection::count playlist::get_count()
      {

         return m_pxmlplaylist->m_pnodeCurrent->get_children_count("song");

      }

      bool playlist::is_recursive()
      {

         synchronous_lock synchronouslock(this->synchronization());

         return get_flag("recursive", true);

      }


      bool playlist::is_shuffle()
      {

         synchronous_lock synchronouslock(this->synchronization());

         return get_flag("shuffle", false);

      }


      bool playlist::is_loop()
      {

         synchronous_lock synchronouslock(this->synchronization());

         return get_flag("loop", false);

      }

      void playlist::set_flag(const ::string & psz, bool bFlag)
      {

         synchronous_lock synchronouslock(this->synchronization());

         m_pxmlplaylist->m_xmldoc.get_root()->set_attribute(psz, bFlag);

      }


      bool playlist::get_flag(const ::string & psz, bool bDefault)
      {

         synchronous_lock synchronouslock(this->synchronization());

         bool bFlag;

         if (!m_pxmlplaylist->m_xmldoc.get_root()->find_attribute(psz, bFlag))
         {

            return bDefault;

         }

         return bFlag;

      }


      void playlist::set_int(const ::string & psz, i64 iValue)
      {

         synchronous_lock synchronouslock(this->synchronization());

         m_pxmlplaylist->m_xmldoc.get_root()->set_attribute(psz, iValue);

      }


      i64 playlist::get_int(const ::string & psz, i64 iDefault)
      {

         synchronous_lock synchronouslock(this->synchronization());

         int iValue;

         if (!m_pxmlplaylist->m_xmldoc.get_root()->find_attribute(psz, iValue))
            return iDefault;

         return iValue;

      }


      void playlist::set_string(const ::string & psz, const ::string & pszValue)
      {

         synchronous_lock synchronouslock(this->synchronization());

         m_pxmlplaylist->m_xmldoc.get_root()->set_attribute(psz, pszValue);

      }

      string playlist::get_string(const ::string & psz, const ::string & pszDefault)
      {

         synchronous_lock synchronouslock(this->synchronization());

         string strValue;

         if (!m_pxmlplaylist->m_xmldoc.get_root()->find_attribute(psz, strValue))
            return pszDefault;

         return strValue;

      }


      bool playlist::erase_song(::collection::index iSong, bool bUpdate)
      {

         ::xml::node * pnode = m_pxmlplaylist->m_pnodeCurrent->get_child_at("song", iSong, 1);

         if (pnode == nullptr)
         {

            return "";

         }

         m_pxmlplaylist->m_pnodeCurrent->erase_child(pnode);

         m_tracka.erase_at(iSong);

         if (bUpdate)
         {

            fork([=]()
               {

                  if (papp->mediaplaylist()->m_pplaylistdoc != nullptr)
                  {

                     if (papp->mediaplaylist()->m_pplaylistdoc->play_playlist() == this)
                     {

                        papp->mediaplaylist()->m_pplaylistdoc->defer_update_songs();

                     }
                  }

               });

         }

         return true;

      }


      void playlist::ensure_playlist()
      {

         synchronous_lock synchronouslock(this->synchronization());

         if (m_pxmlplaylist->m_pnodeCurrent == nullptr || m_pxmlplaylist->m_pnodePlaylist == nullptr)
         {

            if (m_pxmlplaylist->m_pnodePlaylist == nullptr)
            {

               m_pxmlplaylist->m_pnodePlaylist = m_pxmlplaylist->m_xmldoc.get_root()->GetChildByAttr("playlist", "name", "default");

               if (m_pxmlplaylist->m_pnodePlaylist == nullptr)
               {

                  m_pxmlplaylist->m_pnodePlaylist = m_pxmlplaylist->m_xmldoc.get_root()->add_child("playlist");

                  m_pxmlplaylist->m_pnodePlaylist->set_attribute("name", "default");

               }

            }

            m_pxmlplaylist->m_pnodeCurrent = m_pxmlplaylist->m_pnodePlaylist;

         }

      }


   }


} // namespace multimedia_playlist





