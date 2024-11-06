#pragma once


namespace mediaplay
{


   class CLASS_DECL_APP_CORE_AUDIO record_notify_impact :
      virtual public ::user::interaction
   {
   public:
      
      
      unsigned int       m_dwOnTime;
      unsigned int       m_dwOffTime;

      
      record_notify_impact();
      virtual ~record_notify_impact();
   
      void install_message_routing(::channel * pchannel) override;

      using ::user::interaction::create_window;
      bool create_window(::pointer<::user::interaction>pinterface,atom atom);

      virtual void GetParentClientRect(::int_rectangle * lprect);
   
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnTimer(::timer * ptimer);


      static void CALLBACK TimerProc(oswindow, unsigned int, uptr, unsigned int);

   };


} // namespace mediaplay












