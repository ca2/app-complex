#pragma once


namespace mediamanager
{


   class album_build;
   class album_build_thread;


   class CLASS_DECL_APP_CORE_AUDIO album_record :
      public ::object
   {
   public:
      
      
      ::file::path            m_wstrFileName;
      ::file::path            m_wstrFilePath;
      string                  m_wstrTitle;
      string                  m_wstrArtist;
      string                  m_wstrLastWriteTime;
      ::earth::time        m_timeLastWrite;

      memory       m_storage;
      memory       m_storage2;
      string       m_strSql;


      album_record();


      virtual void GetInsertSql(int iId);
      virtual void GetUpdateSql(int iId, bool bFilePath, bool bFileName);
      virtual bool FillFileInfo(::pointer<::mediamanager::album_build>build, const ::string & pcsz);
      virtual bool FillFileInfo(::pointer<::mediamanager::album_build>build, memory & storage);


      static string Prepare(const string & pcsz);
      static string Prepare(::earth::time & time);
      static void Prepare(string & str,::earth::time & time);


   };


} // namespace mediamanager
