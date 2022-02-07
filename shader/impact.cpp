#include "framework.h"
#include <math.h>
#include "acme/constant/identification.h"


namespace simple_shader
{


   impact::impact()
   {

      m_iView = -1;

      payload(FONTSEL_IMPACT) = true;

      m_flagNonClient.erase(non_client_background);

      m_flagNonClient.erase(non_client_focus_rect);

   }


   impact::~impact()
   {

   }


   void impact::assert_ok() const
   {

      user::box::assert_ok();

   }


   void impact::dump(dump_context & dumpcontext) const
   {

      user::box::dump(dumpcontext);

   }


   int64_t impact::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::impact::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t impact::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::impact::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   void impact::install_message_routing(::channel * psender)
   {

      ::user::impact::install_message_routing(psender);
      ::user::interaction::install_simple_ui_default_mouse_handling(psender);
      MESSAGE_LINK(e_message_create,psender,this,&impact::on_message_create);
      MESSAGE_LINK(e_message_destroy, psender, this, &impact::on_message_destroy);
      MESSAGE_LINK(e_message_key_down, psender, this, &impact::on_message_key_down);

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      top_level_frame()->set_prodevian();

      auto predraw = [this]()
         {

            set_need_redraw();

            post_redraw();

         };

      papplication->m_mapRunnable[id_simple_checkbox] += predraw;

      papplication->m_mapRunnable[id_no_client_frame] += predraw;

      auto estatus = __construct_new(m_prender);

      if(!estatus)
      {

         pcreate->set_fail();

         return;

      }

      m_prender->initialize_application_consumer();

      m_prender->m_pimpact = this;

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      string strText;

      if(GetTypedParent<::user::split_view>() != nullptr)
      {

         if(GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != nullptr)
         {

            auto pinteraction = GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view");

            pinteraction->_001SetText(strText,::e_source_initialize);

         }

      }

      m_prender->update_shader();


      {

         ::identification identification = id_simple_text;

         auto pproperty = papplication->fetch_property(identification);

         ::payload payload;

         if (papplication->data_get(identification, payload))
         {

            pproperty->convert(payload);

         }

         auto idRunnable = papplication->translate_property_id(identification);

         papplication->m_mapRunnable[idRunnable] += [this, identification]()
         {

            auto pproperty = fetch_property(identification);

            m_prender->defer_load_fragment(pproperty->get_string());

         };

      }


   }


   void impact::on_message_destroy(::message::message * pmessage)
   {

   }


   void impact::on_message_key_down(::message::message* pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_s)
      {

         m_bSaveFrame = true;




      }


   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_simple_checkbox || ptopic->m_atom == id_no_client_frame)
      {

         set_need_redraw();

      }

      ::user::impact::handle(ptopic, pcontext);

   }


   ::user::document * impact::get_document()
   {

      return ::user::impact::get_document();

   }


   bool impact::keyboard_focus_is_focusable()
   {

      return true;

   }


   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_bSaveFrame)
      {

         m_bSaveFrame = false;

         auto rectangleClient = get_client_rect();

         auto pimage = create_image(rectangleClient);

         ::draw2d::graphics_pointer pgraphics = pimage->get_graphics();

         m_prender->_001OnDraw(pgraphics);

         fork([this, pimage]()
            {

               save_image saveimage;

               saveimage.m_eformat = ::draw2d::format_png;

               string strDate = pdatetime->international().get_gmt_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE);

               pcontext->m_papexcontext->save_image("image://app_simple_shader-" + strDate + ".png", pimage, &saveimage);

            });


      }

      m_prender->_001OnDraw(pgraphics);

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      m_prender->m_rectangle = rectangleClient;

      m_prender->on_layout(pgraphics);

   }


} // namespace simple_shader



