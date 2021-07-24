#include "framework.h"
#include <math.h>


namespace simple_form
{



   simple_form_001::simple_form_001()
   {

   }


   simple_form_001::~simple_form_001()
   {

   }


   void simple_form_001::assert_valid() const
   {

      simple_form::assert_valid();

   }


   void simple_form_001::dump(dump_context & dumpcontext) const
   {

      simple_form::dump(dumpcontext);

   }


   int64_t simple_form_001::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t simple_form_001::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   void simple_form_001::install_message_routing(::channel * psender)
   {

      simple_form::install_message_routing(psender);

      MESSAGE_LINK(e_message_create, psender, this, &simple_form_001::on_message_create);

   }


   void simple_form_001::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      __compose_new(m_pstill);

      __compose_new(m_pedit);

      __compose_new(m_pbutton);

      m_pstill->create_window(this, "still");

      m_pedit->create_window(this, "edit");

      m_pbutton->create_window(this, "send_button");

      m_pstill->set_window_text("Enter new text:");

      m_pedit->m_strEmtpyText = "Enter New Text Here";

      m_pbutton->set_window_text("Send");

   }


   void simple_form_001::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_view::on_layout(pgraphics);

      int iLeft = 100;

      int y = 100;

      int iHeight = 25;

      m_pstill->set_window_position(e_zorder_top, iLeft, y, 200, iHeight, SWP_SHOWWINDOW);

      y += 30;

      m_pedit->set_window_position(e_zorder_top, iLeft, y, 600, iHeight, SWP_SHOWWINDOW);

      y += 30;

      m_pbutton->set_window_position(e_zorder_top, iLeft, y, 200, iHeight, SWP_SHOWWINDOW);

   }


   void simple_form_001::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::e_event_button_clicked)
      {

         if (pevent->m_id == "send_button")
         {

            string strText;

            m_pedit->_001GetText(strText);

            message_box("send_button clicked\nText: " + strText);

            pevent->m_bRet = true;

         }

      }

   }


} // namespace simple_form



