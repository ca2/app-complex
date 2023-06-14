#include "framework.h"



namespace mediamanager
{


   media_manager::media_manager()
   {

      information("media_manager::media_manager(%d)", this);

   }


   media_manager::~media_manager()
   {

   }


   void media_manager::initialize(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __construct_new(m_palbumbuild);

      if(!estatus)
      {

         information("Could not create Multimedia Media Manager Album Build");

         return ::error_failed;

      }

      if(!album_build()->initialize())
      {
         
         information("Could not create Multimedia Media Manager Album Build");
         
         return ::error_failed;

      }

      information("media_manager::media_manager(%d)", this);

      return ::success;

   }


   void media_manager::destroy()
   {
      //return true;

   }

   void media_manager::OnOpenDocumentFile(const ::file::path & lpcsz)
   {
      __UNREFERENCED_PARAMETER(lpcsz);
      //if(album_build() == nullptr)
      // return;
      //if(!album_build().HasFile(lpcsz))
      {
#ifdef _DEBUG
         string str;
         //      str.format("File %S is not in the album", lpcsz);
         //message_box(str);
#endif
      }
   }

   void media_manager::BuildAlbum(::file::listing & wstraFolder)
   {

      ::pointer<::mediamanager::album_build>albumbuild = album_build();

      albumbuild->m_bBuilt = false;

      albumbuild->stop_build();

      albumbuild->m_wstraFolder = wstraFolder;

      albumbuild->start_build();

   }

   void media_manager::start_album_build()
   {

      album_build()->start_build();

   }

   ::pointer<::mediamanager::album_build>media_manager::album_build()
   {

      return m_palbumbuild;

   }


} // namespace mediamanager


