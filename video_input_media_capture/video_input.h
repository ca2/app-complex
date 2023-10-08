#pragma once


#include "app-complex/video_input/video_input.h"
#include "aura/hardware/device_listener.h"


namespace video_input_media_capture
{


   /// The only visiable class for controlling of video devices in format singelton
   class CLASS_DECL_VIDEO_INPUT_MEDIA_CAPTURE video_input :
      virtual public ::video_input::video_input,
      virtual public ::hardware::device_listener
   {
   public:


      //HDEVNOTIFY		m_hdevnotify;


      //::winrt::Windows::Media::Capture::MediaCapture                           m_mediacapture = nullptr;

      video_input();
      ~video_input() override;


      virtual void initialize(::particle * pparticle) override;



      void close_all_devices();

      bool are_devices_accessible();

      virtual void _update_device_list();

      //void initDevices(IMFAttributes * pAttributes);

      //void on_device_nodes_changed() override;

      void on_device_plugged(::hardware::enum_device edevice) override;

      void on_device_unplugged(::hardware::enum_device edevice) override;

   };


} // namespace video_input_media_capture



