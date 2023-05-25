#include "framework.h"



namespace mediaplay
{


   record_notify_impact::record_notify_impact()
   {

      m_dwOnTime = 800;
      m_dwOffTime = 200;

   }


   record_notify_impact::~record_notify_impact()
   {

   }


   bool record_notify_impact::create_window(::pointer<::user::interaction>pchannel, atom atom)
   {

      pchannel->SetTimer((uptr) this, minimum(m_dwOnTime, m_dwOffTime) / 2, nullptr);

      return ::user::interaction::create_window(pchannel, atom);

   }


   void record_notify_impact::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      if(ptimer->m_uEvent == ((uptr) this))
      {

         set_need_redraw();
         ptimer->m_bRet = true;
         return;
      }
      ptimer->m_bRet = false;
   }

   void record_notify_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      if((::get_tick() % (m_dwOnTime + m_dwOffTime)) > m_dwOnTime)
      {
         return;
      }
//      pgraphics->SetBkMode(TRANSPARENT);
      pgraphics->set_text_color(rgb(0, 0, 0));
      //   pgraphics->set(m_pfont);
      ::rectangle rectangle;
      client_rectangle(rectangle);
      pgraphics->color_blend(rectangle,
      rgb(255, 0, 0),
      127);

      pgraphics->draw_text(
      "Recording",
      rectangle,
      e_align_left
      | e_align_bottom);

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void record_notify_impact::install_message_routing(::channel * pchannel)
   {
      //MESSAGE_LINK(e_message_timer, pchannel, this, &record_notify_impact::_001OnTimer);
   }

   void record_notify_impact::GetParentClientRect(::rectangle_i32 * lprect)
   {
      m_puserinteractionParent->client_rectangle(lprect);
   }

} // namespace mediaplay
