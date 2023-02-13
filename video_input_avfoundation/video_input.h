#pragma once


namespace video_input_video_avfoundation
{



	/// The only visiable class for controlling of video devices in format singelton
	class video_input :
		virtual public ::video_input::video_input
	{
	public:


		video_input();
		~video_input() override;


		virtual void initialize(::particle * pparticle) override;




		void close_all_devices();

		bool are_devices_accessible() override;

		void set_verbose(bool state);

		void _update_device_list() override;

		//void initDevices(IMFAttributes * pAttributes);

      void handle(::topic * ptopic, ::context * pcontext) override;

	};


} // namespace video_input_video_avfoundation



