#include "framework.h"
#include "pane_impact.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/graphics/draw2d/_binary_stream.h"
#include "acme/handler/topic.h"
#include "apex/database/_binary_stream.h"
#include "base/user/user/document.h"
#include "app-simple/drawing/render.h"
#include "app-simple/drawing/impact.h"
#include "base/user/user/tab_pane.h"


namespace app_complex_drawing
{


   pane_impact::pane_impact()
   {

   }


   pane_impact::~pane_impact()
   {

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
      set_tab("Options", APP_OPTIONS_IMPACT);
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


   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {
      
      auto papp = get_app();

      if (papp->has_property("notabs"))
      {

         return;

      }

      string strId = pimpactdata->m_atom;

      if (strId.case_insensitive_begins_eat("drawing"))
      {

         auto pimpact = get_app()->create_simple_drawing_impact(this, pimpactdata);

         pimpact->m_atom = pimpactdata->m_atom;

         pimpact->m_prender->initialize_simple_drawing(atoi(strId));

         //pimpactdata->m_eflag.add(::user::e_flag_hidid_on_show);

      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->user_interaction() == get_color_interaction())
      {

         if (ptopic->m_atom == ::id_after_change_cur_sel || ptopic->m_atom == ::id_after_change_cur_hover)
         {

            m_pimpactDrawing->m_prender->m_hlsText = get_color_interaction()->get_sel_color();

            if (ptopic->m_atom == ::id_after_change_cur_sel)
            {

               string strId;

               strId = m_pimpactDrawing->m_atom + ".color";

               auto pdocument = m_pimpactDrawing->get_document();

               pdocument->payload(strId) = m_pimpactDrawing->m_prender->m_hlsText;

               informationf("\n\nSIMPLE_DRAWING::PANE_VIEW::" + strId + "\n\n");

               auto papp = get_app();

               papp->datastream()->set(strId, m_pimpactDrawing->m_prender->m_hlsText);

            }

            m_pimpactDrawing->set_need_redraw();

         }

      }
      else if (ptopic->m_puserelement
               && ptopic->user_interaction_id() == FONTSEL_IMPACT)
      {

         if (ptopic->m_atom == ::id_after_change_cur_sel)
         {

            string strFont = get_font_interaction()->get_sel_by_name();

            if(::is_set(m_pimpactDrawing))
            {

               m_pimpactDrawing->m_prender->set_font(strFont);

            }

         }
         else if (ptopic->m_atom == ::id_after_change_cur_hover)
         {

            string strFont = get_font_interaction()->get_hover_by_name();

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

      string strId = get_impact_id();

      string_array stra;

      stra.explode("->:<-", strId);

      auto pimpactOldDrawing = m_pimpactDrawing;

      if(::is_set(pimpactOldDrawing))
      {

         pimpactOldDrawing->m_prender->set_hover_font("");

      }

      if (get_impact_id().begins("drawing"))
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

         m_pimpactDrawing = m_pimpactdata->m_pplaceholder->get_hold();

         if (::is_set(pimpactOldDrawing))
         {

            pimpactOldDrawing->get_parent()->hide();

         }

      }
      else if (get_impact_id() == FONTSEL_IMPACT)
      {

         if (m_pimpactDrawing != nullptr)
         {

            auto strFont1 = m_pimpactDrawing->m_prender->m_strFont1;

            get_font_interaction()->set_sel_by_name(strFont1);

            m_pimpactDrawing->m_prender->set_hover_font(strFont1);

            get_font_interaction()->ensure_sel_visible();

         }

      }
      else if (get_impact_id() == COLORSEL_IMPACT)
      {

         if (m_pimpactDrawing != nullptr && get_color_interaction())
         {

            get_color_interaction()->set_sel_color(m_pimpactDrawing->m_prender->m_hlsText);

         }

      }

      if (m_pimpactdataOld && !m_pimpactdataOld->m_atom.begins("drawing"))
      {

         m_pimpactdataOld->m_pplaceholder->hide();

      }

   }


} // namespace complex_drawing



