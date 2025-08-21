#include "framework.h"



namespace audio
{


   sound_track_player::sound_track_player()
   {

      defer_create_synchronization();

   }


   sound_track_player::~sound_track_player()
   {

   }


   void sound_track_player::defer_start(::wave::enum_purpose epurpose)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (::is_set(m_pwaveplayer))
      {

         return ::success_none;

      }

      m_pdecoderplugin = paudio->audiowave()->m_pdecoderset->LoadPlugin("audio_decode_wave");

      auto estatus = øconstruct(m_pwaveplayer, øallocate ::wave::device_player());

      if (!estatus)
      {

         return estatus;

      }

      synchronouslock.unlock();

      estatus = m_pwaveplayer->prepare_wave_player(epurpose);

      if (!estatus)
      {

         return estatus;

      }

      if (::is_null(m_paudiomixer))
      {

         auto estatus = øconstruct_new(m_paudiomixer);

         if (!estatus)
         {

            return estatus;

         }

         m_paudiomixer->audio_set_non_stop_on_eof(true);

         //m_paudiomixer->audio_initialize();

         {

            ::wave::player_command_pointer command(e_create);

            command->OpenDecoder(m_paudiomixer);

            m_pwaveplayer->DecoderOpen(command);

         }

         {

            ::wave::player_command_pointer command(e_create);

            command->Play(0, 0);

            m_pwaveplayer->post_command(command);

         }

      }

      return ::success;

   }


   string sound_track_player::sound_path(const ::scoped_string & scopedstr)
   {

      if (papp->m_pgame)
      {

         return papp->m_pgame->sound_path(scopedstr);

      }

      return papp->sound_path(scopedstr);

   }


   file_pointer sound_track_player::sound_file(const ::scoped_string & scopedstr)
   {

      //file_pointer & file = m_mapFile[psz];
      auto pfile = create_memory_file();

      //if(!file.is_set())
      {

         file_pointer fileSrc = file()->get_file(sound_path(scopedstr), ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_write);

         pfile->get_memory()->set_size((memsize) fileSrc->get_size());

         fileSrc->read(pfile->get_memory()->get_data(), pfile->get_memory()->get_length());

      }

      return pfile;

   }


   ::pointer<::object>sound_track_player::sound_plugin(const ::scoped_string & scopedstr, bool bForceCreate)
   {

      synchronous_lock synchronouslock(this->synchronization());

      pointer_array < ::audio::plugin > & plugina = m_mapPlugin[psz];

      if (!bForceCreate)
      {

         auto i = plugina.predicate_find_first([](::audio::plugin *p)
         {

            return p->audio_eof();

         });

         if (i >= 0)
         {

            plugina[i]->audio_initialize();

            return plugina[i];

         }

         if (m_pdecoderplugin == nullptr)
         {

            return nullptr;

         }

      }

      ::pointer<::audio::decoder>pdecoder = m_pdecoderplugin->NewDecoder();

      pdecoder->multimedia_open(sound_file(scopedstr));

      pdecoder->m_bLoop = false;

      if (!pdecoder->audio_matches(m_paudiomixer))
      {

         auto presampler = øallocate ::audio::resampler();



         presampler->m_pplugin = pdecoder;

         presampler->audio_initialize();

         return presampler;

      }


      return pdecoder;

   }


   void sound_track_player::erase(::audio::plugin* pplugin)
   {

      m_paudiomixer->m_plugina.erase(pplugin);

   }


   void sound_track_player::mix(::audio::plugin* ppluginParam)
   {

      ::pointer<::audio::plugin>pplugin(ppluginParam);

      if (!pplugin)
      {

         return;

      }

      if (!pplugin->audio_matches(m_paudiomixer))
      {

         auto presampler = øallocate ::audio::resampler();

         presampler->m_pplugin = pplugin;

         pplugin = presampler;

      }

      double d = (get_nanos() * m_paudiomixer->audio_get_channel_count()
         * m_paudiomixer->audio_get_samples_per_second()
         * m_paudiomixer->audio_get_bits_per_sample()) / 8'000'000'000.0;

      auto iStartOffset = (long long)d;

      pplugin->m_iStartOffset = iStartOffset;

      m_paudiomixer->add_plugin(pplugin);

   }


   void sound_track_player::replace_with_track(::audio::plugin* ppluginParam)
   {

      ::pointer<::audio::plugin>pplugin(ppluginParam);

      if (!pplugin)
      {

         return;

      }

      if (!pplugin->audio_matches(m_paudiomixer))
      {

         auto presampler = øallocate ::audio::resampler();

         presampler->m_pplugin = pplugin;

         presampler->audio_initialize();

         pplugin = presampler;

      }

      pplugin->audio_seek_begin();

      m_paudiomixer->replace_with_track(pplugin);

   }


   void sound_track_player::mix(const ::scoped_string & scopedstr)
   {

      synchronous_lock synchronouslock(this->synchronization());

      string str(scopedstr);

      str.case_insensitive_begins_eat("wait:");

      ::pointer<::audio::plugin>pplugin = sound_plugin(str);

      mix(pplugin);

   }


   ::wave::player * sound_track_player::get_wave_player()
   {

      return m_pwaveplayer;

   }


} // namespace audio



