

#include "aqua/_.h"


#if defined(_app_core_audio_project)
#define CLASS_DECL_APP_CORE_AUDIO  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_CORE_AUDIO  CLASS_DECL_IMPORT
#endif


//CLASS_DECL_APP_CORE_AUDIO string_array_base det_l(::particle * pparticle, const ::scoped_string & scopedstr);


namespace wave
{

   class pre_buffer;
   class out;


} // namespace wave



namespace audio
{


   class decoder;
   class decoder_plugin;




} // namespace audio


namespace audio
{

   class track;

}


namespace audio
{

   class audio;


} // namespace audio



#ifdef APPLEOS
#include <AudioToolbox/AudioToolbox.h>
#endif

#ifndef WINDOWS
unsigned int time_get_time();
#define MMSYSERR_NOERROR 0
#define MMSYSERR_ERROR 1

#endif


#undef Au
#define Au(OBJECT) (*::get_context_audio(OBJECT)->cast < ::audio::audio >())


#define DECL_MM_DEC_LIB(X) \
extern "C" \
::multimedia::decoder * X ## _NewDecoderInterface(::particle * pparticle);


#include "_const.h"

#include "audio/audio/imedia/_.h"


#include "audio/audio/wave/_.h"


#include "sound_track_player.h"


#include "sound_track_player_container.h"


#include "ms_translator_speaker.h"


#include "inteprocess_channel.h"


#include "audio.h"


#include "library.h"



