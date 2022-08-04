#include "framework.h"


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


   void main_impact::assert_ok() const
   {

      ::user::split_impact::assert_ok();

   }


   void main_impact::dump(dump_context & dumpcontext) const
   {

      ::user::split_impact::dump(dumpcontext);

   }


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

      //m_pimpact = create_view < lite_view >();

      m_pimpact = create_view < app_complex_video_capture::impact >(nullptr, get_pane_holder(iPane), "videocapture_view");

      if(m_pimpact == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }

      __pointer(edit_impact) peditview = get_child_by_id("top_edit_impact");

      if(peditview.is_set())
      {

         string strText;

         get_app()->data_get("cur_text",strText);

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



