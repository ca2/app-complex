#pragma once


namespace multimedia
{


   namespace audio_mixer_userbase
   {


      class CLASS_DECL_APP_CORE_AUDIO document :
         virtual public ::user::document
      {
      public:


         document();
         virtual ~document();


         virtual bool on_new_document();


#ifdef _DEBUG
         // void assert_ok() const override;
         // void dump(dump_context & dumpcontext) const override;
#endif


      };


   } // namespace audio_mixer_userbase


} // namespace multimedia




