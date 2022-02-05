#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE font_view:
      virtual public ::user::split_view
   {
   public:


      top_view *                    m_ptopview;
      ::user::font_list_view *      m_pimpact;


      font_view(::object * pobject);
      virtual ~font_view();


      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact();

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void handle(::topic * ptopic, ::context * pcontext);


   };


} // namespace video_capture





