#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class CLASS_DECL_APP_CORE_AUDIO destination :
         virtual public ::audio_mixer::source
      {
      public:


         ::audio_mixer::device *       m_pdevice;
         ::audio_mixer::source_array   m_mixersourcea;


      protected:


         destination();
         virtual ~destination();


      public:


         virtual unsigned int get_component_type();
         virtual void update_all_controls();
         virtual void     initialize_all_controls();
         virtual void     initialize_source_info();

         virtual ::audio_mixer::source_array & get_source_info();

         destination & operator = (const destination & device);

         virtual ::audio_mixer::device * get_device();
         virtual void set_device(::audio_mixer::device * pdevice);

         virtual unsigned int get_mixer_line_id();

      };


      typedef CLASS_DECL_APP_CORE_AUDIO pointer_array < destination > destination_array;


   } // namespace audio_mixer


} // namespace multimedia
