#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      destination::destination()
      {

         m_pdevice = nullptr;
         m_pdestination = this;

      }


      destination::~destination()
      {

      }


      void destination::initialize_source_info()
      {

         return error_failed;

      }


      void destination::initialize_all_controls()
      {

         GetLineControls();

         ::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(i32 i = 0; i < sourcea.get_size(); i++)
         {

            sourcea[i]->GetLineControls();

         }

         return ::success;

      }


      void destination::update_all_controls()
      {

         ::audio_mixer::source::update_all_controls();

         ::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(i32 i = 0; i < sourcea.get_size(); i++)
         {

            sourcea[i]->update_all_controls();

         }

      }


      destination & destination::operator = (const destination & destination)
      {

         m_pdevice = destination.m_pdevice;

         return *this;

      }


      u32 destination::get_component_type()
      {

         return (u32) -1;

      }


      u32 destination::get_mixer_line_id()
      {
         return (u32) -1;
      }

      ::audio_mixer::device * destination::get_device()
      {

         return m_pdevice;

      }


      void destination::set_device(::audio_mixer::device * pdevice)
      {

         m_pdevice = pdevice;

      }


      ::audio_mixer::source_array & destination::get_source_info()
      {

         return m_mixersourcea;

      }


   } // namespace audio_mixer


} // namespace multimedia




