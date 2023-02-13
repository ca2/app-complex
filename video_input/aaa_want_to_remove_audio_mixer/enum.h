#pragma once


namespace multimedia
{


   namespace audio_mixer
   {


      class callback;
      class device;
      class source;
      class destination;
      class thread;
      class audio_mixer;
      class department;


      enum e_destination
      {
         destination_none,
         destination_speakers,
      };


      enum e_control
      {
         control_none,
         control_volume,
         control_boolean,
         control_mux,
      };


   } // namespace audio_mixer




} // namespace multimedia
