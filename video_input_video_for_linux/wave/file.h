#pragma once


namespace wave
{


   class file
   {
   public:


      file_pointer  m_spfile;


      file(::file::file * pfile);
      ~file();


   };


} // namespace wave



