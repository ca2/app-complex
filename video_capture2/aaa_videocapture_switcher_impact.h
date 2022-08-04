#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE switcher_view:
      virtual public ::user::split_impact
   {
   public:


      top_impact *              m_ptopview;
      impact *                  m_pimpact;


      switcher_view();
      virtual ~switcher_view();


      void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void handle(::topic * ptopic, ::context * pcontext);


   };


} // namespace video_capture





