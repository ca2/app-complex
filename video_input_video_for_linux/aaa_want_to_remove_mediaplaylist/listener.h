#pragma once


namespace mediaplaylist
{


   enum e_happening
   {

      event_before_open,

   };


   class document;


   class media_playlist;


   class CLASS_DECL_APP_CORE_AUDIO listener :
      virtual public ::object
   {
   public:


      ::pointer<media_playlist>m_pmediaplaylist;


      listener();
      virtual ~listener();

      virtual void on_event(e_happening ehappening);
      
      virtual ::mediaplaylist::document * _001OnBeforeOpenPlaylist();

   };


} // namespace mediaplaylist


