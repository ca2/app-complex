#include "framework.h"



namespace audio
{


   encoder_plugin_set::encoder_plugin_set()
   {

   }


   encoder_plugin_set::~encoder_plugin_set()
   {

   }


   encoder_plugin * encoder_plugin_set::FindPlugin(i32 iId)
   {

      for(i32 i = 0; i < m_plugina.get_size(); i++)
      {

         if (m_plugina.element_at(i)->GetPluginId() == iId)
         {

            return m_plugina.element_at(i);

         }

      }

      return nullptr;

   }


   encoder_plugin * encoder_plugin_set::LoadPlugin(i32 iId, const ::string & lpcszDll)
   {

      {

         encoder_plugin * pplugin = FindPlugin(iId);

         if (pplugin != nullptr)
         {

            return pplugin;

         }

      }

      auto pplugin = __create_new < encoder_plugin >();

      pplugin->SetPluginId(iId);

      __construct(pplugin->m_plibrary);

      if(!pplugin->m_plibrary->open(lpcszDll))
      {

         TRACE("Fail to open decoder");

         return nullptr;

      }

      pplugin->m_lpfnNewEncoder = pplugin->m_plibrary->get < ::audio::encoder *( * )() > ("NewEncoderInterface");

      if(pplugin->m_lpfnNewEncoder == nullptr)
      {

         pplugin->m_plibrary->close();

         //str.format("NewEncoderInterface function not found in %s", lpcszDll);

         throw ::exception(::exception("NewEncoderInterface function not found"));

         return nullptr;

      }

      //pplugin->m_lpfnDeleteEncoder = pplugin->m_plibrary->get < void( * )(void *) > ("DeleteEncoderInterface");

      //if(pplugin->m_lpfnDeleteEncoder == nullptr)
      //{

      //   pplugin->m_plibrary->close();

      //   //str.format("NewEncoderInterface function not found in %s", lpcszDll);

      //   throw ::exception(::exception("NewEncoderInterface function not found"));

      //   return nullptr;

      //}

      m_plugina.add(pplugin);

      return pplugin;

   }


   encoder * encoder_plugin_set::GetNewEncoder(const ::string & lpcszFileName, file_pointer * pfile)
   {

      __UNREFERENCED_PARAMETER(pfile);

      strsize len = strlen(lpcszFileName);

      ::audio::encoder_plugin * pplugin = nullptr;

      if(_strcmpi(&lpcszFileName[len - 4], ".wav") == 0)
      {

         pplugin = LoadPlugin(0, "audio_wave.dll");

      }
      else if(_strcmpi(&lpcszFileName[len - 4], ".wma") == 0)
      {

         pplugin = LoadPlugin(1, "audio_window_media.dll");

      }
      else if(_strcmpi(&lpcszFileName[len - 4], ".mp3") == 0)
      {

         pplugin = LoadPlugin(2, "auddec_mpglib.dll");

      }

      if(pplugin == nullptr)
         return nullptr;

      return pplugin->NewEncoder();

   }


} // namespace audio



