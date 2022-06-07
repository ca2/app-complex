#include "framework.h"
#include "aura/update.h"
#include "base/user/user/tab_pane.h"


namespace app_complex_drawing
{


   pane_impact::pane_impact()
   {

   }


   pane_impact::~pane_impact()
   {

   }


   void pane_impact::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void pane_impact::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_impact::install_message_routing(::channel * pchannel)
   {

      ::userex::pane_tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_impact::on_message_create);

   }


   void pane_impact::on_message_create(::message::message * pmessage)
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
      set_tab("text://app-simple/drawing/:box gradient", "drawing4");
      set_tab("text://app-simple/drawing/:circle path", "drawing5");
      set_tab("text://app-simple/drawing/:arcs", "drawing6");
      set_tab("text://app-simple/drawing/:arcpths", "drawing7");
      set_tab("Font", FONTSEL_IMPACT);
      set_tab("Color", COLORSEL_IMPACT);
      set_tab("Open", FILEMANAGER_IMPACT);

      set_current_tab_by_id("drawing1");

   }


//   void pane_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::userex::pane_tab_impact::_001OnNcDraw(pgraphics);
//
//   }


//   void pane_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::userex::pane_tab_impact::_001OnDraw(pgraphics);
//
//   }

   
   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {
      
      auto papp = get_app();

      if (papp->has_property("notabs"))
      {

         return;

      }

      string strId = pimpactdata->m_atom;

      if (::::str::ch().begins_eat_ci(strId, "drawing"))
      {

         auto pimpact = m_papp->create_simple_drawing_view(this, pimpactdata);

         pimpact->m_atom = pimpactdata->m_atom;

         pimpact->m_prender->initialize_simple_drawing(atoi(strId));

         pimpactdata->m_eflag.add(::user::e_flag_hidid_on_show);

      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->user_interaction() == m_pcolorview)
      {

         if (ptopic->m_atom == ::id_after_change_cur_sel || ptopic->m_atom == ::id_after_change_cur_hover)
         {

            m_pcolorview->get_color().get_hls(m_pimpactDrawing->m_prender->m_hlsText);

            if (ptopic->m_atom == ::id_after_change_cur_sel)
            {

               string strId;

               strId = m_pimpactDrawing->m_atom + ".color";

               auto pdocument = m_pimpactDrawing->get_document();

               pdocument->payload(strId) = m_pimpactDrawing->m_prender->m_hlsText;

               ::output_debug_string("\n\nSIMPLE_DRAWING::PANE_VIEW::" + strId + "\n\n");

               auto papp = get_app();

               papp->data_set(strId, m_pimpactDrawing->m_prender->m_hlsText);

            }

            m_pimpactDrawing->set_need_redraw();

         }

      }
      else if (ptopic->m_puserelement->m_atom == impact_font_sel)
      {

         if (ptopic->m_atom == ::id_after_change_cur_sel)
         {

            string strFont = m_pfontview->m_pimpact->get_cur_sel_face_name();

            if(::is_set(m_pimpactDrawing))
            {

               m_pimpactDrawing->m_prender->set_font(strFont);

            }

         }
         else if (ptopic->m_atom == ::id_after_change_cur_hover)
         {

            string strFont = m_pfontview->m_pimpact->get_cur_hover_face_name();

            if(::is_set(m_pimpactDrawing))
            {

               m_pimpactDrawing->m_prender->set_hover_font(strFont);

            }

         }

      }

      ::userex::pane_tab_impact::handle(ptopic, pcontext);

   }


   void pane_impact::on_change_cur_sel()
   {

      ::userex::pane_tab_impact::on_change_cur_sel();

      string strId = get_view_id();

      string_array stra;

      stra.explode("->:<-", strId);

      auto pimpactOldDrawing = m_pimpactDrawing;

      if(::is_set(pimpactOldDrawing))
      {

         pimpactOldDrawing->m_prender->set_hover_font("");

      }

      if (::::str::ch().begins(get_view_id().to_string(), "drawing"))
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

         __refer(m_pimpactDrawing, m_pimpactdata->m_pplaceholder->get_hold());

      }

      if (get_view_id() == FONTSEL_IMPACT)
      {

         if (m_pimpactDrawing != nullptr)
         {

            auto strFont1 = m_pimpactDrawing->m_prender->m_strFont1;

            m_pfontview->set_sel_by_name(strFont1);

            m_pimpactDrawing->m_prender->set_hover_font(strFont1);

            m_pfontview->m_pimpact->ensure_sel_visible();

         }

      }

      if (get_view_id() == COLORSEL_IMPACT)
      {

         if (m_pimpactDrawing != nullptr && m_pcolorview)
         {

            m_pcolorview->set_color(m_pimpactDrawing->m_prender->m_hlsText);

         }

      }

   }


} // namespace complex_drawing



