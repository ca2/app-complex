#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class destination;


      class CLASS_DECL_APP_CORE_AUDIO source :
         virtual public ::object
      {
      public:


         


         ::audio_mixer::destination        * m_pdestination;
         ::audio_mixer::control_array        m_mixercontrola;
         bool                                            m_bHasV001Controls;


      protected:


         source();
         virtual ~source();


      public:


         virtual void     mixerGetLineInfo(unsigned int dwSource, unsigned int dwDestination, unsigned int fdwInfo);
         virtual void     mixerGetLineInfo(unsigned int dwSource, ::audio_mixer::destination * pdestination);

         virtual ::atom GetLineID();
         virtual string get_source_name();
         virtual string get_source_short_name();
         virtual void update_all_controls();

         virtual ::audio_mixer::control_array & get_control_array();

         virtual ::audio_mixer::device * get_device();

         virtual void SetDestination(::audio_mixer::destination * pdestination);
         virtual ::audio_mixer::destination * get_destination();

         virtual void OnMixerLineChange();
         virtual void     GetLineControls();

         virtual bool HasV001Controls();

         source & operator = (const source & source);


      };


      class source_array :
         public pointer_array < source >
      {
      public:

         source_array()
         {


         }
      };


   } // namespace audio_mixer


} // namespace multimedia














