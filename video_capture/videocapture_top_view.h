#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE top_view:
      virtual public ::user::split_view
   {
   public:


      edit_view *                   m_peditview;
      toggle_view *                 m_ptoggleview;


      top_view();
      virtual ~top_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_split_impact();

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      //bool is_this_visible(::user::enum_layout elayout = ::user::e_layout_design) override;


   };


} // namespace video_capture







