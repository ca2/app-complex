#include "framework.h"



namespace multimedia
{


   namespace audio_mixer
   {


      device::device()
      {

      }

      
      void device::initialize_multimedia_audio_mixer_device(::audio_mixer::audio_mixer * pmixer)
      {

         auto estatus = ::object::initialize(pmixer);

         if (!estatus)
         {

            return estatus;

         }

         m_pmixer = pmixer;

         return true;

      }

      device::~device()
      {

         close();

      }


      void     device::open(u32 uiMixerId, UINT_PTR dwCallback, u32 dwInstance, u32 fdwOpen)
      {

         return error_failed;

      }


      void     device::initialize_capabilities()
      {

         return error_failed;

      }


      void     device::initialize_destinations()
      {

         return error_failed;

      }


      ::pointer<::audio_mixer::destination>device::get_destination(::audio_mixer::e_destination edestination)
      {

         return error_failed;

      }


      void device::map_controls()
      {
         m_mapIDToControl.erase_all();

         for(i32 i = 0; i < m_mixerdestinationa.get_size(); i++)
         {
            ::audio_mixer::destination & destination = m_mixerdestinationa(i);
            MapLineControls(&destination);
            ::audio_mixer::source_array & sourcea = destination.get_source_info();
            for(i32 j = 0; j < sourcea.get_size(); j++)
            {
               ::audio_mixer::source & source = sourcea(j);
               MapLineControls(&source);
            }
         }
      }

      void device::map_lines()
      {
      }

      void device::OnMixerLineChange(u32 dwLineID)
      {
         ::audio_mixer::source * pSource;
         if(m_mapIDToLine.lookup(dwLineID, pSource))
         {
            pSource->OnMixerLineChange();
         }
      }

      void device::OnMixerControlChange(u32 dwControlID)
      {
         ::audio_mixer::control * pControl;
         if(m_mapIDToControl.lookup(dwControlID, pControl))
         {
            pControl->OnMixerControlChange();
         }
      }

      void device::MapLineControls(::audio_mixer::source * psource)
      {

      }

      void device::MapDlgCtrlIDToControls()
      {
         m_mapDlgItemIDToControl.erase_all();

         ::audio_mixer::destination_array & destinationa = m_mixerdestinationa;
         for(i32 i = 0; i < destinationa.get_size(); i++)
         {
            ::audio_mixer::destination & destination = destinationa(i);
            MapDlgCtrlIDToLineControls(&destination);
            ::audio_mixer::source_array & sourcea = destination.get_source_info();
            for(i32 j = 0; j < sourcea.get_size(); j++)
            {
               ::audio_mixer::source & source = sourcea(j);
               MapDlgCtrlIDToLineControls(&source);
            }
         }

      }

      void device::MapDlgCtrlIDToLineControls(::audio_mixer::source * psource)
      {
         ::audio_mixer::control_array & controla = psource->get_control_array();
         for(i32 k = 0; k < controla.get_size(); k++)
         {

            ::audio_mixer::control & control = controla(k);

            for(i32 l = 0; l < control.get_size(); l++)
            {

               ::audio_mixer::user_control * pinteraction = control[l];

               m_mapDlgItemIDToControl.set_at(pinteraction->GetDlgCtrlId(), &control);

            }

         }

      }


      void     device::close()
      {
         return error_failed;

      }

      bool device::OnCommand(::user::message * pusermessage)
      {

         ::atom atom(LOWORD(pusermessage->m_wparam));

         ::audio_mixer::control * pinteraction;

         if(m_mapDlgItemIDToControl.lookup(atom, pinteraction)
               && pinteraction->OnCommand(pusermessage->m_wparam, pusermessage->m_lparam))
            return true;

         return false;

      }


      string device::get_product_name()
      {

         return nullptr;

      }


      ::audio_mixer::audio_mixer * device::get_mixer()
      {

         return m_pmixer;

      }


   } // namespace audio_mixer


} // namespace multimedia







