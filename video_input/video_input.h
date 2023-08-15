#pragma once


#include "device_array.h"
#include "apex/handler/source.h"


namespace video_input
{


   class CLASS_DECL_VIDEO_INPUT video_input :
      virtual public ::object,
      virtual public ::video_input::device_array,
      virtual public ::source
   {
   public:


      ::e_status m_estatusAccessToDevices;


      video_input();
      ~video_input() override;


      virtual void initialize(::particle * pparticle) override;

      void close_all_devices();

      virtual bool are_devices_accessible();

      virtual void _update_device_list();

      virtual void update_device_list();

      virtual void on_device_added();

      virtual void on_device_removed();

      virtual device * find_device_with_hardware_id(const ::string & strHardwareId) const;

      virtual bool contains_device_with_hardware_id(const ::string & strHardwareId) const;

      void handle(::topic * ptopic, ::context * pcontext) override;


   };


} // namespace video_input



