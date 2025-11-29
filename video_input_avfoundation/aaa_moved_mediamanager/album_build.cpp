#include "framework.h"

//#include "aura/compress/zip/_.h"
//#include "axis/compress/compre.h"

#define DATABASE_FILENAME "album002.db"
#define TABLE_ALBUM_CREATE "create table album (atom integer primary key, filename varchar(128), filepath varchar (1024), title varchar (128), artist varchar (128), lastmodified text (19))"
//#define TABLE_ALBUM_CREATE "create table album (atom integer primary key, filename varchar(128), filepath varchar (1024) unique, title varchar (128), artist varchar (128), lastmodified text (128))"
#define DATASET_READ_SQL "SELECT atom, title, artist, filename, filepath, lastmodified FROM album;"

namespace mediamanager
{

   album_build::album_build()
   {

      m_wstrBuildAlbumExtensions = L"mid/midi/karaoke/st3/mk1";

      //   m_iExistFileStep = -1;
      m_iGetExStep = -1;
      m_bBuilding = false;
      m_bBuilt = false;
      



      //m_pthread = (album_build_thread *) __begin_thread(
      // typeid(album_build_thread ),
      //THREAD_PRIORITY_IDLE);

      m_pthread = nullptr;
   }


   album_build::~album_build()
   {

   }


   void album_build::initialize(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      m_pdatabase = øallocate ::sqlite::database(this);

      ::file::path str = pcontext->directory()->appdata() / "musical_players";

      pcontext->directory()->create(str);

      str = str / DATABASE_FILENAME;

      m_pdatabase->connect(str);

      //m_pdatasetRead1 = m_pdatabase->dataset();
      //m_pdatasetWrite =  m_pdatabase->dataset();
      //m_pdatasetPreBuildRead =  m_pdatabase->dataset();
      //m_pdatasetPreBuildWrite =  m_pdatabase->dataset();
      //m_pdatasetGetExRead = m_pdatabase->dataset();

      return estatus;

   }


   string album_record::Prepare(::earth::time &time)
   {
      string str;
      return time.Format(str, "%Y-%m-%d %H:%M:%S");

   }

   string album_record::Prepare(const string & lpcsz)
   {
      string str = lpcsz;
      str.replace("'", "\'");
      return str;
   }

   void album_record::Prepare(string & str, ::earth::time &time)
   {
      str = time.Format(str, "%Y-%m-%d %H:%M:%S");

   }


   bool album_record::FillFileInfo(
   ::pointer<::mediamanager::album_build>build,
   const char * lpcsz)
   {

      throw todo();
      //string str(lpcsz);

      //m_wstrArtist.empty();

      //m_wstrFilePath = lpcsz;

      //character_count iFind = str.find(".zip:");
      //if(iFind >= 0)
      //{
      //   file_pointer spfile(this);

      //   spfile->open(
      //   str.left(iFind + 4),
      //   ::file::e_open_read |
      //   ::file::e_open_share_deny_write |
      //   ::file::e_open_binary);

      //   zip::file zipfile(this);

      //   zipfile.m_pfile = spfile;

      //   void * pf = zip::api::unzip_open(&zipfile);

      //   if(pf == nullptr)
      //      return false;

      //   string str;

      //   str = str.substr(iFind + 5);

      //   if(unzLocateFile(
      //         pf,
      //         str,
      //         1) != UNZ_OK)
      //      return false;
      //   unz_file_info file_info;
      //   unzGetCurrentFileInfo(
      //   pf,
      //   &file_info,
      //   nullptr,
      //   0,
      //   nullptr, // extra Field
      //   0,
      //   nullptr, // comment
      //   0);

      //   m_storage.allocate(file_info.uncompressed_size);

      //   int iResult = unzOpenCurrentFile(pf);
      //   if(iResult != UNZ_OK)
      //      return false;


      //   unzReadCurrentFile(
      //   pf,
      //   m_storage.get_data(),
      //   (unsigned int) m_storage.get_size());

      //   iResult = unzCloseCurrentFile(pf);

      //   return FillFileInfo(
      //          build,
      //          m_storage);
      //}
      //else
      //{



      //   character_count iFind1 = str.rear_find('\\');
      //   character_count iFind2 = str.rear_find('/');
      //   character_count iFind = 0;
      //   if(iFind1 >= 0)
      //   {
      //      if(iFind2 >= 0)
      //      {
      //         if(iFind1 >= iFind2)
      //         {
      //            iFind = iFind1 + 1;
      //         }
      //         else
      //         {
      //            iFind = iFind2 + 1;
      //         }
      //      }
      //      else
      //      {
      //         iFind = iFind1 + 1;
      //      }
      //   }
      //   else
      //   {
      //      if(iFind2 >= 0)
      //      {
      //         iFind = iFind2 + 1;
      //      }
      //   }

      //   m_wstrFileName = str.substr(iFind);


      //   file_pointer spfile(this);
      //   spfile->open(
      //   lpcsz,
      //   ::file::e_open_read |
      //   ::file::e_open_share_deny_write |
      //   ::file::e_open_binary);
      //   //Archive archive(&file, CArchive::load);



      //   m_storage.transfer_from(*spfile);

      //   return FillFileInfo(build, m_storage);
      //}

   }

