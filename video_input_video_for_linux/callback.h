#pragma once

//#include <mfidl.h>


//struct IMFMediaSource;
#include "acme/parallelization/manual_reset_event.h"


#include "acme/primitive/geometry2d/_geometry2d.h"

extern "C"
{


#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <libavutil/frame.h>


}


namespace video_input_video_for_linux
{


	class CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION callback :
      public ::object
	{
	public:

		
		bool m_bClose;

		long m_cRef;

		::u32 m_uDevice;

      manual_reset_event      m_eventStop;

      bool                    m_bStopCapture;

      ::video::frame *        m_pframe;


		::pointer<device>m_pdevice;

      SwsContext *                           m_psws;
      ::size_i32                             m_sizeSwsDest;

      AVFrame * m_pframePicture;

      int	m_iMemory;

      ::i64 m_iTimestamp;
      bool        m_bCapturing;


      callback(device * pdevice, ::u32 deviceID);
		~callback(void) override;


		void start_capturing();

		void stop_capturing();


	};


} // namespace video_input_video_for_linux



