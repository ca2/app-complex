#include "framework.h"
#include "aura/update.h"


namespace simple_shader
{


   tab_view::tab_view()
   {

   }


   tab_view::~tab_view()
   {

   }


   void tab_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void tab_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void tab_view::install_message_routing(::channel * pchannel)
   {

      ::user::tab_view::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &tab_view::_001OnCreate);

   }


   void tab_view::_001OnCreate(::message::message * pmessage)
   {

      if(pmessage->previous())
      {

         return;

      }

      Application.m_ppaneview = this;

      set_tab("Menu", MENU_IMPACT);
      set_tab("1", "shader1");
      set_tab("2", "shader2");
      set_tab("3", "shader3");
      set_tab("4", "shader4");
      set_tab("5", "shader5");
      set_tab("6", "shader6");
      set_tab("7", "shader7");
      set_tab("8", "shader8");
      set_tab("9", "shader9");
      set_tab("10", "shader10");
      set_tab("11", "shader11");
      set_tab("12", "shader12");
      set_tab("13", "shader13");
      set_tab("14", "shader14");
      set_tab("Font", FONTSEL_IMPACT);
      set_tab("Color", COLORSEL_IMPACT);
      set_tab("Open", FILEMANAGER_IMPACT);

      set_cur_tab_by_id("shader1");

   }


   void tab_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::tab_view::_001OnNcDraw(pgraphics);

   }


   void tab_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::tab_view::_001OnDraw(pgraphics);

   }


   void tab_view::on_change_cur_sel()
   {

      ::user::tab_view::on_change_cur_sel();

      string strId = get_view_id();

      string_array stra;

      stra.explode("->:<-",strId);

      if (get_view_id() == MENU_IMPACT)
      {

         __pointer(::user::menu_list_view) pmenuview = get_view_uie();

         pmenuview->destroy_menu();

       }

      string strShaderPrefix = get_view_id().to_string();

      if(::str::begins_eat_ci(strShaderPrefix, "shader"))
      {

         if(get_pane_by_id(FILEMANAGER_IMPACT) != nullptr && get_pane_by_id(FILEMANAGER_IMPACT)->m_pplaceholder != nullptr)
         {

            get_pane_by_id(FILEMANAGER_IMPACT)->m_pplaceholder->hide();

         }

         if (get_pane_by_id(FONTSEL_IMPACT) != nullptr && get_pane_by_id(FONTSEL_IMPACT)->m_pplaceholder != nullptr)
         {

            get_pane_by_id(FONTSEL_IMPACT)->m_pplaceholder->hide();

         }

         __refer(m_pviewTopic,m_pimpactdata->m_pplaceholder->get_hold());

      }

   }


   void tab_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      if (Application.has_property("notabs"))
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

      string strId = pimpactdata->m_id;

      if(::str::begins_eat_ci(strId, "shader"))
      {

         auto pview = Application.create_simple_shader_view(this, pimpactdata);

         pview->m_id = pimpactdata->m_id;

         pview->m_iView = atoi(strId);

         __pointer(view) pviewShader = pview;

         pviewShader->m_prender->m_strShaderPrefix = strId;

         pimpactdata->m_eflag.add(::user::flag_hide_topic_on_show);

      }

      ::user::tab_view::on_create_impact(pimpactdata);

   }


   void tab_view::on_control_event(::user::control_event * pevent)
   {



   }


   void tab_view::update(::update * pupdate)
   {


      ::user::tab_view::update(pupdate);

   }


} // namespace simple_shader



