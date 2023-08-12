// Created by camilo on 2022-02-19 12:08 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/platform/app_consumer.h"
#include "base/user/user/impact.h"


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE device_selector :
      virtual public app_consumer < application, ::user::impact >
   {
   public:

      //map < ::pointer<::video_input::device>, ::pointer<::item>> m_itemmap;


      device_selector();
      ~device_selector() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      bool on_impact_update() override;


      //item* get_user_item(::video_input::device * pdevice);


      void install_message_routing(::channel * pchannel) override;


      void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      bool on_click(::item * pitem) override;

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      
   };


} // namespace app_complex_video_capture



