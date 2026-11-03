#include "platform.h"
#include "main_impact.h"
#include "impact.h"
#include "edit_impact.h"
#include "application.h"
//#include "acme/platform/sequencer.h"
#include "acme/user/interface/message_box.h"
//#include "acme/user/nano/nano.h"
#include "apex/database/_binary_stream.h"


namespace app_complex_video_capture
{


   main_impact::main_impact()
   {

      m_ptopimpact = nullptr;
      m_pimpact    = nullptr;

   }


   main_impact::~main_impact()
   {

   }


   //void main_impact::assert_ok() const
   //{

   //   ::user::split_impact::assert_ok();

   //}


   //void main_impact::dump(dump_context & dumpcontext) const
   //{

   //   ::user::split_impact::dump(dumpcontext);

   //}


   void main_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {
      ::user::split_impact::handle(ptopic, phandlercontext);
   }


   void main_impact::on_perform_top_down_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {
      // split_layout defaults to a 1px inset on every side. In fullscreen
      // the single video pane must occupy every pixel of the screen.
      const int border = top_level()->layout().is_full_screen(::user::e_layout_layout) ? 0 : 1;
      if (m_cxBorder != border || m_cyBorder != border)
      {
         informationf("Video geometry: split border=%d fullscreen=%d", border, (int) (border == 0));
      }
      m_cxBorder = border;
      m_cyBorder = border;
      ::user::split_impact::on_perform_top_down_layout(pdraw2dgraphics);
      if (border == 0 && m_pimpact)
      {
         // Size the single preview pane from the active layout, not the
         // preceding design frame. Fullscreen must not depend on overlay draws.
         auto bounds = rectangle(::user::e_layout_layout);
         auto holder = get_pane_holder(0);
         if (holder) holder->place(bounds);
         m_pimpact->place({ ::i32_point{}, bounds.size() });
      }
   }


   void main_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      int iPane;


         SetPaneCount(1);

         initialize_split_layout();

         iPane = 0;

      //m_pimpact = create_impact < lite_impact >();

      m_pimpact = create_impact < app_complex_video_capture::impact >(nullptr, get_pane_holder(iPane), "videocapture_impact");

      if(m_pimpact == nullptr)
      {

         auto pmessagebox = createø < ::user_interface::message_box >();
         pmessagebox->initialize_message_box("Could not create file list_base ::user::impact");

         pmessagebox->display(e_display_normal, {});

      }

      ::pointer<edit_impact>peditview = get_child_by_id("top_edit_impact");

      if(peditview.is_set())
      {

         string strText;

         ::cast < ::database::client > pdatabaseclient = application();

         pdatabaseclient->datastream()->get("cur_text",strText);

         peditview->set_text(strText, ::e_source_initialize);

      }

   }


   //void main_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   if(ptopic->id() == ::id_click)
   //   {

   //   }

   //}


} // namespace app_complex_video_capture


