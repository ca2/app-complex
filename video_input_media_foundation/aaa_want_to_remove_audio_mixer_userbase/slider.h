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
         int                 m_iLineSize;
         int                 m_iPageSize;
         int                 m_iRangeMin;
         int                 m_iRangeMax;
         int                 m_iPos;
         int                 m_iTrackingPos;
         int                 m_eorientation;
         bool                    m_bTracking;
         bool                    m_bThumbHover;
         point                   m_sizeTrackOffset;
         ::draw2d::pen_pointer        m_ppenThumbA;
         ::draw2d::pen_pointer        m_ppenThumbB;
         ::draw2d::pen_pointer        m_ppenHoverA;
         ::draw2d::pen_pointer        m_ppenHoverB;
         ::draw2d::brush_pointer      m_pbrush;
         int                 m_iMargin;
         ::pointer < ::mutex >                   m_pmutexPaint;


         slider();
         virtual ~slider();


         void install_message_routing(::channel * pchannel) override;


         using ::audio_mixer_user::level_control::create_window;
         virtual bool create_window(::user::interaction * puiParent, const ::atom & atom) override;


         void update_drawing_objects();
         bool GetPageARect(::int_rectangle * lpRectClient, ::int_rectangle * lpRectTrack,  ::int_rectangle * lpRect);
         bool GetPageBRect(::int_rectangle * lpRectClient, ::int_rectangle * lpRectTrack,  ::int_rectangle * lpRect);
         bool GetThumbRect(::int_rectangle * lpRect);

         bool IsHover();
         void DoHoverSmartUpdate();
         void SetOrientation(enum_orientation orientation) override;

         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
         virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
         double GetRate() const;
         void SetRate(double rate);
         void  SetPos(int iPos) override;
         int   GetPos() const override;
         void  SetRange(int iMin, int iMax, bool bRedraw);
         void  SetRange(int iMin, int iMax) override;
         void  SetRangeMax(int iMax, bool bRedraw);
         void  SetRangeMin(int iMin, bool bRedraw = false);
         void  GetRange(int & iMin, int & iMax) const;
         int   GetRangeMin() const;
         int   GetRangeMax()  const;
         void  SetPageSize(int iPageSize) override;
         int   GetPageSize() const;
         void  SetLineSize(int iLineSize) override;
         int   GetLineSize() const; 

         int   ScrollLineA();
         int   ScrollLineB();
         int   ScrollPageB();
         int   ScrollPageA();


         int SetTrackingPos(::int_point point);


         DECLARE_MESSAGE_HANDLER(on_message_create);
         DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
         DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
         DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
         virtual void _001OnTimer(::timer * ptimer) override;
         //DECLARE_MESSAGE_HANDLER(on_message_size);


      };


   } // namespace audio_mixer_user_base


} // namespace multimedia





