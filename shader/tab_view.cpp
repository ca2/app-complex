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


   void tab_view::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void tab_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void tab_view::install_message_routing(::channel * pchannel)
   {

      ::user::tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &tab_view::on_message_create);

   }


   void tab_view::on_message_create(::message::message * pmessage)
   {

      if(pmessage->previous())
      {

         return;

      }

      papplication->m_ppaneview = this;

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

      set_current_tab_by_id("shader1");

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

         auto ptabpaneFileManager = get_tab_by_id(FILEMANAGER_IMPACT);

         if(ptabpaneFileManager != nullptr && ptabpaneFileManager->m_pplaceholder != nullptr)
         {

            ptabpaneFileManager->m_pplaceholder->hide();

         }

         auto ptabpaneFontSel = get_tab_by_id(FONTSEL_IMPACT);

         if (ptabpaneFontSel != nullptr && ptabpaneFontSel->m_pplaceholder != nullptr)
         {

            ptabpaneFontSel->m_pplaceholder->hide();

         }

         __refer(m_pviewTopic,m_pimpactdata->m_pplaceholder->get_hold());

      }

   }


   void tab_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      if (papplication->has_property("notabs"))
      {

         return;

      }

      switch(pimpactdata->m_atom)
      {
      case MENU_IMPACT:
      {

         ::user::impact::create_view < ::user::menu_list_view >(pimpactdata);

      }
      break;
      }

      string strId = pimpactdata->m_atom;

      if(::str::begins_eat_ci(strId, "shader"))
      {

         auto pview = papplication->create_simple_shader_view(this, pimpactdata);

         pview->m_atom = pimpactdata->m_atom;

         pview->m_iView = atoi(strId);

         __pointer(impact) pviewShader = pview;

         pviewShader->m_prender->m_strShaderPrefix = strId;

         pimpactdata->m_eflag.add(::user::e_flag_hidid_on_show);

      }

      ::user::tab_view::on_create_impact(pimpactdata);

   }


   void tab_view::handle(::topic * ptopic, ::context * pcontext)
   {



   }


   void tab_view::handle(::topic * ptopic, ::context * pcontext)
   {


      ::user::tab_view::handle(ptopic, pcontext);

   }


} // namespace simple_shader



