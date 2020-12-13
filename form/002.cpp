#include "framework.h"
#include <math.h>


namespace simple_form
{



   simple_form_002::simple_form_002()
   {


   }


   simple_form_002::~simple_form_002()
   {

   }


   void simple_form_002::assert_valid() const
   {

      simple_form::assert_valid();

   }


   void simple_form_002::dump(dump_context & dumpcontext) const
   {

      simple_form::dump(dumpcontext);

   }

  
   int64_t simple_form_002::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t simple_form_002::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }


   void simple_form_002::install_message_routing(::channel * psender)
   {

      simple_form::install_message_routing(psender);

      MESSAGE_LINK(e_message_create, psender, this, &simple_form_002::_001OnCreate);

   }


   void simple_form_002::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      __compose_new(m_pstill);

      __compose_new(m_pedit);

      __compose_new(m_pcombobox);

      m_pcombobox->m_bEdit = false;

      __compose_new(m_pbutton);

      m_pstill->create_window(this, "still");

      m_pedit->create_window(this, "edit");

      m_pcombobox->create_window(this, "combo");

      m_pbutton->create_window(this, "send_button");

      m_pstill->set_window_text("Enter new text:");

      m_pedit->m_strEmtpyText = "Enter New Text Here";

      m_pbutton->set_window_text("Send");

      m_pcombobox->m_edatamode = ::user::combo_box::data_mode_string;

      m_pcombobox->AddString("Combo1", "ComboData001");

      m_pcombobox->AddString("Combo2", "ComboData002");

      m_pcombobox->AddString("Combo3", "ComboData003");

      m_pcombobox->AddString("Combo4", "ComboData004");

   }


   void simple_form_002::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_view::on_layout(pgraphics);

      int iLeft = 100;

      int y = 100;

      int iHeight = 25;

      m_pstill->set_window_pos(zorder_top, iLeft, y, 200, iHeight, SWP_SHOWWINDOW);

      y += 30;

      m_pedit->set_window_pos(zorder_top, iLeft-30, y, 200, iHeight, SWP_SHOWWINDOW);

      y += 30;

      m_pcombobox->set_window_pos(zorder_top, iLeft, y, 200, iHeight, SWP_SHOWWINDOW);

      y += 30;

      m_pbutton->set_window_pos(zorder_top, iLeft-30, y, 200, iHeight, SWP_SHOWWINDOW);

   }


   void simple_form_002::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::e_event_button_clicked)
      {

         if (pevent->m_id == "send_button")
         {

            string strText;

            m_pcombobox->_001GetText(strText);

            string strData;

            strData = m_pcombobox->get_current_item_string_value();

            message_box("<h1>send_button clicked</h1><h2>Text: " + strText + "</h2><h2>Data: " + strData+"</h2>");

         }

      }

   }


} // namespace simple_form



