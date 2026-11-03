#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO sound_track_player :
      virtual public ::wave::player::listener,
      virtual public ::aura::sound_track_player
   {
   public:


      ::pointer<::wave::player>                                      m_pwaveplayer;
      ::pointer<::audio::mixer>                               m_paudiomixer;
      ::pointer<::audio::decoder_plugin>                        m_pdecoderplugin;
      string_map_base < pointer_array < ::audio::plugin > >                 m_mapPlugin;
      string_map_base < file_pointer >                                       m_mapFile;


      sound_track_player();
      virtual ~sound_track_player();


      virtual void defer_start(::wave::enum_purpose epurpose);


      virtual ::pointer<::object>sound_plugin(const ::scoped_string & scopedstr, bool bForceCreate = false);

      file_pointer sound_file(const ::scoped_string & scopedstr);

      string sound_path(const ::scoped_string & scopedstr);

      void mix(const ::scoped_string & scopedstr);

      void mix(::audio::plugin * pplugin);

      void erase(::audio::plugin* pplugin);

      void replace_with_track(::audio::plugin* pplugin);

      ::wave::player * get_wave_player();

   };


} // namespace multimedia
