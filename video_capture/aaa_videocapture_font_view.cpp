#include "framework.h"


namespace video_capture
{


   font_view::font_view(::object * pobject):
      object(pobject),
      ::user::split_layout(pobject),
      ::user::split_view(pobject),
      place_holder_container(pobject)
   {

      m_pimpact = nullptr;

      m_ptopview = nullptr;

   }


   font_view::~font_view()
   {

   }


   void font_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void font_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void font_view::handle(::subject * psubject, ::context * pcontext)
   {
      ::user::split_view::handle(psubject, pcontext);
   }


   void font_view::on_create_split_impact()
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

         message_box(nullptr,"Could not create folder edit impact");

      }

      //SetPane(0,m_ptopview,false);

      m_pimpact = create_view < ::user::font_list_view >(nullptr, get_pane_holder(1),"font_list_view");

      if(m_pimpact == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }


   }


   void font_view::handle(::subject * psubject, ::context * pcontext)
   {

      if(psubject->m_id == ::e_subject_click)
      {

         if(psubject->user_element_id() == "switcher_toggle")
         {

            __pointer(impact) pview = m_pimpact;

            pview->m_prender->m_bLite = !pview->m_prender->m_bLite;

         }
         //else if(psubject->user_element_id() == "videocapture_toggle")
         //{

         //   if(m_pimpact->m_prender->m_bLite && !papplication->m_bLoadAiFont)
         //   {

         //      papplication->load_ai_font();

         //   }

         //   m_pimpact->m_prender->m_bLite = !m_pimpact->m_prender->m_bLite;


         //   m_pimpact->on_layout(::draw2d::graphics_pointer & pgraphics);

         //}

      }
      else if(psubject->m_id == ::e_subject_after_change_cur_sel)
      {

         if(m_pimpact == psubject->user_interaction())
         {

            if(GetTypedParent < pane_view >()->m_pviewLast != nullptr)
            {

               string strFont = m_pimpact->get_cur_sel_face_name();

               if(strFont.has_char())
               {

                  GetTypedParent < pane_view >()->m_pviewLast->m_strNewFont = strFont;

                  GetTypedParent < pane_view >()->m_pviewLast->on_layout(::draw2d::graphics_pointer & pgraphics);

               }

            }

         }

      }



      return true;

   }

} // namespace video_capture



