// Created by camilo on 2022-02-19 12:08 <3ThomasBorregaardSørensen!!
#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE device_selector :
      virtual public application_consumer < application, ::user::impact >
   {
   public:

      map < __pointer(::video_input::device), __pointer(::item) > m_itemmap;


      device_selector();
      ~device_selector() override;


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual void update_item_map();


      void install_message_routing(::channel * pchannel) override;


      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      bool on_click(::item * pitem) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      
   };


} // namespace app_complex_video_capture



