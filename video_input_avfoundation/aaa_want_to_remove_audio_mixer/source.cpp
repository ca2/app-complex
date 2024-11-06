#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      source::source()
      {

         m_pdestination = nullptr;

      }


      source::~source()
      {

      }


      void     source::GetLineControls()
      {

         return error_failed;

      }

      /*void     source::GetControl(unsigned int dwControlType, unsigned int dwControlFlags,  ::audio_mixer::control ** ppControl)
      {
      ::audio_mixer::control_array & controla = m_mixercontrola;
      if(controla.get_size() <= 0)
      GetLineControls();
      if(controla.get_size() <= 0)
      return MMSYSERR_ERROR;
      for(int i = 0; i < controla.get_size(); i++)
      {
      if((dwControlType != 0 && controla[i].GetControlType() == dwControlType)
      || (dwControlType == 0 && ((controla[i].GetControlType() & dwControlFlags) != 0)))
      {
      *ppControl = controla(i);
      return MMSYSERR_NOERROR;
      }
      }
      return MMSYSERR_ERROR;
      }*/

      /*void source::OnArrayReallocation(void *pNewPointer)
      {
      m_pmixerdestination = (::audio_mixer::destination *) pNewPointer;
      }*/

      void source::OnMixerLineChange()
      {

      }



      void source::update_all_controls()
      {
         ::audio_mixer::control_array & controla = get_control_array();
         for(int i = 0; i < controla.get_size(); i++)
         {
            controla[i]->OnMixerControlChange();
         }
      }

      source & source::operator = (const source & source)
      {
         m_bHasV001Controls = source.m_bHasV001Controls;
         m_pdestination = source.m_pdestination;
         return *this;
      }

      
      string source::get_source_name()
      {
         
         return "";

      }


      string source::get_source_short_name()
      {

         return "";

      }


      ::atom source::GetLineID()
      {

         return ::atom::e_type_null;

      }


      ::audio_mixer::device * source::get_device()
      {
         return m_pdestination->get_device();
      }

      void source::SetDestination(::audio_mixer::destination * pdestination)
      {
         m_pdestination = pdestination;
      }

      void     source::mixerGetLineInfo(unsigned int dwSource, unsigned int dwDestination, unsigned int fdwInfo)
      {
         return error_failed;
      }

      void     source::mixerGetLineInfo(unsigned int dwSource, ::audio_mixer::destination * pdestination)
      {
         return error_failed;
      }

      ::audio_mixer::destination * source::get_destination()
      {
         return m_pdestination;
      }

      bool source::HasV001Controls()
      {
         return m_bHasV001Controls;
      }

      ::audio_mixer::control_array & source::get_control_array()
      {
         return m_mixercontrola;
      }


   } // namespace audio_mixer


} // namespace multimedia





