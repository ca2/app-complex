#include "framework.h"



namespace mediaplaylist
{


   const LPARAM document::LHINT_FRAMEDOWN    = 1001;
   const LPARAM document::LHINT_FRAMEUP      = 1002;


   info::info()
   {
      m_pdocument       = nullptr;
      m_iCurrentSong    = -1;
      m_ehint           = id_play_if_not_playing;
      m_bMakeVisible    = true;
      m_bFadeIn         = false;

   }

   info::~info()
   {
   }

   document::data::data(::particle * pparticle):
      object(pparticle),
      m_xmldoc(pparticle)
   {
      m_xmldoc.get_root()->set_name("playlist");
      m_pxmledit              = ___new ::xml::edit(this);
      m_xmldoc.m_pedit        = m_pxmledit;
      m_pxmledit->m_spdata    = &m_xmldoc;

      m_pnodePlaylist   = nullptr;
      m_pnodeCurrent    = nullptr;

   }

   void document::data::delete_contents()
   {
      m_pnodePlaylist.release();
      m_pnodeCurrent.release();
      //m_pxmledit.release();
      m_pxmledit->erase_all();
      m_iCurrentSong = -1;
      m_xmldoc.close();
      m_setFile.erase_all();
   }

   document::data & document::data::operator = (const data & data)
   {

      m_path            = data.m_path;
      m_xmldoc          = data.m_xmldoc;
      m_setFile         = data.m_setFile;
      m_pnodePlaylist   = nullptr;
      m_pnodeCurrent    = nullptr;
      //m_pxmledit        = nullptr;
      m_iCurrentSong    = data.m_iCurrentSong;

      ensure_playlist();

      return *this;
   }

   document::data::~data()
   {
   }

   document::document(::particle * pparticle) :
      ::object(pparticle),
      ::data::data_container_base(pparticle),
      ::user::document(pparticle),
      m_impact(pparticle),
      m_play(pparticle)
   {


   }

   bool document::on_new_playlist()
   {

      m_filepath = papp->mediaplaylist()->get_new_playlist_path();

      m_pathFile = m_filepath;

      m_impact.delete_contents();

      delete_contents();

      file()->put_contents(m_pathFile,"");

      on_open_document(m_pathFile);

      //on_save_document(m_filepath);

      informationf("file path is %s",m_filepath);

      update_all_impacts(nullptr,5000);

      return true;

   }


   bool document::on_new_document()
   {

      m_impact.delete_contents();

      delete_contents();

      ::file::path path;

      papp->mediaplaylist()->GetDefaultPath(path);

      m_pathFile = path;

      {

         file_pointer file = file()->get_file(path,::file::e_open_binary | ::file::e_open_read_write | ::file::e_open_no_truncate | ::file::e_open_create | ::file::e_open_defer_create_directory);

      }

      return on_open_document(path);




      return true;
   }

   document::~document()
   {
   }

   void document::on_final_release()
   {
      // When the last object for an automation object is released
      // on_final_release is called.  The base class will automatically
      // deletes the object.  add additional cleanup required for your
      // object before calling the base class.

      ::user::document::on_final_release();
   }


#ifdef _DEBUG
   void document::assert_ok() const
   {
      ::user::document::assert_ok();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }
#endif //_DEBUG

   bool document::on_save_document(::payload payloadFile)
   {

      if(m_play.m_path.has_character())
      {

         string strPlay = m_play.m_xmldoc.get_xml();

         file()->put_contents(m_play.m_path,strPlay);

      }

      if(m_impact.m_path.has_character() && m_impact.m_path != m_play.m_path)
      {

         string strImpact = m_impact.m_xmldoc.get_xml();

         file()->put_contents(m_impact.m_path,strImpact);

      }

      return true;

   }

   void document::write(stream & outputstream)
   {

      //string str;

      //if(m_filepath == m_play.m_path)
      //{
      //
      //   str = m_play.m_xmldoc.get_xml();

      //}
      //else
      //{

      //   str = m_impact.m_xmldoc.get_xml();

      //}

      //outputstream.seek_to_begin();

      //outputstream.write(str);

   }