   bool album_record::FillFileInfo(
   ::pointer<::mediamanager::album_build>build,
   memory & storage)
   {


      __UNREFERENCED_PARAMETER(build);
      __UNREFERENCED_PARAMETER(storage);


      bool bValidRecord = false;


      return bValidRecord;

   }

   //string album_record::GetFileName(
   //   const char * lpcsz)
   //{
   //   string str(lpcsz);


   //   character_count iFind1 = str.rear_find('\\');
   //   character_count iFind2 = str.rear_find('/');
   //   character_count iFind = 0;
   //   if(iFind1 >= 0)
   //   {
   //      if(iFind2 >= 0)
   //      {
   //         if(iFind1 >= iFind2)
   //         {
   //            iFind = iFind1 + 1;
   //         }
   //         else
   //         {
   //            iFind = iFind2 + 1;
   //         }
   //      }
   //      else
   //      {
   //         iFind = iFind1 + 1;
   //      }
   //   }
   //   else
   //   {
   //      if(iFind2 >= 0)
   //      {
   //         iFind = iFind2 + 1;
   //      }
   //   }

   //   return str.substr(iFind);


   //}


   void album_build::Build(::file::listing & wstraFolder,bool bRecursive)
   {
      cslock slRead1(&m_csRead1);
      ::pointer<::sqlite::database>pdb   = m_pdatabase;
//      ::pointer<::sqlite::dataset>pdataset    = m_pdatasetWrite;

      //create Album table if necessary
      //try
      //{
      //   auto ptransaction = pdb->transaction();
      //   pdataset->query("SELECT * FROM sqlite_master where type like 'table' and name like 'album'");
      //   if (pdataset->num_rows()==0)
      //   {
      //      pdataset->exec();
      //   }
      //   ptransaction->commit();
      //}
      //catch (...)
      //{
      //   return;
      //}

      //pdataset->set_sql(::database::sql_select, "select atom, filename, filepath, title, artist from album;");
      //pdataset->set_sql(::database::sql_insert, "insert into album (atom, filename, filepath, title, artist) values (:NEW_aid,:NEW_afn,:NEW_afp,:NEW_at)");
      //pdataset->open();

      //m_pdatasetRead1->exec("PRAGMA show_datatypes=on");

      file_info fileinfo;

      if(bRecursive)
      {
         ::file::listing stra;
         RecurseFolders(stra, wstraFolder);
         FindFiles(fileinfo.m_wstraNew, fileinfo.m_timeaNew, stra);
      }
      else
      {
         FindFiles(fileinfo.m_wstraNew, fileinfo.m_timeaNew, wstraFolder);
      }

      GetExistingFiles(fileinfo.m_iaOld, fileinfo.m_wstraOld, fileinfo.m_timeaOld);


      CalcFiles(fileinfo, false);

      add(fileinfo.m_wstraAdd, fileinfo.m_timeaAdd);
      Update(fileinfo.m_wstraUpdate, fileinfo.m_timeaUpdate);
      erase(fileinfo.m_wstraRemove);

      string strSql;
      strSql = DATASET_READ_SQL;
      //m_pdatasetRead1->query(strSql);

   }

   /*void album_build::PreRestartBuild()
   {
      file_info &     fileinfo = m_fileinfo;
      sqlite::Database * pdb   = m_pdatabase;
      sqlite::database::set * pdataset    = m_pdatasetWrite;

      if(pdataset == nullptr)
      {
         debug_break();
      }
      //create Album table if necessary
      try
      {
         pdb->start_transaction();
         pdataset->query("select * from sqlite_master where type like 'table' and name like 'album'");
         if (pdataset->num_rows()==0)
         {
            pdataset->exec(TABLE_ALBUM_CREATE);
            return;
         }
         pdb->commit_transaction();
      }
      catch (...)
      {
         pdb->rollback_transaction();
         return;
      }

      //pdataset->set_select_sql("select a.atom as aid, a.filename as afn, a.filepath as afp, a.title as at, a.artist as aa from album a;");
      //pdataset->add_insert_sql("insert into album (atom, filename, filepath, title, artist) values (:NEW_aid,:NEW_afn,:NEW_afp,:NEW_at, :NEW_aa)");
      //pdataset->open();

      m_pdatasetRead->exec("PRAGMA show_datatypes=on");

      string strSql;
      strSql = DATASET_READ_SQL;
      m_pdatasetRead->query(strSql);

      GetExistingFiles(
         m_pdatasetRead,
         fileinfo.m_iaOld,
         fileinfo.m_wstraOld,
         fileinfo.m_timeaOld);

      CalcFiles(fileinfo, true);

   }*/

