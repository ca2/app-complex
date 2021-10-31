#include "framework.h"
#include "aura/update.h"
#include "base/user/user/tab_pane.h"


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

      ::userex::pane_tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::on_message_create);

   }


   void pane_view::on_message_create(::message::message * pmessage)
   {

      if(pmessage->previous())
      {

         return;

      }

      set_tab("Menu", MENU_IMPACT);
      set_tab("Options", OPTIONS_IMPACT);
      set_tab("text://app-simple/drawing/:001", "drawing1");
      set_tab("text://app-simple/drawing/:002", "drawing2");
      set_tab("text://app-simple/drawing/:003", "drawing3");
      set_tab("text://app-simple/drawing/:arcs", "drawing4");
      set_tab("text://app-simple/drawing/:arcpths", "drawing5");
      set_tab("Font", FONTSEL_IMPACT);
      set_tab("Color", COLORSEL_IMPACT);
      set_tab("Open", FILEMANAGER_IMPACT);

      set_current_tab_by_id("drawing1");

   }


//   void pane_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::userex::pane_tab_view::_001OnNcDraw(pgraphics);
//
//   }


//   void pane_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::userex::pane_tab_view::_001OnDraw(pgraphics);
//
//   }

   
   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {
      
      auto papplication = get_application();

      if (papplication->has_property("notabs"))
      {

         return;

      }

      string strId = pimpactdata->m_id;

      if (::str::begins_eat_ci(strId, "drawing"))
      {

         auto pview = m_papplication->create_simple_drawing_view(this, pimpactdata);

         pview->m_id = pimpactdata->m_id;

         pview->m_prender->initialize_simple_drawing(atoi(strId));

         pimpactdata->m_eflag.add(::user::e_flag_hide_topic_on_show);

      }

      ::userex::pane_tab_view::on_create_impact(pimpactdata);

   }


   void pane_view::handle(::subject * psubject, ::context * pcontext)
   {

      if (psubject->user_interaction() == m_pcolorview)
      {

         if (psubject->m_id == ::e_subject_after_change_cur_sel || psubject->m_id == ::e_subject_after_change_cur_hover)
         {

            m_pcolorview->get_color().get_hls(m_pimpactTopic->m_prender->m_hlsText);

            if (psubject->m_id == ::e_subject_after_change_cur_sel)
            {

               string strId;

               strId = m_pimpactTopic->m_id + ".color";

               auto pdocument = m_pimpactTopic->get_document();

               pdocument->payload(strId) = m_pimpactTopic->m_prender->m_hlsText;

               ::output_debug_string("\n\nSIMPLE_DRAWING::PANE_VIEW::" + strId + "\n\n");

               auto papplication = get_application();

               papplication->data_set(strId, m_pimpactTopic->m_prender->m_hlsText);

            }

            m_pimpactTopic->set_need_redraw();

         }

      }
      else if (psubject->m_puserelement->m_id == impact_font_sel)
      {

         if (psubject->m_id == ::e_subject_after_change_cur_sel)
         {

            string strFont = m_pfontview->m_pimpact->get_cur_sel_face_name();

            m_pimpactTopic->m_prender->set_font(strFont);

         }
         else if (psubject->m_id == ::e_subject_after_change_cur_hover)
         {

            string strFont = m_pfontview->m_pimpact->get_cur_hover_face_name();

            if (strFont.has_char())
            {

               auto papplication = get_application();

               if (papplication->m_pstrHoverFontFamilyName)
               {

                  *papplication->m_pstrHoverFontFamilyName = strFont;

               }

            }

         }

      }


      ::userex::pane_tab_view::handle(psubject, pcontext);

   }


   void pane_view::on_change_cur_sel()
   {

      ::userex::pane_tab_view::on_change_cur_sel();

      string strId = get_view_id();

      string_array stra;

      stra.explode("->:<-", strId);

      if (::str::begins(get_view_id().to_string(), "drawing"))
      {

         auto ptabpaneFileManager = get_tab_by_id(FILEMANAGER_IMPACT);

         if (ptabpaneFileManager != nullptr && ptabpaneFileManager->m_pplaceholder != nullptr)
         {

            ptabpaneFileManager->m_pplaceholder->hide();

         }

         auto ptabpaneFontSel = get_tab_by_id(FONTSEL_IMPACT);

         if (ptabpaneFontSel != nullptr && ptabpaneFontSel->m_pplaceholder != nullptr)
         {

            ptabpaneFontSel->m_pplaceholder->hide();

         }

         __refer(m_pimpactTopic, m_pimpactdata->m_pplaceholder->get_hold());

         m_pimpactTopic->m_prender->properties().m_strHoverFontFamilyName.Empty();

      }
      
      if (get_view_id() == FONTSEL_IMPACT)
      {

         if (m_pimpactTopic != nullptr)
         {

            auto strFont1 = m_pimpactTopic->m_prender->m_strFont1;

            m_pfontview->set_sel_by_name(strFont1);

            m_pimpactTopic->m_prender->properties().m_strHoverFontFamilyName = strFont1;

            auto papplication = get_application();

            papplication->m_pstrHoverFontFamilyName = &m_pimpactTopic->m_prender->properties().m_strHoverFontFamilyName;

            m_pfontview->m_pimpact->ensure_sel_visible();

         }

      }
      else
      {

         auto papplication = get_application();

         papplication->m_pstrHoverFontFamilyName = nullptr;

      }

      if (get_view_id() == COLORSEL_IMPACT)
      {

         if (m_pimpactTopic != nullptr && m_pcolorview)
         {

            m_pcolorview->set_color(m_pimpactTopic->m_prender->m_hlsText);

         }

      }

   }


} // namespace complex_drawing



