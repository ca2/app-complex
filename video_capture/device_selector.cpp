#include "framework.h"
#include "device_selector.h"
#include "application.h"
#include "pane_impact.h"
#include "acme/handler/item.h"
#include "app-complex/video_input/video_input.h"
#include "app-complex/video_input/device.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"


namespace app_complex_video_capture
{


   device_selector::device_selector()
   {

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

      m_bClickDefaultMouseHandling = true;
      m_bHoverDefaultMouseHandling = true;

   }


   device_selector::~device_selector()
   {

   }


   //void device_selector::assert_ok() const
   //{

   //   user::box::assert_ok();

   //}


   //void device_selector::dump(dump_context & dumpcontext) const
   //{

   //   user::box::dump(dumpcontext);

   //}


   void device_selector::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);


      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &device_selector::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &device_selector::on_message_destroy);

   }


   void device_selector::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      top_level()->add_prodevian(this);

   }


   void device_selector::on_message_destroy(::message::message * pmessage)
   {


   }

   item* device_selector::get_user_item(::video_input::device* pdevice)
   {

      auto& pitem = m_itemmap[pdevice];

      if (::is_null(pitem))
      {

         pitem = __new(::item);

         pitem->m_pparticle = pdevice;

         pitem->m_eelement = e_element_item;

         add_user_item(pitem);

      }

      return pitem;

   }



   void device_selector::update_item_map()
   {


      //for (auto & pdevice : get_app()->m_pvideoinput->devicea())
      //{

      //   auto & pitem = m_itemmap[pdevice];

      //   if (::is_null(pitem))
      //   {

      //      pitem = __new(::item);

      //      pitem->m_pparticle = pdevice;

      //      add_user_item(pitem);

      //   }

      //}

      pointer_array < ::video_input::device > devicea;

      for (auto & pair : m_itemmap)
      {

         devicea.add(pair.m_element1);

      }

      for (auto & pdevice : get_app()->m_pvideoinput->devicea())
      {

         devicea.erase(pdevice);

      }

      for (auto & pdevice : devicea)
      {

         if (get_app()->m_pvideoinputdevice == pdevice)
         {

            get_app()->set_current((::video_input::device *)nullptr);

         }

         auto & pitem = m_itemmap[pdevice];

         m_pitema->erase(pitem);

         m_itemmap.erase_item(pdevice);

      }

      set_need_layout();

   }


   void device_selector::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rectItem;

      for (auto & pair : m_itemmap)
      {

         auto & pitem = pair.m_element2;

         if (::is_set(pitem))
         {

            if (pair.m_element1 == get_app()->m_pvideoinputdevice)
            {

               if (m_pitemHover == pitem)
               {

                  pgraphics->fill_inset_rectangle(pitem->m_rectangle, argb(127, 80, 180, 230));

               }
               else
               {

                  pgraphics->fill_inset_rectangle(pitem->m_rectangle, argb(127, 50, 150, 200));

               }

            }
            else
            {

               if (m_pitemHover == pitem)
               {

                  pgraphics->fill_inset_rectangle(pitem->m_rectangle, argb(127, 100, 200, 255));

               }
               else
               {

                  pgraphics->fill_inset_rectangle(pitem->m_rectangle, argb(127, 0, 0, 0));

               }

            }

            pgraphics->draw_text(pair.m_element1->m_strName, pitem->m_rectangle, e_align_left_center);

         }

      }

   }


   void device_selector::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == ID_INITIAL_UPDATE)
      {

         ::pointer<::userex::pane_tab_impact>ppaneimpact = get_typed_parent < ::userex::pane_tab_impact >();
         //if(ppaneimpact.is_set())
         //{
         //   ppaneimpact->m_pflagview = this;
         //}

      }
      __UNREFERENCED_PARAMETER(ptopic);
   }


   ::user::document * device_selector::get_document()
   {

      return  (::user::impact::get_document());

   }


   bool device_selector::on_click(::item * pitem)
   {

      auto pdevice = dynamic_cast <::video_input::device *>(pitem->m_pparticle.m_p);

      get_app()->set_current(pdevice);

      return true;

   }


   void device_selector::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      int y = 10;

      int h = 50;

      index iItem = 0;

      for (auto & pdevice : get_app()->m_pvideoinput->devicea())
      {

         auto pitem = get_user_item(pdevice);

         if (::is_set(pitem))
         {

            pitem->m_rectangle.left = rectangleClient.left;
            pitem->m_rectangle.right = rectangleClient.right;
            pitem->m_rectangle.top = y;
            pitem->m_rectangle.bottom = y + h;
            y += h;

            pitem->m_iItem = iItem;
            pitem->m_eelement = e_element_item;

            iItem++;

         }



      }



   }



} // namespace app_complex_video_capture