   bool   album_build::PreBuild(
   int &          iStep,
   bool           bRecursive,
   bool           bAddEmpty)
   {
      file_info & fileinfo           = m_fileinfo;
      ::pointer<::sqlite::database>pdb    = m_pdatabase;
//      ::pointer<::sqlite::dataset>pdataset     = m_pdatasetWrite;

      if(iStep < -1)
         return false;

      //create Album table if necessary
      //try
      //{
      //   auto ptransaction = pdb->transaction();
      //   m_pdatasetPreBuildWrite->query("select * from sqlite_master where type like 'table' and name like 'album'");
      //   if (m_pdatasetPreBuildWrite->num_rows()==0)
      //   {
      //      m_pdatasetPreBuildWrite->exec(TABLE_ALBUM_CREATE);
      //   }
      //   ptransaction->commit();
      //}
      //catch (...)
      //{
      //   iStep = -2;
      //   return false;
      //}

      //try
      //{
      //   m_pdatasetPreBuildRead->exec("PRAGMA show_datatypes=on");
      //}
      //catch(...)
      //{
      //}

      //int m_iPreBuildRowCount = m_pdatasetPreBuildRead->num_rows();
      m_wstraPreBuildFolders.erase_all();
      if(bRecursive)
      {
         RecurseFolders(m_wstraPreBuildFolders, m_wstraFolder);
      }
      else
      {
         m_wstraPreBuildFolders = m_wstraFolder;
      }

      //cslock slRead1(&m_csRead1);
      //m_pdatasetRead1->query(DATASET_READ_SQL);
      //if(m_pdatasetRead1->m_result.m_fielda.get_size() != 6)
      //{
      //   m_pdatasetRead1->m_result.m_fielda.erase_all();
      //   ::pointer<database::field>prop = m_pdatasetRead1->m_result.m_fielda.add_new(this);
      //   prop->m_strName = "id";
      //   prop->m_edatatype = database::data_type_wide_string;

      //   prop = m_pdatasetRead1->m_result.m_fielda.add_new(this);
      //   prop->m_strName = "title";
      //   prop->m_edatatype = database::data_type_wide_string;

      //   prop = m_pdatasetRead1->m_result.m_fielda.add_new(this);
      //   prop->m_strName = "artist";
      //   prop->m_edatatype = database::data_type_wide_string;

      //   prop = m_pdatasetRead1->m_result.m_fielda.add_new(this);
      //   prop->m_strName = "filename";
      //   prop->m_edatatype = database::data_type_wide_string;

      //   prop = m_pdatasetRead1->m_result.m_fielda.add_new(this);
      //   prop->m_strName = "filepath";
      //   prop->m_edatatype = database::data_type_wide_string;

      //   prop = m_pdatasetRead1->m_result.m_fielda.add_new(this);
      //   prop->m_strName = "lastmodified";
      //   prop->m_edatatype = database::data_type_wide_string;

      //}

      GetExistingFiles(fileinfo.m_iaOld, fileinfo.m_wstraOld, fileinfo.m_timeaOld);
      FindFiles(fileinfo.m_wstraNew, fileinfo.m_timeaNew, m_wstraPreBuildFolders);
      ZipFindFiles(fileinfo.m_wstraNew, fileinfo.m_timeaNew, m_wstraPreBuildFolders);

      CalcFiles(fileinfo, false);
      if(bAddEmpty)
      {
         AddEmpty(fileinfo.m_iaAdd, fileinfo.m_wstraAdd);
         fileinfo.m_iaUpdate.add(fileinfo.m_iaAdd);
         fileinfo.m_wstraUpdate.add(fileinfo.m_wstraAdd);
         fileinfo.m_timeaUpdate.add(fileinfo.m_timeaAdd);
         fileinfo.m_iaAdd.erase_all();
         fileinfo.m_wstraAdd.erase_all();
         fileinfo.m_timeaAdd.erase_all();
      }
      return true;

   }


   bool album_build::add(::file::listing & stra, time_array_base & timea)
   {

      for(int i = 0; i < stra.get_size(); i++)
      {

         add(stra[i], timea[i]);

      }

      return true;

   }


