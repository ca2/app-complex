#pragma once


namespace audio
{


   class CLASS_DECL_APP_CORE_AUDIO interprocess_handler:
      virtual public ::interprocess::handler
   {
   public:


      string_array                             m_straCallbackApp;


      interprocess_handler(const ::string & strApp);


      void on_interprocess_call(::payload & payload, const ::string & strObject, const ::string & strMember, property_set & set) override;


      virtual void on_media_playback_start(::file::path pathOrigin, string strTitle,string_array straPerformer, string strAlbum, memory & image, string strUrl);
      virtual void on_media_playback_end(::file::path pathOrigin, string strTitle,string_array straPerformer, string strAlbum);


   };


} // namespace audio



