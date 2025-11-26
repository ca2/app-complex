#include "framework.h"
#include "form_002.h"
#include "aura/message/user.h"


namespace app_complex_form
{


   form_002::form_002()
   {


   }


   form_002::~form_002()
   {

   }


   //void form_002::assert_ok() const
   //{

   //   ::app_simple_form::form_002::assert_ok();

   //}


   //void form_002::dump(dump_context & dumpcontext) const
   //{

   //   ::app_simple_form::form_002::dump(dumpcontext);

   //}


#ifdef _DEBUG

  
   long long form_002::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   long long form_002::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif


   void form_002::install_message_routing(::channel * psender)
   {

      ::app_simple_form::form_002::install_message_routing(psender);

      form::install_message_routing(psender);

      USER_MESSAGE_LINK(::user::e_message_create, psender, this, &form_002::on_message_create);

   }


   void form_002::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

//      øconstruct_new(m_pstill);
//
//      øconstruct_new(m_pedit);
//
//      øconstruct_new(m_pcombobox);
//
//      m_pcombobox->m_bEdit = false;
//
//      øconstruct_new(m_pbutton);
//
//      øconstruct_new(m_pstillResponse);
//
//      m_pstill->create_control(this, "still");
//
//      m_pedit->create_control(this, "edit");
//
//      m_pcombobox->create_control(this, "combo_box");
//
//      m_pbutton->create_control(this, "send_button");
//
//      m_pbutton->add_handler(this);
//
//      m_pstill->set_window_text("Enter  text:");
//
//      m_pedit->m_strEmtpyText = "Enter New Text Here";
//
//      m_pstillResponse->create_control(this, "still_response");
//
//      m_pbutton->set_window_text("Send");
//
//      m_pstillResponse->set_window_text("(Waiting for data to be sent...)");
//
//      m_pstillResponse->m_etextwrap = e_text_wrap_character;
//
//      m_pcombobox->m_edatamode = ::user::combo_box::data_mode_string;
//
//      m_pcombobox->add_string("Combo1", "ComboData001");
//
//      m_pcombobox->add_string("Combo2", "ComboData002");
//
//      m_pcombobox->add_string("Combo3", "ComboData003");
//
//      m_pcombobox->add_string("Combo4", "ComboData004");

   }


   void form_002::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::app_simple_form::form_002::on_layout(pgraphics);

//      double iLeft = 100.;
//
//      double y = 100.;
//
//      auto sizeStill = m_pstill->_001CalculateAdjustedFittingSize(pgraphics);
//
//      m_pstill->display_child(::double_rectangle_dimension(iLeft, y, 200, sizeStill.cy));
//
//      y += sizeStill.cy * 1.25;
//
//      auto sizeEdit = m_pedit->_001CalculateAdjustedFittingSize(pgraphics);
//
//      m_pedit->display_child(::double_rectangle_dimension(iLeft, y, 200.0, sizeEdit.cy));
//
//      y += sizeEdit.cy * 1.25;
//
//      auto sizeCombo = m_pcombobox->_001CalculateAdjustedFittingSize(pgraphics);
//
//      m_pcombobox->display_child(::double_rectangle_dimension(iLeft, y, 200., sizeCombo.cy));
//
//      y += sizeCombo.cy * 1.25;
//
//      auto sizeButton = m_pbutton->_001CalculateAdjustedFittingSize(pgraphics);
//
//      m_pbutton->display_child(::double_rectangle_dimension(iLeft, y, 200., sizeButton.cy));
//
//      y += sizeButton.cy * 1.25;
//
//      m_pstillResponse->display_child(::double_rectangle_dimension(iLeft, y, 200, sizeEdit.cy * 8));

   }


   void form_002::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

//      if (ptopic->id() == ::id_click)
//      {
//
//         if (ptopic->user_interaction_id() == "send_button")
//         {
//
//            string strText1;
//
//            m_pedit->get_text(strText1);
//
//            string strText2;
//
//            m_pcombobox->get_text(strText2);
//
//            string strText;
//
//            strText = strText1 + ";" + strText2;
//
//            string strData;
//
//            strData = m_pcombobox->get_current_item_string_value();
//
//            //auto routine = [this, strText, strData]()
//            //{
//            string strMessage = "<h1>send_button clicked</h1><h2>Text: " + strText + "</h2><h2>Data: " + strData + "</h2>" + strText;
//               output_error_message("<h1>send_button clicked</h1><h2>Text: " + strText + "</h2><h2>Data: " + strData + "</h2>", strText);
//
//            //};
//
//            //auto proutine = __routine(routine);
//
//            //main_async(proutine);
//
//               m_pstillResponse->set_window_text(strMessage);
//
//               m_pstillResponse->post_redraw();
//
//         }
//
//      }

      ::app_simple_form::form_002::handle(ptopic, phandlercontext);

   }


} // namespace app_complex_form



