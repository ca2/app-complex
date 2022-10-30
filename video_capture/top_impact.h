#pragma once


#include "base/user/user/split_impact.h"


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE top_impact:
      virtual public ::user::split_impact
   {
   public:


      edit_impact *                   m_peditview;
      toggle_impact *                 m_ptoggleview;


      top_impact();
      ~top_impact() override;


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact() override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      //bool is_this_visible(::user::enum_layout elayout = ::user::e_layout_design) override;


   };


} // namespace app_complex_video_capture







