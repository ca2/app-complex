#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO interprocess_handler:
      virtual public ::interprocess::handler
   {
   public:


      string_array                             m_straCallbackApp;


      interprocess_handler(const ::scoped_string & scopedstrApp);


      void on_interprocess_call(::payload & payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set & set) override;


      virtual void on_media_playback_start(::file::path pathOrigin, string strTitle,string_array straPerformer, string strAlbum, memory & image, string strUrl);
      virtual void on_media_playback_end(::file::path pathOrigin, string strTitle,string_array straPerformer, string strAlbum);


   };


} // namespace audio



