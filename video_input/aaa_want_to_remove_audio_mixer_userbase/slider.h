#pragma once


namespace multimedia
{


   namespace audio_mixer_user_base
   {


      class CLASS_DECL_APP_CORE_AUDIO slider :
         virtual public ::audio_mixer_user::level_control
      {
      public:


         bool                    m_bPresenceOnHover;
         bool                    m_bHover;
         i32                 m_iLineSize;
         i32                 m_iPageSize;
         i32                 m_iRangeMin;
         i32                 m_iRangeMax;
         i32                 m_iPos;
         i32                 m_iTrackingPos;
         i32                 m_eorientation;
         bool                    m_bTracking;
         bool                    m_bThumbHover;
         point                   m_sizeTrackOffset;
         ::draw2d::pen_pointer        m_ppenThumbA;
         ::draw2d::pen_pointer        m_ppenThumbB;
         ::draw2d::pen_pointer        m_ppenHoverA;
         ::draw2d::pen_pointer        m_ppenHoverB;
         ::draw2d::brush_pointer      m_pbrush;
         i32                 m_iMargin;
         ::pointer < ::mutex >                   m_pmutexPaint;


         slider();
         virtual ~slider();


         void install_message_routing(::channel * pchannel) override;


         using ::audio_mixer_user::level_control::create_window;
         virtual bool create_window(::user::interaction * puiParent, const ::atom & atom) override;


         void update_drawing_objects();
         bool GetPageARect(::rectangle_i32 * lpRectClient, ::rectangle_i32 * lpRectTrack,  ::rectangle_i32 * lpRect);
         bool GetPageBRect(::rectangle_i32 * lpRectClient, ::rectangle_i32 * lpRectTrack,  ::rectangle_i32 * lpRect);
         bool GetThumbRect(::rectangle_i32 * lpRect);

         bool IsHover();
         void DoHoverSmartUpdate();
         void SetOrientation(enum_orientation orientation) override;

         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
         virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
         double GetRate() const;
         void SetRate(double rate);
         void  SetPos(i32 iPos) override;
         i32   GetPos() const override;
         void  SetRange(i32 iMin, i32 iMax, bool bRedraw);
         void  SetRange(i32 iMin, i32 iMax) override;
         void  SetRangeMax(i32 iMax, bool bRedraw);
         void  SetRangeMin(i32 iMin, bool bRedraw = false);
         void  GetRange(i32 & iMin, i32 & iMax) const;
         i32   GetRangeMin() const;
         i32   GetRangeMax()  const;
         void  SetPageSize(i32 iPageSize) override;
         i32   GetPageSize() const;
         void  SetLineSize(i32 iLineSize) override;
         i32   GetLineSize() const; 

         i32   ScrollLineA();
         i32   ScrollLineB();
         i32   ScrollPageB();
         i32   ScrollPageA();


         i32 SetTrackingPos(::point_i32 point);


         DECLARE_MESSAGE_HANDLER(on_message_create);
         DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
         DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
         DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
         virtual void _001OnTimer(::timer * ptimer) override;
         //DECLARE_MESSAGE_HANDLER(on_message_size);


      };


   } // namespace audio_mixer_user_base


} // namespace multimedia