   bool album_build::AddEmpty(::int_array & ia, ::file::listing & stra)
   {

      ::pointer<::sqlite::database>pdb   = m_pdatabase;

      //::pointer<::sqlite::dataset>pdataset    = m_pdatasetWrite;

      cslock slRead1(&m_csRead1);

      int iId = 0;

      //pdataset->query("select maximum(atom) as maxid from album;");

      //if (pdataset->num_rows() > 0)
      //{

      //   iId = pdataset->field_value("maxid").as_int();

      //   iId++;

      //}

      album_record record;

      int iGroup = 1;

      string strSql;
      string str;

      database::row row;

      strSql = "insert into album (atom, filepath, filename) values ";
      auto ptransaction = pdb->transaction();
      for(int i = 0; i < stra.get_size(); i++)
      {
         for(int j = 0; j < iGroup; j++)
         {
            if(j >= 1)
               strSql += ", ";
            ia.add(iId);
            str.formatf(
            "('%d','%s', '%s')",
            iId,
            stra[i].c_str(),
            stra[i].name().c_str());
            
            strSql+= str;
            
            row.add(::payload(iId)); // atom
            row.add(::payload("")); // title
            row.add(::payload("")); // artist
            row.add(::payload(stra[i].name())); // filename
            row.add(::payload(stra[i])); // filepath
            row.add(::payload("")); // last modified
//            m_pdatasetRead1->m_result.m_rowa.add(row);

            if(stra.get_size() <= 0)
               break;
            iId++;
            row.erase_all();
         }

         //       pdataset->exec(strSql);

         strSql = "insert into album (atom, filepath, filename) values ";

      }

      ptransaction->commit();

      return true;

   }


   bool album_build::Update(::file::listing & stra, time_array_base & timea)
   {

      for(int i = 0; i < stra.get_size(); i++)
      {

         Update(stra[i], timea[i]);

      }

      return true;

   }


   bool album_build::erase(::file::listing & stra)
   {

      string strSql;

      string str;

      for(int i = 0; i < stra.get_size(); i++)
      {

         str = stra[i];

         str.replace("'","''");

         strSql.formatf("delete from album where filepath = '%s'", str.c_str());

         //m_pdatasetWrite->exec(strSql);

      }

      return true;

   }


   bool album_build::erase(::file::path & str)
   {

      string strSql;

      str =  str;

      str.replace("'","''");

      strSql.formatf("delete from album where filepath = '%s'", str.c_str());

      //m_pdatasetWrite->exec(strSql);

      return true;

   }


   bool album_build::erase(int iId)
   {

      string strSql;

      strSql.formatf("delete from album where atom = '%d'", iId);

      //m_pdatasetWrite->exec(strSql);

      return true;

   }


   bool album_build::erase(::int_array & ia)
   {

      int iGroup = 30;

      string strSql;

      string str;

      while(ia.get_size() > 0)
      {

         strSql = "delete from album where ";

         for(int i = 0; i < iGroup; i++)
         {

            if (i >= 1)
            {

               strSql += " OR ";

            }

            str.formatf("atom = '%d'", ia.last());

            ia.erase_at(ia.get_upper_bound());

            strSql += str;

            if (ia.get_size() <= 0)
            {

               break;

            }

         }

         //m_pdatasetWrite->exec(strSql);

      }

      return true;

   }


   bool album_build::add(const ::file::path & lpcsz, ::earth::time & time)
   {

//      ::pointer<::sqlite::dataset>pdataset = m_pdatasetWrite;

//      ::mediamanager::album_record & albumrecord = album_record();

      bool bValidRecord = record().FillFileInfo(this, lpcsz);

      record().m_timeLastWrite = time;

      if(bValidRecord)
      {

         AddAlbumRecord();

      }
      else
      {

         AddInvalidFile(lpcsz);

      }

      return true;

   }


   bool album_build::Update(const ::file::path & lpcsz, ::earth::time & time, int iId)
   {

//      ::pointer<::sqlite::dataset>pdataset = m_pdatasetWrite;

//      ::mediamanager::album_record & albumrecord = album_record();

      bool bValidRecord = record().FillFileInfo(this, lpcsz);

      record().m_timeLastWrite = time;

      if(bValidRecord)
      {

         UpdateAlbumRecord(iId, false, false);

      }
      else
      {

         UpdateInvalidFile(lpcsz);

      }

      return true;

   }


   ::mediamanager::album_record & album_build::record()
   {

      return *m_palbumrecord;

   }


   bool album_build::AddInvalidFile(const ::file::path & lpcsz)
   {

      __UNREFERENCED_PARAMETER(lpcsz);

      return true;

   }


   bool album_build::UpdateInvalidFile(const file::path & lpcsz)
   {

      __UNREFERENCED_PARAMETER(lpcsz);

      return true;

   }


