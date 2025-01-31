#include "framework.h"
#include "form_001.h"
#include "aura/message/user.h"


namespace app_complex_form
{


   form_001::form_001()
   {

   }


   form_001::~form_001()
   {

   }


#ifdef _DEBUG


   huge_integer form_001::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   huge_integer form_001::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif


   void form_001::install_message_routing(::channel * psender)
   {

      ::app_simple_form::form_001::install_message_routing(psender);

      form::install_message_routing(psender);

      MESSAGE_LINK(e_message_create, psender, this, &form_001::on_message_create);

   }


   void form_001::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

//      __construct_new(m_pstill);
//
//      __construct_new(m_pedit);
//
//      __construct_new(m_pbuttonClear);
//
//      __construct_new(m_pbuttonSend);
//
//      __construct_new(m_pstillReceiver);
//
//      m_pstill->create_control(this, "still");
//
//      m_pedit->create_control(this, "edit");
//
//      m_pedit->add_handler(this);
//
//      m_pbuttonClear->create_control(this, "clear_button");
//
//      m_pbuttonClear->add_handler(this);
//
//      m_pbuttonSend->create_control(this, "send_button");
//
//      m_pbuttonSend->add_handler(this);
//
//      m_pstill->set_window_text("Enter  text:");
//
//      m_pstillReceiver->create_control(this, "still");
//
//      m_pstillReceiver->set_window_text("(Waiting to receive...)");
//
//      m_pedit->m_strEmtpyText = "Enter New Text Here";
//
//      string strInitialText;
//
//      auto papp = get_app();
//
//      strInitialText = papp->datastream()->get("last_text");
//
//      m_pedit->set_text(strInitialText, ::e_source_initialize);
//
//      m_pbuttonClear->set_window_text("Clear");
//
//      m_pbuttonSend->set_window_text("Send");

   }


   void form_001::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::app_simple_form::form_001::on_layout(pgraphics);

//      double iLeft = 100.;
//
//      double y = 100.;
//
//      auto sizeStill = m_pstill->_001CalculateAdjustedFittingSize(pgraphics);
//
//      auto rectangleStillMargin = m_pstill->get_margin(m_pstill->get_style(pgraphics));
//
//      y += rectangleStillMargin.top();
//
//      m_pstill->display_child(::double_rectangle_dimension(iLeft, y, sizeStill.cx(), sizeStill.cy()));
//
//      y += sizeStill.cy();
//
//      y += rectangleStillMargin.bottom();
//
//      auto sizeEdit = m_pedit->_001CalculateAdjustedFittingSize(pgraphics);
//
//      auto rectangleEditMargin = m_pedit->get_margin(m_pedit->get_style(pgraphics), ::e_element_none);
//
//      y += rectangleEditMargin.top();
//
//      m_pedit->display_child(::double_rectangle_dimension(iLeft, y, 600, sizeEdit.cy()));
//
//      y += sizeEdit.cy();
//
//      y += rectangleEditMargin.bottom();
//
//      auto sizeButtonClear = m_pbuttonClear->_001CalculateAdjustedFittingSize(pgraphics);
//
//      auto sizeButtonSend = m_pbuttonSend->_001CalculateAdjustedFittingSize(pgraphics);
//
//      auto sizeButtonMarginClear = m_pbuttonClear->get_margin(m_pedit->get_style(pgraphics));
//
//      auto sizeButtonMarginSend = m_pbuttonSend->get_margin(m_pedit->get_style(pgraphics));
//
//      y += maximum(sizeButtonMarginClear.top(), sizeButtonMarginSend.top());
//
//      auto button_width = maximum(sizeButtonClear.cx() + 32, sizeButtonSend.cx() + 32);
//
//      auto button_height = maximum(sizeButtonClear.cy(), sizeButtonSend.cy());
//
//      m_pbuttonClear->display_child(::double_rectangle_dimension(iLeft, y, button_width, button_height));
//
//      m_pbuttonSend->display_child(::double_rectangle_dimension(iLeft + button_width + 32, y, button_width, button_height));
//
//      y += button_height + 20;
//
//      m_pstillReceiver->display_child(::double_rectangle_dimension(iLeft, y, 600, sizeEdit.cy() * 5));

   }


   void form_001::handle(::topic * ptopic, ::context * pcontext)
   {

//      if (ptopic->id() == ::id_after_change_text)
//      {
//
//         if (ptopic->m_actioncontext.is_user_source())
//         {
//
//            if (ptopic->user_interaction_id() == "edit")
//            {
//
//               string strText;
//
//               m_pedit->get_text(strText);
//
//               auto papp = get_app();
//
//               if (strText == "This is a test. This is a test")
//               {
//
//                  informationf("");
//
//               }
//
//               papp->datastream()->set("last_text", strText);
//
//            }
//
//         }
//
//      }
//      else if (ptopic->id() == ::id_click)
//      {
//
//         if (ptopic->user_interaction_id() == "clear_button")
//         {
//
//            m_pedit->set_text("", ::e_source_user);
//
//         }
//         else if (ptopic->user_interaction_id() == "send_button")
//         {
//
//            string strText;
//
//            m_pedit->get_text(strText);
//
//            //main_async(__routine([this, strText]()
//              // {
//
//                  output_error_message("send_button clicked\nText: " + strText);
//
//               //}));
//
//                  m_pstillReceiver->set_window_text(strText);
//
//                  m_pstillReceiver->post_redraw();
//
//            ptopic->m_bRet = true;
//
//         }
//
//      }

      ::app_simple_form::form_001::handle(ptopic, pcontext);

   }


} // namespace app_complex_form



