#pragma once


#include "app-complex/video_input/video_input.h"


namespace video_input_video_for_linux
{



	/// The only visiable class for controlling of video devices in format singelton
	class video_input :
		virtual public ::video_input::video_input
	{
	public:


		video_input();
		~video_input() override;


		virtual void initialize(::particle * pparticle) override;


/**
 * Initialize udev system to watch for device happenings
 */
      void v4l2_init_udev(void);

/**
 * Unref the udev system
 */
      void v4l2_unref_udev(void);



		void close_all_devices();

		bool are_devices_accessible() override;

		void set_verbose(bool state);

		void _update_device_list() override;

		//void initDevices(IMFAttributes * pAttributes);

      void handle(::topic * ptopic, ::context * pcontext) override;

	};


} // namespace video_input_video_for_linux



