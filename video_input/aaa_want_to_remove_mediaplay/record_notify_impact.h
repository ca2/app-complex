#pragma once


namespace mediaplay
{


   class CLASS_DECL_APP_CORE_AUDIO record_notify_impact :
      virtual public ::user::interaction
   {
   public:
      
      
      u32       m_dwOnTime;
      u32       m_dwOffTime;

      
      record_notify_impact();
      virtual ~record_notify_impact();
   
      void install_message_routing(::channel * pchannel) override;

      using ::user::interaction::create_window;
      bool create_window(::pointer<::user::interaction>pinterface,atom atom);

      virtual void GetParentClientRect(RECTANGLE_I32 * lprect);
   
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnTimer(::timer * ptimer);


      static void CALLBACK TimerProc(oswindow, u32, uptr, u32);

   };


} // namespace mediaplay












