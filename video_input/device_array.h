#pragma once


#include "acme/handler/item.h"


namespace video_input
{


	class device;


	class CLASS_DECL_VIDEO_INPUT device_array :
		virtual public matter
	{
	public:


      /// item : ::video_input::device
      ::pointer < ::item_array >       m_pitemaDevice;
		//DECLARE_ARRAY_OF(device_array, device, ::video_input::device);

		device_array();

		~device_array() override;


		virtual device * get_device_by_id2(const ::string & pszMd5);
		virtual device * get_device_by_name(const ::string & pszMd5);


      virtual ::item_array & itema();
      virtual const ::item_array & itema() const;
      
      virtual bool contains_item(::item * pitem) const;
      
      virtual bool has_item() const;
      

	};



} // namespace video_input



