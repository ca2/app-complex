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
#include "framework.h"
#include "mjpeg_decoder.h"
#include "acme/exception/resource.h"
#include "aura/graphics/image/image.h"
#include "app-complex/video_input/frame.h"


extern "C"
{


   #include <libavutil/frame.h>
   #include <libavutil/imgutils.h>


}



void ffmpeg_free_frame(AVFrame **framep)
{

   AVFrame * frame = *framep;

   if (frame == nullptr)
   {

      return;

   }

   av_freep(frame->data);

   av_frame_free(&frame);

   *framep = nullptr;

}


bool ffmpeg_init_frame(AVFrame **framep, int width, int height)
{

   ffmpeg_free_frame(framep);

   int ret;
   AVFrame *frame;
   frame = av_frame_alloc();
   if (!frame)
   {
      ::platform::get()->informationf( "Could not allocate video frame\n");
      return false;
   }

   frame->format = FFMPEG_DST_PIXEL_FORMAT;
   frame->width = width;
   frame->height = height;
   ret = av_image_alloc(frame->data, frame->linesize, width, height, FFMPEG_DST_PIXEL_FORMAT, 32);
   if (ret < 0)
   {
      ::platform::get()->informationf("Could not allocate raw picture buffer\n");
      return false;
   }
   *framep = frame;
   return true;
}

namespace video_input_video_for_linux
{
//#include "mjpeg.h"

//#define blog(level, msg, ...) \
//	blog(level, "v4l2-input: mjpeg: " msg, ##__VA_ARGS__)

   mjpeg_decoder::mjpeg_decoder()
   {


      //return 0;
   }



   mjpeg_decoder::~mjpeg_decoder()
   {
      information() << "destroying avcodec";
      if (m_pframe)
      {
         av_frame_free(&m_pframe);
      }

      if (m_ppacket)
      {
         av_packet_free(&m_ppacket);
      }

      if (m_papplication)
      {
         avcodec_free_context(&m_papplication);
      }
   }


   void mjpeg_decoder::initialize(::particle * pparticle)
{

      ::object::initialize(pparticle);

      m_pcodec = avcodec_find_decoder(AV_CODEC_ID_MJPEG);

      if (!m_pcodec)
      {

         throw resource_exception();

      }

      m_papplication = avcodec_alloc_context3(m_pcodec);

      if (!m_papplication)
      {

         throw resource_exception();

      }


      m_ppacket = av_packet_alloc();

      if (!m_ppacket)
      {

         throw resource_exception();

      }

      m_pframe = av_frame_alloc();

      if (!m_pframe)
      {

         throw resource_exception();

      }

      m_papplication->flags2 |= AV_CODEC_FLAG2_FAST;

      m_papplication->pix_fmt = AV_PIX_FMT_YUVJ422P;

      if (avcodec_open2(m_papplication, m_pcodec, NULL) < 0)
      {

         throw ::exception(error_failed, "failed to open codec");
         //return -1;

      }

      information() << "initialized avcodec";

   }


   void mjpeg_decoder::decode(::video::frame * pframe, uint8_t * data, size_t length)
   {

      m_ppacket->data = data;

      m_ppacket->size = length;

      if (avcodec_send_packet(m_papplication, m_ppacket) < 0)
      {

         error() <<"failed to send jpeg to codec";

         throw ::exception(error_failed, "failed to send jpeg to codec");

      }

      if (avcodec_receive_frame(m_papplication, m_pframe) < 0)
      {

         error() <<"failed to recieve frame from codec";

         throw ::exception(error_failed, "failed to recieve frame from codec");

      }

      for (int i = 0; i < MAX_AV_PLANES; ++i)
      {

         pframe->m_data[i] = m_pframe->data[i];
         pframe->m_linesize[i] = m_pframe->linesize[i];

      }

      //return 0;

   }


} // namespace video_input_video_for_linux





