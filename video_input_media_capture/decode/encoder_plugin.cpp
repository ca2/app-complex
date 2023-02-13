#include "framework.h"



namespace audio
{


   encoder_plugin::encoder_plugin()
   {

   }


   encoder_plugin::~encoder_plugin()
   {

   }

   void encoder_plugin::SetPluginId(i32 iId)
   {

      m_iId = iId;

   }


   ::audio::encoder * encoder_plugin::NewEncoder()
   {

      ::audio::encoder * pdecoder = m_lpfnNewEncoder();

      if(pdecoder == nullptr)
      {

         return nullptr;

      }

      return pdecoder;

   }


   //void encoder_plugin::DeleteEncoder(::audio::encoder * pdecoder)
   //{

   //   m_lpfnDeleteEncoder(pdecoder);

   //}


   i32 encoder_plugin::GetPluginId()
   {

      return m_iId;

   }


} // namespace audio



