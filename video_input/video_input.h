#pragma once


#include "device_array.h"
#include "acme/handler/source.h"
#include "aura/hardware/device_listener.h"


namespace video_input
{


   class CLASS_DECL_VIDEO_INPUT video_input :
      virtual public ::object,
      virtual public ::video_input::device_array,
      virtual public ::source,
      virtual public ::hardware::device_listener
   {
   public:


      ::e_status m_estatusAccessToDevices;


      video_input();
      ~video_input() override;


      void initialize(::particle * pparticle) override;


      void destroy() override;


      void close_all_devices();

      virtual bool are_devices_accessible();

      virtual void _update_device_list();

      virtual void update_device_list();

      void on_device_plugged(::hardware::enum_device edevice) override;

      void on_device_unplugged(::hardware::enum_device edevice) override;

      virtual device * find_device_with_hardware_id(const ::string & strHardwareId) const;

      virtual bool contains_device_with_hardware_id(const ::string & strHardwareId) const;

      void handle(::topic * ptopic, ::context * pcontext) override;


   };


} // namespace video_input



