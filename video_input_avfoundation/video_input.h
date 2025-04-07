#pragma once


#include "avcapture_video_input_callback.h"
#include "app-complex/video_input/video_input.h"


namespace video_input_video_avfoundation
{



	/// The only visiable class for controlling of video devices in format singelton
	class video_input :
		virtual public ::video_input::video_input,
      virtual public avcapture_video_input_callback
	{
	public:


		video_input();
		~video_input() override;


		virtual void initialize(::particle * pparticle) override;


      void on_device_connected() override;
      void on_device_disconnected() override;


		void close_all_devices();

		bool are_devices_accessible() override;

		void set_verbose(bool state);

		void _update_device_list() override;

		//void initDevices(IMFAttributes * pAttributes);

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

	};


} // namespace video_input_video_avfoundation



