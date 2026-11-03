#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      namespace user
      {


         class CLASS_DECL_APP_CORE_AUDIO control :
            virtual public ::user::interaction
         {
         public:


            ::pointer<::audio_mixer::control_data> m_pdata;


            control();
            virtual ~control();


            using ::user::interaction::create_window;
            virtual bool create_window(::user::interaction * puiParent, const ::atom & atom) override = 0;

            virtual ::audio_mixer::control_data * get_data();


         };


         class CLASS_DECL_APP_CORE_AUDIO control_ptr_array :
            public pointer_array < control >
         {
         };


      } // namespace user


   } // namespace audio_mixer


} // namespace multimedia





