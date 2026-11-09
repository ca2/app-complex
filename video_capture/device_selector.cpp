#include "platform.h"
#include "device_selector.h"
#include "application.h"
#include "pane_impact.h"
#include "acme/constant/id.h"
#include "acme/handler/item.h"
#include "acme/user/user/content.h"
#include "acme/handler/topic.h"
#include "acme/user/user/mouse.h"
#include "app-complex/video_input/video_input.h"
#include "app-complex/video_input/device.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"


namespace app_complex_video_capture
{


   device_selector::device_selector()
   {

      // Let the tab placeholder size this view below visible tabs.
      m_bExtendOnParent = false;
      m_bExtendOnParentHostingArea = false;

      m_enonclient.erase(::user::e_non_client_background);
      m_enonclient.erase(::user::e_non_client_focus_rect);

      m_bDefaultClickHandling = true;
      m_bDefaultMouseHoverHandling = true;
      m_bDefaultParentMouseMessageHandling = true;

   }


   device_selector::~device_selector()
   {

   }


   void device_selector::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);


      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &device_selector::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &device_selector::on_message_destroy);

   }


   void device_selector::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      top_level()->add_fps_interest(this);
      
      get_app()->m_pvideoinput->add_handler(this);

   }


   void device_selector::on_message_destroy(::message::message * pmessage)
   {


   }

   //item* device_selector::get_user_item(::video_input::device* pdevice)
   //{

   //   auto& pitem = m_itemmap[pdevice];

   //   if (::is_null(pitem))
   //   {

   //      pitem = allocateø ::item();

   //      pitem->m_pparticle = pdevice;

   //      pitem->m_item.m_eelement = e_element_item;

   //      add_user_item(pitem);

   //   }

   //   return pitem;

   //}



   bool device_selector::on_impact_update()
   {

      if (!::user::impact::on_impact_update())
      {

         return false;

      }

      //for (auto & pdevice : get_app()->m_pvideoinput->devicea())
      //{

      //   auto & pitem = m_itemmap[pdevice];

      //   if (::is_null(pitem))
      //   {

      //      pitem = allocateø ::item();

      //      pitem->m_pparticle = pdevice;

      //      add_user_item(pitem);

      //   }

      //}

      main_content().m_pitema = get_app()->m_pvideoinput->m_pitemaDevice;

      //pointer_array < ::item > itema;

      //for (auto & pitem : m_itema)
      //{

      //   itema.add(pitem);

      //}

      //for (auto & pitem : itema)
      //{

      //   ::pointer < ::video_input::device > pdevice = pitem;

      //   if (!get_app()->m_pvideoinput->devicea().contains(pdevice))
      //   {

      //      itema.erase(pdevice);

      //   }

      //}

      //for (auto & pdevice : get_app()->m_pvideoinput->devicea())
      //{

      //   if (!itema.contains(pdevice))
      //   {

      //      itema.add(pdevice);

      //   }

      //}

      if (!get_app()->m_pvideoinput->contains_item(get_app()->m_pvideoinputdevice))
      {

         get_app()->set_current((::video_input::device *)nullptr);

      }

      //for (auto & pdevice : devicea)
      //{

      //   if (get_app()->m_pvideoinputdevice == pdevice)
      //   {

      //      get_app()->set_current((::video_input::device *)nullptr);

      //   }

      //   m_itema.erase(pdevice);

      //}

      //m_itema = itema;

      set_need_layout();
      
      set_need_redraw();
      
      post_redraw();

      return true;

   }


   void device_selector::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::i32_rectangle rectItem;
      
      if(main_content().m_pitema)
      {

         for (auto & pitem : *main_content().m_pitema)
         {
            
            auto puseritem = user_item(pitem);
            
            ::pointer < ::video_input::device > pdevice = pitem;
            
            if (::is_set(pdevice))
            {
               
               const bool selected = pdevice == get_app()->m_pvideoinputdevice;
               pdraw2dgraphics->fill_inset_rectangle(puseritem->m_rectangle2,
                  selected ? argb(255, 25, 100, 155)
                     : m_pitemHover == pdevice ? argb(255, 55, 65, 75) : argb(255, 30, 33, 37));
               if (selected)
               {
                  auto marker = puseritem->m_rectangle2;
                  marker.right = marker.left + 5;
                  pdraw2dgraphics->fill_inset_rectangle(marker, argb(255, 105, 220, 95));
               }

               auto rectangleName = puseritem->m_rectangle2;
               auto rectangleOpen = rectangleName;
               rectangleOpen.left = rectangleName.left + rectangleName.width() / 2;
               rectangleName.right = rectangleOpen.left;
               if (selected)
               {
                  pdraw2dgraphics->fill_inset_rectangle(rectangleOpen,
                     argb(255, 64, 70, 62));
                  auto rectangleDivider = rectangleOpen;
                  rectangleDivider.right = rectangleDivider.left + 1;
                  pdraw2dgraphics->fill_inset_rectangle(rectangleDivider, argb(200, 160, 180, 195));
               }
               rectangleName.left += 10;

               pdraw2dgraphics->set_font(this);
               pdraw2dgraphics->set_solid_color(::color::white);
               pdraw2dgraphics->draw_text(pdevice->m_strName, rectangleName, e_align_left_center);
               if (selected)
               {
                  const double playX = rectangleOpen.left + 18.0;
                  const double playY = (rectangleOpen.top + rectangleOpen.bottom) / 2.0;
                  ::f64_point play[] = {
                     {playX, playY - 9.0}, {playX, playY + 9.0}, {playX + 15.0, playY}
                  };
                  pdraw2dgraphics->set_solid_color(argb(255, 105, 220, 95));
                  pdraw2dgraphics->fill_polygon(play, 3);
                  auto rectangleLabel = rectangleOpen;
                  rectangleLabel.left += 45;
                  pdraw2dgraphics->set_solid_color(::color::white);
                  pdraw2dgraphics->draw_text("View capture", rectangleLabel, e_align_left_center);
               }
               
            }
            
         }

      }

   }


   void device_selector::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::impact::handle(ptopic, phandlercontext);
      
      if(ptopic->m_pparticle == get_app()->m_pvideoinput)
      {
         if(ptopic->id() == id_update)
         {
            
            update_impact();
         }
         
      }
      else if (ptopic->id() == id_initial_update)
      {

         ::pointer<::userex::pane_tab_impact>ppaneimpact = get_typed_parent < ::userex::pane_tab_impact >();
         //if(ppaneimpact.is_set())
         //{
         //   ppaneimpact->m_pflagview = this;
         //}

      }
      
   }


   ::user::document * device_selector::get_document()
   {

      return  (::user::impact::get_document());

   }


   bool device_selector::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      auto pdevice = dynamic_cast <::video_input::device *>(pitem);

      if (!pdevice) return false;

      auto puseritem = user_item(pdevice);
      ::i32_point point(-1, -1);
      if (pmouse)
      {
         point = pmouse->m_pointHost;
         point -= host_origin();
      }
      if (pmouse && puseritem
         && point.x >= puseritem->m_rectangle2.left + puseritem->m_rectangle2.width() / 2)
      {
         if (pdevice != get_app()->m_pvideoinputdevice) return true;

         ::pointer<::app_complex_video_capture::application> papp = get_app();
         ::pointer<::video_input::device> pdeviceOpen = pdevice;
         ::pointer<pane_impact> ppane = get_typed_parent<pane_impact>();
         // Recheck selection on the application task before opening the tab.
         papp->post([papp, pdeviceOpen, ppane]()
         {
            if (papp->m_pvideoinputdevice != pdeviceOpen) return;
            if (ppane)
               ppane->user_post([ppane]() { ppane->set_current_tab_by_id(MAIN_IMPACT); });
         });
         return true;
      }

      get_app()->set_current(pdevice);

      return true;

   }


   void device_selector::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle();

      int y = 10;

      int h = 50;

      //index iItem = 0;
      
      if(main_content().m_pitema && main_content().m_pitema->has_element())
      {

         for (auto & pitem : *main_content().m_pitema)
         {
            
            ::pointer < ::video_input::device > pdevice = pitem;
            
            auto puseritem = user_item(pdevice);
            
            if (::is_set(puseritem))
            {
               
               puseritem->m_rectangle2.left = rectangleX.left;
               puseritem->m_rectangle2.right = rectangleX.right;
               puseritem->m_rectangle2.top = y;
               puseritem->m_rectangle2.bottom = y + h;
               y += h;
               
//               pdevice->m_item.m_iItem = iItem;
//               pdevice->m_item.m_eelement = e_element_item;
               
               //iItem++;
               
            }
         
         }

      }

   }



} // namespace app_complex_video_capture