   void document::read(stream & inputstream)
   {

      ::text_stream_string_buffer is;

      is.transfer_from(inputstream);

      m_impact.m_path = m_pathFile;

      m_impact.m_xmldoc.load(is.str());

   }


   bool document::has_next_song()
   {
      if(get_current_playlist_song_count() <= 0)
         return false;
      if(m_play.is_loop())
         return true;
      if(get_current_queue_song_count() <= 0)
         return false;
      return true;
   }

   bool document::get_songs(string_array_base & stra, bool bEditingPlaylist)
   {

      if(bEditingPlaylist)
      {

         if(m_impact.m_pnodePlaylist == nullptr)
            return false;

         m_impact.m_pnodePlaylist->get_child_attr_value(stra,"song","path",m_impact.is_recursive() ? -1 : 1);

      }
      else
      {

         if(m_play.m_pnodePlaylist == nullptr)
            return false;

         m_play.m_pnodePlaylist->get_child_attr_value(stra,"song","path",m_play.is_recursive() ? -1 : 1);



      }

      return true;
   }

   bool document::get_song_current_queue(string_array_base & stra, bool bEditingPlaylist)
   {
      string_array_base straTotal;
      get_songs(straTotal, bEditingPlaylist);
      for(int i = 0; i < m_iaQueue.get_count(); i++)
      {
         stra.add(straTotal[m_iaQueue[i]]);
      }
      return true;
   }

   ::collection::index document::get_current_song(bool bEditingPlaylist)
   {
      if(bEditingPlaylist)
         return m_impact.m_iCurrentSong;
      else
         return m_play.m_iCurrentSong;
   }

   bool document::play(info * pinfo)
   {

      if(m_play.m_path != m_impact.m_path)
      {

         m_play = m_impact;

      }


      string str;

      if (pinfo->m_context.is_user_source()
            || pinfo->m_ehint == id_do_play
            || (pinfo->m_ehint == id_play_if_not_playing && (get_player() == nullptr || !get_player()->is_playing())))
      {

         populate_queue(pinfo->m_iCurrentSong);

      }

      ::collection::index iSong = -1;

      if (get_player() == nullptr)
         return false;

      e_play eplay;

      while(true)
      {

         if(!pick_a_song(iSong, str))
            return false;

         if(m_play.m_setFile[str].is_empty())
            m_play.m_setFile[str] = str;

         pinfo->m_strFilePath = m_play.m_setFile[str];

         pinfo->m_pdocument = this;

         eplay = get_player()->PlaylistPlay(pinfo);

         if(eplay == play_success)
         {

            auto pupdate = new_update();
            update = ::update::HintCurrentSong;
            update_all_impacts(ptopic);


            m_play.set_string("current_playlist",m_play.m_xmldoc.get_root()->get_child_simple_attr_path(m_play.m_pnodePlaylist, "name"));

            m_play.set_string("current_node",m_play.m_pnodePlaylist->get_child_simple_attr_path(m_play.m_pnodeCurrent, "name"));

            m_play.set_int("current_song", iSong);

            m_play.set_int("current_song_position", 0);

            if(IsDefaultPlaylist())
            {

               DoDefaultPlaylistSave();

            }

            return true;

         }
         else if(eplay != play_error_continue)
         {

            return false;

         }

      }

      return false;

   }

   void document::defer_restart_on_was_playing()
   {

      //bool bWasPlaying = false;

      papp->mediaplaylist()->load_startup();

      //papp->mediaplaylist()->datastream()->get("was_playing",bWasPlaying);

      if(papp->mediaplaylist()->m_startup.m_bWasPlaying)
      {

         restart(::e_source_user, true);

      }
      else
      {

         get_impact()->get_top_level()->m_uchAlpha  = 255;

      }

   }


