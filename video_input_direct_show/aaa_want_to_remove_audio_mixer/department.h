#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class CLASS_DECL_APP_CORE_AUDIO department :
         virtual public ::acme::department,
         virtual public ::user::interaction
      {
      public:


         enum EIds
         {

            IdsMuteAll,
            IdsMute

         };


         ::pointer<::acme::library>       m_plibrary;



         department();
         virtual ~department();


         virtual bool ([a-z0-9_]+)_factory(::factory::factory * pfactory);

         virtual void init1() override;

         virtual void init() override;

         virtual void term() override;


      };


   } // namespace mixguserbase


} // namespace multimedia





