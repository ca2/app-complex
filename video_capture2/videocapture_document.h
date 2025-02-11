#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE document :
      public ::user::document
   {
   public:


      document();
	   virtual ~document();

      
	   // void assert_ok() const override;
	   // void dump(dump_context & dumpcontext) const override;

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile) override;

      virtual long long increment_reference_count();

      virtual long long decrement_reference_count();


   };


} // namespace app_complex_video_capture















