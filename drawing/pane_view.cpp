#include "framework.h"
#include "aura/update.h"


namespace complex_drawing
{


   pane_view::pane_view()
   {

   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void pane_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_view::install_message_routing(::channel * pchannel)
   {

      ::simple_drawing::tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::on_message_create);

   }


   void pane_view::on_message_create(::message::message * pmessage)
   {

      if(pmessage->previous())
      {

         return;

      }

      //papplication->__refer(papplication->m_ppaneview, this);

      set_tab("Font", FONTSEL_IMPACT);
      set_tab("Color", COLORSEL_IMPACT);
      set_tab("Open", FILEMANAGER_IMPACT);

      set_cur_tab_by_id("drawing1");

   }


   void pane_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::simple_drawing::tab_view::_001OnNcDraw(pgraphics);

   }


   void pane_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::simple_drawing::tab_view::_001OnDraw(pgraphics);

   }


   //void pane_view::on_change_cur_sel()
   //{

   //   ::simple_drawing::tab_view::on_change_cur_sel();

   //   string strId = get_view_id();

   //   string_array stra;

   //   stra.explode("->:<-",strId);

   //   if (get_view_id() == MENU_IMPACT)
   //   {

   //      __pointer(::user::menu_list_view) pmenuview = get_view_uie();

   //      pmenuview->destroy_menu();

   //      if (pmenuview->load_xml_menu("matter://simple_menu.xml"))
   //      {

   //         pmenuview->create_inline_menu(this, m_pimpactdata->m_pplaceholder);

   //      }

   //   }

   //   string strViewId = get_view_id().to_string();

   //   if(::str::begins(strViewId, "drawing"))
   //   {

   //      if(get_pane_by_id(FILEMANAGER_IMPACT) != nullptr && get_pane_by_id(FILEMANAGER_IMPACT)->m_pplaceholder != nullptr)
   //      {

   //         get_pane_by_id(FILEMANAGER_IMPACT)->m_pplaceholder->hide();

   //      }

   //      if (get_pane_by_id(FONTSEL_IMPACT) != nullptr && get_pane_by_id(FONTSEL_IMPACT)->m_pplaceholder != nullptr)
   //      {

   //         get_pane_by_id(FONTSEL_IMPACT)->m_pplaceholder->hide();

   //      }

   //      __refer(m_pviewTopic,m_pimpactdata->m_pplaceholder->get_hold());

   //   }
   //   //else if (get_view_id() == MENU_IMPACT)
   //   //{

   //   //   m_pdocMenu->open_document("matter://menu.html");

   //   //}

   //}


   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      if (m_papplication->has_property("notabs"))
      {

         return;

      }

      switch(pimpactdata->m_id)
      {
      case MENU_IMPACT:
      {

         ::user::impact::create_view < ::user::menu_list_view >(pimpactdata);

      }
      break;
      }

      ::simple_drawing::tab_view::on_create_impact(pimpactdata);
      ::userex::pane_tab_view::on_create_impact(pimpactdata);

   }




   //void pane_view::on_control_event(::user::control_event * pevent)
   //{


   //}


   void pane_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {


      ::simple_drawing::tab_view::on_subject(psubject, pcontext);

   }


   void pane_view::on_change_cur_sel()
   {

      ::userex::pane_tab_view::on_change_cur_sel();

      string strId = get_view_id();

      string_array stra;

      stra.explode("->:<-", strId);

      if (get_view_id() == MENU_IMPACT)
      {

         __pointer(::user::menu_list_view) pmenuview = get_view_uie();

         pmenuview->destroy_menu();

         if (pmenuview->load_xml_menu("matter://simple_menu.xml"))
         {

            pmenuview->create_inline_menu(this, m_pimpactdata->m_pplaceholder);

         }

      }

      if (::str::begins(get_view_id().to_string(), "drawing"))
      {

         if (get_pane_by_id(FILEMANAGER_IMPACT) != nullptr && get_pane_by_id(FILEMANAGER_IMPACT)->m_pplaceholder != nullptr)
         {

            get_pane_by_id(FILEMANAGER_IMPACT)->m_pplaceholder->hide();

         }

         if (get_pane_by_id(FONTSEL_IMPACT) != nullptr && get_pane_by_id(FONTSEL_IMPACT)->m_pplaceholder != nullptr)
         {

            get_pane_by_id(FONTSEL_IMPACT)->m_pplaceholder->hide();

         }

         __refer(m_pviewTopic, m_pimpactdata->m_pplaceholder->get_hold());

         m_pviewTopic->m_prender->m_strHoverFontFamilyName.Empty();

      }
      //else if (get_view_id() == MENU_IMPACT)
      //{

      //   m_pdocMenu->open_document("matter://menu.html");

      //}
      
      
      if (get_view_id() == FONTSEL_IMPACT)
      {

         if (m_pviewTopic != nullptr)
         {

            auto strFont1 = m_pviewTopic->m_prender->m_strFont1;

            m_pfontview->set_sel_by_name(strFont1);

            m_pviewTopic->m_prender->m_strHoverFontFamilyName = strFont1;

            m_papplication->m_pstrHoverFontFamilyName = &m_pviewTopic->m_prender->m_strHoverFontFamilyName;

            m_pfontview->m_pview->ensure_sel_visible();

         }

      }
      else
      {

         m_papplication->m_pstrHoverFontFamilyName = nullptr;

      }

      
      
      if (get_view_id() == COLORSEL_IMPACT)
      {

         if (m_pviewTopic != nullptr && m_pcolorview)
         {

            m_pcolorview->set_color(m_pviewTopic->m_prender->m_hlsText);

         }

      }

   }


   //void pane_view::on_create_impact(::user::impact_data* pimpactdata)
   //{

   //   if (papplication->has_property("notabs"))
   //   {

   //      return;

   //   }

   //   switch (pimpactdata->m_id)
   //   {
   //   case MENU_IMPACT:
   //   {

   //      ::user::impact::create_view < ::user::menu_list_view >(pimpactdata);

   //   }
   //   break;
   //   }

   //   string strId = pimpactdata->m_id;

   //   if (::str::begins_eat_ci(strId, "drawing"))
   //   {

   //      auto pview = papplication->create_simple_drawing_view(this, pimpactdata);

   //      pview->m_id = pimpactdata->m_id;

   //      pview->m_prender->initialize_simple_drawing(atoi(strId));

   //      pimpactdata->m_eflag.add(::user::e_flag_hide_topic_on_show);

   //   }

   //   ::userex::pane_tab_view::on_create_impact(pimpactdata);

   //}


   //string pane_view::get_hover_font()
   //{

   //   if (m_pimpactdata)
   //   {

   //      if (m_pimpactdata->m_id == impact_font_sel)
   //      {

   //         string strFont = m_pfontview->m_pview->get_cur_hover_face_name();

   //         return strFont;

   //      }

   //   }

   //   return "";

   //}


   void pane_view::on_control_event(::user::control_event* pevent)
   {

      if (pevent->m_puie == m_pcolorview)
      {

         if (pevent->m_eevent == ::user::e_event_after_change_cur_sel || pevent->m_eevent == ::user::e_event_after_change_cur_hover)
         {

            m_pcolorview->get_color().get_hls(m_pviewTopic->m_prender->m_hlsText);

            if (pevent->m_eevent == ::user::e_event_after_change_cur_sel)
            {

               string strId;

               strId = m_pviewTopic->m_id + ".color";

               m_pviewTopic->get_document()->set(strId, m_pviewTopic->m_prender->m_hlsText);

               ::output_debug_string("\n\nSIMPLE_DRAWING::PANE_VIEW::" + strId + "\n\n");

               m_papplication->data_set(strId, m_pviewTopic->m_prender->m_hlsText);

            }

            m_pviewTopic->set_need_redraw();

         }

      }
      else if (pevent->m_id == impact_font_sel)
      {

         if (pevent->m_eevent == ::user::e_event_after_change_cur_sel)
         {

            string strFont = m_pfontview->m_pview->get_cur_sel_face_name();

            m_pviewTopic->m_prender->set_font(strFont);

         }
         else if (pevent->m_eevent == ::user::e_event_after_change_cur_hover)
         {

            string strFont = m_pfontview->m_pview->get_cur_hover_face_name();
            
            if (strFont.has_char())
            {

               if (m_papplication->m_pstrHoverFontFamilyName)
               {

                  *m_papplication->m_pstrHoverFontFamilyName = strFont;

               }

            }

         }

      }


   }




} // namespace complex_drawing



