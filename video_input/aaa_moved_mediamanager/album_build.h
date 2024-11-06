#pragma once


namespace mediamanager
{


   class album_build;
   class album_build_thread;




   class CLASS_DECL_APP_CORE_AUDIO album_build :
      virtual public ::object
   {
   public:


      class file_info
      {
      public:


         ::i32_array         m_iaNew;
         ::i32_array         m_iaOld;
         ::i32_array         m_iaAdd;
         ::i32_array         m_iaUpdate;
         ::i32_array         m_iaRemove;

         ::file::listing   m_wstraNew;
         time_array        m_timeaNew;
         ::file::listing   m_wstraOld;
         time_array        m_timeaOld;
         ::file::listing   m_wstraAdd;
         time_array        m_timeaAdd;
         ::file::listing   m_wstraUpdate;
         time_array        m_timeaUpdate;
         ::file::listing   m_wstraRemove;

         void Reset();

      };



      bool                       m_bBuilding;
      ::file::listing            m_wstraPreBuildFolders;
      int                    m_iPreBuildRowCount;
      //::pointer<::sqlite::dataset>     m_pdatasetPreBuildRead;
      //::pointer<::sqlite::dataset>     m_pdatasetPreBuildWrite;
      //::pointer<::sqlite::dataset>     m_pdatasetGetExRead;
      int                    m_iGetExStep;
      file_info                  m_fileinfo;
      ::i32_array                  m_iaPriority;
      album_build_thread *       m_pthread;
      ::pointer<::sqlite::database>    m_pdatabase;
      //::pointer<::sqlite::dataset>     m_pdatasetRead1;
      critical_section           m_csRead1;
      //::pointer<::sqlite::dataset>     m_pdatasetWrite;
      ::pointer<album_record>              m_palbumrecord;

      ::file::listing            m_wstraFolder;

      ::pointer<::user::interaction>   m_oswindowCallback;

      string                     m_wstrBuildAlbumExtensions;

      bool                       m_bFindFiles;
      bool                       m_bBuilt;


      album_build();
      virtual ~album_build();


      virtual void initialize(::particle * pparticle);

      ::mediamanager::album_record & record();


      void Build(::file::listing & wstraFolder,bool bRecursive);

      bool PreBuild(int &  iStep, bool bRecursive, bool bAddEmpty);
   public:
      bool IsBuilding();
      bool HasFile(const ::string & pcsz);
      void SetCallbackWnd(::pointer<::user::interaction>oswindow);
      bool initialize();

      void start_build();
      void stop_build();


      void RecurseFolders(::file::listing & straFolder,::file::listing & straFolderSource);
      void RecurseFolders(::file::listing & straFolder, ::file::path & wstrFolderSource);

      void FindFiles(::file::listing & straFile,time_array & array,::file::listing & straFolder);
      void ZipFindFiles(::file::listing & straFile,time_array & timea,::file::listing & straFolder);

      void GetExistingFiles(::i32_array & ia,::file::listing & straFile,time_array & array);
      void GetExistingFiles(::pointer<::database::result_set>pset,::i32_array & ia,::file::listing & straFile,time_array & array);

      void CalcFiles(file_info & fileinfo, bool bRestart);

      bool add(::file::listing & straFile,time_array & array);
      bool add(const ::file::path & lpcszFile,::earth::time & time);
      bool add(::mediamanager::album_record & record);
      bool AddAlbumRecord();
      bool AddInvalidFile(const ::file::path & path);
      bool AddEmpty(::i32_array & ia,::file::listing & straFile);
      int  AddEmptyFile(const ::file::path & path);

      bool Update(::file::listing & straFile,time_array & array);
      bool Update(const ::file::path & lpcszFile,::earth::time & time,int iId = I32_MINIMUM);
      bool Update(::mediamanager::album_record & record);
      bool UpdateAlbumRecord(int iId, bool bUpdateFilePath, bool bUpdateFileName);
      bool UpdateInvalidFile(const ::file::path & path);

      bool erase(::file::listing & straFile);
      bool erase(::file::path & wstrFile);
      bool erase(int iId);
      bool erase(::i32_array & ia);

      ::i32_array & GetPriorityArray();


   };


} // namespace mediamanager





