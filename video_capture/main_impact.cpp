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


   void main_impact::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void main_impact::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void main_impact::handle(::topic * psubject, ::context * pcontext)
   {
      ::user::split_view::handle(psubject, pcontext);
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

      m_pimpact = create_view < impact >(nullptr, get_pane_holder(iPane), "videocapture_view");

      if(m_pimpact == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }

      __pointer(edit_view) peditview = get_child_by_id("top_edit_view");

      if(peditview.is_set())
      {

         string strText;

         get_application()->data_get("cur_text",strText);

         peditview->_001SetText(strText, ::e_source_initialize);

      }

   }


   //void main_impact::handle(::topic * psubject, ::context * pcontext)
   //{

   //   if(psubject->m_id == ::id_click)
   //   {

   //   }

   //}


} // namespace app_complex_video_capture



