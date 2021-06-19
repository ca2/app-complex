#pragma once


namespace videocapture
{


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE top_view:
      virtual public ::user::split_view
   {
   public:


      edit_view *                   m_peditview;
      toggle_view *                 m_ptoggleview;


      top_view(::object * pobject);
      virtual ~top_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      void on_create_split_impact();

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual bool is_this_visible() override;


   };


} // namespace videocapture







