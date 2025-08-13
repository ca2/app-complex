#pragma once

//////////////////////////////////////////////////////////////////////////
//
// FILE: TextSpeaker.h
//
// Defines a simple C++ class to speak some text.
//
// by Giovanni Dicanio <gdicanio@mvps.org>
//
// 2010, December 28th
//
//////////////////////////////////////////////////////////////////////////


#undef Context


#include <sapi.h>        // SAPI (for windows::tts::speaker)


namespace windows
{


   namespace tts
   {


      //------------------------------------------------------------------------
      // Simple class to speak some text (using SAPI).
      //------------------------------------------------------------------------
      class speaker :
         virtual public ::tts::speaker
      {
      public:


         string                                       m_strDefaultLang;
         string_map_base < comptr < ISpVoice > >           m_voice;
         string_map_base < comptr < ISpObjectToken > >     m_token;
         string_map_base < unsigned int >                         m_time;
         string_map_base < bool >                          m_tts;
         //--------------------------------------------------------------------
         // Initializes the text speaker.
         //--------------------------------------------------------------------
         speaker();
         virtual ~speaker();

         virtual bool initialize(const ::scoped_string & scopedstrLang);
         virtual bool initialize_translator(const ::scoped_string & scopedstrLang);
         virtual bool destroy(const ::scoped_string & scopedstrLang);
         virtual bool finalize_translator(const ::scoped_string & scopedstrLang);

         virtual bool is_lang_ok(const ::scoped_string & scopedstrLang);

         //--------------------------------------------------------------------
         // Speaks some text.
         // (The input text must not be empty.)
         //--------------------------------------------------------------------
         virtual bool speak(const ::scoped_string & scopedstrText) override;

         virtual bool speak(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSync = false) override;

         virtual bool speak(const ::scoped_string & scopedstrAttributes, const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstrText, bool bSync = false) override;

         virtual bool is_speaking(const ::scoped_string & scopedstrLang) override;

         virtual bool stop(const ::scoped_string & scopedstrLang) override;


      };



   } // namespace tts

} // namespace windows




