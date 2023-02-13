#include "framework.h"



namespace wave
{


   in_listener::in_listener()
   {

   }


   in_listener::~in_listener()
   {

      for(i32 i = 0; i < m_waveinptra.get_size(); i++)
      {

         m_waveinptra[i]->in_erase_listener(this);

      }

   }


   void in_listener::in_data_proc(in *pwavein, u32 dwSampleTime, int iBuffer)
   {

      __UNREFERENCED_PARAMETER(pwavein);
      __UNREFERENCED_PARAMETER(dwSampleTime);
      __UNREFERENCED_PARAMETER(iBuffer);

   }


   void in_listener::HookWaveIn(in * pwavein)
   {

      m_waveinptra.add_unique(pwavein);

   }


   void in_listener::UnhookWaveIn(in * pwavein)
   {

      m_waveinptra.erase(pwavein);

   }


} // namespace wave



