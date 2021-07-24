#include "framework.h"


namespace video_capture
{


   main_view::main_view()
   {

      m_ptopview = nullptr;
      m_pview    = nullptr;

   }


   main_view::~main_view()
   {

   }


   void main_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void main_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void main_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {
      ::user::split_view::on_subject(psubject, pcontext);
   }


   void main_view::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      int iPane;


         SetPaneCount(1);

         initialize_split_layout();

         iPane = 0;

      //m_pview = create_view < lite_view >();

      m_pview = create_view < view >(nullptr, get_pane_holder(iPane), "videocapture_view");

      if(m_pview == nullptr)
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


   void main_view::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::e_event_click)
      {

      }

   }


} // namespace video_capture



