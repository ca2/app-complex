#include "framework.h"



namespace app_complex_video_capture
{


   top_impact::top_impact()
   {
      m_peditview = nullptr;
      m_ptoggleview = nullptr;
   }


   top_impact::~top_impact()
   {

   }


   void top_impact::assert_ok() const
   {

      ::user::split_impact::assert_ok();

   }


   void top_impact::dump(dump_context & dumpcontext) const
   {

      ::user::split_impact::dump(dumpcontext);

   }


   void top_impact::handle(::topic * ptopic, ::context * pcontext)
   {
      ::user::split_impact::handle(ptopic, pcontext);
   }


   void top_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0,0.84);

      initialize_split_layout();

      m_peditview = create_impact < edit_impact >(nullptr, get_pane_holder(0),"top_edit_impact");

      if(m_peditview == nullptr)
      {

         message_box(nullptr,"Could not create folder edit impact");

      }

      m_peditview->m_ptopview = this;

      m_ptoggleview = create_impact < toggle_impact >(nullptr, get_pane_holder(1),"top_toggle_impact");

      if(m_ptoggleview == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }

      m_ptoggleview->m_ptopview = this;



   }



} // namespace app_complex_video_capture



