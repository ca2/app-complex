#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE switcher_impact:
      virtual public ::user::split_impact
   {
   public:


      top_impact *              m_ptopimpact;
      impact *                  m_pimpact;


      switcher_impact();
      virtual ~switcher_impact();


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual void handle(::topic * ptopic, ::handler_context * phandlercontext);


   };


} // namespace video_capture