   bool album_build::AddAlbumRecord()
   {

      //::pointer<::sqlite::database>pdb   = m_pdatabase;

      // ::pointer<::sqlite::dataset>pdataset = m_pdatasetWrite;

      ::mediamanager::album_record & albumrecord = record();

      int iId = 0;

      //pdataset->query("select maximum(atom) as maxid from album;");
      //if (pdataset->num_rows() > 0)
      //{
      //   iId = pdataset->field_value("maxid");
      //   iId++;
      //}

      //   pdb->start_transaction();

      albumrecord.GetInsertSql(iId);

      //pdataset->exec(albumrecord.m_strSql);

      //   pdb->commit_transaction();

      return true;

   }


   int album_build::AddEmptyFile(const ::file::path & lpcsz)
   {

      ::pointer<::sqlite::database>pdb   = m_pdatabase;

      album_record record;

      record.m_wstrFilePath = lpcsz;

      int iId = 0;

      //pdataset->query("select maximum(atom) as maxid from album;");
      //if (pdataset->num_rows() > 0)
      //{
      //   iId = pdataset->field_value("maxid");
      //   iId++;
      //}

      auto ptransaction = pdb->transaction();

      record.GetInsertSql(iId);

      //pdataset->exec(record.m_strSql);

      ptransaction->commit();

      return iId;

   }


   bool album_build::UpdateAlbumRecord(int iId, bool bUpdateFilePath, bool bUpdateFileName)
   {

      //      ::pointer<::sqlite::database>pdb   = m_pdatabase;
      //::pointer<::sqlite::dataset>pdataset    = m_pdatasetWrite;

      ::mediamanager::album_record & albumrecord = record();

      string strSql;

      string str;

      str = albumrecord.m_wstrFilePath;

      str.replace("'","''");

      if(iId < 0)
      {

         strSql.formatf("select atom from album where filepath='%s';", str.c_str());

         //pdataset->query(strSql);

         //ASSERT(pdataset->num_rows() == 1);

         //iId = pdataset->field_value("id");

      }

      //pdb->start_transaction();

      albumrecord.GetUpdateSql(
      iId,
      bUpdateFilePath,
      bUpdateFileName);

      //pdataset->exec(albumrecord.m_strSql);

      //pdb->commit_transaction();

      return true;

   }


   bool album_build::add(::mediamanager::album_record &albumrecord)
   {

      __UNREFERENCED_PARAMETER(albumrecord);

      return true;

   }


   void album_build::RecurseFolders(::file::listing & wstraFolder,::file::listing & wstraFolderSource)
   {

      int i;

      ::file::path str;

      //unsigned int dw = ::_getmbcp();

      for(i = 0; i < wstraFolderSource.get_size(); i++)
      {

         str = wstraFolderSource.element_at(i);

         RecurseFolders(wstraFolder, str);

      }

   }


   void album_build::RecurseFolders(::file::listing & wstraFolder,::file::path & wstrFolderSource)
   {

      wstraFolder.m_pprovider = get_app();

      wstraFolder.rls_dir(wstrFolderSource);

   }


   void album_build::FindFiles(::file::listing & wstraFile,time_array_base & timea,::file::listing & wstraFolder)
   {

      // bool ok = m_bFindFiles;

      int i, j;

      ::earth::time time;

      string str, strFormat;

      if(wstraFolder.get_size() <= 0)
      {
         //output_error_message("There are no folders for the album build.");
      }

      wstraFile.m_pprovider = get_app();

      string_array_base wstraExtension;

      str = m_wstrBuildAlbumExtensions;

      wstraExtension.add_tokens(str, "/", false);

      string strB;

      //int iIteration = 0;

      //int iIterationCount = 10;

      for(i = 0; i < wstraFolder.get_size(); i++)
      {

         for(j = 0; j < wstraExtension.get_size(); j++)
         {

            wstraFile.ls_pattern(wstraFolder[i], { "*." + wstraExtension[j] });

         }

      }

   }


