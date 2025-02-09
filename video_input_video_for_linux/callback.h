#pragma once

//#include <mfidl.h>


//struct IMFMediaSource;
#include "acme/parallelization/manual_reset_happening.h"


//#include "acme/prototype/geometry2d/_geometry2d.h"


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

		unsigned int m_uDevice;

      manual_reset_happening      m_happeningStop;

      bool                    m_bStopCapture;

      ::video::frame *        m_pframe;


		::pointer<device>m_pdevice;

      SwsContext *                           m_psws;
      ::int_size                             m_sizeSwsDest;

      AVFrame * m_pframePicture;

      int	m_iMemory;

      long long m_iTimestamp;
      bool        m_bCapturing;


      callback(device * pdevice, unsigned int deviceID);
		~callback(void) override;


		void start_capturing();

		void stop_capturing();


	};


} // namespace video_input_video_for_linux



