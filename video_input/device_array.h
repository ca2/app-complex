#pragma once


namespace video_input
{


	class device;


	class CLASS_DECL_VIDEO_INPUT device_array :
		virtual public matter
	{
	public:


		DECLARE_ARRAY_OF(device_array, device, ::video_input::device);

		device_array();

		~device_array() override;


		virtual device * get_device_by_id2(const ::string & pszMd5);
		virtual device * get_device_by_name(const ::string & pszMd5);


	};



} // namespace video_input



