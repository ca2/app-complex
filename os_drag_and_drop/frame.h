#pragma once


namespace simple_os_drag_and_drop
{


   class CLASS_DECL_APP_SIMPLE_OS_DRAG_AND_DROP frame :
      virtual public simple_frame_window
   {
   public:


      frame();
      virtual ~frame();


	   void assert_valid() const override;
	   void dump(dump_context & dumpcontext) const override;


//      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;


   };


} // namespace simple_os_drag_and_drop












