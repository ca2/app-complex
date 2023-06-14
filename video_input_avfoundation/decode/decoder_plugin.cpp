#include "framework.h"



namespace audio
{


   decoder_plugin::decoder_plugin()
   {

      m_strNewDecoder = "NewDecoderInterface";

   }


   decoder_plugin::~decoder_plugin()
   {

   }


   //::audio::decoder * decoder_plugin::NewDecoder()
   //{

   //   ::audio::decoder * pdecoder = m_lpfnNewDecoder(this);

   //   if (pdecoder == nullptr)
   //   {
   //      return nullptr;
   //   }

   //   pdecoder->m_pplugin = this;

   //   return pdecoder;

   //}


   //void decoder_plugin::DeleteDecoder(::audio::decoder * pdecoder)
   //{

   //   m_lpfnDeleteDecoder(pdecoder);

   //}


   //bool decoder_plugin::Load(const ::string & pszTitle)
   //{

   //   if (!m_library.open(pszTitle))
   //   {

   //      //SetDllDirectory(dir()->ca2module());
   //      //HINSTANCE hinstance = ::LoadLibrary(pszTitle);
   //      //       if(hinstance == nullptr)
   //      //     {
   //      //      hinstance = ::LoadLibrary(dir()->ca2module(pszTitle));
   //      //    if(hinstance == nullptr)
   //      if (!m_library.open(dir()->ca2module()/pszTitle))
   //      {
   //         u32 dwLastError = GetLastError();
   //         information("LoadLibrary failed to open library %s %d %s", pszTitle, dwLastError, win::error_message(dwLastError));
   //         return false;
   //      }
   //   }
   //   m_lpfnNewDecoder = m_library.get < ::audio::decoder *(*)(::object *) >("NewDecoderInterface");
   //   if (m_lpfnNewDecoder == nullptr)
   //   {
   //      m_library.close();
   //      information("NewDecoderInterface function not found in library %s", pszTitle);
   //      return false;
   //   }
   //   m_lpfnDeleteDecoder = m_library.get < void(*)(::audio::decoder *) >("DeleteDecoderInterface");
   //   if (m_lpfnDeleteDecoder == nullptr)
   //   {
   //      m_library.close();
   //      information("DeleteDecoder function not found in library %s", pszTitle);
   //      return false;
   //   }

   //   m_strTitle = pszTitle;

   //   return true;

   //}

   //string decoder_plugin::GetPluginTitle()
   //{
   //   return m_strTitle;
   //}


} // namespace audio