   void album_build::ZipFindFiles(::file::listing & wstraFile, time_array_base & timea, ::file::listing & wstraFolder)
   {

      __UNREFERENCED_PARAMETER(wstraFile);
      __UNREFERENCED_PARAMETER(timea);
      __UNREFERENCED_PARAMETER(wstraFolder);
      //ASSERT(false);
      /*      FileFind & fileFind = m_filefindZip;
            int i, j;
            ::earth::time time;
            string str, strFormat;

            if(wstraFolder.get_size() <= 0)
            {
               //output_error_message("There are no folders for the album build.");
            }

            if(m_iZipFindFilesStep == -1 || m_iZipFindFilesStep == 0)
            {
               m_iZipFindFileIStart = 0;
               m_iZipFindFileJStart = 0;
            }

            string_array_base wstraExtension2;
            string str;
            str = m_wstrBuildAlbumExtensions;
            wstraExtension2.add_tokens(str, "/", false);

            string_array_base wstraExtension;
            wstraExtension.add("zip");
            string strB;
            string wstrPath;
            string wstrExtraPath;
            for(i = m_iZipFindFileIStart; i < wstraFolder.get_size(); i++)
            {
               m_iZipFindFileIStart = i;
               for(j = m_iZipFindFileJStart; j < wstraExtension.get_size(); j++)
               {
                  m_iZipFindFileJStart = j;
                  str = wstraFolder.element_at(i);
                  str += L"\\*.";
                  str += wstraExtension.element_at(j);
         //         UnicodeToACP(str, str);
                  bool ok;
                  ok = fileFind.FindFile(str);;
                  while(ok)
                  {
                     ok = fileFind.FindNextFile();
                     str = fileFind.GetFilePath();
                     //str.SetACP(str);
                     //UnicodeToACP(strB, str);
                     //ASSERT(str.Collate(strB) == 0);
                     {
                        file_pointer spfile(this);

                        spfile->open(str, ::file::e_open_read | ::file::e_open_binary);

                        zip::File zipfile(this);

                        zipfile.m_pfile = spfile;

                        unzFile pf = zip::api::unzipOpen(&zipfile);

                        if(pf != nullptr)
                        {
                           while(true)
                           {
                              if(unzOpenCurrentFile(pf) == UNZ_OK)
                              {
                                 const int BUFSIZE = 4096;
         //                        char szTempName[MAX_PATH];
         //                        char buffer[BUFSIZE];
                                 WCHAR lpPathBuffer[BUFSIZE];
                                 GetTempPathW(BUFSIZE,   // length of the buffer
                                    lpPathBuffer);      // buffer for path


                                  char szTitle[_MAX_PATH];

                                 unz_file_info file_info;
                                 unzGetCurrentFileInfo(
                                    pf,
                                    &file_info,
                                    szTitle,
                                    _MAX_PATH,
                                    nullptr, // extra Field
                                    0,
                                    nullptr, // comment
                                    0);



                                 wstrExtraPath = szTitle;

                                 for(int i = 0; i < wstraExtension2.get_size(); i++)
                                 {
                                    string wstrExt2 = wstraExtension2[i];
                                    string wstrEnd2;
                                    wstrEnd2 = "." + wstrExt2;
                                    if(wstrExtraPath.right(wstrEnd2.get_length()) ==
                                       wstrEnd2)
                                    {
                                       wstrPath = str + ":" + wstrExtraPath;

                                       wstraFile.add(wstrPath);
                                       //if(file_info.dosDate != nullptr)
                                       //{
                                         // ::earth::time time(HIWORD(file_info.dosDate),
                                           //          LOWORD(file_info.dosDate));
                                          //timea.add(time);
                                       //}
                                       //else
                                       {
                                          ::earth::time time(
                                             file_info.tmu_date.tm_year,
                                             file_info.tmu_date.tm_mon + 1,
                                             file_info.tmu_date.tm_mday,
                                             file_info.tmu_date.tm_hour,
                                             file_info.tmu_date.tm_min,
                                             file_info.tmu_date.tm_sec);
                                          timea.add(time);
                                       }
                                       break;
                                    }

                                 }


         //            nextFile:
                                 unzCloseCurrentFile(pf);
                              }
                              if(unzGoToNextFile(pf) != UNZ_OK)
                              {
                                 break;
                              }

                           }

                        }

                     }
                  }
                  if(m_iZipFindFilesStep >= 0)
                  {
                     m_iZipFindFilesStep++;
                     if(m_iZipFindFilesStep % 2 == 0)
                     {
                        break;
                     }
                  }
               }
               if(m_iZipFindFilesStep >= 0 && m_iZipFindFilesStep % 2 == 0)
               {
                  break;
               }
               m_iFindFileJStart = 0;
            }
            if(i >= wstraFolder.get_size())
            {
               m_iZipFindFilesStep = -1;
            }*/
   }


   void album_record::GetInsertSql(int iId)
   {

      m_strSql.formatf("insert into album (atom, filename, filepath, title, artist, lastmodified) values ('%d','%s','%s','%s','%s','%s');",
                      iId,
                      Prepare(m_wstrFileName).c_str(),
                      Prepare(m_wstrFilePath).c_str(),
                      Prepare(m_wstrTitle).c_str(),
                      Prepare(m_wstrArtist).c_str(),
                      Prepare(m_wstrLastWriteTime).c_str());

   }