   void document::restartconst ::context & context, bool bFadeIn)
   {

      auto pdocument = papp->mediaplaylist()->GetDefaultPlaylist();

      ::file::path path;

      papp->mediaplaylist()->GetDefaultPath(path);

      pdocument->on_open_document(path);

      info info;

      //papp->mediaplaylist()->GetDefaultPlaylist();

      info.m_position.m_number   = m_impact.get_int("current_song_position",0);
      info.m_iCurrentSong        = m_impact.get_int("current_song",0);;
      info.m_ehint               = id_play_if_not_playing;
      info.m_bMakeVisible        = true;
      info.m_context       += ::e_source_user;

      if(bFadeIn && m_impact.get_int("current_song_position",0)> 0)
      {

         ::pointer<::mediaplay::document>pmediadoc = papp->mediaplay()->get_document_template()->get_document();

         if(pmediadoc != nullptr)
         {

            ::pointer<::mediaplay::impact_interface>pimpact = pmediadoc->get_typed_impact < ::mediaplay::impact_interface >();

            pimpact->StartFadeIn(&info);

         }
         else
         {

            play(&info);

         }

      }
      else
      {

         play(&info);

      }

   }

   void document::OnPlay()
   {
      info info;
      info.m_iCurrentSong     = get_current_song(true);
      info.m_ehint            = id_do_play;
      info.m_bMakeVisible     = true;
      play(&info);
   }

   bool document::AddSong(LPINT lpiaSongs, ::collection::count iSongCount, bool bDoPlay, bool bMakeVisible)
   {

      bool bFirst = bDoPlay;

      for(::collection::index i = 0; i < iSongCount; i++)
      {
         AddSong(lpiaSongs[i], bFirst, bMakeVisible, false);
         //        if(pSongsSet->FindCode(lpiaSongs[i]))
         //      {
         //        pSongsSet->GetData(3);
         //      string str(pSongsSet->m_bstrPath);
         //    AddSong(str, bFirst, bMakeVisible, false);
         //  bFirst = false;
         //}
      }
      update_all_impacts(nullptr);

      OnAddSong();

      return true;

   }


   bool document::AddSong(::payload payloadFile, EAddSong eaddsong, bool bMakeVisible, bool bUpdateAllImpacts)
   {
      __UNREFERENCED_PARAMETER(bUpdateAllImpacts);
      string strPathName;
      if(payloadFile.get_type() == ::e_type_property_set && payloadFile.propset()["url"].get_string().has_character())
      {
         strPathName = payloadFile.propset()["url"];
      }
      else if(payloadFile.cast < ::file::file > () != nullptr)
      {
         strPathName = pdatetime->international().get_gmt_date_time() + "." + get_document_template()->m_set["default_extension"];
      }
      else
      {
         strPathName = payloadFile;
      }
      m_impact.m_setFile[strPathName] = payloadFile;

      m_impact.ensure_playlist();

      ::pointer<::xml::node>pnodeSong = m_impact.m_pnodeCurrent->add_child("song");

      pnodeSong->add_attr("path", strPathName);

      switch(eaddsong)
      {
      case AddSongOnly:
         break;
      case AddSongAndPlay:
      case AddSongAndPlayIfNotPlaying:
      {
         info info;
         info.m_iCurrentSong  = m_impact.m_pnodeCurrent->get_children_count("song") - 1;
         info.m_pdocument     = this;
         info.m_bMakeVisible  = bMakeVisible;
         switch(eaddsong)
         {
         case AddSongAndPlay:
            info.m_ehint      = id_do_play;
            break;
         case AddSongAndPlayIfNotPlaying:
            info.m_ehint      = id_play_if_not_playing;
            break;
         default:
            break;
         }

         play(&info);

      }
      break;
      default:
         ASSERT(false);
         return false;
      }

      update_all_impacts(nullptr, 1);

      OnAddSong();

      return true;

   }


   bool document::AddSong(::collection::index nSong, bool bDoPlay, bool bMakeVisible, bool bUpdateAllImpacts)
   {

      __UNREFERENCED_PARAMETER(nSong);
      __UNREFERENCED_PARAMETER(bDoPlay);
      __UNREFERENCED_PARAMETER(bMakeVisible);
      __UNREFERENCED_PARAMETER(bUpdateAllImpacts);

      return false;


      //   CVMSApp * pApp = (CVMSApp *) System;
      //   ASSERT(pApp != nullptr);
      //  db_server* pDataCentral = db();
      //ASSERT(pDataCentral != nullptr);
      //   CDBSongSet * pSongsSet = pDataCentral->GetSongsSet();
      //ASSERT(pSongsSet != nullptr);

      //    if(!pSongsSet->FindCode(nSong))
      //      return false;

      //pSongsSet->GetData(3);
      //   string str(pSongsSet->m_bstrPath);
      //   return AddSong(str, bDoPlay, bMakeVisible, bUpdateAllImpacts);


   }

   bool document::AddSong(string_array_base  & stra, bool bDoPlay, bool bMakeVisible)
   {
      //DBCentralInterface * pDataCentral = db();
      //ASSERT(pDataCentral != nullptr);

      bool bFirst = bDoPlay;

      for(int i = 0; i < stra.get_size(); i++)
      {
         AddSong(stra.element_at(i), bFirst ? (bDoPlay ? AddSongAndPlay : AddSongOnly) : AddSongOnly, bMakeVisible, false);
         //        if(pSongsSet->FindCode(lpiaSongs[i]))
         //      {
         //        pSongsSet->GetData(3);
         //      string str(pSongsSet->m_bstrPath);
         //    AddSong(str, bFirst, bMakeVisible, false);
         //  bFirst = false;
         //}
      }
      update_all_impacts(nullptr);

      OnAddSong();

      return true;

   }

   void document::delete_contents()
   {
      m_iaQueue.erase_all();
      m_iCurrentPlaylistSongCount = -1;
      m_straQueue.erase_all();
   }

   bool document::on_open_document(const ::payload & payloadFile)
   {

      m_impact.delete_contents();

      delete_contents();

      m_pathFile = payloadFile;

      if (!::user::document::on_open_document(payloadFile))
         return false;


      papp->mediaplaylist()->datastream()->set("default_playlist",payloadFile.get_string());
      m_impact.ensure_playlist();
      update_all_impacts(nullptr,  0, nullptr);
      update_all_impacts(nullptr,5000,nullptr);
      return true;
   }

   void document::on_close_document()
   {
      if(IsDefaultPath())
      {
         papp->mediaplaylist()->OnCloseDefaultPlaylist();
      }
      ::user::document::on_close_document();
   }

   bool document::save_modified()
   {
      ::pointer<mediaplaylist::media_playlist>pplaylistcentral = papp->mediaplaylist();
      ::file::path wstrDefault;
      pplaylistcentral->GetDefaultPath(wstrDefault);
      if(IsDefaultPath())
         return do_save(wstrDefault, true);
      return ::user::document::save_modified();
   }

   void document::update_title()
   {
      ::pointer<mediaplaylist::media_playlist>pplaylistcentral = papp->mediaplaylist();
      ::file::path wstrDefault;
      pplaylistcentral->GetDefaultPath(wstrDefault);
      if(IsDefaultPath())
      {
         string str;
         //      str.load_string(IDS_DEFAULT_PLAYLIST_TITLE);
         set_title(str);
      }
   }

   /*bool document::Play(bool bDoPlay, int iOffset, bool bLoop)
   {

      string wstrPath;
      //   bool bOpen = false;
      int iSong = m_iCurrentSong;
      int iNextSong;
      while(PeekSongPath(wstrPath, iOffset, bLoop))
      {
         iNextSong = m_iCurrentSong;
         if(iNextSong == iSong)
            break;
         try
         {
            info info;

            info.m_iCurrentSong  = iNextSong;
            info.m_ehint         = bDoPlay ? mediaplaylist::SetCurrentSongHintDoPlay : mediaplaylist::SetCurrentSongHintPlayIfNotPlaying;
            info.m_bMakeVisible  = true;
            info.m_position      = 0;

            SetCurrentSong(&info);

         }
         catch(...)
         {
            continue;
         }
         break;
      }

      return false;


   }*/

   ::collection::count document::get_song_count(bool bEditingPlaylist)
   {
      string_array_base stra;
      get_songs(stra, bEditingPlaylist);
      return stra.get_size();
   }

   bool document::get_song_at(::file::path & str, ::collection::index iSong, bool bEditingPlaylist)
   {

      string_array_base stra;

      get_songs(stra, bEditingPlaylist);

      if(stra.get_size() <= 0)
         return false;

      if(iSong < 0)
         return false;

      if(iSong >= stra.get_size())
         return false;

      str = stra[iSong];

      return true;
   }

   void document::populate_queue(::collection::index iSong)
   {

      string_array_base stra;

      get_songs(stra, false);

      if(iSong < 0)
         iSong = 0;

      if(iSong >= stra.get_size())
         iSong = 0;

      if(iSong >= stra.get_size())
         return;

      m_iaQueue.erase_all();

      bool bShuffle = false;

      if(m_play.m_xmldoc.get_root()->get_attr("shuffle", bShuffle) && bShuffle)
         iSong = 0;

      ::papaya::array::populate(m_iaQueue, iSong, stra.get_upper_bound(), (index) 1, true, true, true);

      if(bShuffle)
      {

         if(m_iaQueue.contains(iSong))
         {
            // maintains iSong the first song in queue;
            m_iaQueue.erase(iSong);
            ::papaya::array::randomize(m_iaQueue);
            m_iaQueue.insert_at(0, iSong);
         }
         else
         {
            ::papaya::array::randomize(m_iaQueue);
         }

      }

   }

   bool document::pick_a_song(::collection::index & iSong, string & str)
   {

      string_array_base stra;

      get_songs(stra, false);

      if(stra.get_count() <= 0)
         return false;

      if(m_iaQueue.get_count() <= 0)
      {
         bool bLoop = true;
         if(m_play.m_xmldoc.get_root()->get_attr("loop", bLoop) && bLoop)
            return false;
         populate_queue(0);
      }

      if(m_iaQueue.get_size() <= 0)
         return false;

      iSong = m_iaQueue[0];

      m_play.m_iCurrentSong = iSong;

      m_iaQueue.erase_at(0);

      str = stra[iSong];

      return true;

   }

   void document::data::set_flag(const ::scoped_string & scopedstr, bool bFlag)
   {

      m_xmldoc.get_root()->set_attr(scopedstr,bFlag);

   }

   bool document::data::get_flag(const ::scoped_string & scopedstr, bool bDefault)
   {
      bool bFlag;
      if(!m_xmldoc.get_root()->get_attr(scopedstr,bFlag))
         return bFlag;
   }

   void document::data::set_int(const ::scoped_string & scopedstr, long long iValue)
   {
      m_xmldoc.get_root()->set_attr(scopedstr, iValue);
   }

   long long document::data::get_int(const ::scoped_string & scopedstr, long long iDefault)
   {
      int iValue;
      if(!m_xmldoc.get_root()->get_attr(scopedstr,iValue))
         return iDefault;
      return iValue;
   }

   void document::data::set_string(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrValue)
   {
      m_xmldoc.get_root()->set_attr(scopedstr, pszValue);
   }

   string document::data::get_string(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrDefault)
   {
      string strValue;
      if(!m_xmldoc.get_root()->get_attr(scopedstr, strValue))
         return pszDefault;
      return strValue;
   }

   bool document::RemoveSong(::collection::index iSong, ::pointer<::user::impact>pimpact)
   {

      if(iSong < 0)
         return false;

      if(iSong >= get_song_count(true))
         return false;


      ::xml::node * pnode = m_impact.m_pnodeCurrent->get_child_at("song", iSong, 1);

      m_impact.m_pnodeCurrent->erase_child(pnode);

      OnRemoveSong(pimpact);


      return true;
   }


   void document::OnAddSong()
   {

      OnChangeSongs();

   }

   void document::OnChangeSongs(::pointer<::user::impact>pimpact)
   {
      __UNREFERENCED_PARAMETER(pimpact);
      if(IsDefaultPlaylist())
      {
         DoDefaultPlaylistSave();
      }

      update_all_impacts(nullptr);

   }


   void document::DoDefaultPlaylistSave()
   {

      if(IsDefaultPlaylist())
      {

         DoPlaylistSave();

      }

   }


   void document::DoPlaylistSave()
   {

      on_save_document(nullptr);

   }


   bool document::IsDefaultPlaylist()
   {
      return IsDefaultPath();
   }

   void document::OnRemoveSong(::pointer<::user::impact>pimpact)
   {
      OnChangeSongs(pimpact);
   }


   bool document::IsDefaultPath(const ::file::path & lpcsz)
   {
      ::pointer<::mediaplaylist::media_playlist>mediaplaylist = papp->mediaplaylist();
      ::file::path strDefault;
      mediaplaylist->GetDefaultPath(strDefault);
      return strDefault ==  lpcsz;
   }

   bool document::IsDefaultPath()
   {
      return IsDefaultPath(get_file_path());
   }

   ::pointer<::user::impact>document::GetFirstAttachableImpact()
   {
      auto ptopic = new_action(id_get_attachable_impact);
      update_all_impacts(ptopic);
      array < ::pointer<::user::impact> ::pointer<::user::impact>>iewpa;
      update.GetAttachableImpacts(viewpa);
      if(viewpa.get_size() > 0)
         return viewpa[0];
      else
         return nullptr;

   }

   void document::Popimpacts()
   {
      auto ptopic = new_action(id_pop);
      update_all_impacts(ptopic);

   }


   void document::set_current_playlist(const ::scoped_string & scopedstrPath)
   {
      datastream()->set("current_playlist", pszPath);
   }

   string document::get_current_playlist_path()
   {
      string str;
      datastream()->get("current_playlist", str);
      return str;
   }

   string document::get_default_playlist_path()
   {
      return "playlist/default";
   }


   ::collection::count document::get_current_playlist_song_count()
   {
      return m_iCurrentPlaylistSongCount;
   }

   ::collection::count document::get_current_queue_song_count()
   {
      return m_straQueue.get_count();
   }

   bool document::data::is_recursive()
   {
      return get_flag("recursive", true);
   }

   bool document::data::is_shuffle()
   {
      return get_flag("shuffle", false);
   }

   bool document::data::is_loop()
   {
      return get_flag("loop", false);
   }

   void document::data::ensure_playlist()
   {


      if(m_pnodeCurrent == nullptr || m_pnodePlaylist == nullptr)
      {
         if(m_pnodePlaylist == nullptr)
         {
            m_pnodePlaylist = m_xmldoc.get_root()->GetChildByAttr("playlist", "name", "default");
            if(m_pnodePlaylist == nullptr)
            {
               m_pnodePlaylist = m_xmldoc.get_root()->add_child("playlist");
               m_pnodePlaylist->add_attr("name", "default");
            }
         }
         m_pnodeCurrent = m_pnodePlaylist;
      }


   }

   bool document::do_save(const ::scoped_string & scopedstrPathName, bool bReplace)
   // Save the document_interface data to a file
   // lpszPathName = path name where to save document_interface file
   // if lpszPathName is nullptr then the ::account::user will be prompted (SaveAs)
   // note: lpszPathName can be different than 'm_strPathName'
   // if 'bReplace' is true will change file name if successful (SaveAs)
   // if 'bReplace' is false will not change path name (SaveCopyAs)
   {

      on_save_document(nullptr);

      //::memory_file_pointer memfileXml(e_create);
      //::memory_file_pointer memfileEdit(e_create);

      //stream osXml(memfileXml);
      //stream osEdit(memfileEdit);

      //string strXml = m_play.m_xmldoc.get_root()->get_xml();

      //osXml.write(strXml, strXml.length());

      //osEdit.m_b64bit = true;

      //::file::array::write(osEdit, *m_play.m_pxmledit);

      //::collection::count iXmlSize = memfileXml->get_size();
      //::collection::count iEditSize = memfileEdit->get_size();

      //::memory_file * pfile;

      //bool bEdit;

      //if(string_begins_ci(scopedstrPathName, "uifs://") && iEditSize < iXmlSize)
      //{
      //   pfile = memfileEdit;
      //   bEdit = true;
      //}
      //else
      //{
      //   pfile = memfileXml;
      //   bEdit = false;
      //}

      //::payload newName = m_play.m_path;
      //::payload newName = pszPathName;
      //if (newName.is_empty() || is_new_document())
      //{
      //   ::pointer<::user::impact_system>ptemplate = get_document_template();
      //   ASSERT(ptemplate != nullptr);

      //   newName = m_filepath;
      //   if (bReplace && (newName.is_empty() || is_new_document()))
      //   {
      //      newName = m_strTitle;
      //      // check for dubious filename
      //      character_count iBad = newName.get_string().FindOneOf(":/\\");
      //      if (iBad != -1)
      //         newName = newName.get_string().left(iBad);

      //      // append the default suffix if there is one
      //      string strExt;
      //      if (ptemplate->GetDocString(strExt, ::user::impact_system::filterExt) &&
      //        !strExt.is_empty())
      //      {
      //         ASSERT(strExt[0] == '.');
      //         character_count iStart = 0;
      //         newName += strExt.Tokenize(";", iStart);
      //      }
      //   }

      //   if (!psystem->do_prompt_file_name(newName, 0 /*bReplace ? WINDOWS_DEFINITION_IDS_SAVEFILE : WINDOWS_DEFINITION_IDS_SAVEFILECOPY*/, 0 /*OFN_HIDEREADONLY | OFN_PATHMUSTEXIST */, false, ptemplate, this))
      //      return false;       // don't even attempt to save

      //}

//      wait_cursor wait(this);
//
//      if(bEdit)
//      {
//         string strName = newName.get_string();
//         newName["url"] = strName;
//         newName["xmledit"] = __allocate ::memory_file(*memfileEdit);
////         newName["xmledit"].cast < ::memory_file >()->release();
//         newName["xml"] = __allocate ::memory_file(*memfileXml);
//  //       newName["xml"].cast < ::memory_file >()->release();
//      }
//
//      if(!on_save_document(newName))
//      {
//         //if(scopedstrPathName == nullptr)
//         //{
//         //   // be sure to delete the file
//         //   try
//         //   {
//         //      file()->del(newName);
//         //   }
//         //   catch(const ::exception & e)
//         //   {
//         //      information(trace_category_appmsg, 0, "Warning: failed to delete file after failed SaveAs.\n");
//         //      ::exception_pointer esp(pe);
//         //   }
//
//         //}
//         //return false;
//      }
//
//      m_play.m_pxmledit->erase_all();
//      m_play.m_pxmledit->m_iEdit = 0;
//
//      // reset the title and change the document_interface name
//      if (bReplace)
//         set_path_name(newName);

      return true;        // success
   }


   void document::add_listener(::pointer<listener>plistener)
   {

      m_listenerspa.add(plistener);

   }


   void document::erase_listener(::pointer<listener>plistener)
   {

      m_listenerspa.erase(plistener);

   }


   void document::set_player(::pointer<::mediaplaylist::player>spplayer)
   {

      m_spplayer = spplayer;

   }


   ::pointer<::mediaplaylist::player>document::get_player()
   {

      return m_spplayer;

   }


} // namespace mediaplaylist


