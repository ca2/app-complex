#pragma once


namespace mediamanager
{


   class media_manager;
   class album_build;


   class CLASS_DECL_APP_CORE_AUDIO media_manager :
      virtual public ::object
   {
   public:


      ::pointer<::mediamanager::album_build>m_palbumbuild;


      media_manager();
      virtual ~media_manager();


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;


      void BuildAlbum(::file::listing & straFolder);
      void start_album_build();

      
      ::pointer<::mediamanager::album_build>album_build();

      void OnOpenDocumentFile(const ::file::path & path);


   };


} // namespace mediamanager







