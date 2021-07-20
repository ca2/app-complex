#include "framework.h"
#include <math.h>
#include "acme/const/id.h"


namespace simple_shader
{


   view::view()
   {

      m_iView = -1;

      payload(FONTSEL_IMPACT) = true;

      m_flagNonClient.erase(non_client_background);

      m_flagNonClient.erase(non_client_focus_rect);

   }


   view::~view()
   {

   }


   void view::assert_valid() const
   {

      user::box::assert_valid();

   }


   void view::dump(dump_context & dumpcontext) const
   {

      user::box::dump(dumpcontext);

   }


   int64_t view::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return  ::user::impact::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t view::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return  ::user::impact::dec_ref(OBJ_REF_DBG_ARGS);

   }


   void view::install_message_routing(::channel * psender)
   {

      ::user::impact::install_message_routing(psender);
      ::user::interaction::install_simple_ui_default_mouse_handling(psender);
      MESSAGE_LINK(e_message_create,psender,this,&view::on_message_create);
      MESSAGE_LINK(e_message_destroy, psender, this, &view::on_message_destroy);
      MESSAGE_LINK(e_message_key_down, psender, this, &view::on_message_key_down);

   }


   void view::on_message_create(::message::message * pmessage)
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

      m_prender->m_pview = this;

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

         ::id id = id_simple_text;

         auto pproperty = papplication->fetch_property(id);

         ::payload payload;

         if (papplication->data_get(id, payload))
         {

            pproperty->convert(payload);

         }

         auto idRunnable = papplication->translate_property_id(id);

         papplication->m_mapRunnable[idRunnable] += [this, id]()
         {

            auto pproperty = fetch_property(id);

            m_prender->defer_load_fragment(pproperty->get_string());

         };

      }


   }


   void view::on_message_destroy(::message::message * pmessage)
   {

   }


   void view::on_message_key_down(::message::message* pmessage)
   {

      auto pkey = pmessage->m_pkey;

      if (pkey->m_ekey == ::user::e_key_s)
      {

         m_bSaveFrame = true;




      }


   }


   void view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      if (psubject->id() == id_simple_checkbox || psubject->id() == id_no_client_frame)
      {

         set_need_redraw();

      }

      ::user::impact::on_subject(psubject, pcontext);

   }


   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }


   bool view::keyboard_focus_is_focusable()
   {

      return true;

   }


   void view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
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


   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
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



