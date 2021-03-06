#include "framework.h"


namespace video_capture
{


   switcher_view::switcher_view()
   {

      m_pview = nullptr;

      m_ptopview = nullptr;

   }


   switcher_view::~switcher_view()
   {

   }


   void switcher_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void switcher_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void switcher_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {
      ::user::split_view::on_subject(psubject, pcontext);
   }


   void switcher_view::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      m_ptopview = create_view < top_view >(nullptr, get_pane_holder(0),"top_view");

      if(m_ptopview == nullptr)
      {

         message_box(nullptr,"Could not create folder edit view");

      }

      //SetPane(0,m_ptopview,false);

      m_pview = create_view < view >(nullptr, get_pane_holder(1),"videocapture_view");

      m_pview->m_prender->m_bAlternate = true;

      if(m_pview == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }

//      m_ptopview->m_pview = m_pview;


      //SetPane(1,m_pview,false);


   }



   void switcher_view::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::e_event_button_clicked)
      {

         if(pevent->m_puserinteraction->m_id == "switcher_toggle")
         {

            __pointer(view) pview = m_pview;

            pview->m_prender->m_bLite = !pview->m_prender->m_bLite;

         }
         else if(pevent->m_puserinteraction->m_id == "videocapture_toggle")
         {

            if(m_pview->m_prender->m_bLite && !papplication->m_bLoadAiFont)
            {

               papplication->load_ai_font();

            }

            m_pview->m_prender->m_bLite = !m_pview->m_prender->m_bLite;


            m_pview->on_layout(::draw2d::graphics_pointer & pgraphics);

         }

      }


      return true;

   }

} // namespace video_capture



