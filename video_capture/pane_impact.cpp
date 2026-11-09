#include "platform.h"
#include "pane_impact.h"
#include "berg/user/user/tab_data.h"
#include "berg/user/experience/frame_window.h"
#include "device_selector.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/handler/request.h"
#include "acme/handler/topic.h"
#include "berg/user/form/document.h"
#include "berg/user/user/tab_pane.h"
#include "berg/user/user/place_holder.h"
#include "berg/user/user/single_document_template.h"
#include "aura/user/user/system.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "app-complex/video_input/video_input.h"
#include "app-complex/video_input/device.h"


namespace app_complex_video_capture
{

   
   pane_impact::pane_impact()
   {

      // Fullscreen tabs overlay the active view, so draw them after its children.
      m_bDrawTabAtBackground = false;
   }


   pane_impact::~pane_impact()
   {

   }


   //void pane_impact::assert_ok() const
   //{

   //   ::user::impact::assert_ok();

   //}


   //void pane_impact::dump(dump_context & dumpcontext) const
   //{

   //   ::user::impact::dump(dumpcontext);

   //}


   void pane_impact::install_message_routing(::channel * pchannel)
   {

      ::userex::pane_tab_impact::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &pane_impact::on_message_create);

   }


   void pane_impact::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      ::cast<::experience::frame_window> pframe = top_level_frame();
      if (pframe)
      {
         set_auto_hide_controller(pframe->full_screen_auto_hide());
      }

      set_tab("Select Device","device_selector");
      set_tab("app_complex_video_capture", MAIN_IMPACT);
      set_tab("Open", "file_manager_impact");

      // Each tab chooses whether fullscreen chrome overlays its content.
      get_tab_by_id(MAIN_IMPACT)->payload("full_screen_overlay") = true;
      get_tab_by_id("device_selector")->payload("full_screen_overlay") = false;

      set_current_tab_by_id(MAIN_IMPACT);

   }


   ::i32_rectangle pane_impact::hosting_rectangle(::user::enum_layout elayout)
   {
      auto ppane = get_tab(get_current_tab_index());
      if (ppane && ppane->payload("full_screen_overlay").as_bool()
         && top_level()->layout().is_full_screen(::user::e_layout_sketch))
      {
         return rectangle(elayout);
      }
      return ::userex::pane_tab_impact::hosting_rectangle(elayout);
   }


   void pane_impact::on_perform_top_down_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {
      ::userex::pane_tab_impact::on_perform_top_down_layout(pdraw2dgraphics);

      auto rectangleClient = rectangle(::user::e_layout_layout);
      if (m_pAutoHide->m_bEffectiveVisibleControl)
      {
         if (get_data()->m_bVertical)
            rectangleClient.left = get_data()->m_rectangleTab.right;
         else
            rectangleClient.top = get_data()->m_rectangleTab.bottom;
      }
      get_data()->m_rectangleHosting = rectangleClient;

      auto ppane = get_tab(get_current_tab_index());
      if (ppane && ppane->m_pplaceholder)
      {
         const bool bOverlayTabs = ppane->payload("full_screen_overlay").as_bool()
            && top_level()->layout().is_full_screen(::user::e_layout_sketch);
         auto rectanglePane = bOverlayTabs ? rectangle(::user::e_layout_layout) : rectangleClient;
         auto pholder = ppane->m_pplaceholder;
         auto pchild = pholder->get_hold();
         if (pchild)
         {
            pchild->m_bExtendOnParent = bOverlayTabs;
            pchild->m_bExtendOnParentIfOnlyClient = false;
            pchild->m_bExtendOnParentHostingArea = false;
         }
         // The wrapper borrows its child's policy, so it cannot independently
         // force the video back into the smaller tab client area.
         pholder->payload("borrow_child_layout_properties") = true;
         pholder->place(rectanglePane, ::user::e_layout_layout, pdraw2dgraphics);
         pholder->set_need_perform_layout();
      }
   }


   void pane_impact::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {
      // The tab's shared auto-hide controller decides whether the strip draws.
      ::userex::pane_tab_impact::_001OnDraw(pdraw2dgraphics);
   }


   void pane_impact::on_change_cur_sel()
   {

      ::userex::pane_tab_impact::on_change_cur_sel();

   }



   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      if (pimpactdata->id() == "device_selector")
      {

         create_impact < device_selector >(pimpactdata);

      }
      else
      {

         switch (pimpactdata->id().as_i32())
         {
         case MAIN_IMPACT:
         {
         
            auto pcreate = m_pusersystem->m_prequest;

            auto & payloadFile = pcreate->m_payloadFile;

            auto papp = get_app();

            papp->impact_system("impact")->open_document_file(papp, payloadFile, true, pimpactdata->m_pplaceholder);

         }

         break;

         }

      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::userex::pane_tab_impact::handle(ptopic, phandlercontext);
      if (ptopic->id() == "auto_hide_visibility")
      {
         return;
      }

      if (ptopic->user_interaction() && ptopic->user_interaction()->is_ascendant(m_pformdocumentMenu, true))
      {


         if (ptopic->id() == ::id_load_form_data)
         {

            ::user::impact * pimpact = m_pformdocumentMenu->get_impact(0);

            string strDevice = get_app()->get_current_video_input_device();

            for (auto & pitem : get_app()->m_pvideoinput->itema())
            {

               ::pointer < ::video_input::device > pdevice = pitem;

               string strId = pdevice->get_id2();

               string strCheck = "video_input_" + strId;

               ::pointer<::user::interaction>pcheck = pimpact->get_child_by_id(strCheck);

               pcheck->add_handler(this);

               bool bSetCheck = strId == strDevice;

               pcheck->set_check(bSetCheck, ::e_source_sync);

               pcheck->add_handler(this);

            }

            ptopic->m_bOk = true;

            ptopic->m_bRet = true;

            return;

         }

         if (ptopic->id() == ::id_set_check && ptopic->user_interaction() != nullptr)
         {

            if (ptopic->m_actioncontext.is_user_source())
            {

               string strCheck = ptopic->user_interaction_id();

               information() << strCheck;

               string strId;

               if (strCheck.case_insensitive_begins_get_remainder(strId, "video_input_"))
               {

                  if (ptopic->user_interaction()->is_checked())
                  {

                     get_app()->set_current_video_input_device(strId);

                  }
                  else
                  {

                     get_app()->set_current_video_input_device("");

                  }

               }

               ptopic->m_bOk = true;

               ptopic->m_bRet = true;

            }

            return;

         }


         if(ptopic->id() == ::id_after_change_text)
         {


         //if(ptopic->user_interaction_id() == "clockverse")
         //   {
         //      papp->set_binding_clockverse_country_time_zone_set_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_interaction_id() == "clockverse_auto")
         //   {
         //      papp->set_auto_launch_clockverse_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_interaction_id() == "flag")
         //   {
         //      papp->set_binding_flag_country_ca2_domain_image_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_interaction_id() == "flag_auto")
         //   {
         //      papp->set_auto_launch_flag_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         }
      }

      
   }





} // namespace app_complex_video_capture