   void album_record::GetUpdateSql(int iId, bool bUpdateFilePath, bool bUpdateFileName)
   {

      if(!bUpdateFilePath && !bUpdateFileName)
      {

         string str;

         Prepare(str,   m_timeLastWrite);

         m_strSql.formatf("update album set title = '%s', artist = '%s', lastmodified = '%s' where atom = '%d';",
                         Prepare(m_wstrTitle).c_str(),
                         Prepare(m_wstrArtist).c_str(),
                         str.c_str(),
                         iId);

      }
      else
      {

         string str;

         Prepare(str,   m_timeLastWrite);

         m_strSql.formatf("update album set filename = '%s', filepath = '%s', title = '%s', artist = '%s', lastmodified = '%s' where atom = '%d';",
                         Prepare(m_wstrFileName).c_str(),
                         Prepare(m_wstrFilePath).c_str(),
                         Prepare(m_wstrTitle).c_str(),
                         Prepare(m_wstrArtist).c_str(),
                         str.c_str(),
                         iId);
      }

   }


   void album_build::GetExistingFiles(::int_array & ia,  ::file::listing & straFile,   time_array_base & timea)
   {

      //::pointer<::sqlite::dataset>pdataset = m_pdatasetGetExRead;

      if(m_iGetExStep <= 0)
      {

         string strSql;

         strSql = "select atom, filepath, lastmodified from album;";

         //pdataset->query(strSql);
      }

      //GetExistingFiles(pdataset, ia, straFile, timea);

   }


   void album_build::GetExistingFiles(::pointer<::database::result_set>pset,  ::int_array & ia, ::file::listing & wstraFile, time_array_base & timea)
   {

      //::collection::count iRowCount = pset->m_rowa.get_count();

      //int iFieldIndexId = (int) pdataset->field_index("id");

      //int iFieldIndexFilePath = (int) pdataset->field_index("filepath");

      //int iFieldIndexLastModified = (int) pdataset->field_index("lastmodified");

      string strTime;
      //int iYear;
//      int iMonth;
//      int iDay;
//      int iHour;
//      int iMinute;
//      int iSecond;
      ::file::path wstrFile;

//      char * lpszTime;

//      ia.set_size(iRowCount);
//      wstraFile.set_size(iRowCount);
//      timea.set_size(iRowCount);
//
//      if(m_iGetExStep == -1)
//         m_iGetExStep = 0;
//
//      for(; m_iGetExStep < iRowCount; m_iGetExStep++)
//      {
//         int iRow = m_iGetExStep;
////         pdataset->seek(iRow);
//
//         ia.set_at(iRow, pdataset->select_field_value(iFieldIndexId));
//
//         wstrFile = pdataset->select_field_value(iFieldIndexFilePath);
//
//         wstraFile.set_at(iRow, wstrFile);
//
//         strTime = pdataset->select_field_value(iFieldIndexLastModified);
//
//         if(strTime.length() == 19)
//         {
//            lpszTime = (char *) (const ::string &) strTime;
//            lpszTime[4] = '\0';
//            lpszTime[7] = '\0';
//            lpszTime[10] = '\0';
//            lpszTime[13] = '\0';
//            lpszTime[16] = '\0';
//            iYear    = atoi(&lpszTime[0]);
//            iMonth   = atoi(&lpszTime[5]);
//            iDay     = atoi(&lpszTime[8]);
//            iHour    = atoi(&lpszTime[11]);
//            iMinute  = atoi(&lpszTime[14]);
//            iSecond  = atoi(&lpszTime[17]);
//            ::earth::time time(
//            iYear,
//            iMonth,
//            iDay,
//            iHour,
//            iMinute,
//            iSecond);
//            timea.set_at(iRow, time);
//         }
//         else
//         {
//            ::earth::time time;
//            timea.set_at(iRow, time);
//         }
//         if(m_iGetExStep % 100 == 99)
//         {
//            m_iGetExStep++;
//            break;
//         }
//      }
//      if(m_iGetExStep >= iRowCount)
//      {
//         m_iGetExStep = -1;
//      }

   }


