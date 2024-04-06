#pragma once


namespace mediaplaylist
{


   class CLASS_DECL_APP_CORE_AUDIO frame :
      virtual public simple_frame_window
   {
   public:


      simple_toolbar              m_toolbar;


      frame(::particle * pparticle);
      virtual ~frame();

      void install_message_routing(::channel * pchannel) override;

      ::pointer<::user::impact> GetParentLyricWindow();

      DECLARE_MESSAGE_HANDLER(on_message_create);
   };



} // namespace mediaplaylist


