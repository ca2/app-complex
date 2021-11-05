#pragma once

#include "media-io/audio-io.h"
#include "media-io/video-io.h"

class video_enc
{
public:

   video_enc()
   {


   }


   ~video_enc()
   {


   }

   virtual int video_enc_get_width() { return 800; }
   virtual int video_enc_get_height() { return 600; }
   virtual int video_enc_get_fps_num() { return 30; }
   virtual int video_enc_get_fps_den() { return 1; }
   virtual int video_enc_is_active() { return 1;  }

};

#define MAX_AV_PLANES 8

class aura_data
{
public:

   aura_data()
   {


   }


   ~aura_data()
   {


   }


   virtual int aura_data_get_int(const ::string & pszKey) { return 0; }

};

struct obs_source_frame
{
   u64 timestamp;
   int flip;
   u8 * data[MAX_AV_PLANES];
   int linesize[MAX_AV_PLANES];
   video_format format;
   int full_range;
   int width;
   int height;
};


struct obs_source_audio
{
   u64 timestamp;
   u8 * data[MAX_AV_PLANES];
   int samples_per_sec;
   speaker_layout speakers;
   audio_format format;
   int frames;


};




