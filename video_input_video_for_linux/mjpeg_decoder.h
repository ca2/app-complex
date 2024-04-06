/*
Copyright (C) 2020 by Morten Boegeskov <source@kosmisk.dk>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once



extern "C"
{


   #include <libswscale/swscale.h>
   #include <libavutil/avutil.h>
   #include <libavcodec/avcodec.h>


}

class CaptureManager;
// dnf install ffmpeg-devel - RPM Fusion Free Repository
// zypper install ffmpeg-devel


namespace video_input_video_for_linux
{
/**
 * Data structure for mjpeg decoding
 */
class mjpeg_decoder :
virtual public ::object
{
public:

   const AVCodec * m_pcodec;
   AVCodecContext * m_pcontext;
   AVPacket * m_ppacket;
   AVFrame * m_pframe;
   AVFrame * m_pframePicture;
//};



/**
 * Initialize the mjpeg decoder.
 * The decoder must be destroyed on failure.
 *
 * @param props the decoder structure
 * @return non-zero on failure
 */
      mjpeg_decoder();

/**
 * Free any data associated with the decoder.
 *
 * @param decoder the decoder structure
 */
      ~mjpeg_decoder();


      void initialize(::particle * pparticle) override;

/**
 * Decode a jpeg into an obs frame
 *
 * @param out the obs frame to decode into
 * @param data the jpeg data
 * @param length length of the data
 * @param decoder the decoder as initialized by v4l2_init_mjpeg
 * @return non-zero on failure
 */
      void decode(::video::frame * pframe, uint8_t * data, size_t length);

   };


} // namespace video_input_video_for_linux
//#endif