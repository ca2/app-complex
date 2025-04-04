#include "framework.h"


namespace video_capture
{


   font_impact::font_impact(::particle * pparticle):
      object(pparticle),
      ::user::split_layout(pparticle),
      ::user::split_impact(pparticle),
      place_holder_container(pparticle)
   {

      m_pimpact = nullptr;

      m_ptopimpact = nullptr;

   }


   font_impact::~font_impact()
   {

   }


   void font_impact::assert_ok() const
   {

      ::user::split_impact::assert_ok();

   }


   void font_impact::dump(dump_context & dumpcontext) const
   {

      ::user::split_impact::dump(dumpcontext);

   }


   void font_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {
      ::user::split_impact::handle(ptopic, phandlercontext);
   }


   void font_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      m_ptopimpact = create_impact < top_impact >(nullptr, get_pane_holder(0),"top_impact");

      if(m_ptopimpact == nullptr)
      {

         message_box(nullptr,"Could not create folder edit impact");

      }

      //SetPane(0,m_ptopimpact,false);

      m_pimpact = create_impact < ::user::font_list_impact >(nullptr, get_pane_holder(1),"font_list_impact");

      if(m_pimpact == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }


   }


   void font_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      if(ptopic->id() == ::id_click)
      {

         if(ptopic->user_interaction_id() == "switcher_toggle")
         {

            ::pointer<impact>pimpact = m_pimpact;

            pimpact->m_prender->m_bLite = !pimpact->m_prender->m_bLite;

         }
         //else if(ptopic->user_interaction_id() == "videocapture_toggle")
         //{

         //   if(m_pimpact->m_prender->m_bLite && !papp->m_bLoadAiFont)
         //   {

         //      papp->load_ai_font();

         //   }

         //   m_pimpact->m_prender->m_bLite = !m_pimpact->m_prender->m_bLite;


         //   m_pimpact->on_layout(pgraphics);

         //}

      }
      else if(ptopic->id() == ::id_after_change_cur_sel)
      {

         if(m_pimpact == ptopic->user_interaction())
         {

            if(get_typed_parent < pane_impact >()->m_pimpactLast != nullptr)
            {

               string strFont = m_pimpact->get_cur_sel_face_name();

               if(strFont.has_character())
               {

                  get_typed_parent < pane_impact >()->m_pimpactLast->m_strNewFont = strFont;

                  get_typed_parent < pane_impact >()->m_pimpactLast->on_layout(pgraphics);

               }

            }

         }

      }



      return true;

   }

} // namespace video_capture



