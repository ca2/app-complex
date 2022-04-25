#include "framework.h"
#include "aura/update.h"


namespace app_complex_impact3d
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

      //papp->m_ppaneimpact = this;

      set_tab("Menu", MENU_IMPACT);
      set_tab("Main", MAIN_IMPACT);
      set_tab("Font", FONTSEL_IMPACT);
      set_tab("Color", COLORSEL_IMPACT);
      set_tab("Open", FILEMANAGER_IMPACT);

      set_current_tab_by_id(MAIN_IMPACT);

   }


   void pane_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_impact::_001OnNcDraw(pgraphics);

   }


   void pane_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_impact::_001OnDraw(pgraphics);

   }


   void pane_impact::on_change_cur_sel()
   {

      ::userex::pane_tab_impact::on_change_cur_sel();

      string strId = get_view_id();

      string_array stra;

      stra.explode("->:<-",strId);

      string strShaderPrefix = get_view_id().to_string();


   }


   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      if (pimpactdata->m_atom == MAIN_IMPACT)
      {

         get_app()->m_ptemplateImpact->open_document_file(get_app(),
            "", true, pimpactdata->m_pplaceholder);

      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::userex::pane_tab_impact::handle(ptopic, pcontext);

   }


} // namespace app_complex_impact3d



