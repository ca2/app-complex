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


#ifdef _DEBUG


   int64_t simple_form_001::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t simple_form_001::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


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

      __compose_new(m_pbuttonClear);

      __compose_new(m_pbuttonSend);

      __compose_new(m_pstillReceiver);

      m_pstill->create_control(this, "still");

      m_pedit->create_control(this, "edit");

      m_pedit->add_handler(this);

      m_pbuttonClear->create_control(this, "clear_button");

      m_pbuttonClear->add_handler(this);

      m_pbuttonSend->create_control(this, "send_button");

      m_pbuttonSend->add_handler(this);

      m_pstill->set_window_text("Enter new text:");

      m_pstillReceiver->create_control(this, "still");

      m_pstillReceiver->set_window_text("(Waiting to receive...)");

      m_pedit->m_strEmtpyText = "Enter New Text Here";

      string strInitialText;

      auto papplication = get_application();

      strInitialText = papplication->data_get("last_text");

      m_pedit->_001SetText(strInitialText, ::e_source_initialize);

      m_pbuttonClear->set_window_text("Clear");

      m_pbuttonSend->set_window_text("Send");

   }


   void simple_form_001::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_view::on_layout(pgraphics);

      double iLeft = 100.;

      double y = 100.;

      auto sizeStill = m_pstill->_001CalculateAdjustedFittingSize(pgraphics);

      auto rectangleStillMargin = m_pstill->get_margin(m_pstill->get_style(pgraphics));

      y += rectangleStillMargin.top;

      m_pstill->display_child(::rectangle_f64_dimension(iLeft, y, sizeStill.cx, sizeStill.cy));

      y += sizeStill.cy;

      y += rectangleStillMargin.bottom;

      auto sizeEdit = m_pedit->_001CalculateAdjustedFittingSize(pgraphics);

      auto rectangleEditMargin = m_pedit->get_margin(m_pedit->get_style(pgraphics), ::e_element_none);

      y += rectangleEditMargin.top;

      m_pedit->display_child(::rectangle_f64_dimension(iLeft, y, 600, sizeEdit.cy));

      y += sizeEdit.cy;

      y += rectangleEditMargin.bottom;

      auto sizeButtonClear = m_pbuttonClear->_001CalculateAdjustedFittingSize(pgraphics);

      auto sizeButtonSend = m_pbuttonSend->_001CalculateAdjustedFittingSize(pgraphics);

      auto sizeButtonMarginClear = m_pbuttonClear->get_margin(m_pedit->get_style(pgraphics));

      auto sizeButtonMarginSend = m_pbuttonSend->get_margin(m_pedit->get_style(pgraphics));

      y += maximum(sizeButtonMarginClear.top, sizeButtonMarginSend.top);

      auto button_width = maximum(sizeButtonClear.cx + 32, sizeButtonSend.cx + 32);

      auto button_height = maximum(sizeButtonClear.cy, sizeButtonSend.cy);

      m_pbuttonClear->display_child(::rectangle_f64_dimension(iLeft, y, button_width, button_height));

      m_pbuttonSend->display_child(::rectangle_f64_dimension(iLeft + button_width + 32, y, button_width, button_height));

      y += button_height + 20;

      m_pstillReceiver->display_child(::rectangle_f64_dimension(iLeft, y, 600, sizeEdit.cy * 5));

   }


   void simple_form_001::handle(::subject * psubject, ::context * pcontext)
   {

      if (psubject->m_id == ::e_subject_after_change_text)
      {

         if (psubject->m_actioncontext.is_user_source())
         {

            if (psubject->m_puserelement->m_id == "edit")
            {

               string strText;

               m_pedit->_001GetText(strText);

               auto papplication = get_application();

               if (strText == "This is a test. This is a test")
               {

                  output_debug_string("");

               }

               papplication->data_set("last_text", strText);

            }

         }

      }
      else if (psubject->m_id == ::e_subject_click)
      {

         if (psubject->m_puserelement->m_id == "clear_button")
         {

            m_pedit->_001SetText("", ::e_source_user);

         }
         else if (psubject->m_puserelement->m_id == "send_button")
         {

            string strText;

            m_pedit->_001GetText(strText);

            //main_async(__routine([this, strText]()
              // {

                  output_error_message("send_button clicked\nText: " + strText);

               //}));

                  m_pstillReceiver->set_window_text(strText);

                  m_pstillReceiver->post_redraw();

            psubject->m_bRet = true;

         }

      }

   }


} // namespace simple_form



