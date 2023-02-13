#pragma once


namespace wave
{

   CLASS_DECL_APP_CORE_AUDIO void compose_player(::pointer<player>& pplayer, player::listener * plistener);


   class CLASS_DECL_APP_CORE_AUDIO player_container :
      virtual public player::listener
   {
   public:


      ::pointer<player>     m_pwaveplayer;


      player_container();
      virtual ~player_container();


      virtual bool create_logical_wave_player(::wave::enum_purpose epurpose);

      virtual player * get_wave_player();



   };


} // namespace wave



