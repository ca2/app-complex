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

      pchannel->set_timer((uptr) this, minimum(m_dwOnTime, m_dwOffTime) / 2, nullptr);

      return ::user::interaction::create_window(pchannel, atom);

   }


   void record_notify_impact::on_timer(::timer * ptimer)
   {

      ::user::interaction::on_timer(ptimer);

      if(ptimer->m_uTimer == ((uptr) this))
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
      ::double_rectangle rectangle;
      this->rectangle(rectangle);
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
      //MESSAGE_LINK(e_message_timer, pchannel, this, &record_notify_impact::on_timer);
   }

   void record_notify_impact::GetParentClientRect(::int_rectangle * lprect)
   {
      m_puserinteractionParent->rectangle(lprect);
   }

} // namespace mediaplay
