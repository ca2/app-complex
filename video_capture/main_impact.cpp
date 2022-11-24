#include "framework.h"
#include "main_impact.h"
#include "impact.h"
#include "edit_impact.h"
#include "application.h"
#include "acme/platform/sequencer.h"
#include "acme/user/nano/nano.h"
#include "apex/database/_binary_stream.h"


namespace app_complex_video_capture
{


   main_impact::main_impact()
   {

      m_ptopview = nullptr;
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


   void main_impact::handle(::topic * ptopic, ::context * pcontext)
   {
      ::user::split_impact::handle(ptopic, pcontext);
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

         auto psequencer = nano()->message_box_sequencer(nullptr,"Could not create file list ::user::impact");

         psequencer->do_asynchronously();

      }

      ::pointer<edit_impact>peditview = get_child_by_id("top_edit_impact");

      if(peditview.is_set())
      {

         string strText;

         get_app()->datastream()->get("cur_text",strText);

         peditview->_001SetText(strText, ::e_source_initialize);

      }

   }


   //void main_impact::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   if(ptopic->m_atom == ::id_click)
   //   {

   //   }

   //}


} // namespace app_complex_video_capture



