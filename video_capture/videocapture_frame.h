#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE frame :
      virtual public simple_frame_window
   {
   public:


      frame();
      virtual ~frame();


	   void assert_valid() const override;
	   void dump(dump_context & dumpcontext) const override;


      ::user::enum_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace video_capture