   void album_build::CalcFiles(file_info & fileinfo, bool bRestart)
   {
      ::int_array & iaOld    = fileinfo.m_iaOld;
      ::int_array & iaUpdate = fileinfo.m_iaUpdate;
      ::int_array & iaRemove = fileinfo.m_iaRemove;
      ::file::listing & straNew = fileinfo.m_wstraNew; // [in]  the files that must be in the album
      time_array_base & timeaNew = fileinfo.m_timeaNew; // [in]  the files last write time
      ::file::listing & straOld = fileinfo.m_wstraOld; // [in]  the files that are already in the album
      time_array_base & timeaOld = fileinfo.m_timeaOld; // [in]  the existing files recotds last write time
      ::file::listing & straAdd = fileinfo.m_wstraAdd; // [out] files not in the album that must be in the album
      time_array_base & timeaAdd = fileinfo.m_timeaAdd; // [out] their time
      ::file::listing & straUpdate = fileinfo.m_wstraUpdate; // [out] files already in the album that must be updated
      time_array_base & timeaUpdate = fileinfo.m_timeaUpdate; // [out] their time
      ::file::listing & straRemove = fileinfo.m_wstraRemove; // [out] files that don't need to be in the album

      time_array_base timeaRemove;

      fileinfo.m_wstraAdd.erase_all();
      fileinfo.m_timeaAdd.erase_all();

      if(bRestart)
      {
         fileinfo.m_wstraUpdate = fileinfo.m_wstraOld;
         fileinfo.m_timeaUpdate = fileinfo.m_timeaOld;
      }


      straUpdate = straNew;
      timeaUpdate = timeaNew;

      iaRemove    = iaOld;
      straRemove = straOld;
      timeaRemove = timeaOld;

      int iUpdate = 0;
      ::collection::index iFound;

      while(iUpdate < straUpdate.get_size())
      {
         iFound = straRemove.find_first(straUpdate[iUpdate]);

         if(iFound >= 0)
         {
            if(timeaUpdate[iUpdate] == timeaRemove[iFound])
            {
               // The file has been found in the old array
               // and its write time has not changed, so
               // it is not necessary to Update.
               straUpdate.erase_at(iUpdate);
               timeaUpdate.erase_at(iUpdate);
            }
            else
            {

               // It needs update.
               iaUpdate.add(iaRemove[iFound]);
               iUpdate++;
            }
            // The file has been found in the old array,
            // so it will not be Removed.
            iaRemove.erase_at(iFound);
            straRemove.erase_at(iFound);
            timeaRemove.erase_at(iFound);
         }
         else
         {
            // Not found so it must be added.
            straAdd.add(straUpdate[iUpdate]);
            timeaAdd.add(timeaUpdate[iUpdate]);
            straUpdate.erase_at(iUpdate);
            timeaUpdate.erase_at(iUpdate);
         }
      }

      straNew.erase_all();
      timeaNew.erase_all();
      straOld.erase_all();
      timeaOld.erase_all();

   }


   void album_build::start_build()
   {
      
      if(m_pthread == nullptr)
      {
         
         m_pthread = ___new album_build_thread();

         if(!m_pthread->begin_synch())
         {
            delete m_pthread;
            m_pthread = nullptr;
            return;
         }
         m_pthread->Initialize(this);
         m_pthread->m_puserinteraction->m_oswindowCallback = m_oswindowCallback;
      }
      m_bBuilding = true;
      m_pthread->m_puserinteraction->start_build();
   }

   void album_build::stop_build()
   {
      if(m_pthread != nullptr)
      {
         m_pthread->m_puserinteraction->stop_build();
      }
      m_fileinfo.Reset();
      m_bBuilding = false;
   }


   ::int_array & album_build::GetPriorityArray()
   {
      return m_iaPriority;
   }

   bool album_build::initialize()
   {
      if(m_pthread != nullptr)
      {
         m_pthread->Initialize(this);
      }
      return true;
   }

   void album_build::SetCallbackWnd(::pointer<::user::interaction>oswindowCallback)
   {
      m_oswindowCallback = oswindowCallback;
      if(m_pthread != nullptr)
      {
         m_pthread->m_puserinteraction->m_oswindowCallback = oswindowCallback;
      }
   }

   void album_build::file_info::Reset()
   {
      m_iaAdd.erase_all();
      m_iaNew.erase_all();
      m_iaOld.erase_all();
      m_iaRemove.erase_all();
      m_iaUpdate.erase_all();
      m_timeaAdd.erase_all();
      m_timeaNew.erase_all();
      m_timeaOld.erase_all();
      m_timeaUpdate.erase_all();
      m_wstraAdd.erase_all();
      m_wstraNew.erase_all();
      m_wstraOld.erase_all();
      m_wstraRemove.erase_all();
      m_wstraUpdate.erase_all();
   }


   bool album_build::HasFile(const ::string & lpcsz)
   {

      //::pointer<::sqlite::dataset>pdataset    =  m_pdatabase->dataset();

      //if(pdataset.is_null())
      //   return false;

      string strSql;
      strSql.formatf("select atom from album where filepath='%s';", lpcsz);
      //pdataset->query(strSql);
      //bool bHasFile = pdataset->num_rows() >= 1;

      //bool b

      //pdataset->close();
      //pdataset.release();

      //return bHasFile;

      return false;


   }


   album_record::album_record()
   {

   }


   bool album_build::IsBuilding()
   {

      return m_bBuilding;

   }


} // namespace mediamanager



