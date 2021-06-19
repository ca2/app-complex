#pragma once


namespace videocapture
{


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE font_view:
      virtual public ::user::split_view
   {
   public:


      top_view *                    m_ptopview;
      ::user::font_list_view *      m_pview;


      font_view(::object * pobject);
      virtual ~font_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_split_impact();

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual void on_control_event(::user::control_event * pevent);


   };


} // namespace videocapture





