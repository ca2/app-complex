#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE main_impact:
      virtual public ::user::split_impact
   {
   public:


      top_impact *              m_ptopview;
      impact *                  m_pimpact;


      main_impact();
      virtual ~main_impact();


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void handle(::topic * ptopic, ::context * pcontext);


   };


} // namespace app_complex_video_capture





