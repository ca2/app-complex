#include "framework.h"


namespace app_complex_video_capture
{


   top_impact::top_impact()
   {
      m_peditimpact = nullptr;
      m_ptoggleimpact = nullptr;
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


   void top_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {
      ::user::split_impact::handle(ptopic, phandlercontext);
   }


   void top_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0,0.84);

      initialize_split_layout();

      m_peditimpact = create_impact < edit_impact >(nullptr, get_pane_holder(0),"top_edit_impact");

      if(m_peditimpact == nullptr)
      {

         message_box(nullptr,"Could not create folder edit impact");

      }

      m_peditimpact->m_ptopimpact = this;

      m_ptoggleimpact = create_impact < toggle_impact >(nullptr, get_pane_holder(1),"top_toggle_impact");

      if(m_ptoggleimpact == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }

      m_ptoggleimpact->m_ptopimpact = this;



   }



} // namespace app_complex_video_capture



