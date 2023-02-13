#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class CLASS_DECL_APP_CORE_AUDIO device :
         virtual public ::object
      {
      public:


         
         u32                                                   m_uiMixerID;
         ::pointer<::audio_mixer::audio_mixer>  m_pmixer;
         ::audio_mixer::destination_array          m_mixerdestinationa;

         dword_map < ::audio_mixer::control * >    m_mapIDToControl;
         atom_map < ::audio_mixer::control * >       m_mapDlgItemIDToControl;
         dword_map < ::audio_mixer::source * >     m_mapIDToLine;


         device();
         virtual ~device();


         virtual void initialize_multimedia_audio_mixer_device(::audio_mixer::audio_mixer * pmixer);

         virtual ::audio_mixer::audio_mixer * get_mixer();
         virtual string get_product_name();
         virtual bool OnCommand(::user::message * pusermessage);
         virtual void     close();
         virtual void MapDlgCtrlIDToLineControls(::audio_mixer::source * pSource);
         virtual void MapDlgCtrlIDToControls();
         virtual void MapLineControls(::audio_mixer::source * pSource);
         virtual void OnMixerControlChange(u32 dwControlID);
         virtual void OnMixerLineChange(u32 dwLineID);
         virtual void map_lines();
         virtual void map_controls();
         virtual ::pointer<::audio_mixer::destination>get_destination(::audio_mixer::e_destination edestination);
         virtual void     initialize_destinations();
         virtual void     initialize_capabilities();
         virtual void     open(u32 uiMixerId, UINT_PTR dwCallback, u32 dwInstance, u32 fdwOpen);


      };


   } // namespace audio_mixer


} // namespace multimedia






