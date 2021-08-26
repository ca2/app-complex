#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE main_impact:
      virtual public ::user::split_view
   {
   public:


      top_view *              m_ptopview;
      impact *                  m_pimpact;


      main_impact();
      virtual ~main_impact();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_split_impact();

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual void on_control_event(::user::control_event * pevent);


   };


} // namespace video_capture





