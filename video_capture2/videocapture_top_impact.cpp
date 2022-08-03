#include "framework.h"


namespace app_complex_video_capture
{


   top_view::top_view()
   {
      m_peditview = nullptr;
      m_ptoggleview = nullptr;
   }


   top_view::~top_view()
   {

   }


   void top_view::assert_ok() const
   {

      ::user::split_view::assert_ok();

   }


   void top_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void top_view::handle(::topic * ptopic, ::context * pcontext)
   {
      ::user::split_view::handle(ptopic, pcontext);
   }


   void top_view::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0,0.84);

      initialize_split_layout();

      m_peditview = create_view < edit_view >(nullptr, get_pane_holder(0),"top_edit_view");

      if(m_peditview == nullptr)
      {

         message_box(nullptr,"Could not create folder edit impact");

      }

      m_peditview->m_ptopview = this;

      m_ptoggleview = create_view < toggle_view >(nullptr, get_pane_holder(1),"top_toggle_view");

      if(m_ptoggleview == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }

      m_ptoggleview->m_ptopview = this;



   }



} // namespace app_complex_video_capture



